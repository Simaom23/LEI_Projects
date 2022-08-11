//Libraries
#include <windows.h>
#include <stdio.h>
#include <GL\glut.h>

// Prototypes
void init(void);
void keyboard(unsigned char key, int x, int y);
void specialKeys(int key, int x, int y);
void display(void);
void square(float coordenates[4][2]);
void triangle(float coordenates[3][2]);

// Global Variables
GLfloat r, g, b;
GLfloat mx = 0, my = 0;

// House Foundations
float house[4][2] = {{-30.0f, -30.0f},
                     {-30.0f, 30.0f},
                     {30.0f, 30.0f},
                     {30.0f, -30.0f}};

float window[4][2] = {{5.0f, -30.0f},
                      {20.0f, -30.0f},
                      {20.0f, 0.0f},
                      {5.0f, 0.0f}};

float door[4][2] = {{-22.5f, -10.0f},
                    {-2.5f, -10.0f},
                    {-2.5f, 10.0f},
                    {-22.5f, 10.0f}};

float roof[3][2] = {{-30.0f, 30.5f},
                    {0.0f, 62.0f},
                    {30.0f, 30.5f}};

// Main
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(600, 500);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Trabalho 0");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutMainLoop();
    return 1;
}

// Init function
void init(void)
{
    glClearColor(0.5, 0.5, 0.5, 1.0);
    gluOrtho2D(-100, 100, -100, 100);
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

// Special Keys Function
void specialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
    {
        my++;
    }

    if (key == GLUT_KEY_DOWN)
    {
        my--;
    }

    if (key == GLUT_KEY_LEFT)
    {
        mx--;
    }

    if (key == GLUT_KEY_RIGHT)
    {
        mx++;
    }

    //glutPostRedisplay();
    glutPostRedisplay();
}

// Display Function
void display(void)
{
    // Clears predefined color
    glClear(GL_COLOR_BUFFER_BIT);

    // Renders House
    glColor3f(1, 0.7, 0);
    square(house);

    // Renders Window
    glColor3f(0, 0, 0);
    square(door);

    // Renders Door
    glColor3f(0, 0.6, 1);
    square(window);

    // Renders roof
    glColor3f(1, 0, 0);
    triangle(roof);

    // Updates display
    glutSwapBuffers();
}

// Renders a quad
void square(float coordenates[4][2])
{
    glBegin(GL_QUADS);
    for (int i = 0; i < 4; i++)
    {
        glVertex2f(coordenates[i][0] + mx, coordenates[i][1] + my);
    }
    glEnd();
}

// Renders a triangle
void triangle(float coordenates[3][2])
{
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; i++)
    {
        glVertex2f(coordenates[i][0] + mx, coordenates[i][1] + my);
    }
    glEnd();
}
