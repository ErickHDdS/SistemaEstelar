#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include "../Headers/carregaTextura.h"
#include <stdio.h>
#include <math.h>
#include <stdio.h>


GLuint idBackground,idEstrela;
int marsTexture;
const float s = 50.0;                      // Expoente especular do material (shininess)
float matShine[] = { s };                      // expoente especular (shininess)


void setup()//CARREGA TODAS AS TEXTURAS
{
    glClearColor(0, 0, 0, 0.0);

    // habilita o depth buffer para que a coordenada Z seja usada
    glEnable(GL_DEPTH_TEST);

    // Propriedades do material da esfera
    float matAmbAndDif[] = {1.0, 1.0, 1.0, 1.0};    // cor ambiente e difusa: branca
    float matSpec[] = { 1.0, 1.0, 1,0, 1.0 };       // cor especular: branca

    // Definindo as propriedades do material
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Carrega a textura
    marsTexture = SOIL_load_OGL_texture
	(
		"../Img/sol.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    if(marsTexture == 0)
    {
        printf("Erro do SOIL: '%s'\n", SOIL_last_result());
    }

    // Não mostrar faces do lado de dentro
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Esconder o ponteiro do mouse quando dentro da janela
    //glutSetCursor(GLUT_CURSOR_NONE);
    idBackground = carregaTextura("../Img/background.png");
    idEstrela = carregaTextura("../Img/star.png");


}
