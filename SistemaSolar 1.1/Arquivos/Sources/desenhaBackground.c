#include <GL/glew.h>
#include <GL/freeglut.h>
#include <SOIL/SOIL.h>
#include "../Headers/setup.h"

GLuint idBackground;
//GLuint idSol;

//fundo da cena


void desenhabackground()
{
    glColor3f(1.0, 1.0, 1.0);//BRANCO
    glMatrixMode(GL_TEXTURE);
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();

    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
     // Habilita o uso de texturas
    glEnable(GL_TEXTURE_2D);
    // Começa a usar a textura que criamos
    glBindTexture(GL_TEXTURE_2D, idBackground);
        glBegin(GL_TRIANGLE_FAN);
        glTexCoord2f(0, 0);
        glVertex3f(0, 0, 1); // v3---v2
        glTexCoord2f(1, 0);
        glVertex3f(100, 0, 1); // |     |
        glTexCoord2f(1, 1);
        glVertex3f(100, 100, 1); // |     |
        glTexCoord2f(0, 1);
        glVertex3f(0,  100, 1); // v0---v1
    glEnd();
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();
}
