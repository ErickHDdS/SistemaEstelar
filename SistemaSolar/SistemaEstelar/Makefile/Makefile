CC=gcc
OPCOES_COMPILADOR=-I. -I/usr/include/SOIL -lglut -lGLU -lSOIL -lGLEW -lGL -lm -lstdc++ -lSDL -lSDL_mixer
TODOS_ARQUIVOS_PONTOH = 
TODOS_ARQUIVOS_OBJ = planetas.o main.o

%.o: ../Source/%.cpp $(TODOS_ARQUIVOS_PONTOH)
	$(CC) -o $@ -c $< $(OPCOES_COMPILADOR)

all: $(TODOS_ARQUIVOS_OBJ)
	gcc -o main $^ $(OPCOES_COMPILADOR)

run: all
	(cd .. && exec Makefile/main)

clean:
	rm *.o main
