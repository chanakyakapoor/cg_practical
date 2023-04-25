#include <GL/glut.h>
#include <math.h>
// Function to draw an ellipse using Bresenham's algorithm
void drawEllipse(int xCenter, int yCenter, int Rx, int Ry)
{
    int x = 0, y = Ry;
    int p1 = Ry * Ry - Rx * Rx * Ry + Rx * Rx / 4;

    glBegin(GL_POINTS);

    // Region 1
    while (2 * Ry * Ry * x < 2 * Rx * Rx * y)
    {
        glVertex2i(x + xCenter, y + yCenter);
        glVertex2i(-x + xCenter, y + yCenter);
        glVertex2i(x + xCenter, -y + yCenter);
        glVertex2i(-x + xCenter, -y + yCenter);

        if (p1 < 0)
        {
            x++;
            p1 = p1 + 2 * Ry * Ry * x + Ry * Ry;
        }
        else
        {
            x++;
            y--;
            p1 = p1 + 2 * Ry * Ry * x - 2 * Rx * Rx * y - Ry * Ry;
        }
    }

    // Region 2
    int p2 = Ry * Ry * (x + 1 / 2) * (x + 1 / 2) + Rx * Rx * (y - 1) * (y - 1) - Rx * Rx * Ry * Ry;
    while (y >= 0)
    {
        glVertex2i(x + xCenter, y + yCenter);
        glVertex2i(-x + xCenter, y + yCenter);
        glVertex2i(x + xCenter, -y + yCenter);
        glVertex2i(-x + xCenter, -y + yCenter);

        if (p2 > 0)
        {
            y--;
            p2 = p2 - 2 * Rx * Rx * y + Rx * Rx;
        }
        else
        {
            x++;
            y--;
            p2 = p2 + 2 * Ry * Ry * x - 2 * Rx * Rx * y + Rx * Rx;
        }
    }

    glEnd();
}
// Function to display the window
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    // Draw the ellipse with center at (200, 200), Rx = 100, Ry = 50
    drawEllipse(200, 200, 100, 50);

    glFlush();
}
// Main function
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bresenham Ellipse");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(0, 400, 0, 400);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}