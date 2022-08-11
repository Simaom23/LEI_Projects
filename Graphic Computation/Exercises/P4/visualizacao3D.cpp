/* ===================================================================================
	Departamento Eng. Informatica - FCTUC
	Computacao Grafica - 2021/22
	................................................ JHenriques / APerrotta
	Trabalho 4 - Projeccoes
======================================================================================= */
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
#define PI 3.14159

//--------------------------------- Definir cores
#define BLUE 0.0, 0.0, 1.0, 1.0
#define YELLOW 1.0, 1.0, 0.0, 1.0
#define GREEN 0.0, 1.0, 0.0, 1.0
#define ORANGE 1.0, 0.5, 0.1, 1.0
#define CYAN 0.0, 1.0, 1.0, 1.0
#define WHITE 1.0, 1.0, 1.0, 1.0
#define BLACK 0.0, 0.0, 0.0, 1.0
#define GRAY 0.3, 0.3, 0.3, 1.0

//================================================================================
//------------------------------------------------------------ Sistema Coordenadas
GLint wScreen = 600, hScreen = 500; //.. janela
GLfloat size = 10.0;				//.. Mundo  size=coordenadas x=y=z

//========================================================= Objeto Mesa
float centrox = 0;
float rotacao = 0;
GLint sempreRodar = 0;
GLfloat altura = 0;
GLfloat incALT = 0.03;

//============================================================= Observador
GLfloat rVisao = 8, aVisao = -0.5 * PI, incVisao = 1;
GLfloat obsP[] = {5, 2.0, 5};
GLfloat obsT[] = {0, 2.0, 0};
GLfloat anguloZ = 35;

//============================================================= Projecao
int tipoProjeccao = 0;

//===========================================================Variaveis e constantes
GLint msec = 10;
char texto[30]; //.. texto a ser escrito no ecra

//================================================================================
//================================================ VERTEX ARAY
//------------------------------------------- coordenadas + normais + cores
GLfloat tam = 0.5;
static GLfloat vertices[] = {
	//�������������������������������������� x=tam (Esquerda)
	-tam, -tam, tam,  // 0
	-tam, tam, tam,	  // 1
	-tam, tam, -tam,  // 2
	-tam, -tam, -tam, // 3
					  //�������������������� Direita
	tam, -tam, tam,	  // 4
	tam, tam, tam,	  // 5
	tam, tam, -tam,	  // 6
	tam, -tam, -tam,  // 7
					  //��������������������� (Cima
	-tam, tam, tam,	  // 8
	-tam, tam, -tam,  // 9
	tam, tam, -tam,	  // 10
	tam, tam, tam,	  // 11
};
static GLfloat normais[] = {
	//�������������������������������������� x=tam (Esquerda)
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
	//�������������������������������������� x=tam (Direita)
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
	//�������������������������������������� y=tam (Cima)
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
static GLfloat cores[] = {
	//�������������������������������������� x=tam (Esquerda) - Red
	1.0, 0.0, 0.0, // 0
	1.0, 0.0, 0.0, // 1
	1.0, 1.0, 0.0, // 2
	1.0, 1.0, 0.0, // 3
				   //�������������������������������������� y=tam (Cima) - Blue
	1.1, 0.0, 1.0, // 8
	1.0, 0.0, 1.0, // 9
	0.0, 1.0, 1.0, // 10
	0.0, 0.5, 1.0, // 11
				   //�������������������������������������� x=2*tam (Direita) - Green
	0.0, 1.0, 1.0, // 4
	0.0, 1.0, 1.0, // 5
	0.0, 1.0, 0.0, // 6
	0.0, 1.0, 0.0  // 7

};
static GLuint esquerda[] = {0, 1, 2, 3};
static GLuint direita[] = {4, 7, 6, 5};
static GLuint cima[] = {8, 11, 10, 9};

//================================================================================
//=========================================================================== INIT
void initialize(void)
{
	glClearColor(BLACK);	 //������������������������������Apagar
	glEnable(GL_DEPTH_TEST); //������������������������������Profundidade
	glShadeModel(GL_SMOOTH); //������������������������������Interpolacao de cores

	//glEnable(GL_CULL_FACE);		//������������������������������Faces visiveis
	//glCullFace(GL_BACK);		//������������������������������Mostrar so as da frente

	glVertexPointer(3, GL_FLOAT, 0, vertices); //���������������Posicoes
	glEnableClientState(GL_VERTEX_ARRAY);
	glNormalPointer(GL_FLOAT, 0, normais); //���������������Normais
	glEnableClientState(GL_NORMAL_ARRAY);
	glColorPointer(3, GL_FLOAT, 0, cores); //���������������Cores
	glEnableClientState(GL_COLOR_ARRAY);

	srand(1);
}

float aleatorio(GLint minimo, GLint maximo)
{
	GLfloat y;
	y = rand() % 1000;
	return (minimo + 0.001 * y * (maximo - minimo));
}

void desenhaTexto(char *string, GLfloat x, GLfloat y)
{
	glPushMatrix();
	glTranslatef(x, 0, y);
	glRasterPos2f(0, 0);
	while (*string)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, *string++);
	glPopMatrix();
}

