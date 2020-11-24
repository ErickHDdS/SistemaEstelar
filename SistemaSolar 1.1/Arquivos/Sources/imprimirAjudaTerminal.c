#include <stdio.h>

// Imprime a ajuda no terminal
void imprimirAjudaTerminal(void)
{
    printf("Ajuda\n");
    printf("Aperte 'l' para ligar/desligar a iluminacao do OpenGL.\n");
    printf("Aperte 'w' para ligar/desligar a fonte de luz\n");
    printf("Aperte 'd/D' para aumentar/reduzir a intensidade difusa da luz\n");
    printf("Aperte 'e/E' para aumentar/reduzir a intensidade especular da luz\n");
    printf("Aperte 'm/M' para aumentar/reduzir a intensidade da luz ambiente global.\n");
    printf("Aperte 's/S' para aumentar/reduzir o expoente especular do material.\n");
    printf("Aperte 'p' para alternar entre fonte posicional ou direcional.\n");
    printf("Aperte 't' para alternar entre modo com/sem textura.\n");
    printf("Aperte as setas para rotacionar a fonte de luz\n");
}