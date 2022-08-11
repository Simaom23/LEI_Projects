/* Simão Monteiro Nº 2019215412 */

// Libraries
#include "project.h"

// Main
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(wScreen, hScreen);
    glutInitWindowPosition(300, 100);
    glutCreateWindow("The Lamp Remote - Controls: A/D - Change Colour | O - Lamp ON/OFF | Arrow Keys - Rotate Observer | Z/X - Zoom | Q - Ambient ON/OFF | W - Ambient Intensity | E - Floor Specular Coefficient");
    init();
    glutSpecialFunc(otherKeyboard);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(msec, timer, 1);
    glutMainLoop();
    return 0;
}

// Init
void init(void)
{
    glClearColor(1, 1, 1, 1);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_NORMALIZE);

    // Textures
    texturesInit();

    // Lighting
    lightingInit();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glDisable(GL_LIGHT1);

    // Vertex Arrays
    glVertexPointer(3, GL_FLOAT, 0, vertex);
    glEnableClientState(GL_VERTEX_ARRAY);
    glNormalPointer(GL_FLOAT, 0, normals);
    glEnableClientState(GL_NORMAL_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, textures);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
}

void display(void)
{
    glClearColor(0, 0, 0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Viewport 1 - Remote Zoom
    glViewport(0.35 * wScreen, 0.001 * hScreen, 0.30 * wScreen, 0.30 * hScreen);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, (float)(wScreen * 0.4) / (hScreen * 0.4), 0.1, 3 * zC);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(-1.6, 0.2, 1.6, 0, 0, 0, 0, 1, 0);
    renderScene();

    // Viewport 2 - Standard View
    glViewport(0.15 * wScreen, 0.3 * hScreen, wScreen * 0.7, hScreen * 0.7);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fov, (float)wScreen / hScreen, 0.1, 3 * zC);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(obsP[0], obsP[1], obsP[2], 0, 0, 0, 0, 1, 0);

    // Objects
    // renderAxis();
    renderScene();

    // Refresh
    glutSwapBuffers();
}

void texturesInit(void)
{

    // SkyBox
    glGenTextures(1, &texture[0]);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    image.LoadBmpFile("Textures/SkyBox.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 image.GetNumCols(),
                 image.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 image.ImageData());

    // Wall Texture
    glGenTextures(1, &texture[1]);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    image.LoadBmpFile("Textures/Wall.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 image.GetNumCols(),
                 image.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 image.ImageData());

    // Floor Texture
    glGenTextures(1, &texture[2]);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    image.LoadBmpFile("Textures/Sand.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 image.GetNumCols(),
                 image.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 image.ImageData());

    // Remote Texture
    glGenTextures(1, &texture[3]);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    image.LoadBmpFile("Textures/Remote.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 image.GetNumCols(),
                 image.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 image.ImageData());

    // Lamp Texture
    glGenTextures(1, &texture[4]);
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    image.LoadBmpFile("Textures/Lamp.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexImage2D(GL_TEXTURE_2D, 0, 3,
                 image.GetNumCols(),
                 image.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE,
                 image.ImageData());
}

void lightingInit(void)
{
    // Ambient Lighting
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbColor);

    // Button Light
    glLightfv(GL_LIGHT0, GL_POSITION, localPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, localAmbColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, localDifColor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, localSpeColor);

    // Lamp Spotlight
    glLightfv(GL_LIGHT1, GL_POSITION, spotlighPos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, spotlightColor);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, spotlightCA);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, spotlightLA);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, spotlightQA);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotlightAperture);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotlightDirection);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spotlightExp);
}

void lighting()
{
    // Button Light
    glLightfv(GL_LIGHT0, GL_POSITION, localPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, localAmbColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, localDifColor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, localSpeColor);

    // Lamp Spotlight
    glLightfv(GL_LIGHT1, GL_POSITION, spotlighPos);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, spotlightColor);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, spotlightCA);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, spotlightLA);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, spotlightQA);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, spotlightAperture);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spotlightDirection);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, spotlightExp);
}

void renderScene()
{
    lighting();
    renderSkybox();
    renderRoom();
    renderRemote();
    renderLamp();
}

// Render Axis
void renderAxis()
{
    // X Axis
    glColor4f(RED);
    glBegin(GL_LINES);
    glVertex3i(0, 0, 0);
    glVertex3i(10, 0, 0);
    glEnd();

    // Y Axis
    glColor4f(GREEN);
    glBegin(GL_LINES);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 10, 0);
    glEnd();

    // Z Axis
    glColor4f(BLUE);
    glBegin(GL_LINES);
    glVertex3i(0, 0, 0);
    glVertex3i(0, 0, 10);
    glEnd();
}

