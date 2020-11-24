#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <time.h>

#include "../Headers/desenhaTelaCena.h"
#include "../Headers/rotacionaEsfera.h"


int controleEstrela; //PARA FAZER ANIMAÇÕES DE ESTRELA
float anguloSolY;

void atualizaCena(int valorQualquer)
{
        controleEstrela++;
        glutIdleFunc(rotacionaEsfera);
        glutPostRedisplay();

    glutTimerFunc(33, atualizaCena, 0);//33
}
