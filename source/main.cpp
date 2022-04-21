// OPENGL FINAL PROJECT
// GROUP 5

// Naufal Hadi Syukrima     (A19EC0272)
// Shafia Carina Saptomo	(A19EC0286)


#include <windows.h>  // MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <math.h>
#include "pack.h"

/* Global variables */
char title[] = "Star Fish";
GLfloat star = 0.0f;     // Rotational angle for DIAMOND [NEW]
int refreshMills = 8;        // refresh interval in milliseconds [NEW]

//x,y,z axis for star rotation
float _x = 0.0f;
float _y = 1.0f;
float _z = 0.0f;

// angle of rotation for the camera direction
float angle = 0.0f;

//actual vector representing the camera's direction
float lx = 0.0f, lz = -1.0f;

// XZ position of the camera
float x = 0.0f, z = 5.0f;

//the key states. These variables will be zero
//when no key is being presses
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

void keyBind(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
    case 'q':
        glEnable(GL_LIGHTING);
        break;
    case 'w':
        glDisable(GL_LIGHTING);
        break;
    case 'a':
        _x = 1.0f;
        _y = 0.0f;
        _z = 0.0f;
        break;
    case 's':
        _x = 0.0f;
        _y = 1.0f;
        _z = 0.0f;
        break;
    case 'd':
        _x = 0.0f;
        _y = 0.0f;
        _z = 1.0f;
        break;
    case 'z':  
        PlaySoundA("C:\\zmisc\\ocean-wave-1.wav", NULL, SND_ASYNC | SND_LOOP | SND_FILENAME);
        break;
    case 'x': //Stop
        PlaySound(NULL, 0, 0);
        break;
        
    }
}

GLuint displayTexture(Image* image)
{
    GLuint textureId;
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexImage2D(GL_TEXTURE_2D,
        0,
        GL_RGB,
        image->width, image->height,
        0,
        GL_RGB,
        GL_UNSIGNED_BYTE,
        image->pixels);
    return textureId;
}

GLuint texture1;
GLuint texture2;
GLuint texture3;
GLuint texture4;
GLuint texture5;

void initTexture()
{
    Image* image1 = loadBMP("C:\\zmisc\\1.bmp");
    texture1 = displayTexture(image1);
    delete image1;

    Image* image2 = loadBMP("C:\\zmisc\\1.bmp");
    texture2 = displayTexture(image2);
    delete image2;

    Image* image3 = loadBMP("C:\\zmisc\\1.bmp");
    texture3 = displayTexture(image3);
    delete image3;

    Image* image4 = loadBMP("C:\\zmisc\\1.bmp");
    texture4 = displayTexture(image4);
    delete image4;
    
    Image* image5 = loadBMP("C:\\zmisc\\1.bmp");
    texture5 = displayTexture(image5);
    delete image5;
}

/* Initialize OpenGL Graphics */
void initGL() {
    glClearColor(0.282, 0.820, 0.800, 0); // Set background color to blue ocean (Med Turqoise) 
    glClearDepth(1.0f);                   // Set background depth to fa0rthest
    glDepthFunc(GL_LEQUAL);    // Set the type of depth-test
    glShadeModel(GL_SMOOTH);   // Enable smooth shading
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);  // Getting the best perspective corrections
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
}

void computePos(float deltaMove) {
    x += deltaMove * lx * 0.1f;
    z += deltaMove * lz * 0.1f;
}

