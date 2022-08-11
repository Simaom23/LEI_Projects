import os.path
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.colors as clr
import scipy.fftpack as fft
import cv2
import math as m

# Global Variables
Ct = np.array([[0.299, 0.587, 0.114],
               [-0.168736, -0.331264, 0.5],
               [0.5, -0.418688, -0.081312]])

QY = np.array([[16, 11, 10, 16,  24,  40,  51,  61],
               [12, 12, 14, 19,  26,  58,  60,  55],
               [14, 13, 16, 24,  40,  57,  69,  56],
               [14, 17, 22, 29,  51,  87,  80,  62],
               [18, 22, 37, 56,  68, 109, 103,  77],
               [24, 35, 55, 64,  81, 104, 113,  92],
               [49, 64, 78, 87, 103, 121, 120, 101],
               [72, 92, 95, 98, 112, 100, 103,  99]])

QC = np.array([[17, 18, 24, 47, 99, 99, 99, 99],
               [18, 21, 26, 66, 99, 99, 99, 99],
               [24, 26, 56, 99, 99, 99, 99, 99],
               [47, 66, 99, 99, 99, 99, 99, 99],
               [99, 99, 99, 99, 99, 99, 99, 99],
               [99, 99, 99, 99, 99, 99, 99, 99],
               [99, 99, 99, 99, 99, 99, 99, 99],
               [99, 99, 99, 99, 99, 99, 99, 99]])


# JPEG Compression
def main():
    print("\n#### - JPEG Encoder/Decoder - ####")
    while True:
        file = input("Enter file name: ")
        if not os.path.isfile(file):
            print("File not found!")
        else:
            break

    greyCm = colormap([(0, 0, 0), (1, 1, 1)])
    global size
    img = readImg(file)
    size = img.shape

    while True:
        subsampling = input("\nSubsampling:\n1 - 4:2:0\n2 - 4:2:2\nChoose: ")
        try:
            subsampling = int(subsampling)
            if subsampling == 1 or subsampling == 2:
                break
        except:
            print("Choice not valid!\n")

    while True:
        cubic = input(
            "\nDo you want cubic interpolation?\n1 - Yes\n2 - No\nChoose: ")
        try:
            cubic = int(subsampling)
            if cubic == 1 or cubic == 2:
                break
        except:
            print("Choice not valid!\n")

    if (cubic == 1):
        interpolation = True
    elif (cubic == 2):
        interpolation = False

    while True:
        compressionRate = input(
            "\nPick a compression quality between 1 and 100\nCompression rate: ")
        try:
            compressionRate = int(compressionRate)
            if compressionRate >= 1 and compressionRate <= 100:
                break
        except:
            print("Choice not valid!\n")

    # Enconde Image to JPEG
    jpegEncoded = encoder(img, compressionRate, interpolation, subsampling)
    jpegDecoded = decoder(jpegEncoded, compressionRate,
                          interpolation, subsampling)

    # Visualize Original Image
    visualize(img)

    # Visualize Decoded Image
    visualize(jpegDecoded)

    # Get Distortion
    getDistortion(img, jpegDecoded)


def encoder(img, compressionRate, interpolation, subsampling):
    if (subsampling == 1):
        subX = 2
        subY = 2
    elif (subsampling == 2):
        subX = 2
        subY = 1
    paddedImg = padding(img, 16)
    ycbcrImg = rgb_to_ycbcr(paddedImg)
    Y_d, Cb_d, Cr_d = subSampling(ycbcrImg, subX, subY, interpolation)
    Y_dct, Cb_dct, Cr_dct = dct(Y_d, Cb_d, Cr_d, 8)
    Y_quant, Cb_quant, Cr_quant = quantization(
        Y_dct, Cb_dct, Cr_dct, compressionRate, 8)
    Y_quant, Cb_quant, Cr_quant = dpcm(Y_quant, Cb_quant, Cr_quant)

    return Y_quant, Cb_quant, Cr_quant


# Decode JPEG Image
def decoder(img, conversionRate, interpolation, subsampling):
    if (subsampling == 1):
        subX = 2
        subY = 2
    elif (subsampling == 2):
        subX = 2
        subY = 1
    Y_invDpcm, Cb_invDpcm, Cr_invDpcm = invDpcm(img[0], img[1], img[2])
    Y_invQuant, Cb_invQuant, Cr_invQuant = invQuantization(
        Y_invDpcm, Cb_invDpcm, Cr_invDpcm, conversionRate, 8)
    Y_invDct, Cb_invDct, Cr_invDct = invDct(
        Y_invQuant, Cb_invQuant, Cr_invQuant, 8)
    imgUp = upSampling(Y_invDct, Cb_invDct, Cr_invDct,
                       subX, subY, interpolation)
    rgbImg = ycbcr_to_rgb(imgUp)
    decodedImg = unpadding(rgbImg, size)

    return decodedImg


