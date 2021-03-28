#include <GL/glut.h>

void upper_right_quadrant(void)
{
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(1, 1, 0);
    glVertex3f(0, 1, 0);    
}

void lower_right_quadrant(void)
{
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(1, -1, 0);
    glVertex3f(0, -1, 0);   
}

void lower_left_quadrant(void)
{
    glVertex3f(0, 0, 0);
    glVertex3f(0, -1, 0);
    glVertex3f(-1, -1, 0);
    glVertex3f(-1, 0, 0);    
}

void upper_left_quadrant(void)
{
    glVertex3f(0, 0, 0);
    glVertex3f(-1, 0, 0);
    glVertex3f(-1, 1, 0);
    glVertex3f(0, 1, 0);    
}

void displayMe(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POLYGON);

    lower_left_quadrant();

    glEnd();
    glFlush();
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hi there");
    glutDisplayFunc(displayMe);
    glutMainLoop();
    return 0;
}