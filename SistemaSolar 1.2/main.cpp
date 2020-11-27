#include <iostream>
#include <fstream>
#include <SOIL/SOIL.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>    

#include "Headers/planetas.h"
//#include "Headers/musica.h"

using namespace std;

static bool light0Ligada = 1;   // Luz branca ligada?
static float IntensidadeDifusa = 1.0;           // Intensidade da cor difusa da luz branca
static float IntensidadeEspecular = 1.0;           // Intensidade da cor especular da luz branca
static float IntensidadeLuzAmbiente = 0.2;           // Intensidade da luz ambiente global
static float LuzPosicional = 1.0;           // A luz branca é posicional?
static float ExpoenteEspecular = 50.0;          // Expoente especular do material (shininess)
static float VelocidadeTranslacao = 900.0;           // Velocidade de translação
static float VelocidadeRotacao = 100.0;          // Velocidade de rotação
float matShine[] = { ExpoenteEspecular };                       // expoente especular (shininess)
static float xAngle = 0.0, yAngle = 0.0;        // Rotação da luz branca
static long font = (long)GLUT_BITMAP_8_BY_13;   // Fonte usada para imprimir na tela
static char theStringBuffer[10];                // String buffer
static float larguraJanela, alturaJanela;       // (w,h) da janela
static bool isLightingOn = true;               // O sistema de iluminação está ligado?
static int esferaLados = 2000;                   // Quantas subdivisões latitudinais/longitudinais da esfera
static bool localViewer = false;
static int sunTexture, mercurioTexture, venusTexture, terraTexture, marteTexture, jupiterTexture, saturnoTexture, uranoTexture, neturnoTexture, plutaoTexture;
static bool usarTextura = true;

int camera = 1;
int zoomPlaneta = 120;
int eixoY = 0;
int eixoX = 0;

static float xMouse = 250, yMouse = 250;        // (x,y) do ponteiro do mouse
Planeta sol,mercurio,venus,terra,marte,jupiter,saturno,urano,neturno,plutao;

Mix_Music *musicaDeFundo;


void inicializarMusica()
{
    SDL_Init( SDL_INIT_AUDIO);
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 1024 ); //- inicializa SDL_Mixer
    atexit(Mix_CloseAudio);
}

void carregarMusica()
{
    musicaDeFundo = Mix_LoadMUS("star_wars.mp3");
    if(musicaDeFundo == NULL)
      cout << "nada" << endl;
}