# Reads Image Data
def readImg(file):
    image = plt.imread(file)
    return image


# Visualize Image
def visualize(img, cm=None, log=False):
    if log:
        img = np.log(np.abs(img) + 0.0001)
    plt.figure()
    plt.imshow(img, cm)
    plt.axis('off')
    plt.show()


# Define Colormap
def colormap(value):
    nl = 5
    nc = 50
    linGray = np.linspace(0., 1., nc).reshape(1, nc)
    linGray = np.repeat(linGray, nl, axis=1).reshape(nc, nl).T
    linGrayImg = np.zeros((nl, nc, 3))
    linGrayImg[:, :, 0] = linGray
    linGrayImg[:, :, 1] = linGray
    linGrayImg[:, :, 2] = linGray
    cm = clr.LinearSegmentedColormap.from_list('cmap', value, N=256)
    return cm


# Separates RGB Channels
def channelSep(imgData):
    red = imgData[:, :, 0]
    green = imgData[:, :, 1]
    blue = imgData[:, :, 2]

    return red, green, blue


# Unifie RGB Channels
def channelUni(red, green, blue):
    auxImage = np.array(red)
    auxImage[:, :, 1] = green[:, :, 1]
    auxImage[:, :, 2] = blue[:, :, 2]

    return auxImage


# Visualize RGB Channels
def visualizeRGB(red, green, blue):
    redCm = colormap([(0, 0, 0), (1, 0, 0)])
    greenCm = colormap([(0, 0, 0), (0, 1, 0)])
    blueCm = colormap([(0, 0, 0), (0, 0, 1)])

    visualize(red, redCm)
    visualize(green, greenCm)
    visualize(blue, blueCm)


# Pad Image
def padding(img, n):
    imgShape = img.shape
    red = img[:, :, 0]
    green = img[:, :, 1]
    blue = img[:, :, 2]

    # Número de linhas a adicionar
    if imgShape[0] % n != 0:
        r = n - (imgShape[0] % n)
        red = np.vstack([red, np.tile(red[-1, :], (r, 1))])
        green = np.vstack([green, np.tile(green[-1, :], (r, 1))])
        blue = np.vstack([blue, np.tile(blue[-1, :], (r, 1))])

    # Número de colunas a adicionar
    if imgShape[1] % n != 0:
        c = n - (imgShape[1] % n)
        red = np.column_stack([red, np.tile(red[:, -1], (c, 1)).T])
        green = np.column_stack([green, np.tile(green[:, -1], (c, 1)).T])
        blue = np.column_stack([blue, np.tile(blue[:, -1], (c, 1)).T])

    paddedImg = np.zeros((red.shape[0], red.shape[1], 3), np.uint8)
    paddedImg[:, :, 0] = red
    paddedImg[:, :, 1] = green
    paddedImg[:, :, 2] = blue

    return paddedImg


# Unpad Image
def unpadding(paddedImg, shapeImg):
    unpaddedImg = paddedImg[:shapeImg[0], :shapeImg[1], :]

    return unpaddedImg


# Convert RGB to YCbCr
def rgb_to_ycbcr(img):
    convertedImg = img.dot(Ct.T)
    convertedImg[:, :, [1, 2]] += 128

    return convertedImg


# Convert YCbCr to RGB
def ycbcr_to_rgb(img):
    invertedCt = np.linalg.inv(Ct.T)
    img[:, :, [1, 2]] -= 128
    convertedImg = img.dot(invertedCt)
    convertedImg = convertedImg.round()
    convertedImg[convertedImg > 255] = 255
    convertedImg[convertedImg < 0] = 0
    convertedImg = convertedImg.astype(np.uint8)

    return convertedImg


# Visualize YCbCr Channels
def visualizeYCbCr(ycbcrImg):
    greyCm = colormap([(0, 0, 0), (1, 1, 1)])

    visualize(ycbcrImg[:, :, 0], greyCm)
    visualize(ycbcrImg[:, :, 1], greyCm)
    visualize(ycbcrImg[:, :, 2], greyCm)


