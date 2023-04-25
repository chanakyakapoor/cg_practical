#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

// function to draw a line using Mid-Point algorithm
void MidPointLine(int x1, int y1, int x2, int y2)
{
    // calculate the slope of the line
    float m = (float)(y2 - y1) / (float)(x2 - x1);

    // calculate the initial values of x, y, and d
    int x = x1, y = y1;
    int d = (2 * (y1 - y2)) + (x2 - x1);

    // draw the first point
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();

    // draw the remaining points using Mid-Point algorithm
    while (x < x2)
    {
        x++;
        if (d < 0)
        {
            d += 2 * (y1 - y2);
        }
        else
        {
            y++;
            d += 2 * ((y1 - y2) + (x1 - x2));
        }
        // draw the point
        glBegin(GL_POINTS);
        glVertex2i(x, y);
        glEnd();
    }
}

// display function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    MidPointLine(50, 50, 150, 150);
    glFlush();
}

// main function
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Mid-Point Line Drawing");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
