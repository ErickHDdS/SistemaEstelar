#include <GL/glew.h>
#include <GL/freeglut.h>
#include <stdlib.h>
#include <stdbool.h>

#include <stdio.h>
#include "../Headers/desenhaTelaCena.h"


int controleLight;

bool lightLigada;


float d;           // Intensidade da cor difusa da luz branca
float e;           // Intensidade da cor especular da luz branca
float m;           // Intensidade da luz ambiente global
float p;           // A luz branca é posicional?
float s;          // Expoente especular do material (shininess)


bool usarTextura;
bool localViewer;
bool isLightingOn = true;               // O sistema de iluminação está ligado?

// Callback do evento de teclado
void teclaPressionada(unsigned char key, int x, int y)
{
    // vê qual tecla foi pressionada
    switch (key)
    {
    case 27:
        exit(0);
        break;
        
    case 'w':
    case 'W':
        if (lightLigada) lightLigada = false;
        else lightLigada = true;
        break;
    
    case 'p':
    case 'P':
        if (p) p = 0.0;
        else p = 1.0;
        break;

    case 'd':
        if (d > 0.0) d -= 0.05;
        break;
    case 'D':
        if (d < 1.0) d += 0.05;
        break;

    case 'e':
        if (e > 0.0) e -= 0.05;
        break;
    case 'E':

        if (e < 1.0) e += 0.05;
        break;
    case 's':
        if (s > 5.0) s -= 2.00;
        break;
    case 'S':
        if (s < 100.0) s += 2.00;
        break;

    case 'm':
        if (m > 0.0) m -= 0.05;
        break;
    case 'M':
        if (m < 1.0) m += 0.05;
        break;

    case 'l':
    case 'L':
        controleLight *= (-1);
        isLightingOn = !isLightingOn;
        break;

    case 't':
    case 'T':
        usarTextura = !usarTextura;
        break;

    case 'v':
    case 'V':
        localViewer = !localViewer;
        break;

    default:
        break;
    }
    glutPostRedisplay();
    
}