# SubSampling Image
def subSampling(img, factorX, factorY, interpolation):
    Y_d = img[:, :, 0]
    if(interpolation):
        Cb_d = cv2.resize(img[:, :, 1], None, fx=1/factorX,
                          fy=1/factorY, interpolation=cv2.INTER_CUBIC)
        Cr_d = cv2.resize(img[:, :, 2], None, fx=1/factorX,
                          fy=1/factorY, interpolation=cv2.INTER_CUBIC)
    else:
        Cb_d = img[:, :, 1][::factorX, ::factorY]
        Cr_d = img[:, :, 2][::factorX, ::factorY]

    return Y_d, Cb_d, Cr_d


# UpSampling Image
def upSampling(Y_d, Cb_d, Cr_d, factorX, factorY, interpolation):
    Y_u = Y_d
    if(interpolation):
        Cb_u = cv2.resize(Cb_d, None, fx=factorX, fy=factorY,
                          interpolation=cv2.INTER_CUBIC)
        Cr_u = cv2.resize(Cr_d, None, fx=factorX, fy=factorY,
                          interpolation=cv2.INTER_CUBIC)
    else:
        Cb_u = np.repeat(Cb_d, factorX, axis=0)
        Cr_u = np.repeat(Cr_d, factorX, axis=0)
        Cb_u = np.repeat(Cb_u, factorY, axis=1)
        Cr_u = np.repeat(Cr_u, factorY, axis=1)

    imgUp = np.dstack([Y_u, Cb_u, Cr_u])

    return imgUp


# DCT Image
def dct(Y_dct, Cb_dct, Cr_dct, n):
    sizeY = Y_dct.shape
    sizeC = Cb_dct.shape
    for i in range(0, sizeY[0], n):
        for j in range(0, sizeY[1], n):
            Y_dct[i:i + n, j:j +
                  n] = fft.dct(fft.dct(Y_dct[i:i + n, j:j + n], norm="ortho").T, norm="ortho").T
            if i < sizeC[0] and j < sizeC[1]:
                Cb_dct[i:i + n, j:j + n] = fft.dct(
                    fft.dct(Cb_dct[i:i + n, j:j + n], norm="ortho").T, norm="ortho").T
                Cr_dct[i:i + n, j:j + n] = fft.dct(
                    fft.dct(Cr_dct[i:i + n, j:j + n], norm="ortho").T, norm="ortho").T

    return Y_dct, Cb_dct, Cr_dct


# Inverse DCT Image
def invDct(Y_invDct, Cb_invDct, Cr_invDct, n):
    sizeY = Y_invDct.shape
    sizeC = Cb_invDct.shape
    for i in range(0, sizeY[0], n):
        for j in range(0, sizeY[1], n):
            Y_invDct[i:i + n, j:j +
                     n] = fft.idct(fft.idct(Y_invDct[i:i + n, j:j + n], norm="ortho").T, norm="ortho").T
            if i < sizeC[0] and j < sizeC[1]:
                Cb_invDct[i:i + n, j:j + n] = fft.idct(
                    fft.idct(Cb_invDct[i:i + n, j:j + n], norm="ortho").T, norm="ortho").T
                Cr_invDct[i:i + n, j:j + n] = fft.idct(
                    fft.idct(Cr_invDct[i:i + n, j:j + n], norm="ortho").T, norm="ortho").T

    Y_invDct[Y_invDct < 0] = 0
    Y_invDct[Y_invDct > 255] = 255

    Cb_invDct[Cb_invDct < 0] = 0
    Cb_invDct[Cb_invDct > 255] = 255

    Cr_invDct[Cr_invDct < 0] = 0
    Cr_invDct[Cr_invDct > 255] = 255

    # Verificar se a DCT Inversa está correta
    # diffY = Y_d - Y_invDct
    # diffY[diffY < 0.000001] = 0.

    # diffCb = Cb_d - Cb_invDct
    # diffCb[diffCb < 0.000001] = 0.

    # diffCr = Cr_d - Cr_invDct
    # diffCr[diffCr < 0.000001] = 0.

    return Y_invDct,  Cb_invDct, Cr_invDct


# Quantitize Image
def quantization(Y_dct, Cb_dct, Cr_dct, qf, n):
    if (qf == 100):
        qy = np.ones((8, 8))
        qc = np.ones((8, 8))
    elif (qf == 50):
        qy = QY
        qc = QC
    else:
        qy = np.round(QY * ((100 - qf) / 50))
        qy[qy > 255] = 255
        qc = np.round(QC * ((100 - qf) / 50))
        qc[qc > 255] = 255

    sizeY = Y_dct.shape
    sizeC = Cb_dct.shape
    for i in range(0, sizeY[0], n):
        for j in range(0, sizeY[1], n):
            Y_dct[i:i + n, j:j + n] = np.round(Y_dct[i:i + n, j: j + n] / qy)
            if i < sizeC[0] and j < sizeC[1]:
                Cb_dct[i:i + n, j:j +
                       n] = np.round(Cb_dct[i:i + n, j:j + n] / qc)
                Cr_dct[i:i + n, j:j +
                       n] = np.round(Cr_dct[i:i + n, j: j + n] / qc)

    return Y_dct, Cb_dct, Cr_dct


