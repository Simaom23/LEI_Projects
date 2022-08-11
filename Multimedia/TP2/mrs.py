from cv2 import sqrt
import librosa  # https://librosa.org/
import librosa.display
import librosa.beat
import sounddevice as sd  # https://anaconda.org/conda-forge/python-sounddevice
import warnings
import numpy as np
import scipy.stats as st
from scipy.spatial import distance as dt
import os
import time


# Files and directorys name - change if you need too
# Put all features inside the chosen features directory
featuresDir = "./Features/"
metadata = "./Dataset/panda_dataset_taffc_metadata.csv"
datasetDir = "./Dataset/All Songs/"
top100File = "top100_features.csv"
top100Normalized = "normalized/top100_features_normalized.csv"
allSongsNormalized = "normalized/allsongs_features_normalized.csv"
euclideanAllSongs = "distances/euclidian_all_songs.csv"
euclideanTop100 = "distances/euclidian_top100.csv"
manhattanAllSongs = "distances/manhattan_all_songs.csv"
manhattanTop100 = "distances/manhattan_top100.csv"
cosineAllSongs = "distances/cosine_all_songs.csv"
cosineTop100 = "distances/cosine_top100.csv"
metadataEvaluation = "distances/metadata_equality_evaluation.csv"
allSongs = os.listdir(datasetDir)
allSongs.sort()
queries = ["MT0000202045", "MT0000379144", "MT0000414517", "MT0000956340"]


def main():
    while True:
        print("\n### - Musicfy - ###")
        choice = input(
            "\n1 - Get recommendation\n2 - Create new dataset\nChoose: ")
        try:
            choice = int(choice)
            if choice != 1 and choice != 2:
                continue
        except:
            print("Choice not valid!\n")
            continue

        if choice == 1:
            query = str(input(
                "\nSong ID to get recommendations?\nSong ID: "))

            if query + ".mp3" not in allSongs:
                print("Song ID doesn't exist!")
                break

            matrix = None
            isMetadata = 0
            while True:
                print("\nWhat distance and features do you want to use?")
                distance = input(
                    "1 - Euclidian (All Songs Features)\n2 - Manhattan (All Songs Features)\n3 - Cosine (All Songs Features)\n4 - Euclidian (Top 100 Features)\n5 - Manhattan (Top 100 Features)\n6 - Cosine (Top 100 Features)\n7 - Based on Metadata\nChoose: ")

                try:
                    distance = int(distance)
                    if distance == 1:
                        matrix = readNormalizedFeatures(
                            featuresDir + euclideanAllSongs)
                        break

                    elif distance == 2:
                        matrix = readNormalizedFeatures(
                            featuresDir + manhattanAllSongs)
                        break

                    elif distance == 3:
                        matrix = readNormalizedFeatures(
                            featuresDir + cosineAllSongs)
                        break

                    elif distance == 4:
                        matrix = readNormalizedFeatures(
                            featuresDir + euclideanTop100)
                        break

                    elif distance == 5:
                        matrix = readNormalizedFeatures(
                            featuresDir + manhattanTop100)
                        break

                    elif distance == 6:
                        matrix = readNormalizedFeatures(
                            featuresDir + cosineTop100)
                        break

                    elif distance == 7:
                        matrix = readNormalizedFeatures(
                            featuresDir + metadataEvaluation)
                        isMetadata = 1
                        break

                    else:
                        print("Choice not valid!\n")
                        continue
                except:
                    print("Choice not valid!\n")
                    continue

            print("\nRecommendations for " + query + ".mp3" + ":")

            ranking = similarityRanking(matrix, query)
            if (isMetadata == 1):
                ranking = calculatePrecisionMetrics(query, matrix, ranking)

            for s in ranking:
                playSong(s)
                print(s)
                time.sleep(10)
            print()

            break

        elif choice == 2:
            featuresFile = featuresDir + top100Normalized
            if (os.path.isfile(featuresFile)):
                while True:
                    process = input(
                        "\nDo you want to process Top 100 features again?\n1 - Yes\n2 - No\nChoose: ")
                    try:
                        process = int(process)
                        if process == 1:
                            print("Extracting Top 100 features...")
                            top100 = readFeatures(featuresFile)
                            newTop100 = normalize(top100)
                            saveFeatures(
                                newTop100, featuresDir + top100Normalized)
                            break
                        if process == 2:
                            print("Top 100 features not processed!")
                            break
                    except:
                        print("Choice not valid!\n")
            else:
                print("Extracting Top 100 features...")
                top100 = readFeatures(featuresDir + top100File)
                r, c = top100.shape
                top100 = top100[1:, 1:(c - 1)]
                newTop100 = normalize(top100)
                saveFeatures(
                    newTop100, featuresDir + top100Normalized)

            normalizedSongs = featuresDir + top100Normalized
            if (os.path.isfile(normalizedSongs)):
                while True:
                    process = input(
                        "\nDo you want to process features for all songs again?\n1 - Yes\n2 - No\nChoose: ")
                    try:
                        process = int(process)
                        if process == 1:
                            print(
                                "Extracting all songs features... (This is going to take a while)")
                            songsFeatures = extractFeatures()
                            normalizedSongsFeatures = normalize(songsFeatures)
                            saveFeatures(normalizedSongsFeatures, featuresDir +
                                         allSongsNormalized)
                            break
                        if process == 2:
                            print("All songs features not processed!")
                            break
                    except:
                        print("Choice not valid!\n")
            else:
                print("Extracting all songs features... (This is going to take a while)")
                songsFeatures = extractFeatures()
                normalizedSongsFeatures = normalize(songsFeatures)
                saveFeatures(normalizedSongsFeatures, featuresDir +
                             allSongsNormalized)

            while True:
                process = input(
                    "\nDo you want to calculate similarity metrics?\n1 - Yes\n2 - No\nChoose: ")
                try:
                    process = int(process)
                    top100features = readNormalizedFeatures(
                        featuresDir + top100Normalized)
                    allSongsFeatures = readNormalizedFeatures(
                        featuresDir + allSongsNormalized)

                    allSongsFeatures = np.nan_to_num(allSongsFeatures)

                    if process == 1:
                        print(
                            "Calculating metrics...")
                        euclideanAllSongsM = calculateEuclideanDistance(
                            allSongsFeatures)
                        euclideanTop100M = calculateEuclideanDistance(
                            top100features)
                        manhattanAllSongsM = calculateManhattanDistance(
                            allSongsFeatures)
                        manhattanTop100M = calculateManhattanDistance(
                            top100features)
                        cosineAllSongsM = calculateCosineDistance(
                            allSongsFeatures)
                        cosineTop100M = calculateCosineDistance(
                            top100features)

                        saveFeatures(euclideanAllSongsM,
                                     featuresDir + euclideanAllSongs)
                        saveFeatures(euclideanTop100M,
                                     featuresDir + euclideanTop100)
                        saveFeatures(manhattanAllSongsM,
                                     featuresDir + manhattanAllSongs)
                        saveFeatures(manhattanTop100M,
                                     featuresDir + manhattanTop100)
                        saveFeatures(cosineAllSongsM,
                                     featuresDir + cosineAllSongs)
                        saveFeatures(cosineTop100M, featuresDir + cosineTop100)
                        break

                    if process == 2:
                        print("Similarity metrics not processed!")
                        break
                except:
                    print("Choice not valid!\n")


