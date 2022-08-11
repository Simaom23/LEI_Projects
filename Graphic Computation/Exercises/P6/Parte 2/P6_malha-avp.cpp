

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <windows.h>
#include "RgbImage.h"
#include <GL\Glut.h>


//--------------------------------- Definir cores
#define PI		 3.14159

//………………………………………………………………………………………………………………………………………………………………………………………… A variar no programa
bool 		Focos[] = { 1,1 };		//.. Dois Focos ligados ou desligados
GLfloat		aberturaFoco = 10.0;		//.. angulo inicial do foco
GLfloat		anguloINC = 3.0;		//.. incremento
GLfloat		anguloMIN = 3.0;		//.. minimo
GLfloat		anguloMAX = 70.0;		//.. maximo


//………………………………………………………………………………………………………………………………… Textura
RgbImage  imag;
GLuint    tex;
GLuint    texture[1];



//…………………………………………………………………………………………………………………………………
GLint	  dim = 10;   //numero divisoes da grelha
GLfloat meshW = 2.;
GLfloat meshH = 2.;

GLfloat Pos1[] = { -1.f, 0.0f,  1.0f, 1.0f };   // Foco 1
GLfloat Pos2[] = { 1.0f - meshW / float(dim - 1), 0.0f,  1.0f, 1.0f };   // Foco 2 

GLfloat meshPos[] = { 0., 0., 0. };
GLfloat alpha = 0.9;
GLint order = 1;
GLenum options[] =
{
	GL_ZERO,
	GL_ONE,
	GL_SRC_COLOR,
	GL_ONE_MINUS_SRC_COLOR,
	GL_DST_COLOR,
	GL_ONE_MINUS_DST_COLOR,
	GL_SRC_ALPHA,
	GL_ONE_MINUS_SRC_ALPHA,
	GL_DST_ALPHA,
	GL_ONE_MINUS_DST_ALPHA
};

GLint src = 6;
GLint dst = 1;

void drawMesh() {
	//draw wireFrame
	glDisable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDisable(GL_LIGHTING);
	//glEnable(GL_BLEND);
	//glBlendFunc(options[src], options[dst]);
	glColor4f(1., 1., 1., alpha);
	glPushMatrix();
	glTranslatef(-meshW * 0.5, -meshH * 0.5, 0.01);  // meio do poligono 

	glNormal3f(0, 0, 1);          //normal 

	glBegin(GL_QUADS);
	for (int i = 0; i < dim - 1; i++)
		for (int j = 0; j < dim - 1; j++) {
			GLfloat x0 = meshW * i / float(dim - 1);
			GLfloat y0 = meshH * j / float(dim - 1);
			GLfloat u0 = i / float(dim - 1);
			GLfloat v0 = j / float(dim - 1);

			GLfloat x1 = meshW * (i + 1) / float(dim - 1);
			GLfloat y1 = meshH * j / float(dim - 1);
			GLfloat u1 = (i + 1) / float(dim - 1);
			GLfloat v1 = j / float(dim - 1);

			GLfloat x2 = meshW * (i + 1) / float(dim - 1);
			GLfloat y2 = meshH * (j + 1) / float(dim - 1);
			GLfloat u2 = (i + 1) / float(dim - 1);
			GLfloat v2 = (j + 1) / float(dim - 1);

			GLfloat x3 = meshW * i / float(dim - 1);
			GLfloat y3 = meshH * (j + 1) / float(dim - 1);
			GLfloat u3 = i / float(dim - 1);
			GLfloat v3 = (j + 1) / float(dim - 1);

			glColor4f(1., 1., 1., alpha);
			glTexCoord2f(u0, v0);
			glVertex3f(x0, y0, 0.);
			glTexCoord2f(u1, v1);
			glVertex3f(x1, y1, 0.);
			glTexCoord2f(u2, v2);
			glVertex3f(x2, y2, 0.);
			glTexCoord2f(u3, v3);
			glVertex3f(x3, y3, 0.);

		}
	glEnd();
	glPopMatrix();
	//glDisable(GL_BLEND);
}

void defineTexturas()
{
	//……………………………………………………………………………………………………………………………  Textura
	glGenTextures(1, &texture[0]);
	glBindTexture(GL_TEXTURE_2D, texture[0]);
	imag.LoadBmpFile("caracol.bmp");
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D, 0, 3,
		imag.GetNumCols(),
		imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
		imag.ImageData());
}



