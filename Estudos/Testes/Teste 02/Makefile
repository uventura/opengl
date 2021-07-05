TITULO = Teste02

all: $(TITULO)

$(TITULO): main.o Class/Shader.o
	@g++ -o $(TITULO) main.o Class/Shader.o -lGL -lglfw -lGLEW
	@echo Projeto Compilado!

Class/Shader.o: Class/Shader.cpp
	@g++ -o Class/Shader.o -c Class/Shader.cpp 

main.o: main.cpp Class/Shader.h
	@g++ -o main.o -c main.cpp

clean:
	@rm -rf *.o Class/*.o
	@echo Arquivos Objetos Removidos!