#include <cstdlib>
#include <time.h>
#include <math.h>
#include <GL/glut.h>

class Object
{
public:
    float posX;
    float posY;
    float rad;
    float dirX;
    float dirY;

    int connectionCount=0;

    bool isConnected = false;
    bool isGrowing = true;

    void drawMe()
    {
        glColor3ub (255, 255, 255);
        /*if(.5>=rad && !isGrowing)
        {
            glBegin(GL_POINTS);
                glVertex2f(posX, posY);
            glEnd();
        }
        else*/
        {
            glBegin(GL_POLYGON);
                for (double i = 0; i < 2 * 3.1416; i += 3.1416 / 50)
                    glVertex2f(posX+cos(i) * rad, posY+sin(i) * rad);
            glEnd();
        }
    }

    void resizeMe()
    {
        if(isGrowing)
            if(rad<2)
                rad+=.0625;
            else
                isGrowing = false;
        else
            if(rad>.5)
                rad-=.0625;
            else
                isGrowing = true;

        // Check if the ball exceeds the edges

        posX += dirX;
        posY += dirY;
        if (posX > 1280)
        {
            posX = 1280;
            dirX = -dirX;
            //dirY = -dirY;
        }
        else if (posX < 0)
        {
            posX = 0;
            dirX = -dirX;
            //dirY = -dirY;
        }

        if (posY > 720)
        {
            posY = 720;
            //dirX = -dirX;
            dirY = -dirY;
        }
        else if (posY < 0)
        {
            posY = 0;
            //dirX = -dirX;
            dirY = -dirY;
        }
    }
};

const int objectCount = 250;

int R = 0;
bool rRising = true;
int G = 0;
bool gRising = true;
int B = 0;
bool bRising = true;

int mouseOldX;
int mouseOldY;

Object ob[objectCount];

void colorMeth()
{
    if(rRising)
        if(R<240)
            R+=1;
        else
            rRising = false;
    else
        if(R>16)
            R-=3;
        else
            rRising = true;

    if(gRising)
        if(G<240)
            G+=2;
        else
            gRising = false;
    else
        if(G>16)
            G-=2;
        else
            gRising = true;

    if(bRising)
        if(B<240)
            B+=3;
        else
            bRising = false;
    else
        if(B>16)
            B-=1;
        else
            bRising = true;
}

void myDisplay(void)
{
    glClear (GL_COLOR_BUFFER_BIT);

    glPushMatrix();
    //glRotatef(5, 540, 0, 960);
    glTranslatef(0, 0, 0);
    float dist = 0;
    colorMeth();
    for(int i = 0; i < objectCount; i++)
    {
        for(int j = 0; j < objectCount; j++)
        {
            dist = sqrt(pow((ob[j].posX-ob[i].posX), 2) + pow((ob[j].posY-ob[i].posY), 2));
            if(dist<50)
            {
                glColor3ub(R, G, B);
                glBegin(GL_LINES);
                    glVertex2f(ob[i].posX, ob[i].posY);
                    glVertex2f(ob[j].posX, ob[j].posY);
                glEnd();
            }
        }
    }

    for(int i = 0; i < objectCount; i++)
    {
            ob[i].drawMe();
            ob[i].resizeMe();
    }
    glPopMatrix();

    glutSwapBuffers();
}

void myTimer(int v)
{
    glutPostRedisplay();
	glutTimerFunc(50, myTimer, 0);
}

void myKeyboard(unsigned char key, int a, int b)
{
    glutDestroyWindow(glutGetWindow());
    exit(0);

	glutPostRedisplay();
}

void myMouse(int x, int y)
{
    if(0 == mouseOldX || 0 == mouseOldY)
    {
        mouseOldX=x;
        mouseOldY=y;
    }
    else if(mouseOldX != x || mouseOldY != y)
    {
        glutDestroyWindow(glutGetWindow());
        exit(0);
    }
}

void myInit (void)
{
    for(int i = 0; i < objectCount; i++)
    {
            //drawMe(rand() % 1280, rand() % 720);
            ob[i].posX = rand() % 1280;
            ob[i].posY = rand() % 720;
            ob[i].rad = rand()%2 + 1;
            ob[i].dirX = (rand()%5 - 2)/7.5;
            ob[i].dirY = (ob[i].dirX)/2.5;
    }

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glLineWidth(0.0125);
    glEnable(GL_LINE_SMOOTH);
    gluOrtho2D(0.0, 1280.0, 0.0, 720.0);
}

void handleResize(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1.1, 501.1);
}

int main(int argc, char** argv)
{
    srand(time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);

    glutInitWindowSize (1280, 720);
    glutInitWindowPosition (100, 100);
    glutCreateWindow("SHAREit Home");
    glutFullScreen();

    glutDisplayFunc(myDisplay);
    glutKeyboardFunc(myKeyboard);
    //glutMouseFunc(myMouse);
    glutPassiveMotionFunc(myMouse);
    glutTimerFunc(0, myTimer, 0);

    myInit ();
    glutMainLoop();

    return 0;
}



