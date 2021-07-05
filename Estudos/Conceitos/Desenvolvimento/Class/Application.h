#include "MainHeader.h"

class Application
{
private:
    GLFWwindow* m_window;
    int m_width, m_height;
    bool m_view;
    float rgb[3];

    bool m_change; // Window change
public:
    Application(const char* title, int width, int height, bool view = false);
    ~Application();

    inline GLFWwindow* getWindowPtr(){return m_window;};
    inline int getWidth(){return m_width;};
    inline int getHeight(){return m_height;};
    inline void setWidth(int w){m_width = w;};
    inline void setHeight(int h){m_height = h;};

    bool Execute();
    void Clear();
    void Update();
    inline void ActiveViewport(bool status){m_view = status;};
    inline bool WindowChange();

    void ChangeBackground(float r, float g, float b);
};