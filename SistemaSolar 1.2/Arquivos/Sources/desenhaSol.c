#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../Headers/esfera.h"

float d = 1.0;           // Intensidade da cor difusa da luz branca
float e = 1.0;           // Intensidade da cor especular da luz branca
float m = 0.2;           // Intensidade da luz ambiente global
float p = 1.0;           // A luz branca é posicional?

bool localViewer = false;
bool lightLigada = 1;                     // Luz branca ligada?
float xAngle = 0.0, yAngle = 0.0;        // Rotação da luz branca

float xMouse = 250, yMouse = 250;        // (x,y) do ponteiro do mouse
float larguraJanela, alturaJanela;       // (w,h) da janela

float s;                           // Expoente especular do material (shininess)
float solShine[];                       // expoente especular (shininess)

float anguloSolY = 0;                 // Rotação da esfera em torno do eixo y
int esferaLados = 200;                   // Quantas subdivisões latitudinais/longitudinais da esfera
int solTexture;
bool usarTextura = true;

bool isLightingOn; 

void desenhaSol()
{
   // Propriedades das fontes de luz
    float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
    float lightDif0[] = { d, d, d, 1.0 };
    float lightSpec0[] = { e, e, e, 1.0 };
    float lightPos0[] = { 0.0, 0.0, 3.0, p }; // posicao da fonte de luz
    float globAmb[] = { m, m, m, 1.0 };

    // Propriedades da fonte de luz LIGHT0
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec0);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb);        // Luz ambiente global
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, localViewer);// Enable local viewpoint
    
    // Ativa as fontes de luz (branca)
    if (lightLigada)   
        glEnable(GL_LIGHT0);
    else 
        glDisable(GL_LIGHT0);


    // Limpa a tela e o z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();

    informacoesTela();

    // Posiciona a câmera de acordo com posição x,y do mouse na janela
    gluLookAt(1*(xMouse-larguraJanela/2)/(larguraJanela/16), -1*(yMouse-alturaJanela/2)/(alturaJanela/16) + 3, 5, 0, 0, 0, 0, 1, 0);

    // Desabilita iluminação para desenhar as esferas que representam as luzes
    glDisable(GL_LIGHTING);

    // Light0 e esfera indicativa (ou seta)
    glPushMatrix();
        glRotatef(xAngle, 1.0, 0.0, 0.0); // Rotação no eixo x
        glRotatef(yAngle, 0.0, 1.0, 0.0); // Rotação no eixo y
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
        glTranslatef(lightPos0[0], lightPos0[1], lightPos0[2]);

        glColor3f(d, d, d);

        if (lightLigada)
        {
            if (p) glutWireSphere(0.05, 4, 4); // Esfera indicativa de luz, a ideia que essa esfera seja desenhada dentro do sol, para que o sol seja a fonte de luz
            else // Seta apontando na direção da fonte de luz direcional
            {
                glLineWidth(3.0);
                glBegin(GL_LINES);
                glVertex3f(0.0, 0.0, 0.25);
                glVertex3f(0.0, 0.0, -0.25);
                glVertex3f(0.0, 0.0, -0.25);
                glVertex3f(0.05, 0.0, -0.2);
                glVertex3f(0.0, 0.0, -0.25);
                glVertex3f(-0.05, 0.0, -0.2);
                glEnd();
                glLineWidth(1.0);
            }
        }

    if (isLightingOn) 
        glEnable(GL_LIGHTING);
    else
    {
        glDisable(GL_LIGHTING);
        glDisable(GL_LIGHT0);
    }
    glPopMatrix();


    // Define (atualiza) o valor do expoente de especularidade
    solShine[0] = s;
    glMaterialfv(GL_FRONT, GL_SHININESS, solShine);
    glColor3f(1, 1, 1);

    // Desenha a esfera grande e bem arredondada
    if (usarTextura) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, solTexture);
    }
    glPushMatrix();
        glRotatef(anguloSolY, 0, 1, 0);
        glRotatef(90, 1, 0, 0);
        solidSphere(1.5, esferaLados, esferaLados);

    glPopMatrix();
    if (usarTextura) {
        glDisable(GL_TEXTURE_2D);
    }
}