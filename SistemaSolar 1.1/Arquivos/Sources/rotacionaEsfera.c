#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>

float anguloSolY;

//A IDEIA QUE ESSA FUNÇÃO IRÁ ROTACIONAR TODOS ELEMENTOS JUNTOS
void rotacionaEsfera() 
{

    //anguloSolY += .1f;
    glutPostRedisplay();
}