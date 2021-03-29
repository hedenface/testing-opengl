#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>

int width = 64;
int height = 64;
unsigned char * data = NULL;

void load_image_data(const char * image_path)
{
    FILE * file = fopen(image_path, "rb");

    if (file == NULL) {
        printf("Unable to open <%s>!\n", image_path);
        exit(1);
    }

    data = calloc(width * height * 3, sizeof(unsigned char));

    fread(data, width * height * 3, 1, file);
    fclose(file);
}

void display(void)
{
    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_BGR, GL_UNSIGNED_BYTE, data);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_BGR, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    glMatrixMode(GL_PROJECTION);
    glOrtho(0, width, 0, height, -1, 0);

    glClear(GL_COLOR_BUFFER_BIT);

    glBindTexture(GL_TEXTURE_2D, texture);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2i(0, 0);
    glVertex2i(0, 0);
    glTexCoord2i(0, 1);
    glVertex2i(0, height);
    glTexCoord2i(1, 1);
    glVertex2i(width, height);
    glTexCoord2i(1, 0);
    glVertex2i(width, 0);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
    glFlush();
}

int main(int argc, char ** argv)
{
    load_image_data("squares.bmp");

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Squares!");

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glClearColor(0, 0, 0, 0);

    glutDisplayFunc(display);

    glutMainLoop();

    free(data);
    return 0;
}
