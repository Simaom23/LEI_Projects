/* ===================================================================================
	Departamento Eng. Informatica - FCTUC
	Computacao Grafica - 2021/22
	................................................ JHenriques / APerrotta
	Trabalho 0 - Introducao ao OpenGL
======================================================================================= */

//.................................................... Bibliotecas necessarias
#include <windows.h>
//#include <stdio.h>			// printf
#include <GL\glut.h> // openGL  a GLUT j� inclui as librarias: GL.h e GLU.h

//.................................................... Variaveis
GLfloat r, g, b; // cor RGB

//-----------------------------------------------------------------------------------
//																		Inicializacao
//-----------------------------------------------------------------------------------
void Inicializa(void)
{
	glClearColor(0.0, 0.0, 0.0, 1.0); //....	Cor para apagar ecran (Preto)
	gluOrtho2D(-50, 50, -50, 50);	  //....	Definicao sistema coordenadas area de desenho
	glShadeModel(GL_SMOOTH);		  //....  Interpolacao de cor com base na cor dos vertices

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	r = 1;
	g = 0;
	b = 0; //....  Vermelho
}

//-----------------------------------------------------------------------------------
//-------------------------------------------------------------------- INTERACCAO
//-----------------------------------------------------------------------------------
//����������������������������������������Fun��o callback eventos teclado
void Teclado(unsigned char key, int x, int y)
{

	switch (key)
	{
	case 'r':
		r = 1.0;
		g = 0.0;
		b = 0.0;
		glutPostRedisplay();
		break;
	case 'g':
		r = 0.0;
		g = 1.0;
		b = 0.0;
		glutPostRedisplay();
		break;
	case 'b':
		r = 0.0;
		g = 0.0;
		b = 1.0;
		glutPostRedisplay();
		break;

	case 27: // ESC
		exit(0);
		break;
	}
}

//---------------------------------------- Fun��o callback de desenho (principal)
void Desenha(void)
{
	glClear(GL_COLOR_BUFFER_BIT); //.. Limpa de acordo com cor predefinida -glClearColor

	glColor3f(r, g, b);	 //.. Inicializa cor
	glBegin(GL_POLYGON); //.. primitiva poligono - 4 vertices~
	glRotatef(45.0f, 0, 0, 1);
	glScalef(0.0f, 0.67f, 0.0f);
	glRotatef(-45.0f, 0, 0, 1);
	glTranslatef(0.0f, -10.0f, 0.0f);
	glScalef(0.0f, 10.25f, 0.0f);
	glTranslatef(0.0f, 10.0f, 0.0f);
	glVertex2f(-10.0f, -10.0f);
	glVertex2f(-10.0f, 10.0f);
	glVertex2f(10.0f, 10.0f);
	glVertex2f(10.0f, -10.0f);
	glEnd();

	glutSwapBuffers(); //.. actualiza ecran
}

//-----------------------------------------------------------------------------------
//																		         MAIN
//-----------------------------------------------------------------------------------
int main(int argc, char **argv)
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	glutInit(&argc, argv);						 //===1:Inicia janela
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //		:Recursos que ajanela vai usar: Double mode, RBG
	glutInitWindowSize(600, 500);				 //		:dimensoes (pixeis)
	glutInitWindowPosition(200, 100);			 //		:localizacao do vertoce superior esquerdo
	glutCreateWindow("Square");					 //     :nome da janela

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Inicializa(); //===2:Inicializacao estado/parametros

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//===3:Definicao callbaks
	glutDisplayFunc(Desenha);  //		:desenho
	glutKeyboardFunc(Teclado); //		:eventos teclado

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	glutMainLoop(); //===4:Inicia processamento
	return 1;
}
