//Libraries
#include <windows.h>
#include <stdio.h>
#include <GL\glut.h>
#include <time.h>

// Prototypes
void init(void);
void keyboard(unsigned char key, int x, int y);
void specialKeys(int key, int x, int y);
void display(void);
void quad(float coordenates[4][2]);
void triangle(float coordenates[3][2]);
void output(int x, int y, char *string);

// Global Variables
GLfloat mx = 0, my = 0;
GLint hour, minute, second;

// Unit objects
float unitQuad[4][2] = {{-1.0f, -1.0f},
                        {-1.0f, 1.0f},
                        {1.0f, 1.0f},
                        {1.0f, -1.0f}};

float unitTriangle[3][2] = {{-1.0f, -1.0f},
                            {-1.0f, 1.0f},
                            {1.0f, 1.0f}};

// Main
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(320, 180);
    glutCreateWindow("Ship");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 1;
}

// Init function
void init(void)
{
    glClearColor(0.898, 0.49, 0.376, 1.0);
    gluOrtho2D(-640, 640, -360, 360);
    glShadeModel(GL_SMOOTH);
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

    // Renders clock back circle
    glColor3f(0.255, 0.702, 0.639);
    // Pushes matrix
    glPushMatrix();

    // Rotates object
    glRotatef(i, 0, 0, 1);

    // Scales object
    glScalef(3.14f, 265.0f, 0.0f);

    // Renders quad
    quad(unitQuad);

    // Pop's matrix
    glPopMatrix();

    // Renders clock front circle
    glColor3f(0.522, 0.863, 0.69);

    // Updates display
    glutSwapBuffers();
}

// Renders a quad
void quad(float coordenates[4][2])
{
    glBegin(GL_QUADS);
    for (int i = 0; i < 4; i++)
    {
        // Generates quads vertex
        glVertex2f(coordenates[i][0], coordenates[i][1]);
    }
    glEnd();
}

void triangle(float coordenates[3][2])
{
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; i++)
    {
        // Generates quads vertex
        glVertex2f(coordenates[i][0], coordenates[i][1]);
    }
    glEnd();
}