// Escreve uma cadeia de caracteres
void escreveTextoNaTela(void *font, char *string){
    char *c;
    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

// Converte um número decimal em string
void floatParaString(char * destStr, int precision, float val){
    sprintf(destStr,"%f",val);
    destStr[precision] = '\0';
}

// Escreve as informações variáveis na tela
void informacoesTela(void){
    glDisable(GL_LIGHTING); // Desabilita iluminação
    glColor3f(1, 1, 1);

    glRasterPos3f(-1.0, 1.10, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Iluminacao (l): ");
    escreveTextoNaTela((void*)font, (char*)(isLightingOn ? "ligada" : "desligada"));
    floatParaString(theStringBuffer, 4, IntensidadeLuzAmbiente);

    glRasterPos3f(-1.0, 1.00, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Luz ambiente global: ");
    glRasterPos3f(-1.0, 0.95, -2.0);
    escreveTextoNaTela((void*)font, (char*)"  - Intensidade (m/M): ");
    escreveTextoNaTela((void*)font, theStringBuffer);

    glRasterPos3f(-1.0, 0.85, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Luz branca: ");
    glRasterPos3f(-1.0, 0.80, -2.0);
    escreveTextoNaTela((void*)font, (char*)"  - Intensidade difusa (d/D): ");
    floatParaString(theStringBuffer, 4, IntensidadeDifusa);
    escreveTextoNaTela((void*)font, theStringBuffer);
    glRasterPos3f(-1.0, 0.75, -2.0);
    escreveTextoNaTela((void*)font, (char*)"  - Intensidade especular (e/E): ");
    floatParaString(theStringBuffer, 4, IntensidadeEspecular);
    escreveTextoNaTela((void*)font, theStringBuffer);

    glRasterPos3f(-1.0, 0.65, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Material: ");
    glRasterPos3f(-1.0, 0.60, -2.0);
    escreveTextoNaTela((void*)font, (char*)"  - Expoente especular (s/S): ");
    floatParaString(theStringBuffer, 5, ExpoenteEspecular);
    escreveTextoNaTela((void*)font, theStringBuffer);

    glRasterPos3f(-1.0, 0.50, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Planetas: ");
    glRasterPos3f(-1.0, 0.45, -2.0);
    escreveTextoNaTela((void*)font, (char*)"  - Velocidade de translacao (v/V): ");
    floatParaString(theStringBuffer, 6, VelocidadeTranslacao);
    escreveTextoNaTela((void*)font, theStringBuffer);
    glRasterPos3f(-1.0, 0.40, -2.0);
    escreveTextoNaTela((void*)font, (char*)"  - Velocidade de rotacao (r/R): ");
    floatParaString(theStringBuffer, 6, VelocidadeRotacao);
    escreveTextoNaTela((void*)font, theStringBuffer);

    glRasterPos3f(-1.0, 0.30, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Câmeras: ");
    glRasterPos3f(-1.0, 0.30, -2.0);
    escreveTextoNaTela((void*)font, (char*)"        ");
    floatParaString(theStringBuffer, 2, camera);
    escreveTextoNaTela((void*)font, theStringBuffer);
}

void carregaTextura()
{
	(
		"Image/fundo.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

    sunTexture = SOIL_load_OGL_texture
	(
		"Image/sun.jpg",
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

  mercurioTexture = SOIL_load_OGL_texture
  (
    "Image/mercury.jpg",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
  );

  venusTexture = SOIL_load_OGL_texture
  (
    "Image/venus.jpg",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
  );
  terraTexture = SOIL_load_OGL_texture
  (
    "Image/terra.jpg",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
  );
  marteTexture = SOIL_load_OGL_texture
  (
    "Image/marte.jpg",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
  );
  jupiterTexture = SOIL_load_OGL_texture
  (
    "Image/jupiter.jpg",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
  );
  saturnoTexture = SOIL_load_OGL_texture
  (
    "Image/saturno.jpg",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
  );
  uranoTexture = SOIL_load_OGL_texture
  (
    "Image/urano.jpg",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
  );
  neturnoTexture = SOIL_load_OGL_texture
  (
    "Image/neturno.jpg",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
  );
  plutaoTexture = SOIL_load_OGL_texture
  (
    "Image/plutao.jpg",
    SOIL_LOAD_AUTO,
    SOIL_CREATE_NEW_ID,
    SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
  );

    if(sunTexture == 0 || mercurioTexture == 0 || venusTexture == 0 || terraTexture == 0 ||
       marteTexture == 0 || jupiterTexture == 0 || saturnoTexture == 0 || uranoTexture == 0 ||
      neturnoTexture == 0 || plutaoTexture == 0)
    {
        cout << "Problema ao carregar textura: " << SOIL_last_result() << endl;
    }
}

void solidSphere(float radius, int stacks, int columns){
    // cria uma quádrica
    GLUquadric* quadObj = gluNewQuadric();
    // estilo preenchido... poderia ser GLU_LINE, GLU_SILHOUETTE
    // ou GLU_POINT
    gluQuadricDrawStyle(quadObj, GLU_FILL);
    // chama 01 glNormal para cada vértice.. poderia ser
    // GLU_FLAT (01 por face) ou GLU_NONE
    gluQuadricNormals(quadObj, GLU_SMOOTH);
    // chama 01 glTexCoord por vértice
    gluQuadricTexture(quadObj, GL_TRUE);
    // cria os vértices de uma esfera
    gluSphere(quadObj, radius, stacks, columns);
    // limpa as variáveis que a GLU usou para criar
    // a esfera
    gluDeleteQuadric(quadObj);
}

// Desenha uma esfera na origem, com certo raio e subdivisões
// latitudinais e longitudinais
//
// Não podemos usar glutSolidSphere, porque ela não chama
// glTexCoord para os vértices. Logo, se você quer texturizar
// uma esfera, não pode usar glutSolidSphere
void desenhaEsfera(Planeta planeta)
{
      glPushMatrix();
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, planeta.textura);

      //translaciona
      glRotatef(planeta.anguloX, planeta.angulo_rotacao.x, planeta.angulo_rotacao.y, planeta.angulo_rotacao.z);
      
      //rotaciona
      glRotatef(planeta.anguloY, planeta.angulo_translacao.x, planeta.angulo_translacao.y, planeta.angulo_translacao.z);
        
      glTranslatef(planeta.angulo_translacao.x, planeta.angulo_translacao.y, planeta.angulo_translacao.z);
      
      solidSphere(planeta.medida, esferaLados, esferaLados);

    
    glPopMatrix();

}

// Configuração inicial do OpenGL e GLUT
void setup(void){
  
    //glClearColor(.4,.4,.4, 0.0);                    // fundo cinza
    glClearColor( 0, 0, 0, 0.0);
    glEnable(GL_DEPTH_TEST);                        // Ativa teste Z

    // Propriedades do material da esfera
    float matAmbAndDif[] = {1.0, 1.0, 1.0, 1.0};    // cor ambiente e difusa: branca
    float matSpec[] = { 1.0, 1.0, 1,0, 1.0 };       // cor especular: branca

    // Definindo as propriedades do material
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    carregaTextura();

    //criando os planetas
    //                 textura,       anguloX,anguloY, x_rotate, y_rotate, z_rotate, float x_translate, float y_translate, float z_translate, float medida
    sol = CriaPlaneta(sunTexture          , 0, 0, 0, 1, 0, 0  , 0, 0, 8);
    mercurio = CriaPlaneta(mercurioTexture, 0, 0, 0, 0, 0, -10, 0, 0, 0.3);
    venus = CriaPlaneta(venusTexture      , 0, 0, 0, 0, 0, -15, 0, 0, 0.7);
    terra = CriaPlaneta(terraTexture      , 0, 0, 0, 0, 0, -20, 0, 0, 1);
    marte = CriaPlaneta(marteTexture      , 0, 0, 0, 0, 0, -25, 0, 0, 0.39);
    jupiter = CriaPlaneta(jupiterTexture  , 0, 0, 0, 0, 0, 40 , 0, 0, 8.21);
    saturno = CriaPlaneta(saturnoTexture  , 0, 0, 0, 0, 0, -50, 0, 0, 6.9);
    urano = CriaPlaneta(uranoTexture      , 0, 0, 0, 0, 0, 60 , 0, 0, 2.92);
    neturno = CriaPlaneta(neturnoTexture  , 0, 0, 0, 0, 0, -65, 0, 0, 2.72);
    plutao = CriaPlaneta(plutaoTexture    , 0, 0, 0, 0, 0, 70 , 0, 0, 0.13);

    // Não mostrar faces do lado de dentro
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    // Esconder o ponteiro do mouse quando dentro da janela
    // glutSetCursor(GLUT_CURSOR_NONE);
}

// Callback de desenho
void desenhaCena() {
  //desenhabackgroung();
  // SOL Mercurio Venus Terra Marte Jupiter SAturno Urano Neturno Plutão
  // Proporção do tamanho: 8 0.29 0.7 0.73 0.39 8.21 6.90 2.92 2.79 0.13
  //
  // Fonte de Luz do Sistema: SOL

    // Propriedades das fontes de luz
    float lightAmb[] =    {0.0                   , 0.0                   , 0.0                   , 1.0 };
    float lightDif0[] =   {IntensidadeDifusa     , IntensidadeDifusa     , IntensidadeDifusa     , 1.0 };
    float lightSpec0[] =  {IntensidadeEspecular  , IntensidadeEspecular  , IntensidadeEspecular  , 1.0};
    float lightPos0[] =   {0.0                   , 0.0                   , 3.0                   , LuzPosicional };
    float globAmb[] =     {IntensidadeLuzAmbiente, IntensidadeLuzAmbiente, IntensidadeLuzAmbiente, 1.0 };

    // Propriedades da fonte de luz LIGHT0
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDif0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec0);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, globAmb);        // Luz ambiente global
    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, localViewer);// Enable local viewpoint

    // Ativa as fontes de luz (branca)
    if (light0Ligada)   
        glEnable(GL_LIGHT0);
    else 
        glDisable(GL_LIGHT0);

    // Limpa a tela e o z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    informacoesTela();

    if(camera == 1)
        gluLookAt(1*(xMouse)/(larguraJanela), -1*(yMouse)/(alturaJanela) + zoomPlaneta, -5, eixoX, eixoY, 0, 0, 1, 0);

    if(camera == 2)
      gluLookAt(0, zoomPlaneta, 150 , eixoX, eixoY, 0, 0, 10,0 );

    if(camera == 3) // minha ideia era essa camera focar em um planeta, mas como obter as coordenadas atuais dele?
    {
    //cout << terra.anguloX << endl;
      //gluLookAt(terra.anguloX, terra.anguloY, 00, eixoX, eixoY, 0, 0, 1, 0);
    }

    // Light0 e esfera = Sol
    glPushMatrix();
        glRotatef(xAngle, 1.0, 0.0, 0.0); // Rotação no eixo x
        glRotatef(yAngle, 0.0, 1.0, 0.0); // Rotação no eixo y
        glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
        glTranslatef(0, 0, 0);
        glColor3f(IntensidadeDifusa, IntensidadeDifusa, IntensidadeDifusa);
        glRotatef(sol.anguloY, 0, 1, 0);
        glRotatef(90, 1, 0, 0);
        desenhaEsfera(sol);
    glPopMatrix();
    
    if(isLightingOn)
      glEnable(GL_LIGHTING);
    else
      glDisable(GL_LIGHTING);
      

    // Define (atualiza) o valor do expoente de especularidade
    matShine[0] = ExpoenteEspecular;
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    glColor3f(1, 1, 1);

  desenhaEsfera(mercurio);
  desenhaEsfera(jupiter);
  desenhaEsfera(venus);
  desenhaEsfera(terra);
  desenhaEsfera(marte);
  desenhaEsfera(saturno);
  desenhaEsfera(urano);
  desenhaEsfera(neturno);
  desenhaEsfera(plutao);

    glutSwapBuffers();
}

// Callback do evento de teclado
void keyInput(unsigned char key, int x, int y){
    switch (key)
    {
    case 27: //esc
        exit(0);
        break;
    case 43: //+
        zoomPlaneta++;
        break;
    case 45: //-
        zoomPlaneta--;
        break;        
    case 49: //1
        camera = 1;
        break;
    case 50: //2
        camera = 2;
        break; 
    case 51: //1
        //camera = 3;
        break;
    case 52: //2
        //camera = 4;
        break;              
    case 'w':
    case 'W':
        if (light0Ligada) light0Ligada = false;
        else light0Ligada = true;
        break;
    case 'p':
    case 'P':
        if (LuzPosicional) LuzPosicional = 0.0;
        else LuzPosicional = 1.0;
        break;
    case 'd':
      if(isLightingOn)
        if (IntensidadeDifusa > 0.0) IntensidadeDifusa -= 0.05;
        break;
    case 'D':
      if(isLightingOn)
        if (IntensidadeDifusa < 1.0) IntensidadeDifusa += 0.05;
        break;
    case 'e':
      if(isLightingOn)
        if (IntensidadeEspecular > 0.0) IntensidadeEspecular -= 0.05;
        break;
    case 'E':
      if(isLightingOn)
        if (IntensidadeEspecular < 1.0) IntensidadeEspecular += 0.05;
        break;
    case 's':
      if(isLightingOn)
        if (ExpoenteEspecular > 5.0) ExpoenteEspecular -= 2.00;
        break;
    case 'S':
      if(isLightingOn)
        if (ExpoenteEspecular < 100.0) ExpoenteEspecular += 2.00;
        break;
    case 'm':
      if(isLightingOn)
        if (IntensidadeLuzAmbiente > 0.0) IntensidadeLuzAmbiente -= 0.05;
        break;
    case 'M':
      if(isLightingOn)
        if (IntensidadeLuzAmbiente < 1.0) IntensidadeLuzAmbiente += 0.05;
        break;
    case 'l':
    case 'L':
        isLightingOn = !isLightingOn;
        break;
    case 'v':
        if(VelocidadeTranslacao > 0.0) VelocidadeTranslacao-=1; 
        break;
    case 'V':
      if(VelocidadeTranslacao < 1000.0) VelocidadeTranslacao+=1;
        break;
    case 'r':
        if(VelocidadeRotacao > 0.0) VelocidadeRotacao-=1; 
        break;
    case 'R':
      if(VelocidadeRotacao < 100.0) VelocidadeRotacao+=1;
        break;        
    default:
        break;
    }

    glutPostRedisplay();
}


// Callback para setas do teclado
void specialKeyInput(int key, int x, int y){
     if(key == GLUT_KEY_DOWN)
     {
       eixoY--;
     }
     if(key == GLUT_KEY_UP)
     {
       eixoY++;
     }
     if(key == GLUT_KEY_RIGHT)
     {
       eixoX++;
     }  
     if(key == GLUT_KEY_LEFT)
     {
       eixoX--;
     }

     
    glutPostRedisplay();
}

// Callback de redimensionamento
void resize(int w, int h){
    larguraJanela = w;
    alturaJanela = h;

    glViewport (0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (float)w/(float)h, 1.0, 300.0);
    glMatrixMode(GL_MODELVIEW);
}

void posicionaCamera(int x, int y) {
     xMouse = x;
     yMouse = y;;
    glutPostRedisplay();
}

void translacaoPlanetas() 
{   
    mercurio.angulo_rotacao.z = 1; 
    jupiter.angulo_rotacao.z = 1;
    venus.angulo_rotacao.z = 1;
    terra.angulo_rotacao.z = 1;
    marte.angulo_rotacao.z = 1;
    saturno.angulo_rotacao.z = 1;
    urano.angulo_rotacao.z = 1;
    neturno.angulo_rotacao.z = 1;
    plutao.angulo_rotacao.z = 1; 

    mercurio.anguloY += VelocidadeRotacao / 58.6;
    venus.anguloY += VelocidadeRotacao / 243.0;
    terra.anguloY += VelocidadeRotacao / 1;
    marte.anguloY += VelocidadeRotacao / 1.03 ;
    jupiter.anguloY += 10;
    saturno.anguloY += VelocidadeRotacao / 0.45;
    urano.anguloY += VelocidadeRotacao / 0.72;
    neturno.anguloY += VelocidadeRotacao / 0.67;
    plutao.anguloY += VelocidadeRotacao / 6.39;
  
    glutPostRedisplay();
}

void rotacaoPlanetas() {

    mercurio.angulo_rotacao.z = 0; 
    jupiter.angulo_rotacao.z = 0;
    venus.angulo_rotacao.z = 0;
    terra.angulo_rotacao.z = 0;
    marte.angulo_rotacao.z = 0;
    saturno.angulo_rotacao.z = 0;
    urano.angulo_rotacao.z = 0;
    neturno.angulo_rotacao.z = 0;
    plutao.angulo_rotacao.z = 0; 

    mercurio.anguloX  += VelocidadeTranslacao / 88;
    venus.anguloX += VelocidadeTranslacao / 224;
    terra.anguloX += VelocidadeTranslacao / 365;
    marte.anguloX += VelocidadeTranslacao / (1.88 * 365) ;
    jupiter.anguloX += VelocidadeTranslacao / (11.86 * 365);
    saturno.anguloX += VelocidadeTranslacao / (29.46 * 365);
    urano.anguloX += VelocidadeTranslacao / (84,01 * 365);
    neturno.anguloX += VelocidadeTranslacao / (164,79 * 365);
    plutao.anguloX += VelocidadeTranslacao / (248,59 * 365);

    //mercurio.angulo_rotacao.z = jupiter.angulo_rotacao.z = venus.angulo_rotacao.z = terra.angulo_rotacao.z = marte.angulo_rotacao.z = saturno.angulo_rotacao.z = urano.angulo_rotacao.z = neturno.angulo_rotacao.z = plutao.angulo_rotacao.z = 1;
   glutPostRedisplay();
}

void moverPlanetas()
{
    rotacaoPlanetas();
    translacaoPlanetas();
}

// Imprime a ajuda no console
void imprimirAjudaConsole(void){
    cout << "Ajuda:" << endl;
    cout << "  Aperte 'l' para ligar/desligar a iluminacao do OpenGL." << endl
         << "  Aperte 'w' para ligar/desligar a fonte de luz branca." << endl
         << "  Aperte 'd/D' para aumentar/reduzir a intensidade difusa da luz branca." << endl
         << "  Aperte 'e/E' para aumentar/reduzir a intensidade especular da luz branca." << endl
         << "  Aperte 'm/M' para aumentar/reduzir a intensidade da luz ambiente global." << endl
         << "  Aperte 's/S' para aumentar/reduzir o expoente especular do material." << endl
         << "  Aperte 'v/V' para aumentar/reduzir a velocidade de translação" << endl
         << "  Aperte 'r/R' para aumentar/reduzir a velocidade de rotacao" << endl
         << "  Aperte 'p' para alternar entre fonte posicional ou direcional." << endl
         << "  Aperte 't' para alternar entre modo com/sem textura." << endl
         << "  Aperte entre 1,2 para alternar as câmeras." << endl
         << "  Utilize as setas para controlar as câmeras." << endl
         << "  Utilize as teclas '-' e '+' para aplicar um zoom." << endl
         << "  Pressione ESC para sair" << endl;
}

int main(int argc, char *argv[]){
    imprimirAjudaConsole();
    glutInit(&argc, argv);

    inicializarMusica();
    carregarMusica();

    Mix_PlayMusic(musicaDeFundo, 1);
    
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow("Luz e Materiais");
    setup();
    glutDisplayFunc(desenhaCena);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(specialKeyInput);
    glutPassiveMotionFunc(posicionaCamera);
    glutIdleFunc(moverPlanetas);
    
    glutMainLoop();
    return 0;
}
