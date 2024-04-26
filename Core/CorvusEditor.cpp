#include "CorvusEditor.h"
#include "Logger.h"

namespace CorvusEngine{

CorvusEditor::CorvusEditor()
{
    LOG(Debug, "Starting Corvus Editor");

    m_window = std::make_shared<Window>(1280, 720, L"Corvus Editor");
    m_window->DefineOnResize([](int width, int height)
    {
        // TODO define resize functions
        LOG(Debug, "Window resize !");
    });

    // m_window->Maximize();
}

CorvusEditor::~CorvusEditor()
{
    LOG(Debug, "Destroying Corvus Editor");
    Logger::WriteLogsToFile();
}

void CorvusEditor::Run()
{
    while(m_window->IsRunning())
    {
        m_window->BroadCast();
    }
}

}
