//Libraries
#include <windows.h>
#include <stdio.h>
#include <GL\glut.h>
#include <time.h>

// Prototypes
void init(void);
void timer(int value);
void keyboard(unsigned char key, int x, int y);
void display(void);
void quad(float coordenates[4][2]);
void output(int x, int y, char *string);

// Global Variables
GLint hour, minute, second;
GLint msecDelay = 100;
struct tm *timeinfo;
time_t t;
char timeString[8] = "";

// Unit objects
float unitQuad[4][2] = {{-1.0f, -1.0f},
                        {-1.0f, 1.0f},
                        {1.0f, 1.0f},
                        {1.0f, -1.0f}};

// Main
int main(int argc, char **argv)
{
    t = time(0);
    timeinfo = localtime(&t);
    second = timeinfo->tm_sec;
    minute = timeinfo->tm_min;
    hour = timeinfo->tm_hour;
    sprintf(timeString, "%02d:%02d:%02d", hour, minute, second);
    second *= 6.0;
    minute *= 6.0;
    hour *= 30.0;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(320, 180);
    glutCreateWindow("P1");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(msecDelay, timer, 1);
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

void timer(int value)
{
    t = time(0);
    timeinfo = localtime(&t);
    second = timeinfo->tm_sec;
    minute = timeinfo->tm_min;
    hour = timeinfo->tm_hour;
    sprintf(timeString, "%02d:%02d:%02d", hour, minute, second);
    second *= 6.0;
    minute *= 6.0;
    hour *= 30.0;
    glutPostRedisplay();
    glutTimerFunc(msecDelay, timer, 1);
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

    char string[] = "The Clock";
    output(-50, 300, string);
    output(-40, -315, timeString);

    // Renders clock back circle
    glColor3f(0.255, 0.702, 0.639);
    for (int i = 0; i < 360; i++)
    {
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
    }

    // Renders clock front circle
    glColor3f(0.522, 0.863, 0.69);
    for (int i = 0; i < 360; i++)
    {
        glPushMatrix();
        glRotatef(i, 0, 0, 1);
        glScalef(3.14f, 250.0f, 0.0f);
        quad(unitQuad);
        glPopMatrix();
    }

    // Renders clock hours indicators
    glColor3f(0.255, 0.702, 0.639);
    for (int i = 0; i < 8; i++)
    {
        glPushMatrix();
        glRotatef(i * 45, 0, 0, 1);
        glScalef(5.0f, 15.0f, 0.0f);

        // Translates object
        glTranslatef(0.0f, 16.67f, 0.0f);

        quad(unitQuad);
        glPopMatrix();
    }

    // Render clocks seconds pointer
    glPushMatrix();
    glRotatef(-second, 0, 0, 1);
    glScalef(2.0f, 120.0f, 0.0f);
    glTranslatef(0.0f, 0.7f, 0.0f);
    quad(unitQuad);
    glPopMatrix();

    // Render clocks minutes pointer
    glColor3f(0.898, 0.49, 0.376);
    glPushMatrix();
    glRotatef(-minute, 0, 0, 1);
    glScalef(3.0f, 70.0f, 0.0f);
    glTranslatef(0.0f, 0.9f, 0.0f);
    quad(unitQuad);
    glPopMatrix();

    // Render clocks hours pointer
    glColor3f(0.898, 0.49, 0.376);
    glPushMatrix();
    glRotatef(-hour, 0, 0, 1);
    glScalef(4.0f, 40.0f, 0.0f);
    glTranslatef(0.0f, 0.8f, 0.0f);
    quad(unitQuad);
    glPopMatrix();

    // Renders clock pointers holder
    glColor3f(0.255, 0.702, 0.639);
    for (int i = 0; i < 360; i++)
    {
        glPushMatrix();
        glRotatef(i, 0, 0, 1);
        glScalef(3.14f, 10.0f, 0.0f);
        quad(unitQuad);
        glPopMatrix();
    }

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

void output(int x, int y, char *string)
{
    glColor3f(0, 0, 0);
    glRasterPos2d(x, y);
    int len;
    len = (int)strlen(string);
    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
    }
}
