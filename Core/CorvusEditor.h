#pragma once
#include <memory>

#include "Window.h"

namespace CorvusEngine{

class CorvusEditor {
public:
    CorvusEditor();
    ~CorvusEditor();

    void Run();

private:
    std::shared_ptr<Window> m_window;
};

}
