#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include "../Headers/desenhaBackground.h"
#include "../Headers/desenhaEstrela.h"

#include "../Headers/desenhaSol.h"

int controleEstrela = 0; //CONTROLE PARA ANIMAR A TELA

void desenhaTelaCena()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    //Desenhos
    desenharEstrelas();
    desenhabackground();
    desenhaSol();

    glutSwapBuffers();
}

void desenharEstrelas()
{
  int x,y;
  if(controleEstrela == 33)//DESENHANDO UMAS ESTRELAS ALEATORIAMENTE 1 VEZES POR SEGUNDO
  {
    srand(time(0)); // SORTEANDO DENTRO DA JANELA UMA POSICAO PARA A ESTRELA SER DESENHADA
    x = rand()%99;
    y = rand()%99;
    controleEstrela=0; // ZERANDO PARA REDESENHAR NOVAS ESTRELAS
    desenhaEstrela(x,y);
  }
}
