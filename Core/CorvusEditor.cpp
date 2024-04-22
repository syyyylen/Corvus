#include "CorvusEditor.h"

namespace CorvusEngine{

CorvusEditor::CorvusEditor()
{
    m_window = std::make_shared<Window>(1280, 720, L"Corvus Editor");
    m_window->DefineOnResize([](int width, int height)
    {
        // TODO define resize functions
    });
}

CorvusEditor::~CorvusEditor()
{

}

void CorvusEditor::Run()
{
    while(m_window->IsRunning())
    {
        m_window->BroadCast();
    }
}

}
