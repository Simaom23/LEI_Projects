
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/Glut.h>

//==================================================================== Definir cores
#define AZUL 0.0, 0.0, 1.0, 1.0
#define VERMELHO 1.0, 0.0, 0.0, 1.0
#define AMARELO 1.0, 1.0, 0.0, 1.0
#define VERDE 0.0, 1.0, 0.0, 1.0
#define LARANJA 0.8, 0.6, 0.1, 1.0
#define WHITE 1.0, 1.0, 1.0, 1.0
#define BLACK 0.0, 0.0, 0.0, 1.0
#define GRAY1 0.2, 0.2, 0.2, 1.0
#define GRAY2 0.9, 0.9, 0.9, 1.0
#define PRETO 0.0, 0.0, 0.0, 1.0

#include "RgbImage.h"
#define PI 3.14159

//================================================================================
//===========================================================Variaveis e constantes
GLint msec = 100; //.. definicao do timer (actualizacao)

//------------------------------------------------------------ Sistema Coordenadas: mundo e janela (pixeis)
GLfloat xC = 10.0, yC = 10.0, zC = 10.0;
GLint wScreen = 800, hScreen = 600;

//------------------------------------------------------------ Observador
GLfloat rVisao = 3.0, aVisao = PI, incPos = 0.5;
GLfloat angPersp = 109.0;
GLfloat obsPini[] = {2, 1.0, 2};
GLfloat obsPfin[] = {obsPini[0] - rVisao * cos(aVisao), obsPini[1], obsPini[2] - rVisao *sin(aVisao)};

//=================================================================== ESCADA - VERTEX ARRAY
int facesESC = 3; // 3 faces
static GLuint poligono[] = {0, 0, 0, 0};
static GLfloat vertices[] = {
	-0.50, 0.00, -0.96,
	0.50, 0.00, -0.96,
	0.50, 0.00, -0.00,
	-0.50, 0.00, -0.00,
	-0.50, 0.00, -0.96,
	0.50, 0.00, -0.96,
	0.50, 0.16, -0.96,
	-0.50, 0.16, -0.96,
	-0.50, 0.16, -1.28,
	0.50, 0.16, -1.28,
	0.50, 0.16, -0.96,
	-0.50, 0.16, -0.96};
static GLfloat normais[] = {
	0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,
	0.0, 1.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,
	0.0, 0.0, 1.0,
	0.0, 0.0, 1.0};
static GLfloat cores[] = {
	0.0, 1.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 1.0, 0.0,
	0.0, 1.0, 0.0,
	1.0, 0.0, 0.0,
	1.0, 0.0, 0.0,
	1.0, 0.0, 0.0,
	1.0, 0.0, 0.0,
	1.0, 0.0, 1.0,
	1.0, 0.0, 1.0,
	1.0, 0.0, 1.0,
	1.0, 0.0, 1.0};
static GLfloat texturas[] = {
	0, 0,
	1, 0,
	1, 1,
	0, 1,
	0, 0,
	1, 0,
	1, 1,
	0, 1,
	0, 0,
	1, 0,
	1, 1,
	0, 1};

//=================================================================== TEXTURAS
RgbImage imag;

//------------------------------------------------------------ Skybox
GLUquadricObj *esfera = gluNewQuadric();
//------------------------------------------------------------ Texturas (5 texturas)
GLuint texture[5];

//================================================================================
//=========================================================================== INIT
//================================================================================
void initTexturas()
{
	//----------------------------------------- Chao - tapete
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	imag.LoadBmpFile("tapete.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
				 imag.GetNumCols(),
				 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
				 imag.ImageData());

	//----------------------------------------- Esfera - skybox envolvente
	glGenTextures(1, &texture[1]);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	imag.LoadBmpFile("sky.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
				 imag.GetNumCols(),
				 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
				 imag.ImageData());

	//-----------------------------------------  Eescada - cima
	glGenTextures(1, &texture[2]);
	glBindTexture(GL_TEXTURE_2D, texture[2]);
	imag.LoadBmpFile("madeira.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
				 imag.GetNumCols(),
				 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
				 imag.ImageData());

	//-----------------------------------------  Escada - lado
	glGenTextures(1, &texture[3]);
	glBindTexture(GL_TEXTURE_2D, texture[3]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile("colorida.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
				 imag.GetNumCols(),
				 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
				 imag.ImageData());

	//----------------------------------------- Chaleria
	glGenTextures(1, &texture[4]);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	imag.LoadBmpFile("tea.bmp");
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
				 imag.GetNumCols(),
				 imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
				 imag.ImageData());
}

//---------------------------------------- Inicializacoes
void init(void)
{
	glClearColor(WHITE);
	glShadeModel(GL_SMOOTH);

	initTexturas();
	glEnable(GL_DEPTH_TEST);

	//------------------------------- Defini��o da ESCADA
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais);
	glEnableClientState(GL_NORMAL_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, cores);
	glEnableClientState(GL_COLOR_ARRAY);
	glTexCoordPointer(2, GL_FLOAT, 0, texturas); // coordenadas textura
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

GLvoid resize(GLsizei width, GLsizei height)
{
	wScreen = width;
	hScreen = height;
	glViewport(0, 0, wScreen, hScreen);
	glutPostRedisplay();
}