void display() {//To display 3d obj
    if (deltaMove)
        computePos(deltaMove);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);


    // create a object
    glLoadIdentity();
    gluLookAt(x, 1.0f, z,
        x + lx, 1.0f, z + lz,
        0.0f, 1.0f, 0.0f);
    glTranslatef(0.0f, 1.1f, -4.0f);  // Positioning
    glRotatef(star, _x, _y, _z);  // Rotate the object

    //Add ambient light
    GLfloat ambientColor[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat ambientPos[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    //Add positioned light
    GLfloat lightColor0[] = { 0.7f, 0.7f, 0.7f, 0.7f };
    GLfloat lightPos0[] = { 0.0f, 0.0f, -1.0f, 0.0f };
    //Add directed light
    GLfloat lightColor1[] = { 0.2f, 0.1f, 0.1f, 0.1f };
    GLfloat lightPos1[] = { 0.0f, 1.0f, 0.0f, 1.0f };
    //Add ambient
    GLfloat ambientLight[] = { 1.0f, 0.9f, 0.9f, 0.6f };
    GLfloat directedLight[] = { 0.5f, 1.0f, 1.0f, 1.0f };
    GLfloat directedLightPos[] = { 0.0f, 15.0f, 20.0f, 0.0f };

    //Assigning created components
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
    glLightModelfv(GL_POSITION, ambientPos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, directedLight);
    glLightfv(GL_LIGHT0, GL_POSITION, directedLightPos);
    //obj

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texture1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBegin(GL_TRIANGLES);
    glColor3f(0.8f, 0.8f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.451, -0.0423, 0.0f); //c
    glColor3f(0.8f, 0.8f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.255, -0.235, 0.0f); //l front
    glColor3f(0.6f, 0.6f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.059, -0.163, 0.1f); //m
   

    glColor3f(0.8f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.451, -0.0423, 0.0f); //c
    glColor3f(0.8f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.255, -0.235, 0.0f); //l back
    glColor3f(0.6f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.059, -0.163, -0.1f); //m

    glColor3f(1.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.451, -0.042, 0.0f); //c
    glColor3f(0.9f, 0.9f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.182, -0.002, 0.0f); //d front
    glColor3f(1.0f, 1.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.059, -0.163, 0.1f); //m

    glColor3f(0.5f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.451, -0.042, 0.0f); //c
    glColor3f(0.8f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.182, -0.002, 0.0f); //d back
    glColor3f(0.6f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.059, -0.163, -0.1f); //m
    glEnd();


    glBindTexture(GL_TEXTURE_2D, texture2);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBegin(GL_TRIANGLES);
    glColor3f(0.8f, 0.8f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.3, -0.5, 0.0f); //k
    glColor3f(0.8f, 0.8f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.066, -0.376, 0.0f); //j front
    glColor3f(0.6f, 0.6f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.059, -0.163, 0.1f); //m

    glColor3f(0.8f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.3, -0.5, 0.0f); //k
    glColor3f(0.8f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.066, -0.376, 0.0f); //j back
    glColor3f(0.6f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.059, -0.163, -0.1f); //m

    glColor3f(1.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.3, -0.5, 0.0f); //k
    glColor3f(0.9f, 0.9f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.255, -0.235, 0.0f); //l front
    glColor3f(1.0f, 1.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.059, -0.163, 0.1f); //m

    glColor3f(0.5f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.3, -0.5, 0.0f); //k
    glColor3f(0.8f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.255, -0.235, 0.0f); //l back
    glColor3f(0.6f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.059, -0.163, -0.1f); //m
    glEnd();

    glBindTexture(GL_TEXTURE_2D, texture3);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBegin(GL_TRIANGLES);
    glColor3f(0.8f, 0.8f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.177, -0.498, 0.0f); //l
    glColor3f(0.8f, 0.8f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.066, -0.376, 0.0f); //j front
    glColor3f(0.6f, 0.6f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.059, -0.163, 0.1f); //m

    glColor3f(0.8f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.177, -0.498, 0.0f); //l
    glColor3f(0.8f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.066, -0.376, 0.0f); //j back
    glColor3f(0.6f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.059, -0.163, -0.1f); //m

    glColor3f(1.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.177, -0.498, 0.0f); //l
    glColor3f(0.9f, 0.9f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.133, -0.239, 0.0f); //h front
    glColor3f(1.0f, 1.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.059, -0.163, 0.1f); //m

    glColor3f(0.5f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.177, -0.498, 0.0f); //l
    glColor3f(0.8f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.133, -0.239, 0.0f); //h back
    glColor3f(0.6f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.059, -0.163, -0.1f); //m
    glEnd();



    glBindTexture(GL_TEXTURE_2D, texture4);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBegin(GL_TRIANGLES);
    glColor3f(0.8f, 0.8f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.325, -0.047, 0.0f); //g
    glColor3f(0.8f, 0.8f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.133, -0.239, 0.0f); //h front
    glColor3f(0.6f, 0.6f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.059, -0.163, 0.1f); //m

    glColor3f(0.8f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.325, -0.047, 0.0f); //g
    glColor3f(0.8f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.133, -0.239, 0.0f); //h back
    glColor3f(0.6f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.059, -0.163, -0.1f); //m

    glColor3f(1.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.325, -0.047, 0.0f); //g
    glColor3f(0.9f, 0.9f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.061, 0.004, 0.0f); //f front
    glColor3f(1.0f, 1.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.059, -0.163, 0.1f); //m

    glColor3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.325, -0.047, 0.0f); //g
    glColor3f(0.8f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.061, 0.004, 0.0f); //f back
    glColor3f(0.6f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.059, -0.163, -0.1f); //m
    glEnd();



    glBindTexture(GL_TEXTURE_2D, texture5);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBegin(GL_TRIANGLES);
    glColor3f(1.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.061, 0.249, 0.0f); //e
    glColor3f(0.9f, 0.9f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.061, 0.004, 0.0f); //f front
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.059, -0.163, 0.1f); //m

    glColor3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.061, 0.249, 0.0f); //e
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.061, 0.004, 0.0f); //f back
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.059, -0.163, -0.1f); //m

    glColor3f(1.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(-0.061, 0.249, 0.0f); //e
    glColor3f(0.9f, 0.9f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.182, -0.002, 0.0f); //d front
    glColor3f(1.0f, 1.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.059, -0.163, 0.1f); //m

    glColor3f(0.5f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(-0.061, 0.249, 0.0f); //e
    glColor3f(0.8f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(-0.182, -0.002, 0.0f); //d back
    glColor3f(0.6f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(-0.059, -0.163, -0.1f); //m
    glEnd();
    glPopMatrix();


    glDisable(GL_TEXTURE_2D);
    //Draw Eyes
    glPushMatrix();
    glColor3f(0.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 0.05f);
    glutSolidSphere(0.02f, 10, 10);
    glTranslatef(-0.1f, 0.0f, 0.0f);
    glutSolidSphere(0.02f, 10, 10);
    glPopMatrix();

    //Draw Bubble
    glPushMatrix();
    glTranslatef(0.3, -0.3, 0.0);
    glScalef(0.1, 0.1, 0.1);
    //glTranslatef(0.0, 0.0, 0.0);
    glColor3f(0.0f, 0.5f, 0.9f);
    glutSolidSphere(0.2f, 10, 10);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.4, -0.4, 0.0);
    glScalef(0.2, 0.2, 0.2);
    glRotatef(45, 0, 1, 1);
    glColor3f(0.0, 0.5, 0.9);
    glutSolidSphere(0.2f, 15, 15);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5, -0.5, 0.0);
    glScalef(0.3, 0.3, 0.3);
    glRotatef(45, 0, 1, 1);
    glColor3f(0.0, 0.5, 0.9);
    glutSolidSphere(0.2f, 15, 15);
    glPopMatrix();

    //
    glPushMatrix();
    glTranslatef(0.1, 0.1, 0.0);
    glScalef(0.1, 0.1, 0.1);
    glRotatef(45, 0, 1, 1);
    glColor3f(0.0, 0.5, 0.9);
    glutSolidSphere(0.2f, 15, 15);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.2, 0.2, 0.0);
    glScalef(0.2, 0.2, 0.2);
    glRotatef(45, 0, 1, 1);
    glColor3f(0.0, 0.5, 0.9);
    glutSolidSphere(0.2f, 15, 15);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.3, 0.3, 0.0);
    glScalef(0.3, 0.3, 0.3);
    glRotatef(45, 0, 1, 1);
    glColor3f(0.0, 0.5, 0.9);
    glutSolidSphere(0.2f, 15, 15);
    glPopMatrix();

    //
    glPushMatrix();
    glTranslatef(-0.4, -0.3, 0.0);
    glScalef(0.1, 0.1, 0.1);
    glRotatef(45, 0, 1, 1);
    glColor3f(0.0, 0.5, 0.9);
    glutSolidSphere(0.2f, 15, 15);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.5, -0.4, 0.0);
    glScalef(0.2, 0.2, 0.2);
    glRotatef(45, 0, 1, 1);
    glColor3f(0.0, 0.5, 0.9);
    glutSolidSphere(0.2f, 15, 15);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-0.6, -0.5, 0.0);
    glScalef(0.3, 0.3, 0.3);
    glRotatef(45, 0, 1, 1);
    glColor3f(0.0, 0.5, 0.9);
    glutSolidSphere(0.2f, 15, 15);
    glPopMatrix();

    glutSwapBuffers();

    star -= 0.70f;  //rotation speed


}

