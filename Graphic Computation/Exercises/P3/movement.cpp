/* ===================================================================================
	Departamento Eng. Informatica - FCTUC
	Computacao Grafica - 2021/22
	................................................ JHenriques / APerrotta
	Trabalho 3 - Visualizacao
======================================================================================= */

#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/Glut.h>
#include <unistd.h>

// Definir cores
#define BLUE 0.0, 0.0, 1.0, 1.0
#define RED 1.0, 0.0, 0.0, 1.0
#define YELLOW 1.0, 1.0, 0.0, 1.0
#define GREEN 0.0, 1.0, 0.0, 1.0
#define WHITE 1.0, 1.0, 1.0, 1.0
#define BLACK 0.0, 0.0, 0.0, 1.0
#define PI 3.14159

// Variaveis e constantes
GLfloat tam = 0.5;
static GLfloat vertices[] = {
    // x=tam (Esquerda)
    -tam, -tam, tam,  // 0
    -tam, tam, tam,   // 1
    -tam, tam, -tam,  // 2
    -tam, -tam, -tam, // 3
                      // Direita
    tam, -tam, tam,   // 4
    tam, tam, tam,    // 5
    tam, tam, -tam,   // 6
    tam, -tam, -tam,  // 7
                      // Cima
    -tam, tam, tam,   // 8
    -tam, tam, -tam,  // 9
    tam, tam, -tam,   // 10
    tam, tam, tam,    // 11
};

static GLfloat normais[] = {
    // x=tam (Esquerda)
    -1.0,
    0.0,
    0.0,
    -1.0,
    0.0,
    0.0,
    -1.0,
    0.0,
    0.0,
    -1.0,
    0.0,
    0.0,
    // x=tam (Direita)
    1.0,
    0.0,
    0.0,
    1.0,
    0.0,
    0.0,
    1.0,
    0.0,
    0.0,
    1.0,
    0.0,
    0.0,
    // y=tam (Cima)
    0.0,
    1.0,
    0.0,
    0.0,
    1.0,
    0.0,
    0.0,
    1.0,
    0.0,
    0.0,
    1.0,
    0.0,
};
//------------------------------------------------------------ Cores
static GLfloat cor[] = {
    // Esquerda
    RED,
    GREEN,
    BLUE,
    YELLOW,

    // Direita
    RED,
    GREEN,
    BLUE,
    YELLOW,

    // Cima
    RED,
    GREEN,
    BLUE,
    YELLOW,
};

// FACES DA MESA
// Regra da mao direita
GLboolean frenteVisivel = 0;
static GLuint cima[] = {8, 11, 10, 9};
static GLuint esquerda[] = {3, 0, 1, 2};
static GLuint direita[] = {4, 7, 6, 5};

// Objectos (sistema coordenadas)
GLint wScreen = 800, hScreen = 600;      // Janela (pixeis)
GLfloat xC = 10.0, yC = 10.0, zC = 10.0; // Mundo  (unidades mundo)

// Visualizacao/Observador
GLfloat rVisao = 10, aVisao = 0.5 * PI, incVisao = 0.05;
GLfloat obsP[] = {rVisao * cos(aVisao), 1.0, rVisao *sin(aVisao)};
GLfloat dirP[] = {0, 0, 0};
GLfloat angZoom = 45;
GLfloat incZoom = 3;

// Variaveis globais
GLfloat xMove = 0.0;
GLfloat rotate = 0.0;
GLint alwaysRotate = 0;

// INIT
void inicializa(void)
{
    glClearColor(BLACK);     // Apagar
    glEnable(GL_DEPTH_TEST); // Profundidade
    glShadeModel(GL_SMOOTH); // Interpolacao de cores

    //VertexArrays: vertices + normais + cores
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glEnableClientState(GL_VERTEX_ARRAY);
    glColorPointer(4, GL_FLOAT, 0, cor);
    glEnableClientState(GL_COLOR_ARRAY);
    glNormalPointer(GL_FLOAT, 0, normais);
    glEnableClientState(GL_NORMAL_ARRAY);
}

