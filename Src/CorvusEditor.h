#pragma once
#include <Core.h>

#include "Window.h"
#include "RHI/Renderer.h"

namespace CorvusEngine{

class CorvusEditor {
public:
    CorvusEditor();
    ~CorvusEditor();

    void Run();

private:
    std::shared_ptr<Window> m_window;
    std::unique_ptr<Renderer> m_renderer;
};

}
