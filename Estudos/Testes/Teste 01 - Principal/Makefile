NAME = exec

CXX = g++

CXXFLAGS = -lGL -lGLEW -lglfw -DIMGUI_IMPL_OPENGL_LOADER_GLEW
CXXFLAGS += -I../ -I../../ `pkg-config --cflags glfw3`
CXXFLAGS += -Wformat

SOURCES = main.cpp Shader.cpp
SOURCES += libs/imgui/examples/imgui_impl_glfw.cpp libs/imgui/examples/imgui_impl_opengl3.cpp
SOURCES += libs/imgui/imgui.cpp libs/imgui/imgui_demo.cpp libs/imgui/imgui_draw.cpp
SOURCES += libs/imgui/imgui_widgets.cpp

OBJ = $(SOURCES:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)
	@echo Projeto Compilado!

Shader.o: Class/Shader.cpp
	@$(CXX) -o Shader.o -c Class/Shader.cpp

main.o: main.cpp Class/Shader.h
	@$(CXX) -o main.o -c main.cpp 

%.o:libs/imgui/%.cpp
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:libs/imgui/examples/%.cpp
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -rf *.o Class/*.o $(OBJ)