void drawEixos()
{
    // Eixo X
    glColor4f(RED);
    glBegin(GL_LINES);
    glVertex3i(0, 0, 0);
    glVertex3i(10, 0, 0);
    glEnd();

    // Eixo Y
    glColor4f(GREEN);
    glBegin(GL_LINES);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 10, 0);
    glEnd();

    // Eixo Z
    glColor4f(BLUE);
    glBegin(GL_LINES);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 0, 10);
    glEnd();
}

void drawScene()
{

    if (frenteVisivel == 0)
        glDisable(GL_CULL_FACE);
    else
        glEnable(GL_CULL_FACE);

    if (frenteVisivel == 1)
        glCullFace(GL_FRONT);
    else if (frenteVisivel == 2)
        glCullFace(GL_BACK);

    // Sempre a rodar
    if (alwaysRotate)
    {
        rotate += 2;
        glutPostRedisplay();
    }

    // MESA
    glPushMatrix();
    glTranslatef(xMove, 0, 0);
    glRotatef(rotate, 0, 1, 0);

    glPushMatrix();
    glScalef(2, 1, 2);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);     // Face de cima
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda); // Face esquerda
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);  //  Face direita
    glPopMatrix();

    // Chaleira Amarela
    glColor4f(YELLOW);
    glPushMatrix();
    glTranslatef(0, tam + 0.4, 0);
    glutWireTeapot(0.5);
    glPopMatrix();

    glPopMatrix();
}

void display(void)
{

    // Apaga ecran e lida com profundidade (3D)
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // ! - Nao modificar - !
    glViewport(0, 0, wScreen, hScreen);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(angZoom, (float)wScreen / hScreen, 0.1, 3 * zC);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(obsP[0], obsP[1], obsP[2], dirP[0], dirP[1], dirP[2], 0, 1, 0);

    // Objectos
    drawEixos();
    drawScene();

    // Actualizacao
    glutSwapBuffers();
}

// EVENTOS
void keyboard(unsigned char key, int x, int y)
{

    switch (key)
    {
    // Lado da frente ou de tras visivel
    case 'f' | 'F':
        frenteVisivel += 1;
        if (frenteVisivel > 2)
            frenteVisivel = 0;
        break;

    // Rodar esquerda/direita
    case 'e' | 'E':
        rotate += 2;
        break;
    case 'd' | 'D':
        rotate -= 2;
        break;

    // Sempre a rodar
    case 'r' | 'R':
        if (!alwaysRotate)
            alwaysRotate = 1;
        else
            alwaysRotate = 0;
        break;

    // Movimeto eixo x
    case 'a' | 'A':
        xMove -= 0.1;
        break;
    case 's' | 'S':
        xMove += 0.1;
        break;

    // Escape
    case 27:
        exit(0);
        break;
    }

    glutPostRedisplay();
}

void teclasNotAscii(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
    {
        obsP[0] = (obsP[0] + 0.1) * cos(aVisao);
        obsP[2] = (obsP[2] + 0.1) * sin(aVisao);
    }
    if (key == GLUT_KEY_DOWN)
    {
        obsP[0] = (obsP[0] - 0.1) * cos(aVisao);
        obsP[2] = (obsP[2] - 0.1) * sin(aVisao);
    }
    if (key == GLUT_KEY_LEFT)
        aVisao = (aVisao + 0.1);
    if (key == GLUT_KEY_RIGHT)
        aVisao = (aVisao - 0.1);

    dirP[0] = (obsP[0] + rVisao) * cos(aVisao);
    dirP[2] = (obsP[2] + rVisao) * sin(aVisao);

    glutPostRedisplay();
}

// MAIN
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(wScreen, hScreen);
    glutInitWindowPosition(300, 100);
    glutCreateWindow("{jh,avperrotta@dei.uc.pt| |Mover/rodar Cima:'r'| |FaceVisivel:'f'| |Observador:'SETAS'| |Andar-'a/s'| |Rodar -'e/d'|");
    inicializa();
    glutSpecialFunc(teclasNotAscii);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
