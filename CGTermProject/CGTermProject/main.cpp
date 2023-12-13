#include "stdafx.h"
#include "shaders.h"
#include "character.h"
#include "camera.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid keyboard(unsigned char key, int x, int y);

GLclampf g_color[4] = { 0.2f, 0.2f, 0.2f, 1.0f };

// shader variables
GLuint shaderProgramID;

character LEGO;
Camera camera;

float angle;

float moveLeftRight = 0.f;
float moveBackForth = 0.f;
float moveUpDown = 0.f;
float rotationAngle = 0.f;

void xAxisMovementTimer(int value);
void zAxisMovementTimer(int value);
void yAxisMovementTimer(int value);
bool robotMovement = false;
bool robotJump = false;

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

    glutKeyboardFunc(keyboard);
    glutDisplayFunc(drawScene);
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
    case 'r':
        angle = LEGO.getRotate().y;
        LEGO.setRotateY(angle + 10);
        break;

    case 'a':
        rotationAngle = glm::radians(-90.0f);
        glutTimerFunc(50, xAxisMovementTimer, -1);
        break;
    case 'd':
        rotationAngle = glm::radians(90.0f);
        glutTimerFunc(50, xAxisMovementTimer, 1);
        break;
    case 'w':
        rotationAngle = glm::radians(180.0f);
        glutTimerFunc(50, zAxisMovementTimer, -1);
        break;
    case 's':
        rotationAngle = glm::radians(0.0f);
        glutTimerFunc(50, zAxisMovementTimer, 1);
        break;
    case 'j':
        glutTimerFunc(50, yAxisMovementTimer, 1);
        break;

    case 'Q':
    case 'q':
        exit(0);
        break;
    }
    glutPostRedisplay();
}

void xAxisMovementTimer(int value)
{  
    moveLeftRight += value;

    glutPostRedisplay();

    if (moveLeftRight > 5.f || moveLeftRight < -5.f) {
        rotationAngle += glm::radians(180.0f);
        glutTimerFunc(50, xAxisMovementTimer, -value);
    }
    else
        glutTimerFunc(50, xAxisMovementTimer, value);
}

void zAxisMovementTimer(int value)
{
    moveBackForth += value;

    glutPostRedisplay();

    if (moveBackForth > 5.f || moveBackForth < -5.f) {
        rotationAngle += glm::radians(180.0f);
        glutTimerFunc(50, zAxisMovementTimer, -value);
    }
    else
        glutTimerFunc(50, zAxisMovementTimer, value);
}

void yAxisMovementTimer(int value)
{
    moveUpDown += value * 0.2f;
    std::cout << "jump: " << moveUpDown << std::endl;

    glutPostRedisplay();

    if (moveUpDown > 2.f) {
        glutTimerFunc(50, yAxisMovementTimer, -value);
    }
    else if (moveUpDown > 0.f)
        glutTimerFunc(50, yAxisMovementTimer, value);

}