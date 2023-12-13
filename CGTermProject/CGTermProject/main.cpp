#include "stdafx.h"
#include "shaders.h"
#include "character.h"
#include "camera.h"

#include "bg.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid keyboard(unsigned char key, int x, int y);
void init();

GLclampf g_color[4] = { 0.2f, 0.2f, 0.2f, 1.0f };

// shader variables
GLuint shaderProgramID;

character LEGO;
Camera camera;
BG bg;

float angle;
float movementvalue = 0.1f;

void welcomeDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.933333, 0.913725, 0.913725);
    glRasterPos3f(-1, 0.5, 0);
    char msg0[] = "* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *";
    for (int i = 0; i < strlen(msg0); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg0[i]);
    }

    glColor3f(0.529412,	0.807843, 0.980392);
    glRasterPos3f(-0.2, 0.1, 0);
    char msg1[] = "Let's Winter!!";
    for (int i = 0; i < strlen(msg1); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);
    }

    glColor3f(0.545098, 0.513725, 0.470588);
    glRasterPos3f(-0.15, -0.2, 0);
    char msg2[] = "Game Start";
    for (int i = 0; i < strlen(msg2); i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]);
    }
    glColor3f(0.545098, 0.513725, 0.470588);
    glRasterPos3f(-0.12, -0.25, 0);
    char msg3[] = "press X";
    for (int i = 0; i < strlen(msg3); i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg3[i]);
    }

    glColor3f(0.933333, 0.913725, 0.913725);
    glRasterPos3f(-1, -0.5, 0);
    char msg4[] = "* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *";
    for (int i = 0; i < strlen(msg4); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg4[i]);
    }

    
    glutSwapBuffers();
}

void main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Let's Winter!");
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Unable to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    else
        std::cout << "GLEW Initialized" << std::endl;

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    shaderProgramID = initShader("vertex.vert", "fragment.frag");
    
    LEGO.initBuffer();
    LEGO.initTexture();
    init();

    
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(welcomeDisplay); //opening
    //glutDisplayFunc(drawScene);
    glutReshapeFunc(Reshape);
    glutMainLoop();
}

GLvoid drawScene()
{
    glClearColor(g_color[0], g_color[1], g_color[2], g_color[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shaderProgramID);
    
    camera.setCamera(shaderProgramID);
    LEGO.render(shaderProgramID);
    bg.render(shaderProgramID);
    
    glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
    glViewport(0, 0, 800, 800);
}

GLvoid keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'x':
    case 'X':
        glutDisplayFunc(drawScene);
        break;

    case 'r':
        angle = LEGO.getRotate().y;
        LEGO.setRotateY(angle + 10);
        break;

    case 'a':
        LEGO.setPosX(LEGO.getPos().x - movementvalue);
        break;
    case 'd':
        LEGO.setPosX(LEGO.getPos().x + movementvalue);
        break;
    case 'w':
        LEGO.setPosZ(LEGO.getPos().z - movementvalue);
        break;
    case 's':
        LEGO.setPosZ(LEGO.getPos().z + movementvalue);
        break;
    case 'j':
        break;

    case 'Q':
    case 'q':
        exit(0);
        break;
    }
    glutPostRedisplay();
}

void init()
{
    bg.initBuffer();
    bg.initTexture();
}