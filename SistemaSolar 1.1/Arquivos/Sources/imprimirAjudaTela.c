#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>

bool isLightingOn;
long font = (long)GLUT_BITMAP_8_BY_13;   // Fonte usada para imprimir na tela
char theStringBuffer[10];                // String buffer

float d;           // Intensidade da cor difusa da luz branca
float e;           // Intensidade da cor especular da luz branca
float m;           // Intensidade da luz ambiente global
float p;           // A luz branca é posicional?
float s; 

// Escreve uma cadeia de caracteres
void escreveTextoNaTela(void *font, char *string)
{
    char *c;
    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

// Converte um número decimal em string
void floatParaString(char * destStr, int precision, float val)
{
    sprintf(destStr,"%f",val);
    destStr[precision] = '\0';
}

// Escreve as informações variáveis na tela
void informacoesTela(void)
{
    glDisable(GL_LIGHTING); // Desabilita iluminação
    glColor3f(.85f, .85f, .85f);

    glRasterPos3f(-1.0, 1.10, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Iluminacao (l): ");
    escreveTextoNaTela((void*)font, (char*)(isLightingOn ? "ligada" : "desligada"));

    floatParaString(theStringBuffer, 4, m);
    glRasterPos3f(-1.0, 1.00, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Luz ambiente global: ");
    glRasterPos3f(-1.0, 0.95, -2.0);
    escreveTextoNaTela((void*)font, (char*)"  - Intensidade (m/M): ");
    escreveTextoNaTela((void*)font, theStringBuffer);

    glRasterPos3f(-1.0, 0.85, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Luz branca: ");
    glRasterPos3f(-1.0, 0.80, -2.0);
    escreveTextoNaTela((void*)font, (char*)"  - Intensidade difusa (d/D): ");
    floatParaString(theStringBuffer, 4, d);
    escreveTextoNaTela((void*)font, theStringBuffer);
    glRasterPos3f(-1.0, 0.75, -2.0);
    escreveTextoNaTela((void*)font, (char*)"  - Intensidade especular (e/E): ");
    floatParaString(theStringBuffer, 4, e);
    escreveTextoNaTela((void*)font, theStringBuffer);


    glRasterPos3f(-1.0, 0.65, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Material: ");
    glRasterPos3f(-1.0, 0.60, -2.0);
    escreveTextoNaTela((void*)font, (char*)"  - Expoente especular (s/S): ");
    floatParaString(theStringBuffer, 5, s);
    escreveTextoNaTela((void*)font, theStringBuffer);

}