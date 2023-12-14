#include "stdafx.h"
#include "shaders.h"
#include "character.h"
#include "camera.h"
#include "blockMgr.h"

#include "bg.h"

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid keyboardUp(unsigned char key, int x, int y);
GLvoid keyboardDown(unsigned char key, int x, int y);
void init();

void blockMovingTimer(int value);

GLclampf g_color[4] = { 0.2f, 0.2f, 0.2f, 1.0f };

// shader variables
GLuint shaderProgramID;

character LEGO;
Camera camera;
BG bg;
BlockMgr blocks;

float angle;
float movementvalue = 0.05f;
bool blockMoving = true;

void player_movement(int);
void yAxisMovementTimer(int value);
bool robotJump = false;
bool jumpdown = false;

bool aleft = false;
bool dright = false;
bool wfront = false;
bool sback = false;

float jumpPos = 0.f;

int score = 100;


void welcomeDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.933333, 0.913725, 0.913725);
    glRasterPos3f(-1, 0.5, 0);
    char msg0[] = "* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *";
    for (int i = 0; i < strlen(msg0); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg0[i]);
    }

    glColor3f(0.529412, 0.807843, 0.980392);
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

    std::cout << "Playing music \n";
    PlaySound(TEXT("audio.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    //std::string input;
    //std::getline(std::cin, input);
    //PlaySound(0, 0, 0);
    //std::cout << "Stopped music \n";

    //std::getline(std::cin, input);
    //std::cout << "Playing music \n";
    //PlaySound(TEXT("audio.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    //std::getline(std::cin, input);


    glutSwapBuffers();
}

void EndScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(0.933333, 0.913725, 0.913725);
    glRasterPos3f(-1, 0.5, 0);
    char msg0[] = "* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *";
    for (int i = 0; i < strlen(msg0); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg0[i]);
    }

    glColor3f(0.529412, 0.807843, 0.980392);
    glRasterPos3f(-0.2, 0.1, 0);
    char msg1[] = "The End";
    for (int i = 0; i < strlen(msg1); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, msg1[i]);
    }

    glColor3f(0.545098, 0.513725, 0.470588);
    glRasterPos3f(-0.15, -0.2, 0);
    char msg2[] = "Game Over";
    for (int i = 0; i < strlen(msg2); i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg2[i]);
    }
    glColor3f(0.545098, 0.513725, 0.470588);
    glRasterPos3f(-0.12, -0.25, 0);
    char msg3[] = "your score is Zer0!!";
    for (int i = 0; i < strlen(msg3); i++) {
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, msg3[i]);
    }

    glColor3f(0.933333, 0.913725, 0.913725);
    glRasterPos3f(-1, -0.5, 0);
    char msg4[] = "* ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ * ~ *";
    for (int i = 0; i < strlen(msg4); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, msg4[i]);
    }
    //std::string input;
    //std::getline(std::cin, input);
    //PlaySound(0, 0, 0);
    //std::cout << "Stopped music \n";

    //std::getline(std::cin, input);
    //std::cout << "Playing music \n";
    //PlaySound(TEXT("audio.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    //std::getline(std::cin, input);


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

    blocks.initList();

    init();

    

    glutKeyboardUpFunc(keyboardUp);
    glutKeyboardFunc(keyboardDown);

    glutDisplayFunc(welcomeDisplay); //opening

    //glutDisplayFunc(drawScene);

    glutReshapeFunc(Reshape);
    glutMainLoop();
}

GLvoid drawScene()
{
    glClearColor(g_color[0], g_color[1], g_color[2], g_color[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //glUseProgram(shaderProgramID);

    // 블록 <-> 캐릭터 충돌체크
    if (blocks.checkCollision(LEGO.getPos()).getPos() == glm::vec3(-10, -10, -10)) {
        LEGO.setPosY(LEGO.getPos().y - 0.01f);
    }
    else {
        if (LEGO.getPos().y <= blocks.checkCollision(LEGO.getPos()).getPos().y + blocks.checkCollision(LEGO.getPos()).getScale().y)
            LEGO.setPosY(blocks.checkCollision(LEGO.getPos()).getPos().y + blocks.checkCollision(LEGO.getPos()).getScale().y);
        else
            if (!robotJump && !jumpdown)
                LEGO.setPosY(blocks.checkCollision(LEGO.getPos()).getPos().y + blocks.checkCollision(LEGO.getPos()).getScale().y);
            else
                LEGO.setPosY(LEGO.getPos().y - 0.01f);
    }

    // 카메라 시점 -> 캐릭터에게 고정
    camera.setEye(glm::vec3(LEGO.getPos().x, LEGO.getPos().y + 5.f, LEGO.getPos().z + 10.f));
    camera.setTarget(glm::vec3(LEGO.getPos().x, LEGO.getPos().y, LEGO.getPos().z));

    bg.render(shaderProgramID);
    camera.setCamera(shaderProgramID);
    LEGO.render(shaderProgramID);
    blocks.render(shaderProgramID);

    //cout << LEGO.getPos().x << ", " << LEGO.getPos().y << ", " << LEGO.getPos().z << endl;


    glutSwapBuffers();

    //if (score < 90) {
    //    glutDisplayFunc(EndScene);
    //    glutIdleFunc(drawScene);
    //}
}

GLvoid Reshape(int w, int h)
{
    glViewport(0, 0, 800, 800);
}

GLvoid keyboardDown(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'x':
    case 'X':
        glutDisplayFunc(drawScene);
        glutTimerFunc(50, blockMovingTimer, 1);
        glutTimerFunc(1000 / 60, player_movement, 0);
        break;

    case 'r':
        angle = LEGO.getRotate().y;
        LEGO.setRotateY(angle + 10);
        break;

    case 'a':
        aleft = true;
        break;
    case 'd':
        dright = true;
        break;
    case 'w':
        wfront = true;
        break;
    case 's':
        sback = true;
        break;

    case 'f': //jump
        if (robotJump) break;
        robotJump = true;
        jumpPos = LEGO.getPos().y;
        break;


    case 'Q':
    case 'q':
        exit(0);
        break;
    }
    glutPostRedisplay();
}

GLvoid keyboardUp(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'a':
        aleft = false;
        break;
    case 'd':
        dright = false;
        break;
    case 'w':
        wfront = false;
        break;
    case 's':
        sback = false;
        break;
    }
    glutPostRedisplay();
}

