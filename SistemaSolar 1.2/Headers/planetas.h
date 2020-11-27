typedef struct angulo
{
  float x,y,z;
} Angulo;

typedef struct planeta
{
  int textura;
  float anguloX;
  float anguloY;
  Angulo angulo_rotacao;
  Angulo angulo_translacao;
  float medida;

}Planeta;

Planeta CriaPlaneta(int , float , float , float , float , float , float , float , float , float );