/* Called back when timer expired [NEW] */
void timer(int value) {
    glutPostRedisplay();      // Post re-paint request to activate display()
    glutTimerFunc(refreshMills, timer, 0); // next timer call (ms)
}

void reshape(GLsizei width, GLsizei height) {  // GLsizei for non-negative integer
    if (height == 0) height = 1;                // To prevent divide by 0
    GLfloat aspect = (GLfloat)width / (GLfloat)height;

    // Set the viewport to cover the new window
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(10.0f, aspect, 0.1f, 100.0f);//setting scale perspective
}


void renderScene(void) {
    if (deltaMove)
        computePos(deltaMove);

    //Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Reset transformations
    glLoadIdentity();

    //Set the camera
    gluLookAt(x, 1.0f, z,
        x + lx, 1.0f, z + lz,
        0.0f, 1.0f, 0.0f);
}

void processNormalKeys(unsigned char key, int xx, int yy) {
    if (key == 27)
        exit(0);
}

void pressKey(int key, int xx, int yy) {
    switch (key) {
    case GLUT_KEY_UP: deltaMove = 0.5f; break;
    case GLUT_KEY_DOWN: deltaMove = -0.5f; break;
    }
}

void releaseKey(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
    case GLUT_KEY_DOWN:
        deltaMove = 0;
        break;
    }
}