void defineLuzes()
{
	GLfloat Foco_direccao[] = { 0, 0, -1, 0 };	//……… -Z
	GLfloat Foco1_cor[] = { 0, 1,  0, 1 };	//……… Cor da luz 1
	GLfloat Foco2_cor[] = { 1, 0,  0, 1 };	//……… Cor da luz 2
	GLfloat Foco_ak = 1.0;
	GLfloat Foco_al = 0.05f;
	GLfloat Foco_aq = 0.0f;
	GLfloat Foco_Expon = 1.0;		// Foco, SPOT_Exponent

	//……………………………………………………………………………………………………………………………Foco Esquerda
	glLightfv(GL_LIGHT0, GL_POSITION, Pos1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, Foco1_cor);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, Foco_ak);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, Foco_al);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, Foco_aq);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, aberturaFoco);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, Foco_direccao);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, Foco_Expon);

	//……………………………………………………………………………………………………………………………Foco Direita
	glLightfv(GL_LIGHT1, GL_POSITION, Pos2);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Foco2_cor);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, Foco_ak);
	glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, Foco_al);
	glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, Foco_aq);
	glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, aberturaFoco);
	glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, Foco_direccao);
	glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, Foco_Expon);

}



void init(void)
{
	//……………………………………………………………………………………………………………………………Apagar
	glClearColor(0, 0, 0, 1.);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);

	//……………………………………………………………………………………………………………………………Texturas
	defineTexturas();
	glEnable(GL_TEXTURE_2D);

	//……………………………………………………………………………………………………………………………Luzes
	defineLuzes();
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);

	glEnable(GL_BLEND);
	glBlendFunc(options[src], options[dst]);

}




void desenha()
{
	int				i, j;
	float			med_dim = (float)dim / 2;


	//===========================================================
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glEnable(GL_BLEND);
	


	glViewport(0, 0, 550, 550);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(20.0f, 1.0f, 0.1f, 100.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

	//============================================Esferasverde e vermelha
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	//desenha só o wireframe
	if (order == 0)
		drawMesh();
	
	/*glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor4f(1., 0., 0., 1.);
	glPushMatrix();
	glBegin(GL_POLYGON);
	glVertex3f(-0.5, 0.5, -0.5);
	glVertex3f(0.5, 0.5, -0.5);
	glVertex3f(0.5, -0.5, -0.5);
	glVertex3f(-0.5, -0.5, -0.5);
	glEnd();
	glPopMatrix();*/


	//…………………………………………………………………………………Verde
	if (Focos[0]) {
		glPushMatrix();
		glColor4f(0.0f, 1.0f, 0.0f, 1.);
		glTranslatef(Pos1[0], Pos1[1], Pos1[2]);
		glutSolidSphere(0.1f, 100, 100);
		glPopMatrix();
	}
	//…………………………………………………………………………………Vermelha
	if (Focos[1]) {
		glPushMatrix();
		glColor4f(1.0f, 0.0f, 0.0f, 1.);
		glTranslatef(Pos2[0], Pos2[1], Pos2[2]);
		glutSolidSphere(0.1f, 100, 100);
		glPopMatrix();
	}

	//============================================ Grelha de polionos (dim*dim)
	//============================================ O ponto minimo   e (0,0), o maximo (2,2)
	//============================================ A textura minimo e (0,0), o maximo (1,1)
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

	//----------------------------------------------- Luzes
	defineLuzes();

	//----------------------------------------------- Quadro Material - branco
	float corAmb[] = { 0.8,0.8,0.8,1 };
	glMaterialfv(GL_FRONT, GL_AMBIENT, corAmb);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, corAmb);
	glMaterialfv(GL_FRONT, GL_SPECULAR, corAmb);

	//----------------------------------------------- Textura - caracol
	glBindTexture(GL_TEXTURE_2D, texture[0]);

	//Desenha mesh com normais perpendiculares
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPushMatrix();

	glTranslatef(-meshW * 0.5, -meshH * 0.5, 0);  // meio do poligono 

	glNormal3f(0, 0, 1);          //normal 

	glBegin(GL_QUADS);
	for (i = 0; i < dim - 1; i++) {
		for (j = 0; j < dim - 1; j++) {
			GLfloat x0 = meshW * i / GLfloat(dim - 1);
			GLfloat y0 = meshH * j / GLfloat(dim - 1);
			GLfloat u0 = i / GLfloat(dim - 1);
			GLfloat v0 = j / GLfloat(dim - 1);

			GLfloat x1 = meshW * (i + 1) / GLfloat(dim - 1);
			GLfloat y1 = meshH * j / GLfloat(dim - 1);
			GLfloat u1 = (i + 1) / GLfloat(dim - 1);
			GLfloat v1 = j / GLfloat(dim - 1);

			GLfloat x2 = meshW * (i + 1) / GLfloat(dim - 1);
			GLfloat y2 = meshH * (j + 1) / GLfloat(dim - 1);
			GLfloat u2 = (i + 1) / GLfloat(dim - 1);
			GLfloat v2 = (j + 1) / GLfloat(dim - 1);

			GLfloat x3 = meshW * i / GLfloat(dim - 1);
			GLfloat y3 = meshH * (j + 1) / GLfloat(dim - 1);
			GLfloat u3 = i / GLfloat(dim - 1);
			GLfloat v3 = (j + 1) / GLfloat(dim - 1);

			glTexCoord2f(u0, v0);
			glVertex3f(x0, y0, 0.);
			glTexCoord2f(u1, v1);
			glVertex3f(x1, y1, 0.);
			glTexCoord2f(u2, v2);
			glVertex3f(x2, y2, 0.);
			glTexCoord2f(u3, v3);
			glVertex3f(x3, y3, 0.);

		}
	}
	glEnd();
	glPopMatrix();
	if (order == 1)
		drawMesh();

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Actualizacao
	glutSwapBuffers();
}




