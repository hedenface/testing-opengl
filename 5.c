#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <png.h>

unsigned int width;
unsigned int height;
unsigned char * data = NULL;

png_bytep * read_png_file(char * image_path)
{
    png_bytep * row_pointers = NULL;

    FILE * fp = fopen(image_path, "rb");
    if (fp == NULL) {
        exit(0);
    }

    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (png == NULL || setjmp(png_jmpbuf(png))) {
        abort();
    }

    png_infop info = png_create_info_struct(png);

    png_init_io(png, fp);
    png_read_info(png, info);

    width = png_get_image_width(png, info);
    height = png_get_image_height(png, info);

    if (row_pointers != NULL) {
        abort();
    }

    row_pointers = malloc(sizeof(png_bytep) * height);

    for (unsigned int y = 0; y < height; y++) {
        row_pointers[y] = malloc(png_get_rowbytes(png, info));
    }

    png_read_image(png, row_pointers);

    fclose(fp);

    png_destroy_read_struct(&png, &info, NULL);

    return row_pointers;
}

unsigned char * process_png(png_bytep * row_pointers, int width, int height)
{
    unsigned int x, y;
    unsigned char * data = calloc(width * height * 4, sizeof(unsigned char));
    int i = 0;
    for (y = 0; y < height; y++) {
        png_bytep row = row_pointers[y];
        for (x = 0; x < width; x++) {
            png_bytep px = &(row[x * 4]);
            data[i++] = px[0];
            data[i++] = px[1];
            data[i++] = px[2];
            data[i++] = px[3];
        }
    }

    return data;
}

void display(void)
{
    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

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

void init(void)
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glClearColor(0, 0, 0, 0);
}

void keyboard(unsigned char key, int x, int y)
{
    if (key == 27) {
        exit(0);
    }
}

int main(int argc, char ** argv)
{

    if (argc < 1) {
        printf("%s\n", "First argument needs to be filename of a bitmap.");
        exit(1);
    }

    png_bytep * row_pointers = read_png_file(argv[1]);
    data = process_png(row_pointers, width, height);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Hi there");

    init();

    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
