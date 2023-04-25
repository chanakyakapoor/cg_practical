#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

// function to clip a line using NLN algorithm
void NLNLineClip(float x1, float y1, float x2, float y2, float xmin, float ymin, float xmax, float ymax)
{
    // calculate the slope of the line
    float slope = (y2 - y1) / (x2 - x1);

    // calculate the intersections of the line with the clipping window
    float x0 = x1 + (1 / slope) * (ymin - y1);
    float x3 = x1 + (1 / slope) * (ymax - y1);
    float y0 = y1 + slope * (xmin - x1);
    float y3 = y1 + slope * (xmax - x1);

    // initialize the clipped endpoints
    float xc1 = x1;
    float yc1 = y1;
    float xc2 = x2;
    float yc2 = y2;

    // check if the endpoints lie inside or outside the clipping window
    if (x1 < xmin)
    {
        xc1 = x0;
        yc1 = ymin;
    }
    if (x2 > xmax)
    {
        xc2 = x3;
        yc2 = ymax;
    }
    if (y1 < ymin)
    {
        xc1 = xmin;
        yc1 = y0;
    }
    if (y2 > ymax)
    {
        xc2 = xmax;
        yc2 = y3;
    }

    // draw the clipped line
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(xc1, yc1);
    glVertex2f(xc2, yc2);
    glEnd();
}

// display function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex2f(-0.8, 0.5);
    glVertex2f(0.8, -0.5);
    glEnd();
    NLNLineClip(-0.8, 0.5, 0.8, -0.5, -0.5, -0.5, 0.5, 0.5);
    glFlush();
}

// main function
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Nicholl-Lee-Nicholl Line Clipping");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
