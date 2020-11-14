#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <math.h>

#include "../Headers/setup.h"
#include "../Headers/redimensionada.h"
#include "../Headers/imprimirAjudaTerminal.h"
#include "../Headers/teclaPressionada.h"
#include "../Headers/teclaEspecialPressionada.h"
#include "../Headers/desenhaTelaCena.h"
#include "../Headers/esfera.h"
#include "../Headers/rotacionaEsfera.h"

float xMouse, yMouse;        // (x,y) do ponteiro do mouse

void posicionaCamera(int x, int y) {
    xMouse = x;
    yMouse = y;;
    glutPostRedisplay();
}


int main(int argc, char *argv[])
{
    imprimirAjudaTerminal();
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    //glutInitWindowPosition (100, 100);
    glutCreateWindow("Luz e Materiais");
    glutDisplayFunc(desenhaTelaCena);
    glutReshapeFunc(redimensionada);
    glutKeyboardFunc(teclaPressionada);
    glutPassiveMotionFunc(posicionaCamera);
    glutSpecialFunc(teclaEspecialPressionada);
   // glutIdleFunc(rotacionaEsfera);

    setup();

    glutMainLoop();
}
