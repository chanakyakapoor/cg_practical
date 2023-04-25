#include <GL/glut.h>
#include <iostream>
using namespace std;
const int INSIDE = 0;              // Binary code for inside region
const int LEFT = 1;                // Binary code for left region
const int RIGHT = 2;               // Binary code for right region
const int BOTTOM = 4;              // Binary code for bottom region
const int TOP = 8;                 // Binary code for top region
double x_min, y_min, x_max, y_max; // Coordinates of the window
double x1, y1, x2, y2;             // Coordinates of the line
// Function to compute the binary code of a point
int computeCode(double x, double y)
{
    int code = INSIDE;
    if (x < x_min)
    { // to the left of rectangle
        code |= LEFT;
    }
    else if (x > x_max)
    { // to the right of rectangle
        code |= RIGHT;
    }
    if (y < y_min)
    { // below the rectangle
        code |= BOTTOM;
    }
    else if (y > y_max)
    { // above the rectangle
        code |= TOP;
    }
    return code;
}
// Function to draw a line using the Cohen-Sutherland algorithm
void cohenSutherland()
{
    // Compute the codes for the endpoints of the line
    int code1 = computeCode(x1, y1);
    int code2 = computeCode(x2, y2);
    // Initialize the flag to indicate if the line is visible or not
    bool visible = false;
    while (true)
    {
        if ((code1 == 0) && (code2 == 0))
        { // both endpoints inside the rectangle
            visible = true;
            break;
        }
        else if (code1 & code2)
        { // both endpoints outside same side of rectangle
            break;
        }
        else
        {
            // Select one of the endpoints that is outside the rectangle
            int code_out;
            double x, y;
            if (code1 != 0)
            {
                code_out = code1;
            }
            else
            {
                code_out = code2;
            }
            // Compute the intersection point of the line with the corresponding edge of the
            // rectangle 
            if (code_out & TOP)
            { // intersection with top edge
                x = x1 + (x2 - x1) * (y_max - y1) / (y2 - y1);
                y = y_max;
            }
            else if (code_out & BOTTOM)
            { // intersection with bottom edge
                x = x1 + (x2 - x1) * (y_min - y1) / (y2 - y1);
                y = y_min;
            }
            else if (code_out & RIGHT)
            { // intersection with right edge
                y = y1 + (y2 - y1) * (x_max - x1) / (x2 - x1);
                x = x_max;
            }
            else
            { // intersection with left edge
                y = y1 + (y2 - y1) * (x_min - x1) / (x2 - x1);
                x = x_min;
            }
            // Replace the endpoint outside the rectangle with the intersection point
            if (code_out == code1)
            {
                x1 = x;
                y1 = y;
                code1 = computeCode(x1, y1);
            }
            else
            {
                x2 = x;
                y2 = y;
                code2 = computeCode(x2, y2);
            }
        }
    }
    if (visible)
    { // if the line is visible, draw it
        glBegin(GL_LINES);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
        glEnd();
    }
}
// Function to display the window
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    // Draw the rectangle
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINE_LOOP);
    // cout << x_max << y_max << x_min << y_min;
    // cout << x1 << x2 << y1 << y2;
    glVertex2d(x_min, y_min);
    glVertex2d(x_min, y_max);
    glVertex2d(x_max, y_max);
    glVertex2d(x_max, y_min);
    glEnd();
    // Draw the line
    glColor3f(0.0, 1.0, 0.0);
    cohenSutherland();
    glFlush();
}
// Function to initialize the window
void init(int xw0, int xw1, int yw0, int yw1, int xl0, int xl1, int yl0, int yl1)
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(0, 640, 0, 480);
    x_min = xw0;
    y_min = yw0;
    x_max = xw1;
    y_max = yw1;
    x1 = xl0;
    y1 = yl0;
    x2 = xl1;
    y2 = yl1;
}
// Main function
int main(int argc, char **argv)
{
    int x_min, x_max, y_min, y_max, x1, x2, y1, y2;
    glClearColor(0.0, 0.0, 0.0, 0.0);
    gluOrtho2D(0, 640, 0, 480);
    cout << "Enter x_min, y_min, x_max, y_max:";
    cin >> x_min;
    cin >> y_min;
    cin >> x_max;
    cin >> y_max;
    cout << "Enter x1, y1, x2, y2:";
    cin >> x1;
    cin >> y1;
    cin >> x2;
    cin >> y2;
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Cohen-Sutherland Algorithm");
    init(x_min, x_max, y_min, y_max, x1, x2, y1, y2);
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}