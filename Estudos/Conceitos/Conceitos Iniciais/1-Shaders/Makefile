NAME = result

CXX = g++
CXXFLAGS = -lGL -lGLEW -lglfw

OBJ = shader.o teste.o

all: $(NAME)

$(NAME): teste.o shader.o
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)
	@echo Projeto Compilado!

shader.o : ../Class/shader.cpp
	$(CXX) -o shader.o -c ../Class/shader.cpp

teste.o : ../Class/shader.h teste.cpp
	$(CXX) -o teste.o -c teste.cpp

clean:
	rm -rf *.o