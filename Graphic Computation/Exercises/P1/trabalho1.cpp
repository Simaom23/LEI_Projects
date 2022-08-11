//Libraries
#include <windows.h>
#include <stdio.h>
#include <GL\glut.h>

// Prototypes
void init(void);
void keyboard(unsigned char key, int x, int y);
void display(void);
void square(float coordenates[4][2]);

// Global Variables
GLfloat r, g, b;

// Unit objects
float unitSquare[4][2] = {{-1.0f, -1.0f},
                          {-1.0f, 1.0f},
                          {1.0f, 1.0f},
                          {1.0f, -1.0f}};

// Main
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 500);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Trabalho 1");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 1;
}

// Init function
void init(void)
{
    glClearColor(0.5, 0.5, 0.5, 1.0);
    gluOrtho2D(-300, 300, -250, 250);
    glShadeModel(GL_SMOOTH);

    r = 1;
    g = 0;
    b = 0;
}

// Keyboard Function
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    // ESC
    case 27:
        exit(0);
        break;
    }
}

// Display Function
void display(void)
{
    // Clears predefined color
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1, 0.7, 0);
    glPushMatrix();

    // Rotates object
    glRotatef(45.0f, 0, 0, 1);

    // Scales object
    glScalef(50.0f, 50.0f, 0.0f);

    // Translates object
    glTranslatef(2.0f, 2.0f, 0.0f);

    // Renders object
    square(unitSquare);

    glPopMatrix();

    // Updates display
    glutSwapBuffers();
}

// Renders a quad
void square(float coordenates[4][2])
{
    glBegin(GL_QUADS);
    for (int i = 0; i < 4; i++)
    {
        glVertex2f(coordenates[i][0], coordenates[i][1]);
    }
    glEnd();
}
