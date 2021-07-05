#include "Application.h"

Application::Application(const char* title, int width, int height, bool view)
{
    if(!glfwInit())
    {
        std::cout << "App: [GLFW ERROR] Could not init GLFW.\n";
        m_window = nullptr;
    }
    else
    {  
        m_window = glfwCreateWindow(width, height, title, NULL, NULL);
        if(!m_window)
        {
            std::cout << "App: [GLFW ERROR] Could not init Window.\n";
        }

        m_width = width;
        m_height = height;

        glfwMakeContextCurrent(m_window);
        
        unsigned int glewStatus = glewInit();
        if(glewStatus != GLEW_OK)
        {
            std::cout << "App: [GLEW ERROR] Could not init GLEW.\n";
            m_window = nullptr;
        }

        m_view = view;
        m_change = false;

        rgb[0] = 0.05f;
        rgb[1] = 0.05f;
        rgb[2] = 0.13f;

        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

        show("OpenGl Version:" << glGetString(GL_VERSION));
        
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_NOTEQUAL, 1, 0XFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
}

Application::~Application()
{
    glfwTerminate();
}

bool Application::Execute()
{
    if(glfwWindowShouldClose(m_window)) return false;
    return true;
}

void Application::Clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    glClearColor(rgb[0], rgb[1], rgb[2], 1.0f);
}

void Application::Update()
{
    if(m_view) glViewport(0, 0, m_width, m_height);

    int tempw = m_width, temph = m_height;
    glfwGetWindowSize(m_window, &m_width, &m_height);
    if(tempw != m_width || temph != m_height) m_change = true;

    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

inline bool Application::WindowChange()
{
    if(m_change)
    {
        m_change = false;
        return true;
    }
    else
    {
        return false;
    }
}

void Application::ChangeBackground(float r, float g, float b)
{
    if(r < 0 || r > 1.0f || g < 0 || g > 1.0f || b < 0 || b > 1.0f)
    {
        std::cout << "App: [Change Background] Background colors must be between 0.0f and 1.0f.\n";
    }
    else
    {
        rgb[0] = r;
        rgb[1] = g;
        rgb[2] = b;
    }
}