#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <png.h>

unsigned int width_bg;
unsigned int height_bg;
unsigned int width_sprite;
unsigned int height_sprite;
unsigned char * data_bg = NULL;
unsigned char * data_sprite = NULL;

int sprite_x = 0;
int sprite_y = 0;

png_bytep * read_png_file(char * image_path, unsigned int * width, unsigned int * height)
{
    png_byte color_type;
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

    *width = png_get_image_width(png, info);
    *height = png_get_image_height(png, info);

    color_type = png_get_color_type(png, info);

    if (row_pointers != NULL) {
        abort();
    }

    if (color_type == PNG_COLOR_TYPE_RGB) {
        png_set_filler(png, 0xFF, PNG_FILLER_AFTER);
    }

    png_read_update_info(png, info);

    row_pointers = malloc(sizeof(png_bytep) * (*height));

    for (unsigned int y = 0; y < (*height); y++) {
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

void bind_my_texture(unsigned char * data, unsigned int width, unsigned int height, int x, int y)
{
    GLuint texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, texture);
    glEnable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    glTexCoord2i(0, 0);
    glVertex2i(x, y);
    glTexCoord2i(0, 1);
    glVertex2i(x, y + height);
    glTexCoord2i(1, 1);
    glVertex2i(x + width, y + height);
    glTexCoord2i(1, 0);
    glVertex2i(x + width, y);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    bind_my_texture(data_bg, width_bg, height_bg, 0, 0);
    bind_my_texture(data_sprite, width_sprite, height_sprite, sprite_x, sprite_y);

    glFlush();
    glutPostRedisplay();
    glutSwapBuffers();
}

void init(void)
{
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glClearColor(0, 0, 0, 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glOrtho(0, width_bg, 0, height_bg, -1, 0);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    }
}

void specialKeyboard(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        sprite_x++;
        glutPostRedisplay();
        break;

    case GLUT_KEY_RIGHT:
        sprite_x--;
        glutPostRedisplay();
        break;

    case GLUT_KEY_UP:
        sprite_y++;
        glutPostRedisplay();
        break;

    case GLUT_KEY_DOWN:
        sprite_y--;
        glutPostRedisplay();
        break;
    }
}

int main(int argc, char ** argv)
{

    if (argc < 2) {
        printf("%s\n", "First argument needs to be filename of a bitmap (background).");
        printf("%s\n", "First argument needs to be filename of a bitmap (sprite).");
        exit(1);
    }

    png_bytep * row_pointers_bg = read_png_file(argv[1], &width_bg, &height_bg);
    png_bytep * row_pointers_sprite = read_png_file(argv[2], &width_sprite, &height_sprite);

    data_bg = process_png(row_pointers_bg, width_bg, height_bg);
    data_sprite = process_png(row_pointers_sprite, width_sprite, height_sprite);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(width_bg, height_bg);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Hi there");

    init();

    glutKeyboardFunc(keyboard);
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeyboard);

    glutMainLoop();
    return 0;
}
