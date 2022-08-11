#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <GL\Glut.h>

#define PI 3.14159
//------------------------------------------------- Propriedades Materiais
void initMaterials(int material);
char Materiais[18][30] = {
	"Esmerald", "Jade", "obsidian", "Pearl", "Ruby",
	"Turquoise", "Brass", "Bronze", "Chrome", "Copper",
	"Gold", "Silver", "blackPlastic", "cyankPlastic", "greenPlastic",
	"redPlastic", "whitePlastic", "yellowPlastic"};

//=================================================== INICIALIZACOES
//---------------------------------------------------- Globais
GLfloat xC = 20.0, zC = 15.0;
GLint wScreen = 800, hScreen = 600;
char texto[30];
GLint msec = 100;

//---------------------------------------------------- Observador
//:::   Uso das setas -> esquerda/direita/tras/frente
GLfloat rVisao = 20.0, aVisao = 0.5 * PI;
GLfloat incAngulo = 0.1;
GLfloat obsPini[] = {rVisao * cos(aVisao), 5, rVisao *sin(aVisao)};

//---------------------------------------------------- AMBIENTE - fixa
GLint Dia = 0; //:::   'D'
GLfloat intensidadeDia = 0.0;
GLfloat luzGlobalCorAmb[4] = {intensidadeDia, intensidadeDia, intensidadeDia, 1.0}; //

//---------------------------------------------------- Luz pontual no TETO (eixo Y)
GLint ligaTeto = 1;			//:::   'T'
GLfloat intensidadeT = 0.3; //:::   'I'
GLint luzR = 1;				//:::   'R'
GLint luzG = 1;				//:::   'G'
GLint luzB = 1;				//:::   'B'
GLfloat localPos[4] = {0.0, 5.0, 0.0, 1.0};
GLfloat localCorAmb[4] = {0, 0, 0, 0.0};
GLfloat localCorDif[4] = {(GLfloat)luzR, (GLfloat)luzG, (GLfloat)luzB, 1.0};
GLfloat localCorEsp[4] = {(GLfloat)luzR, (GLfloat)luzG, (GLfloat)luzB, 1.0};
//--------------------------------------------------nao se considera atenua��o
// GLfloat localAttCon = 1;
// GLfloat localAttLin = 1;
// GLfloat localAttQua = 1;

//=========================================== Objecto
GLint material = 10;

//����������������������������������������������������� LUZES
void initLights(void)
{
	//����������������������������������������������������� Ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);

	//����������������������������������������������������� Teto
	glLightfv(GL_LIGHT0, GL_POSITION, localPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);
}

//================================================================================
//================== OBJECTOS
//================================================================================

void drawChao()
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Chao y=0
	initMaterials(material);
	glPushMatrix();
	glNormal3f(0, 1, 0); // virado para cima

	glBegin(GL_QUADS);
	glVertex3d(0, 0.1, 0);
	glVertex3d(0, 0.1, xC);
	glVertex3d(xC, 0.1, xC);
	glVertex3d(xC, 0.1, 0);
	glEnd();
	glPopMatrix();
}

//=============================================================================
//=============================================================================
void initialization(void)
{

	glClearColor(1, 1, 1, 1); // apagar ecran = branco
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);

	//����������������������������������������������� ILUMINACAO / MAteriais
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	initLights();
	initMaterials(10); // gold
}

//================================================================================
//======================================================================== DISPLAY
void desenhaTexto(char *string, GLfloat x, GLfloat y, GLfloat z)
{
	glRasterPos3f(x, y, z);
	while (*string)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *string++);
}
GLvoid resize(GLsizei width, GLsizei height)
{
	wScreen = width;
	hScreen = height;
	glViewport(0, 0, wScreen, hScreen);
	glutPostRedisplay();
}

void drawEixos()
{
	initMaterials(16); // whitw
	//----------------------- EIXOS
	glBegin(GL_LINES);
	glVertex3i(0, 0, -xC);
	glVertex3i(0, 0, xC);
	glEnd();
	glBegin(GL_LINES);
	glVertex3i(0, -xC, 0);
	glVertex3i(0, xC, 0);
	glEnd();
	glBegin(GL_LINES);
	glVertex3i(-xC, 0, 0);
	glVertex3i(xC, 0, 0);
	glEnd();
}

//======================================================================== ILUMINCCAO
void iluminacao()
{
	glLightfv(GL_LIGHT0, GL_POSITION, localPos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);
	if (ligaTeto)
		glEnable(GL_LIGHT0);
	else
		glDisable(GL_LIGHT0);
}