void drawOrientacao()
{
	//----------------------- OBSERVADOR: onde esta; para onde olha
	glPushMatrix();
	glColor4f(VERDE);
	glTranslatef(obsPini[0], obsPini[1], obsPini[2]);
	glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
	glColor4f(VERMELHO);
	glTranslatef(obsPfin[0], obsPfin[1], obsPfin[2]);
	glutSolidCube(1.0);
	glPopMatrix();

	//----------------------- EIXOS
	glColor4f(VERMELHO);
	glBegin(GL_LINES);
	glVertex3i(0, 0, -xC);
	glVertex3i(0, 0, xC);
	glEnd();
	glColor4f(VERDE);
	glBegin(GL_LINES);
	glVertex3i(0, -xC, 0);
	glVertex3i(0, xC, 0);
	glEnd();
	glColor4f(AZUL);
	glBegin(GL_LINES);
	glVertex3i(-xC, 0, 0);
	glVertex3i(xC, 0, 0);
	glEnd();
}

//================================================================================
//================== OBJECTOS
//================================================================================

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Chao : poligono regular
void drawChao()
{
	float L = 0.8;
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	glPushMatrix();
	glTranslatef(0, -3, 0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3i(-L * xC, 0, L * xC); //A
	glTexCoord2f(1.0f, 0.0f);
	glVertex3i(L * xC, 0, L * xC); //B
	glTexCoord2f(1.0f, 1.0f);
	glVertex3i(L * xC, 0, -L * xC); //C
	glTexCoord2f(0.0f, 1.0f);
	glVertex3i(-L * xC, 0, -L * xC); //D
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Esfera : Quadrica
void drawEsfera()
{
	//------------------------- Esfera
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glPushMatrix();
	//glTranslatef(2, 4, 2);
	glRotatef(-90, 1, 0, 0);
	gluQuadricDrawStyle(esfera, GLU_FILL);
	gluQuadricNormals(esfera, GLU_SMOOTH);
	gluQuadricTexture(esfera, GL_TRUE);
	gluSphere(esfera, 60.0, 100, 100);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Vertex Array
void drawEscada()
{
	glEnable(GL_TEXTURE_2D);
	//------------------------- Posicionamento da ESCADA
	glPushMatrix();
	glTranslatef(5, -2.0, 0.0);
	glScalef(6, 8, 7);

	for (int p = 0; p < facesESC; p++)
	{ //..................... texturas diferentes cima/lado escada
		if (p % 2 == 0)
			glBindTexture(GL_TEXTURE_2D, texture[2]);
		else
			glBindTexture(GL_TEXTURE_2D, texture[3]);

		poligono[0] = p * 4 + 0;
		poligono[1] = p * 4 + 1;
		poligono[2] = p * 4 + 2;
		poligono[3] = p * 4 + 3;
		glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, poligono);
	}
	glPopMatrix();
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ GLUT ??? chaleira
void drawChaleira()
{
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, texture[4]);
	//------------------------- Posicionamento da Chaleira
	glPushMatrix();
	glTranslatef(-2, -2.0, 5.0);
	glScalef(2, 2.5, 2);
	glutSolidTeapot(1.0);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}

//___________________________________________________   jh
void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//================================================================= Viewport2
	glViewport(0.3 * wScreen, 0, 0.7 * wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90, (float)wScreen / hScreen, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsPini[0], obsPini[1], obsPini[2], obsPfin[0], obsPfin[1], obsPfin[2], 0, 1, 0);
	//--------------------- desenha objectos
	drawChao();
	drawEsfera();
	drawEscada();
	drawChaleira();

	//================================================================= Viewport1
	glViewport(0, 0, 0.3 * wScreen, 0.3 * hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-xC, xC, -yC, yC, -zC, zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 5, 0, 0, 0, 0, 0, 0, -1);
	//--------------------- desenha objectos
	drawOrientacao();
	drawChao();
	drawEsfera();
	drawEscada();
	drawChaleira();

	glutSwapBuffers();
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	//--------------------------- Escape
	case 27:
		exit(0);
		break;
	}
}

void teclasNotAscii(int key, int x, int y)
{
	if (key == GLUT_KEY_UP)
	{
		obsPini[0] = obsPini[0] + incPos * cos(aVisao);
		obsPini[2] = obsPini[2] - incPos * sin(aVisao);
	}
	if (key == GLUT_KEY_DOWN)
	{
		obsPini[0] = obsPini[0] - incPos * cos(aVisao);
		obsPini[2] = obsPini[2] + incPos * sin(aVisao);
	}
	if (key == GLUT_KEY_LEFT)
		aVisao = (aVisao + 0.1);
	if (key == GLUT_KEY_RIGHT)
		aVisao = (aVisao - 0.1);

	obsPfin[0] = obsPini[0] + rVisao * cos(aVisao);
	obsPfin[2] = obsPini[2] - rVisao * sin(aVisao);
	glutPostRedisplay();
}

void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(msec, Timer, 1);
}

//======================================================= MAIN
int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(400, 100);
	glutCreateWindow("{jh,avperrotta}@dei.uc.pt  ");

	init();
	glutSpecialFunc(teclasNotAscii);
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(msec, Timer, 1);

	glutMainLoop();

	return 0;
}
