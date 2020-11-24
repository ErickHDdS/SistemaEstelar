#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include "../Headers/atualizaCena.h"
#include "../Headers/desenhaTelaCena.h"
#include "../Headers/redimensionada.h"
#include "../Headers/teclaPressionada.h"
#include "../Headers/posicionaCamera.h"

int main(int argc, char** argv)
{
   glutInit(&argc, argv);
   glutInitContextVersion(1, 1);
   glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
   glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
   glutInitWindowSize(500, 500);
   glutInitWindowPosition(100, 100);
   glutCreateWindow("SISTEMA ESTELAR");
   setup();

   // Registra callbacks para eventos
   glutDisplayFunc(desenhaTelaCena);
   glutReshapeFunc(redimensionada);
   glutKeyboardFunc(teclaPressionada);


   glutPassiveMotionFunc(posicionaCamera);
   //glutSpecialFunc(specialKeyInput);
   //glutIdleFunc(rotacionaEsfera);

   glutTimerFunc(33, atualizaCena, 0);

   //INICIALIZANDO A MÚSICA DE FUNDO
   //Mix_PlayMusic(musicaDeFundo, -1);
   
   
   glutMainLoop();
   return 0;
}