# Inverse Quantitize Image
def invQuantization(Y_dct, Cb_dct, Cr_dct, qf, n):
    if (qf == 100):
        qy = np.ones((8, 8))
        qc = np.ones((8, 8))
    elif (qf == 50):
        qy = QY
        qc = QC
    else:
        qy = np.round(QY * ((100 - qf) / 50))
        qy[qy > 255] = 255
        qc = np.round(QC * ((100 - qf) / 50))
        qc[qc > 255] = 255

    sizeY = Y_dct.shape
    sizeC = Cb_dct.shape
    for i in range(0, sizeY[0], n):
        for j in range(0, sizeY[1], n):
            Y_dct[i:i + n, j:j + n] = np.round(Y_dct[i:i + n, j: j + n] * qy)
            if i < sizeC[0] and j < sizeC[1]:
                Cb_dct[i:i + n, j:j +
                       n] = np.round(Cb_dct[i:i + n, j:j + n] * qc)
                Cr_dct[i:i + n, j:j +
                       n] = np.round(Cr_dct[i:i + n, j:j + n] * qc)

    return Y_dct, Cb_dct, Cr_dct


# DPCM Image
def dpcm(Y_dct, Cb_dct, Cr_dct):
    sizeY = Y_dct.shape
    sizeC = Cb_dct.shape

    for i in range(0, sizeY[0], 8):
        for j in range(0, sizeY[1], 8):
            if (i == 0 and j == 0):
                dcY0 = Y_dct[0, 0]
                dcCb0 = Cb_dct[0, 0]
                dcCr0 = Cr_dct[0, 0]
                continue
            dcY = Y_dct[i, j]
            diffY = dcY - dcY0
            Y_dct[i, j] = diffY
            dcY0 = dcY
            if i < sizeC[0] and j < sizeC[1]:
                dcCb = Cb_dct[i, j]
                dcCr = Cr_dct[i, j]

                diffCb = dcCb - dcCb0
                diffCr = dcCr - dcCr0

                Cb_dct[i, j] = diffCb
                Cr_dct[i, j] = diffCr

                dcCb0 = dcCb
                dcCr0 = dcCr

    return Y_dct, Cb_dct, Cr_dct


# Inverse DPCM Image
def invDpcm(Y_dct, Cb_dct, Cr_dct):
    sizeY = Y_dct.shape
    sizeC = Cb_dct.shape
    for i in range(0, sizeY[0], 8):
        for j in range(0, sizeY[1], 8):
            if (i == 0 and j == 0):
                dcY0 = Y_dct[0, 0]
                dcCb0 = Cb_dct[0, 0]
                dcCr0 = Cr_dct[0, 0]
                continue
            dcY = Y_dct[i, j]
            sumY = dcY0 + dcY
            Y_dct[i, j] = sumY
            dcY0 = sumY
            if i < sizeC[0] and j < sizeC[1]:
                dcCb = Cb_dct[i, j]
                dcCr = Cr_dct[i, j]

                sumCb = dcCb0 + dcCb
                sumCr = dcCr0 + dcCr

                Cb_dct[i, j] = sumCb
                Cr_dct[i, j] = sumCr

                dcCb0 = sumCb
                dcCr0 = sumCr

    return [Y_dct, Cb_dct, Cr_dct]


# Calculate Distortions
def getDistortion(imgOr, imgDec):
    imgOr = imgOr.astype(float)
    imgDec = imgDec.astype(float)
    p = np.sum(imgOr**2)/(size[0]*size[1])
    spike = np.max(imgOr)
    mse = np.sum((imgOr - imgDec)**2)/(size[0]*size[1])
    rmse = m.sqrt(mse)
    snr = 10 * m.log(p/mse, 10)
    psnr = 10 * m.log((spike**2)/mse, 10)

    print(
        f"\nDistortion Calculations:\nMSE -> {mse}\nRMSE -> {rmse}\nSNR -> {snr}\nPSNR -> {psnr}")


if __name__ == "__main__":
    main()