void mouseMove(int x, int y) {
    // this will only be true when the left button is down
    if (xOrigin >= 0) {
        // update deltaAngle
        deltaAngle = (x - xOrigin) * 0.001f;

        // update camera's direction
        lx = sin(angle + deltaAngle);
        lz = -cos(angle + deltaAngle);
    }
}

void mouseButton(int button, int state, int x, int y) {
    // only start motion if the left button is pressed
    if (button == GLUT_LEFT_BUTTON) {
        // when the button is released
        if (state == GLUT_UP) {
            angle += deltaAngle;
            xOrigin = -1;
        }
        else // state = GLUT_ DOWN
        {
            xOrigin = x;
        }
    }
}





/* Main function: GLUT runs as a console application starting at main() */
int main(int argc, char** argv) {
    glutInit(&argc, argv);                                      // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   // Enable double buffered mode
    glutInitWindowSize(800, 650);                               // Set the window's initial width & height
    glutInitWindowPosition(50, 50);                             // Position the window's initial top-left corner
    glutCreateWindow(title);                                    // Create window with the given title
    glutDisplayFunc(display);                                   // Register callback handler for window re-paint event
    glutReshapeFunc(reshape);                                   // Register callback handler for window re-size event
    initTexture();                                               // texture initialization
    initGL();                                                   // Our own OpenGL initialization
    glutTimerFunc(0, timer, 0);                                 // First timer call immediately [NEW]

    glutIgnoreKeyRepeat(1);
    glutKeyboardFunc(processNormalKeys);
    glutKeyboardFunc(keyBind);
    glutSpecialFunc(pressKey);
    glutSpecialUpFunc(releaseKey);

    // here are the two new functions
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMove);

    // OpenGL init
    glEnable(GL_DEPTH_TEST);



    glutMainLoop();                     // Enter the infinite event-processing loop
    return 0;
}