def readNormalizedFeatures(filename):
    features = np.genfromtxt(filename, delimiter=',')

    return features


# Read files
def readFeatures(filename):
    features = np.genfromtxt(filename, delimiter=',')
    r, c = features.shape
    features = features[1:, 1:(c - 1)]
    return features


# Normalize values
def normalize(matrix):
    normalizedMatrix = np.zeros(matrix.shape)
    r, c = normalizedMatrix.shape
    for i in range(c):
        vmax = matrix[:, i].max()
        vmin = matrix[:, i].min()
        normalizedMatrix[:, i] = (matrix[:, i] - vmin) / (vmax - vmin)
    normalizedMatrix = np.nan_to_num(normalizedMatrix)

    return normalizedMatrix


# Save files
def saveFeatures(newFeatures, filename):
    if os.path.isfile(filename):
        dirs = filename.split("/")
        filenameOnly = dirs[len(dirs) - 1]
        while True:
            substitutes = input(
                f"\n{filenameOnly} already exists! Do you want to replace it?\n1 - Yes\n2 - No\nChoose: ")
            try:
                substitutes = int(substitutes)
                if substitutes == 1:
                    os.remove(filename)
                    break
                if substitutes == 2:
                    print("File not saved!")
                    return
            except:
                print("Choice not valid!\n")

    np.savetxt(filename, newFeatures, fmt="%lf", delimiter=',')


