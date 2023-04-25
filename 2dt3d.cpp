#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

// object coordinates
float vertices[][2] = {{0, 0}, {50, 0}, {50, 50}, {0, 50}};

// function to draw the object
void drawObject()
{
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 4; i++)
    {
        glVertex2f(vertices[i][0], vertices[i][1]);
    }
    glEnd();
}

// function to perform translation
void translate(float tx, float ty)
{
    for (int i = 0; i < 4; i++)
    {
        vertices[i][0] += tx;
        vertices[i][1] += ty;
    }
}

// function to perform scaling
void scale(float sx, float sy)
{
    for (int i = 0; i < 4; i++)
    {
        vertices[i][0] *= sx;
        vertices[i][1] *= sy;
    }
}

// function to perform rotation
void rotate(float angle)
{
    float rad = angle * 3.14159 / 180.0;
    float cosVal = cos(rad);
    float sinVal = sin(rad);

    for (int i = 0; i < 4; i++)
    {
        float x = vertices[i][0];
        float y = vertices[i][1];

        vertices[i][0] = x * cosVal - y * sinVal;
        vertices[i][1] = x * sinVal + y * cosVal;
    }
}

// display function
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawObject();
    glFlush();
}

// keyboard function to handle transformations
void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 't':
        translate(50, 50);
        break;
    case 's':
        scale(1.5, 1.5);
        break;
    case 'r':
        rotate(45);
        break;
    case 'd':
        translate(-50, -50);
        break;
    case 'n':
        scale(0.5, 0.5);
        break;
    case 'u':
        rotate(-45);
        break;
    }
    glutPostRedisplay();
}

// main function
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("2D Transformations");
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-250, 250, -250, 250);
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
