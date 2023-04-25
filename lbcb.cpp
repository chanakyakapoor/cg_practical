#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

// Liang Barsky line clipping algorithm
bool LiangBarsky(int x1, int y1, int x2, int y2, int xmin, int ymin, int xmax, int ymax, float &t1, float &t2)
{
    int dx = x2 - x1, dy = y2 - y1;
    float p[4] = {-dx, dx, -dy, dy};
    float q[4] = {x1 - xmin, xmax - x1, y1 - ymin, ymax - y1};
    float u1 = 0.0, u2 = 1.0;

    for (int i = 0; i < 4; i++)
    {
        if (p[i] == 0.0)
        {
            if (q[i] < 0)
            {
                return false;
            }
        }
        else
        {
            float t = q[i] / p[i];
            if (p[i] < 0)
            {
                u1 = max(u1, t);
            }
            else
            {
                u2 = min(u2, t);
            }
        }
    }

    if (u1 > u2)
    {
        return false;
    }

    t1 = u1;
    t2 = u2;
    return true;
}

// function to draw a clipped line using Liang Barsky algorithm
void drawClippedLine(int x1, int y1, int x2, int y2, int xmin, int ymin, int xmax, int ymax)
{
    float t1, t2;
    bool result = LiangBarsky(x1, y1, x2, y2, xmin, ymin, xmax, ymax, t1, t2);

    if (result)
    {
        int xc1 = x1 + t1 * (x2 - x1);
        int yc1 = y1 + t1 * (y2 - y1);
        int xc2 = x1 + t2 * (x2 - x1);
        int yc2 = y1 + t2 * (y2 - y1);

        glBegin(GL_LINES);
        glVertex2i(xc1, yc1);
        glVertex2i(xc2, yc2);
        glEnd();
    }
}

// display function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    drawClippedLine(50, 50, 150, 150, 75, 75, 125, 125);
    glFlush();
}

// main function
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Liang Barsky Line Clipping");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
