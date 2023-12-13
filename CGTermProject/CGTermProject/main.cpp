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
float movementvalue = 0.1f;

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