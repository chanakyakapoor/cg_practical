#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

// function to draw a parabola using Bresenham algorithm
void BresenhamParabola(int a, int b, int h)
{
    int x = 0, y = b;
    int d = 2 * b - a;

    // draw the first point
    glBegin(GL_POINTS);
    glVertex2i(x + h, y);
    glEnd();

    // draw the remaining points using Bresenham algorithm
    while (x <= a)
    {
        x++;
        if (d < 0)
        {
            d += 2 * b;
        }
        else
        {
            d += 2 * (b - a);
            y--;
        }
        // draw the point
        glBegin(GL_POINTS);
        glVertex2i(x + h, y);
        glVertex2i(-x + h, y);
        glEnd();
    }
}

// display function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    BresenhamParabola(40, 80, 100);
    glFlush();
}

// main function
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Bresenham Parabola Drawing");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
