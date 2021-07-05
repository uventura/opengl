#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "../includes/functions/mainFunc.cpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{
    GLFWwindow *window;

    if(!glfwInit())
    {
        show("Erro ao inicializar o GLFW.");
        return -1;
    }

    window = glfwCreateWindow(680, 420, "Titulo", NULL, NULL);
    if(!window)
    {
        show("Erro ao criar janela.");
        glfwTerminate();
        return -1;
    }

    /* Pré definições sobre o GLFW e como a janela deve se comportar*/

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    /*============================================================*/

    glfwMakeContextCurrent(window);

    GLenum error = glewInit();
    if(GLEW_OK != error)
    {
        show("Erro ao inicializar o GLEW.");
    }

    show("Versao do GLEW: " << glewGetString(GLEW_VERSION));
    show("Versao do OpenGL: " << glGetString(GL_VERSION));
    show("Versao do GLFW: " << glfwGetVersionString());

    //<<<<<<<<<<| DEFINIÇÕES |>>>>>>>>>>
    float vertices[48] = 
    {
        //|  Coordenadas   |      Cores     |

        // Plano da Frente
        -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 1.0f,
         0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
         0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, 0.0f, 0.5f, 0.5f, 0.5f,

        // Plano de Trás
        -0.5f, -0.5f, 0.5f, 0.5f, 0.0f, 0.5f,
         0.5f, -0.5f, 0.5f, 0.8f, 0.8f, 0.0f,
         0.5f,  0.5f, 0.5f, 0.2f, 0.2f, 0.2f,
        -0.5f,  0.5f, 0.5f, 0.6f, 0.7f, 0.4f
    };

    unsigned int indices[36] = 
    {
        // Face
        0, 1, 2,
        0, 2, 3,
        // Face
        0, 1, 4,
        1, 4, 5,
        // Face
        4, 5, 6,
        4, 7, 6,
        // Face
        3, 4, 6,
        3, 6, 7,
        // Face
        1, 4, 6,
        1, 5, 6,
        // Face
        0, 3, 7,
        0, 4, 7,
    };

    // Definições de Vertice
    unsigned int vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Layouts
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (const void *) 3);

    // Element Buffer Array
    unsigned int ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Shader
    shaderCode src = getShaderSource("../includes/shaders/camera3.shader");
    
        // Vertex Shader 
        unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex, 1, &src.vertexPtr, NULL);
        glCompileShader(vertex);
        
        // Fragment Shader
        unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment, 1, &src.fragmentPtr, NULL);
        glCompileShader(fragment);

        // Shader Program
        unsigned int shader = glCreateProgram();
        glAttachShader(shader, vertex);
        glAttachShader(shader, fragment);
        glLinkProgram(shader);

        glDeleteShader(vertex);
        glDeleteShader(fragment);
        glUseProgram(shader);

    // Transformations
    glm::mat4 model(1.0f);
    model = glm::rotate(model, glm::radians(-50.0f), glm::vec3(1.0f, 1.0f, 0.0f));

    glm::mat4 view(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 persp(1.0f);
    persp = glm::perspective(glm::radians(45.0f), (float)640/480, 0.1f, 100.0f);

    glm::mat4 form(1.0f);
    form = persp * view * model;

    int u_trans = glGetUniformLocation(shader, "transform");
    if(u_trans == -1)
        show("Erro ao carregar o uniform.");

    glUniformMatrix4fv(u_trans, 1, GL_FALSE, glm::value_ptr(form));

    //<<<<<<<<<<| EXECUÇÃO |>>>>>>>>>>
    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}