#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>

/*

    this makes a 2x2 block of different colored pixels like:

    (blue) (black)
    (red)  (green)

*/
GLubyte pixels[16] = { 
    0xff, 0x00, 0x00, 0x00,   0x00, 0xff, 0x00, 0x00,
    0x00, 0x00, 0xff, 0x00,   0x00, 0x00, 0x00, 0x00
};

void display(void)
{
    glRasterPos2i(100, 200);
    glDrawPixels(2, 2, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    glFlush();
}

void init(void)
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glClearColor(0, 0, 0, 0);
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, w, 0, h, -1, 1);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 27) {
        exit(0);
    }
}

int main(int argc, char ** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 300);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Hi there");

    init();

    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}