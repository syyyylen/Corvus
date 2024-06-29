#pragma once
#include <Core.h>

#include "Window.h"
#include "RHI/Buffer.h"
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
    std::shared_ptr<GraphicsPipeline> m_trianglePipeline;
    std::shared_ptr<Buffer> m_vertexBuffer;
    std::shared_ptr<Buffer> m_indicesBuffer;
};

}