void renderSkybox()
{
    // SkyBox
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glPushMatrix();
    glRotatef(-90, 1, 0, 0);
    gluQuadricDrawStyle(skybox, GLU_FILL);
    gluQuadricNormals(skybox, GLU_SMOOTH);
    gluQuadricTexture(skybox, GL_TRUE);
    gluSphere(skybox, 15.0, 100, 100);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

// Render Room
void renderRoom()
{
    // Room Walls
    initMaterials(1);
    glEnable(GL_TEXTURE_2D);
    glPushMatrix();
    glTranslatef(0, 1.5, 0);
    glScalef(9.5, 5, 8);
    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, top);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, back);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, right);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, left);
    glPopMatrix();

    // Polygon Mesh - Floor
    glPushMatrix();
    initMaterials(0);
    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTranslatef(-4.75, -1, -4);
    glScalef(4.75, 1, 4);
    glNormal3f(0, 1, 0);
    glBegin(GL_QUADS);
    for (int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
        {
            glTexCoord2f((float)j / dim, (float)i / dim);
            glVertex3d((float)j / med_dim, 0, (float)i / med_dim);
            glTexCoord2f((float)(j + 1) / dim, (float)i / dim);
            glVertex3d((float)(j + 1) / med_dim, 0, (float)i / med_dim);
            glTexCoord2f((float)(j + 1) / dim, (float)(i + 1) / dim);
            glVertex3d((float)(j + 1) / med_dim, 0, (float)(i + 1) / med_dim);
            glTexCoord2f((float)j / dim, (float)(i + 1) / dim);
            glVertex3d((float)j / med_dim, 0, (float)(i + 1) / med_dim);
        }
    glEnd();
    glPopMatrix();
}

// Render Remote
void renderRemote()
{
    // Remote
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glPushMatrix();
    glScalef(1, 2, 0.2);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, top);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, left);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, right);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, bottom);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, front);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, back);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    // ON/OFF Button
    glDisable(GL_LIGHTING);
    if (lampState == 1)
    {
        buttonOffset = 0.1;
        glColorPointer(4, GL_FLOAT, 0, on_colour);
    }
    else
    {
        buttonOffset = 0.2;
        glColorPointer(4, GL_FLOAT, 0, off_colour);
    }
    glPushMatrix();
    glEnableClientState(GL_COLOR_ARRAY);
    glTranslatef(0, -size, 0.1);
    glScalef(size, size, buttonOffset);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, top);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, left);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, right);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, bottom);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, front);
    glPopMatrix();
    glEnable(GL_LIGHTING);
    lighting();

    // Change Colours Nob (Intensity in the future)
    glPushMatrix();
    glRotated(-(lampIntensity - 1) * 40, 0, 0, 1);
    glTranslatef(0, 0.2, 0.08);
    glScalef(0.05, size, 0.1);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, top);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, left);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, right);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, bottom);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, front);
    glPopMatrix();
    for (int i = -45; i < 45; i++)
    {
        glPushMatrix();
        glRotated(-i, 0, 0, 1);
        glTranslatef(0, 0.6, 0.08);
        glScalef(0.05, 0.05, 0.1);
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, top);
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, left);
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, right);
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, bottom);
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, front);
        glPopMatrix();
    }
    for (int i = -1; i < 2; i++)
    {
        glPushMatrix();
        glRotated(-i * 40, 0, 0, 1);
        glTranslatef(0, 0.6, 0.08);
        glScalef(0.05, 0.15, 0.1);
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, top);
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, left);
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, right);
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, bottom);
        glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, front);
        glPopMatrix();
    }
}
// Render Lamp
void renderLamp()
{
    // Lamp Holder Cord
    glLineWidth(2);
    glColor4f(CORD_COLOUR);
    glBegin(GL_LINES);
    glVertex3f(3.0, 4.0, 0);
    glVertex3f(3.0, 2.0, 0);
    glEnd();

    // Spotlight
    glDisable(GL_LIGHTING);
    if (lampState == 0)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0.32, 0.31, 0.29, 0.5);
    }
    else
    {
        if (lampIntensity == 0)
            glColor4f(0.32, 0.31, 0.29, 1.0);
        else if (lampIntensity == 1)
            glColor4f(0.64, 0.62, 0.58, 1.0);
        else
            glColor4f(0.97, 0.93, 0.87, 1.0);
    }
    glPushMatrix();
    glTranslatef(3.0, 2.0, 0);
    glutSolidSphere(0.4, 50, 50);
    glPopMatrix();
    glDisable(GL_BLEND);
    glEnable(GL_LIGHTING);
    lighting();

    // Lamp Holder
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glPushMatrix();
    glTranslatef(3.0, 2.3, 0);
    glScalef(0.8, 0.8, 0.8);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, top);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, left);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, right);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, front);
    glDrawElements(GL_POLYGON, 4, GL_UNSIGNED_INT, back);
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

