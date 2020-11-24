#include <GL/glew.h>
#include <GL/freeglut.h>

float larguraJanela, alturaJanela;

void redimensionada(int w, int h)//largura e altura
{
    larguraJanela = w;
    alturaJanela = h;

    glViewport (0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w/(float)h, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}