void drawEixos()
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Eixo
	glColor4f(ORANGE);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0.5 * size, 0, 0);
	glEnd();
	glColor4f(GREEN);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.5 * size, 0);
	glEnd();
	glColor4f(BLUE);
	glBegin(GL_LINES);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 0.5 * size);
	glEnd();
}

void drawObservador_Onde()
{
	glColor4f(GREEN);
	glPushMatrix();
	glTranslatef(obsP[0], obsP[1], obsP[2]);
	glutSolidCube(1.5);
	glPopMatrix();
}

void drawObservador_ParaOnde()
{
	glColor4f(GREEN);
	glPushMatrix();
	glTranslatef(obsP[0], obsP[1], obsP[2]);
	glutSolidCube(0.8);
	glPopMatrix();
}

void draw_Informacao()
{
	if (tipoProjeccao)
		sprintf(texto, "Projecao = Ortogonal");
	else
		sprintf(texto, "Projecao = Perspectiva");
	desenhaTexto(texto, -15, -15);
}

//======================================
void drawScene()
{

	//==================================== MESAS
	if (sempreRodar)
	{
		rotacao = rotacao + 1;
		altura = altura + incALT;
		if (altura > 3)
			incALT = -incALT;
		if (altura < -1)
			incALT = -incALT;
	}
	glTranslatef(centrox, altura, 0.0);
	glRotatef(rotacao, 0.0, 1.0, 0.0);
	glScalef(2.5, 2.0, 2.5);
	glPushMatrix();
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, esquerda);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, direita);
	glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, cima);
	glPopMatrix();

	glColor4f(YELLOW);
	glTranslatef(0, tam + 0.3, 0.0);
	glutWireTeapot(0.4);
}

//======================================================
//======================================================
void display(void)
{

	//================================================================= APaga
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//================================================================= Viewport 1 MAPA
	// MAPA DO LADO ESQUERDO  -  VISTA ORTOGONAL
	glViewport(0.40 * wScreen, 0.01 * hScreen, 0.25 * wScreen, 0.25 * hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-20, 20, -20, 20, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 1, 0, 0, 0, 0, 1, 0, 1);
	drawEixos();
	drawScene();
	drawObservador_ParaOnde();

	//================================================================= Viewport 2
	//====  largura 70%, altura 100%
	glViewport(0.15 * wScreen, 0.3 * hScreen, 0.70 * wScreen, 0.70 * hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (tipoProjeccao == 0)
		gluPerspective(anguloZ, (float)wScreen / hScreen, 0.1, 9999);

	if (tipoProjeccao == 1)
		glOrtho(-20, 20, -20, 20, -100, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsP[0], obsP[1], obsP[2], obsT[0], obsT[1], obsT[2], 0, 1, 0);

	//����������������������������������������������������������Objectos
	drawEixos();
	if (tipoProjeccao == 1)
		drawObservador_Onde();
	drawScene();

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Actualizacao
	glutSwapBuffers();
}

void Timer(int value)
{
	glutPostRedisplay();
	glutTimerFunc(msec, Timer, 1);
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y)
{

	switch (key)
	{

	case 'R':
	case 'r':
		sempreRodar = !sempreRodar;
		glutPostRedisplay();
		break;

		//------------------------------ translacao
	case 'A':
	case 'a':
		centrox = centrox + 0.5;
		glutPostRedisplay();
		break;

	case 'S':
	case 's':
		centrox = centrox - 0.5;
		glutPostRedisplay();
		break;
		//------------------------------ rotacao
	case 'e':
	case 'E':
		rotacao = rotacao + 2.5;
		glutPostRedisplay();
		break;
	case 'd':
	case 'D':
		rotacao = rotacao - 2.5;
		glutPostRedisplay();
		break;

		//------------------------------ zoom
	case 'z':
	case 'Z':
		anguloZ = anguloZ - 2.5;
		glutPostRedisplay();
		break;

	case 'x':
	case 'X':
		anguloZ = anguloZ + 2.5;
		glutPostRedisplay();
		break;

		//------------------------------ projeccao
	case 'p':
	case 'P':
		tipoProjeccao = (tipoProjeccao + 1) % 2;
		glutPostRedisplay();
		break;

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
		obsP[0] += 0.5 * cos(aVisao);
		obsP[2] += 0.5 * sin(aVisao);
	}
	if (key == GLUT_KEY_DOWN)
	{
		obsP[0] -= 0.5 * cos(aVisao);
		obsP[2] -= 0.5 * sin(aVisao);
	}
	if (key == GLUT_KEY_LEFT)
		aVisao -= 0.1;
	if (key == GLUT_KEY_RIGHT)
		aVisao += 0.1;

	obsT[0] = obsP[0] + rVisao * cos(aVisao);
	obsT[2] = obsP[2] + rVisao * sin(aVisao);

	glutPostRedisplay();
}

//======================================================= MAIN
//======================================================= MAIN
int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(wScreen, hScreen);
	glutInitWindowPosition(400, 100);
	glutCreateWindow("{jh,avperrotta}@dei.uc.pt|  |Projeccao :'p'|  |Observador:'SETAS'|  |Mesa-'a/s' 'e/d' 'r'  ");

	initialize();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(msec, Timer, 1);

	glutMainLoop();

	return 0;
}
