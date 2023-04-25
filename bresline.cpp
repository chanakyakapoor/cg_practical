#include <GL/glut.h>
#include <iostream>
using namespace std;
int x1, y1, x2, y2;
void backg(void)
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(0.0, 0.5, 1.0);
    glPointSize(10.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}
void plotPoint(int x1, int y1, int x2, int y2)
{
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
}
void bresenham(int x1, int y1, int x2, int y2)
{
    int dx, dy, p, x, y, xp, yp;
    dx = x2 - x1;
    dy = y2 - y1;
    x = x1;
    y = y1;
    xp = x1;
    yp = y1;
    p = 2 * dy - dx;
    while (x < x2)
    {
        if (p >= 0)
        {
            plotPoint(x, y, xp, yp);
            xp = x;

            yp = y;
            y = y + 1;
            p = p + 2 * dy - 2 * dx;
        }
        else
        {
            plotPoint(x, y, xp, yp);
            xp = x;
            yp = y;
            p = p + 2 * dy;
        }
        x = x + 1;
    }
}
void line()
{
    glClear(GL_COLOR_BUFFER_BIT);
    bresenham(x1, y1, x2, y2);
    glLoadIdentity();
    glFlush();
}
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(min(x1, x2) - 1, max(x1, x2) + 1, min(y1, y2) - 1, max(y1, y2) + 1);
    glMatrixMode(GL_MODELVIEW);
}
int main(int argc, char **argv)
{
    cin >> x1 >> y1 >> x2 >> y2;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Bresenham Line");
    backg();
    glutDisplayFunc(line);
    glutReshapeFunc(reshape);

    glutMainLoop();
}