// Keyboard - ASCII Events
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    // Change Lamp Spotlight Intensity/Aperture/Attenuation
    case 'a' | 'A':
        if (lampIntensity != 0)
        {
            lampIntensity--;
            if (lampIntensity == 0)
            {
                spotlightColor[0] = 9.7;
                spotlightColor[1] = 9.3;
                spotlightColor[2] = 8.7;
                spotlightAperture = 25.0;
                spotlightLA = 0.5;
                spotlightQA = 0.2;
            }
            else
            {
                spotlightColor[0] = 9.7 * lampIntensity * 2;
                spotlightColor[1] = 9.3 * lampIntensity * 2;
                spotlightColor[2] = 8.7 * lampIntensity * 2;
                spotlightAperture -= 20.0;
                spotlightLA += (spotlightLA / 2);
                spotlightQA += (spotlightQA / 2);
            }
        }
        break;
    case 'd' | 'D':
        if (lampIntensity != 2)
        {
            lampIntensity++;
            spotlightColor[0] = 9.7 * lampIntensity * 2;
            spotlightColor[1] = 9.3 * lampIntensity * 2;
            spotlightColor[2] = 8.7 * lampIntensity * 2;
            spotlightAperture += 20.0;
            spotlightLA -= (spotlightLA / 2);
            spotlightQA -= (spotlightQA / 2);
        }
        break;

    // Change Zoom Value
    case 'z' | 'Z':
        obsP[0] += 0.2 * cos(visionAngle);
        obsP[2] += 0.2 * sin(visionAngle);
        break;
    case 'x' | 'X':
        obsP[0] -= 0.2 * cos(visionAngle);
        obsP[2] -= 0.2 * sin(visionAngle);
        break;

    // Turn ON/OFF Lamp
    case 'o' | 'O':
        if (lampState == 0)
        {
            lampState++;
            glEnable(GL_LIGHT1);
            localDifColor[0] = 0.0;
            localDifColor[1] = 3.0;
            localSpeColor[0] = 0.0;
            localSpeColor[1] = 3.0;
        }
        else
        {
            lampState = 0;
            glDisable(GL_LIGHT1);
            localDifColor[0] = 3.0;
            localDifColor[1] = 0.0;
            localSpeColor[0] = 3.0;
            localSpeColor[1] = 0.0;
        }
        break;

    // Turn Ambient Light ON/OFF
    case 'q' | 'Q':
        isDay = !isDay;
        if (isDay)
        {
            dayIntensity = 1;
            globalAmbColor[0] = (GLfloat)0.97;
            globalAmbColor[1] = (GLfloat)0.93;
            globalAmbColor[2] = (GLfloat)0.87;
        }
        else
        {
            globalAmbColor[0] = 0.0;
            globalAmbColor[1] = 0.0;
            globalAmbColor[2] = 0.0;
        }
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbColor);

        break;

    // Ambient Light Intensity
    case 'w' | 'W':
        if (isDay)
        {
            if (dayIntensity < 6)
            {
                dayIntensity++;
                globalAmbColor[0] = (GLfloat)0.97 * dayIntensity;
                globalAmbColor[1] = (GLfloat)0.93 * dayIntensity;
                globalAmbColor[2] = (GLfloat)0.87 * dayIntensity;
            }
            else
            {
                dayIntensity = 1;
                globalAmbColor[0] = (GLfloat)0.97;
                globalAmbColor[1] = (GLfloat)0.93;
                globalAmbColor[2] = (GLfloat)0.87;
            }
            glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globalAmbColor);
        }
        break;

    // Obsidian Material Coefficient
    case 'e' | 'E':
        if (obsidian_shine < 100)
            obsidian_shine += 10;
        else
            obsidian_shine = 8.4;
        break;

    // Escape
    case 27:
        exit(0);
        break;
    }

    glutPostRedisplay();
}

// Keyboard - Not ASCII Events
void otherKeyboard(int key, int x, int y)
{
    // Moves Observer in Y-Axis
    if (key == GLUT_KEY_UP)
        obsP[1] += 0.15;
    if (key == GLUT_KEY_DOWN)
        obsP[1] -= 0.15;

    // Moves Observer in X and Z-Axis
    if (key == GLUT_KEY_LEFT)
        visionAngle += 0.10;
    if (key == GLUT_KEY_RIGHT)
        visionAngle -= 0.10;

    // Restrict Y-Axis Movement
    if (obsP[1] > yC)
        obsP[1] = yC;
    if (obsP[1] < -yC)
        obsP[1] = -yC;

    // Calculate Vision Radius
    visionRadius = sqrt(pow(obsP[0], 2) + pow(obsP[2], 2));

    // Updates Observer Position
    obsP[0] = visionRadius * cos(visionAngle);
    obsP[2] = visionRadius * sin(visionAngle);

    glutPostRedisplay();
}

// Timer Function
void timer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(msec, timer, 1);
}