void player_movement(int value)
{
    if (aleft) {
        LEGO.setPosX(LEGO.getPos().x - movementvalue);
    }
    else if (dright) {
        LEGO.setPosX(LEGO.getPos().x + movementvalue);
    }
    if (wfront) {
        LEGO.setPosZ(LEGO.getPos().z - movementvalue);
    }
    else if (sback) {
        LEGO.setPosZ(LEGO.getPos().z + movementvalue);
    }

    if (robotJump) {
        LEGO.setPosY(LEGO.getPos().y + 0.1);
        //cout << LEGO.getPos().y << endl;

        if (jumpPos + 1.0f < LEGO.getPos().y) {
            robotJump = false;
        }
    }
    if (!robotJump)
        LEGO.setPosY(LEGO.getPos().y - 0.05);

    if (LEGO.getPos().y < -10) {
        LEGO.setPos(glm::vec3(-10.f, 0.0f, 10.f));
        if (score >0) {
            score -= 10;
            cout << score << endl;
            if (score == 0) {
                cout << "Your score is zer0\n Game Over!!" << endl;
                exit(0);
            }
        }
        
    }

    glutTimerFunc(1000 / 60, player_movement, value);
}

void init()
{
    bg.initBuffer();
    bg.initTexture();
}

void blockMovingTimer(int value)
{
    if (blockMoving)
    {
        blocks.moveAllBlocks();
        glutTimerFunc(50, blockMovingTimer, 1);
    }
    glutPostRedisplay();
}

void yAxisMovementTimer(int value)
{
    //aleft = false;
    //dright = false;
    //wfront = false;
    //sback = false;

    if (robotJump) {
        if (aleft) {
            // LEGO.setPosX(LEGO.getPos().x - movementvalue);
            LEGO.setPosY(LEGO.getPos().y + value * (0.05));
        }
        else if (dright) {
            // LEGO.setPosX(LEGO.getPos().x + movementvalue);
            LEGO.setPosY(LEGO.getPos().y + value * (0.05));
        }
        else if (wfront) {
            // LEGO.setPosZ(LEGO.getPos().z - movementvalue);
            LEGO.setPosY(LEGO.getPos().y + value * (0.05));
        }
        else if (sback) {
            // LEGO.setPosZ(LEGO.getPos().z + movementvalue);
            LEGO.setPosY(LEGO.getPos().y + value * (0.05));
        }
        else LEGO.setPosY(LEGO.getPos().y + value * (0.05));
        //cout << LEGO.getPos().y << endl;

        if (LEGO.getPos().y > 1.0f) {
            robotJump = false;
            jumpdown = true;
            glutTimerFunc(25, yAxisMovementTimer, value);
        }

        else {
            glutTimerFunc(25, yAxisMovementTimer, value);
        }

    }
    if (jumpdown)
    {
        if (aleft) {
            // LEGO.setPosX(LEGO.getPos().x - movementvalue);
            LEGO.setPosY(LEGO.getPos().y + value * (-0.05));
        }
        else if (dright) {
            // LEGO.setPosX(LEGO.getPos().x + movementvalue);
            LEGO.setPosY(LEGO.getPos().y + value * (-0.05));
        }
        else if (wfront) {
            // LEGO.setPosZ(LEGO.getPos().z - movementvalue);
            LEGO.setPosY(LEGO.getPos().y + value * (-0.05));
        }
        else if (sback) {
            // LEGO.setPosZ(LEGO.getPos().z + movementvalue);
            LEGO.setPosY(LEGO.getPos().y + value * (-0.05));
        }
        else LEGO.setPosY(LEGO.getPos().y + value * (-0.05));

        if (LEGO.getPos().y > 0.f) {
            glutTimerFunc(25, yAxisMovementTimer, value);
        }
        else if (LEGO.getPos().y <= 0.f) {
            jumpdown = !jumpdown;
            //cout << "jump 끝" << endl;
        }
    }
    glutPostRedisplay();
}