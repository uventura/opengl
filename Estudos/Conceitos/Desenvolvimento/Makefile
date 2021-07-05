
NAMEFILES = 24.cpp
NAMEFILES += Class/Application.cpp
NAMEFILES += Class/Buffer.cpp
NAMEFILES += Class/Shader.cpp
NAMEFILES += Class/Menu.cpp
NAMEFILES += Class/Camera.cpp
NAMEFILES += Class/Texture.cpp
NAMEFILES += Class/Mesh.cpp
NAMEFILES += Class/Model.cpp

NAMEFILES += Class/imgui/imgui_impl_glfw.cpp imgui
NAMEFILES += Class/imgui/imgui_impl_opengl3.cpp
NAMEFILES += Class/imgui/imgui.cpp
NAMEFILES += Class/imgui/imgui_demo.cpp
NAMEFILES += Class/imgui/imgui_draw.cpp
NAMEFILES += Class/imgui/imgui_widgets.cpp

OBJS = $(addsuffix .o, $(basename $(notdir $(NAMEFILES))))

%.o:%.cpp
	@g++ -lGL -lGLEW -lglfw -lassimp -c -o $@ $<

%.o:Class/%.cpp
	@g++ -lGL -lGLEW -lglfw -lassimp -c -o $@ $<

%.o:Class/imgui/%.cpp
	@g++ -lGL -lGLEW -lglfw -lassimp -c -o $@ $<

all: exec

exec: $(OBJS)
	@g++ -o $@ $^ -lGL -lGLEW -lglfw -lassimp -g
	@echo "Compiled!"
clean:
	@rm -rf $(OBJS)

mrproper:
	@rm *.o
