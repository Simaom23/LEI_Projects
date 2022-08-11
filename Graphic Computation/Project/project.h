/* Simão Monteiro Nº 2019215412 */

#ifndef PROJECT_H
#define PROJECT_H

// Libraries
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/Glut.h>
#include <unistd.h>
#include "RgbImage.h"

// Colours Macros
#define CORD_COLOUR 0.180, 0.251, 0.392, 1.0
#define BLUE 0.0, 0.0, 1.0, 1.0
#define RED 1.0, 0.0, 0.0, 1.0
#define GREEN 0.0, 1.0, 0.0, 1.0
#define PI 3.14159

// Prototypes
void init(void);
void display(void);
void texturesInit(void);
void lightingInit(void);
void lighting();
void renderAxis();
void renderScene();
void renderRoom();
void renderRemote();
void renderLamp();
void renderSkybox();
void keyboard(unsigned char key, int x, int y);
void otherKeyboard(int key, int x, int y);
void timer(int value);
void initMaterials(int material);

// Vertex Array
GLfloat size = 0.5;
static GLfloat vertex[] = {
    // Remote Left
    -size, -size, size,  // 0
    -size, size, size,   // 1
    -size, size, -size,  // 2
    -size, -size, -size, // 3
    // Remote Right
    size, -size, size,  // 4
    size, size, size,   // 5
    size, size, -size,  // 6
    size, -size, -size, // 7
    // Remote Top
    -size, size, size,  // 8
    -size, size, -size, // 9
    size, size, -size,  // 10
    size, size, size,   // 11
    // Remote Bottom
    -size, -size, size,  // 12
    -size, -size, -size, // 13
    size, -size, -size,  // 14
    size, -size, size,   // 15
    // Remote Front
    -size, size, size,  // 16
    -size, -size, size, // 17
    size, -size, size,  // 18
    size, size, size,   // 19
    // Remote Back
    -size, size, -size,  // 20
    -size, -size, -size, // 21
    size, size, -size,   // 22
    size, -size, -size,  // 23
};

// Normal Array
static GLfloat normals[] = {
    // Remote Left
    -1.0, 0.0, 0.0, //
    -1.0, 0.0, 0.0, //
    -1.0, 0.0, 0.0, //
    -1.0, 0.0, 0.0, //
    // Remote Right
    1.0, 0.0, 0.0, //
    1.0, 0.0, 0.0, //
    1.0, 0.0, 0.0, //
    1.0, 0.0, 0.0, //
    // Remote Top
    0.0, 1.0, 0.0, //
    0.0, 1.0, 0.0, //
    0.0, 1.0, 0.0, //
    0.0, 1.0, 0.0, //
    // Remote Bottom
    0.0, -1.0, 0.0, //
    0.0, -1.0, 0.0, //
    0.0, -1.0, 0.0, //
    0.0, -1.0, 0.0, //
    // Remote Front
    0.0, 0.0, 1.0, //
    0.0, 0.0, 1.0, //
    0.0, 0.0, 1.0, //
    0.0, 0.0, 1.0, //
    // Remote Back
    0.0, 0.0, -1.0, //
    0.0, 0.0, -1.0, //
    0.0, 0.0, -1.0, //
    0.0, 0.0, -1.0, //
};

// Textures Array
static GLfloat textures[] = {
    1, 0,
    1, 1,
    0, 1,
    0, 0,
    0, 0,
    0, 1,
    1, 1,
    1, 0,
    0, 0,
    0, 1,
    1, 1,
    1, 0,
    0, 0,
    0, 1,
    1, 1,
    1, 0,
    0, 1,
    0, 0,
    1, 0,
    1, 1,
    1, 1,
    1, 0,
    0, 1,
    0, 0};

// Color Arrays
// Button OFF Color
static GLfloat off_colour[] = {
    // Left
    RED,
    RED,
    RED,
    RED,
    // Right
    RED,
    RED,
    RED,
    RED,
    // Top
    RED,
    RED,
    RED,
    RED,
    // Bottom
    RED,
    RED,
    RED,
    RED,
    // Front
    RED,
    RED,
    RED,
    RED,
    // Back
    RED,
    RED,
    RED,
    RED,
};

// Button ON Color
static GLfloat on_colour[] = {
    // Left
    GREEN,
    GREEN,
    GREEN,
    GREEN,
    // Right
    GREEN,
    GREEN,
    GREEN,
    GREEN,
    // Top
    GREEN,
    GREEN,
    GREEN,
    GREEN,
    // Bottom
    GREEN,
    GREEN,
    GREEN,
    GREEN,
    // Front
    GREEN,
    GREEN,
    GREEN,
    GREEN,
    // Back
    GREEN,
    GREEN,
    GREEN,
    GREEN,
};

// Square Sides
static GLuint top[] = {11, 10, 9, 8};
static GLuint left[] = {3, 0, 1, 2};
static GLuint right[] = {7, 6, 5, 4};
static GLuint bottom[] = {13, 14, 15, 12};
static GLuint front[] = {17, 18, 19, 16};
static GLuint back[] = {23, 21, 20, 22};

// Coordenates System
GLint wScreen = 1280, hScreen = 720;
GLfloat xC = 10.0, yC = 10.0, zC = 10.0;

// Observer/Visualization
GLfloat visionRadius = 10, visionAngle = 0.5 * PI;
GLfloat obsP[] = {visionRadius * cos(visionAngle), 5.0, visionRadius *sin(visionAngle)};
GLfloat fov = 60;

// Textures
RgbImage image;
GLuint texture[5];
GLUquadricObj *skybox = gluNewQuadric();

// Spotlight
bool spotlight = true;
GLfloat spotlightAperture = 25.0;
GLfloat spotlighPos[] = {3.0, 1.5, 0.0, 1.0};
GLfloat spotlightDirection[] = {0.0, -1.0, 0.0, 0.0};
GLfloat spotlightColor[] = {9.7, 9.3, 8.7, 1.0};
GLfloat spotlightCA = 1.0;
GLfloat spotlightLA = 0.5;
GLfloat spotlightQA = 0.2;
GLfloat spotlightExp = 2.0;

// Ambient light
GLint dayIntensity = 1;
GLfloat globalAmbColor[4] = {(GLfloat)0.0, (GLfloat)0.0, (GLfloat)0.0, 0.0};

GLfloat redLight = 3.0;
GLfloat greenLight = 0.0;
GLfloat blueLight = 0.0;

// Local Light
GLfloat localAmbColor[4] = {0.0, 0.0, 0.0, 0.0};
GLfloat localDifColor[4] = {redLight, greenLight, blueLight, 1.0};
GLfloat localSpeColor[4] = {redLight, greenLight, blueLight, 1.0};
GLfloat localPos[4] = {0.0, -size, 0.3, 1.0};

// Global variables
GLint lampIntensity = 0;
GLint lampState = 0;
GLfloat buttonOffset = 0.2;
GLfloat xMove = 0.0;
GLfloat rotate = 0.0;
GLint isDay = 0;
int dim = 64;
float med_dim = 32;
extern GLfloat obsidian_shine;

// Display Update Time
GLint msec = 100;

#endif
