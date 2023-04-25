#include <GL/glut.h>
#include <cmath>
void drawCircle(int x0, int y0, int radius)
{
    int x = 0;
    int y = radius;
    int d = 3 - 2 * radius;
    while (x <= y)
    {
        glVertex2i(x + x0, y + y0);
        glVertex2i(y + x0, x + y0);
        glVertex2i(-x + x0, y + y0);
        glVertex2i(-y + x0, x + y0);
        glVertex2i(-x + x0, -y + y0);
        glVertex2i(-y + x0, -x + y0);
        glVertex2i(x + x0, -y + y0);
        glVertex2i(y + x0, -x + y0);
        if (d < 0)
        {
            d += 4 * x + 6;
        }
        else
        {
            d += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    glColor3f(1.0f, 1.0f, 1.0f);
    int x0 = 200;
    int y0 = 200;
    int radius = 100;
    drawCircle(x0, y0, radius);
    glEnd();
    glFlush();
}
void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 400.0, 0.0, 400.0);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham's Circle Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}