//======================================================= EVENTOS
void keyboard(unsigned char key, int x, int y) {

	switch (key) {

	case 'G':
	case 'g':
		Focos[0] = !Focos[0];
		if (Focos[0] == 0)
			glDisable(GL_LIGHT0);
		else
			glEnable(GL_LIGHT0);
		glutPostRedisplay();
		break;
	case 'R':
	case 'r':
		Focos[1] = !Focos[1];
		if (Focos[1] == 0)
			glDisable(GL_LIGHT1);
		else
			glEnable(GL_LIGHT1);
		glutPostRedisplay();
		break;

	case 'a':
	case 'A':
		dim++;
		if (dim > 256) dim = 256;
		Pos2[0] = 1. - meshW / float(dim - 1);
		glutPostRedisplay();
		break;
	case 'z':
	case 'Z':
		dim--;
		if (dim < 2) dim = 2;
		Pos2[0] = 1. - meshW / float(dim - 1);
		glutPostRedisplay();
		break;

	case 'w':
	case 'W':
		alpha += 0.05;
		if (alpha > 1.) alpha = 1.;
		glutPostRedisplay();
		break;
	case 's':
	case 'S':
		alpha -= 0.05;
		if (alpha < 0.) alpha = 0.;
		glutPostRedisplay();
		break;
	case 'o':
		order = 1 - order;
		glutPostRedisplay();
		break;
	case 'e':
		src++;
		if (src >= 10) src = 0;
		printf("src, dst = (%d, %d)\n", src, dst);
		glBlendFunc(options[src], options[dst]);
		glutPostRedisplay();
		break;
	case 'd':
		dst++;
		if (dst >= 10) dst = 0;
		printf("src, dst = (%d, %d)\n", src, dst);
		glBlendFunc(options[src], options[dst]);
		glutPostRedisplay();
		break;

		//--------------------------- Escape
	case 27:
		exit(0);
		break;
	}

}


void teclasNotAscii(int key, int x, int y) {

	if (key == GLUT_KEY_UP) {
		aberturaFoco = aberturaFoco + anguloINC;
		if (aberturaFoco > anguloMAX)
			aberturaFoco = anguloMAX;
	}
	if (key == GLUT_KEY_DOWN) {
		aberturaFoco = aberturaFoco - anguloINC;
		if (aberturaFoco < anguloMIN)
			aberturaFoco = anguloMIN;
	}
	glutPostRedisplay();
}



//======================================================= MAIN
int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(550, 550);
	glutInitWindowPosition(300, 100);
	glutCreateWindow("{jh,avperrotta}  'G/R'-Ligar  'A:Z'-Grelha  'Dow:Up'-Angulo' ");


	init();

	glutSpecialFunc(teclasNotAscii);
	glutDisplayFunc(desenha);
	glutKeyboardFunc(keyboard);

	glutMainLoop();

	return 0;
}