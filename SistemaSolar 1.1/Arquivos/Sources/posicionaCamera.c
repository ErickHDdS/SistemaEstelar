#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>

float xMouse, yMouse;        // (x,y) do ponteiro do mouse
void posicionaCamera(int x, int y) 
{
    xMouse = x;
    yMouse = y;;
    glutPostRedisplay();
}