//======================================================================== MAIN
void display(void)
{

	glClearColor(0, 0, 0, 1.0);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//=============================================== Viewport0 Informacao - sem corIluminacao
	glDisable(GL_LIGHTING);
	glViewport(0, 400, wScreen / 6, hScreen / 5);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-xC, xC, -xC, xC, -zC, zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 5, 0, 0, 0, 0, 0, 0, -1);

	//------------------------------------------------ Informacao
	glColor3f(1, 1, 1); // nao se est� a usar LUZ !!   DisableLight
	sprintf(texto, "%d - Dia 'D' ", Dia);
	desenhaTexto(texto, -12, 1, -14);
	sprintf(texto, "%d - Teto 'T' ", ligaTeto);
	desenhaTexto(texto, -12, 1, -8);
	sprintf(texto, "   %d%d%d - Luz 'RGB' ", luzR, luzG, luzB);
	desenhaTexto(texto, -12, 1, -5);
	sprintf(texto, "   %4.2f - Intensidade 'I'", intensidadeT);
	desenhaTexto(texto, -12, 1, -2);
	sprintf(texto, "   %s   - Material", Materiais[material]);
	desenhaTexto(texto, -12, 1, 4);
	glEnable(GL_LIGHTING);

	//=========================================== Viewport1 / COR+ILUMINACAO
	glViewport(0, 0, wScreen / 6, hScreen / 5);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-xC, xC, -xC, xC, -zC, zC);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 5, 0, 0, 0, 0, 0, 0, -1);

	//--------------------- desenha objectos
	iluminacao();
	drawEixos();
	drawChao();

	//================================================================= Viewport2
	glEnable(GL_LIGHTING);
	glViewport(wScreen / 5, 0, 0.75 * wScreen, hScreen);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(120, (float)wScreen / hScreen, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(obsPini[0], obsPini[1], obsPini[2], 0, 0, 0, 0, 1, 0);

	iluminacao();
	drawEixos();
	drawChao();

	//___________________________________________________
	glutSwapBuffers();
}

void updateLuz()
{
	localCorAmb[0] = luzR * intensidadeT;
	localCorAmb[1] = luzG * intensidadeT;
	localCorAmb[2] = luzB * intensidadeT;
	localCorDif[0] = luzR * intensidadeT;
	localCorDif[1] = luzG * intensidadeT;
	localCorDif[2] = luzB * intensidadeT;
	localCorEsp[0] = luzR * intensidadeT;
	localCorEsp[1] = luzG * intensidadeT;
	localCorEsp[2] = luzB * intensidadeT;
	;
	glLightfv(GL_LIGHT0, GL_AMBIENT, localCorAmb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, localCorDif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, localCorEsp);
}

//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{

		//===================================== ILUMINCAAO
		//--------------------------- Dia/noite
	case 'd':
	case 'D':
		Dia = !Dia;
		if (Dia)
		{
			luzGlobalCorAmb[0] = 1.0;
			luzGlobalCorAmb[1] = 1.0;
			luzGlobalCorAmb[2] = 1.0;
		}
		else
		{
			luzGlobalCorAmb[0] = 0.0;
			luzGlobalCorAmb[1] = 0.0;
			luzGlobalCorAmb[2] = 0.0;
		}
		glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzGlobalCorAmb);
		glutPostRedisplay();
		break;

		//--------------------------- TETO
	case 't':
	case 'T':
		ligaTeto = !ligaTeto;
		updateLuz();
		glutPostRedisplay();
		break;
		//--------------------------- Iluminacaoda sala
	case 'i':
	case 'I':
		intensidadeT = intensidadeT + 0.1;
		if (intensidadeT > 1.1)
			intensidadeT = 0;
		updateLuz();
		glutPostRedisplay();
		break;
	case 'r':
	case 'R':
		luzR = (luzR + 1) % 2;
		updateLuz();
		glutPostRedisplay();
		break;
	case 'g':
	case 'G':
		luzG = (luzG + 1) % 2;
		updateLuz();
		glutPostRedisplay();
		break;
	case 'b':
	case 'B':
		luzB = (luzB + 1) % 2;
		updateLuz();
		glutPostRedisplay();
		break;

		//--------------------------- MAterial
	case 'm':
	case 'M':
		material = (material + 1) % 18;
		initMaterials(material);
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
		obsPini[1] = obsPini[1] + 1;
	if (key == GLUT_KEY_DOWN)
		obsPini[1] = obsPini[1] - 1;

	if (key == GLUT_KEY_LEFT)
		aVisao = (aVisao + 0.1);
	if (key == GLUT_KEY_RIGHT)
		aVisao = (aVisao - 0.1);
	obsPini[0] = rVisao * cos(aVisao);
	obsPini[2] = rVisao * sin(aVisao);
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
	glutInitWindowPosition(400, 10);
	glutCreateWindow("{jh,avperrotta}@dei.uc.pt-CG  LEI / CG - 2021");

	initialization();
	glutSpecialFunc(teclasNotAscii);
	glutReshapeFunc(resize);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutTimerFunc(msec, Timer, 1);

	glutMainLoop();
	return 0;
}