def extractFeatures():
    if not os.path.isdir(datasetDir):
        print("Directory not found!")
        return

    warnings.filterwarnings("ignore")

    # List of songs to extract features
    numFiles = len(allSongs)
    songs = np.zeros((numFiles, 190))

    # Extract features of each song
    for i in range(numFiles):
        features = []

        # Song to extract
        inFile = librosa.load(
            datasetDir + allSongs[i], sr=22050, mono=True)[0]

        # Extract mfcc
        mfcc = librosa.feature.mfcc(inFile, n_mfcc=13)
        features.append(mfcc)

        # Extract pectral centroid
        spectral_centroid = librosa.feature.spectral_centroid(
            inFile)
        features.append(spectral_centroid)

        # Extract spectral bandwith
        spectral_bandwidth = librosa.feature.spectral_bandwidth(
            inFile)
        features.append(spectral_bandwidth)

        # Extract spectral contrast
        spectral_contrast = librosa.feature.spectral_contrast(
            inFile, n_bands=6)
        features.append(spectral_contrast)

        # Extract spectral flatness
        spectral_flatness = librosa.feature.spectral_flatness(
            inFile)
        features.append(spectral_flatness)

        # Extract spectral rollof
        spectral_rolloff = librosa.feature.spectral_rolloff(
            inFile)
        features.append(spectral_rolloff)

        # Extract F0
        F0 = librosa.yin(
            inFile, fmin=20, fmax=11025)
        F0 = F0[np.newaxis, :]
        F0[F0 == 11025] = 0
        features.append(F0)

        # Extract rms
        rms = librosa.feature.rms(inFile)
        features.append(rms)

        # Extract zero_crossing_rate
        zero_crossing_rate = librosa.feature.zero_crossing_rate(
            inFile)
        features.append(zero_crossing_rate)

        # Extract tempo
        tempo = librosa.beat.tempo(inFile)

        allFeatures = np.array([])
        for feature in features:
            try:
                r, c = feature.shape
            except:
                r = feature.shape[0]
                feature = feature.reshape((1, r), order='F')
                r, c = feature.shape

            addFeature = np.zeros((r, 7))
            for j in range(r):
                mean = np.mean(feature[j, :])
                stdDev = np.std(feature[j, :])
                skew = st.skew(feature[j, :])
                kurtosis = st.kurtosis(feature[j, :])
                median = np.median(feature[j, :])
                maxv = np.max(feature[j, :])
                minv = np.min(feature[j, :])

                addFeature[j, :] = np.array(
                    [mean, stdDev, skew, kurtosis, median, maxv, minv])

            addFeature = addFeature.flatten()
            allFeatures = np.append(allFeatures, addFeature)

        allFeatures = np.append(allFeatures, tempo)
        songs[i] = allFeatures

    return songs


# Euclidean distance
def calculateEuclideanDistance(matrix):
    r, c = matrix.shape
    distanceMatrix = np.zeros((r, r))
    for i in range(r):
        for j in range(i + 1, r):
            distance = dt.euclidean(matrix[i], matrix[j])
            distanceMatrix[i][j] = distance
            distanceMatrix[j][i] = distance

    return distanceMatrix


# Manhattan distance
def calculateManhattanDistance(matrix):
    r, c = matrix.shape
    distanceMatrix = np.zeros((r, r))
    for i in range(r):
        for j in range(i + 1, r):
            distance = dt.cityblock(matrix[i], matrix[j])
            distanceMatrix[i][j] = distance
            distanceMatrix[j][i] = distance

    return distanceMatrix


# Cosine distance
def calculateCosineDistance(matrix):
    r, c = matrix.shape
    distanceMatrix = np.zeros((r, r))
    for i in range(r):
        for j in range(i + 1, r):
            distance = dt.cosine(matrix[i], matrix[j])
            distanceMatrix[i][j] = distance
            distanceMatrix[j][i] = distance

    return distanceMatrix


# Simlarity rankings
def similarityRanking(dataset, querie):
    ID = allSongs.index(querie + ".mp3")
    files = np.asarray(allSongs)

    ranking = np.argsort(dataset[ID])
    sortedRanking = files[ranking]
    sortedRanking = sortedRanking[1:21]
    # print(sortedRanking)
    return sortedRanking


def objectiveEvaluation():
    metadataRawMatrix = np.genfromtxt(
        metadata, delimiter=',', dtype="str")

    metadataMatrix = metadataRawMatrix[1:, [1, 3, 9, 11]]
    r, c = metadataMatrix.shape
    metadataScores = np.zeros((r, r))

    for i in range(r):
        for j in range(i, r):
            if (i == j):
                metadataScores[i, j] = -1
                continue

            score = 0
            for x in range(c):
                # Check artist and quadrant
                if x < 2:
                    if metadataMatrix[i][x] == metadataMatrix[j][x]:
                        score = score + 1
                else:
                    # Check MoodStrSplit and GenresStr
                    listA = metadataMatrix[i, x][1:-1].split('; ')
                    listB = metadataMatrix[j, x][1:-1].split('; ')
                    for e in listA:
                        for ee in listB:
                            if e == ee:
                                score = score + 1

            metadataScores[i, j] = score
            metadataScores[j, i] = score

    metadataScores = metadataScores.astype(int)
    return metadataScores


def calculatePrecisionMetrics(querie, metadataScores, distanceRanking):
    ID = allSongs.index(querie + ".mp3")
    files = np.asarray(allSongs)

    ranking = np.argsort(-1 * metadataScores[ID])
    rank = (metadataScores[ID])[ranking]
    rank = rank[0:20]
    sortedRanking = files[ranking]
    sortedRanking = sortedRanking[0:20]
    count = 0
    for i in range(0, 20):
        if (distanceRanking[i] in sortedRanking):
            count += 1
    metric = count/20

    return sortedRanking


# Play Songs
def playSong(song):
    fName = datasetDir + song
    sr = 22050
    mono = True
    warnings.filterwarnings("ignore")
    y, fs = librosa.load(fName, sr=sr, mono=mono)
    sd.play(y, sr, blocking=False)
    return


if __name__ == "__main__":
    main()
