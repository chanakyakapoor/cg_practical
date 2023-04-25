#include <iostream>
#include <vector>
#include <GL/glut.h>
    using namespace std;
// Define the clipping window coordinates
int xmin = 50, ymin = 100, xmax = 300, ymax = 300;
// Define the polygon vertices
vector<int> X = {100, 200, 250, 150};
vector<int> Y = {100, 50, 150, 200};
// Define a function to clip a single edge of the polygon
void clipEdge(int x1, int y1, int x2, int y2, int edgeCode)
{
    float m = (float)(y2 - y1) / (x2 - x1);
    if (edgeCode & 1)
    { // clip against left edge
        y1 = y1 + (xmin - x1) * m;
        x1 = xmin;
    }
    if (edgeCode & 2)
    { // clip against bottom edge
        x1 = x1 + (ymin - y1) / m;
        y1 = ymin;
    }
    if (edgeCode & 4)
    { // clip against right edge
        y1 = y1 + (xmax - x1) * m;
        x1 = xmax;
    }
    if (edgeCode & 8)
    { // clip against top edge
        x1 = x1 + (ymax - y1) / m;
        y1 = ymax;
    }
    glVertex2i(x1, y1);
}
// Define a function to clip the polygon against the clipping window
void clipPolygon()
{
    glBegin(GL_LINE_LOOP);
    glVertex2i(xmin, ymin);
    glVertex2i(xmax, ymin);
    glVertex2i(xmax, ymax);
    glVertex2i(xmin, ymax);
    glEnd();
    glBegin(GL_LINE_LOOP);
    glColor3f(0.5, 0.5, 1.0);
    for (int i = 0; i < X.size(); i++)
    {
        int x1 = X[i], y1 = Y[i];
        int x2 = X[(i + 1) % X.size()], y2 = Y[(i + 1) % Y.size()];
        int edgeCode = 0;
        if (x1 < xmin)
            edgeCode |= 1;
        if (y1 < ymin)
            edgeCode |= 2;
        if (x1 > xmax)
            edgeCode |= 4;
        if (y1 > ymax)
            edgeCode |= 8;
        if (edgeCode == 0)
        {
            glVertex2i(x1, y1);
        }
        else
        {
            clipEdge(x1, y1, x2, y2, edgeCode);
        }
    }
    glEnd();
}
// Define the display function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 400.0, 0.0, 400.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    clipPolygon();
    glFlush();
}
// Define the main function
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100); // Set the window position
    glutCreateWindow("Sutherland-Hodgman Clipping");
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}