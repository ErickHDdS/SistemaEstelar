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

Planeta CriaPlaneta(int textura, float anguloX, float anguloY, float x_rotate, float y_rotate, float z_rotate, float x_translate, float y_translate, float z_translate, float medida)
{
  Angulo a,b;
  a.x = x_rotate;
  b.y = y_rotate;
  a.z = z_rotate;

  b.x = x_translate;
  b.y = y_translate;
  b.z = z_translate;

  Planeta s;
  s.textura = textura;
  s.anguloX = anguloX;
  s.anguloY = anguloY;
  s.angulo_rotacao = a;
  s.angulo_translacao = b;

  s.medida = medida;

  return s;
}
