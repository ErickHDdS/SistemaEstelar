CC=gcc
OPCOES_COMPILADOR=-I. -lglut -lGLU -lGLEW -lGL -lSOIL -lm -lSDL -lSDL_mixer
TODOS_ARQUIVOS_PONTOH =
TODOS_ARQUIVOS_OBJ =  carregaTextura.o setup.o desenhaEstrela.o desenhaBackground.o desenhaSol.o esfera.o rotacionaEsfera.o desenhaTelaCena.o redimensionada.o imprimirAjudaTela.o imprimirAjudaTerminal.o teclaPressionada.o teclaEspecialPressionada.o atualizaCena.o main.o

%.o: ../Sources/%.c $(TODOS_ARQUIVOS_PONTOH)
	$(CC) -o $@ -c $< $(OPCOES_COMPILADOR)

all: $(TODOS_ARQUIVOS_OBJ)
	gcc -o ../Sources/main $^ $(OPCOES_COMPILADOR)

run: all
	./../Sources/main

clean:
	rm *.o main
