#include "CorvusEditor.h"
#include "Logger.h"
#include <ImGui/imgui.h>

namespace CorvusEngine{

CorvusEditor::CorvusEditor()
{
    LOG(Debug, "Starting Corvus Editor");

    m_window = std::make_shared<Window>(1280, 720, L"Corvus Editor");
    m_window->DefineOnResize([this](int width, int height)
    {
        LOG(Debug, "Window resize !");
        m_renderer->Resize(width, height);
    });

    // m_window->Maximize();

    m_renderer = std::make_unique<Renderer>(m_window->GetHandle());
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
        m_renderer->BeginFrame();

        auto commandBuffer = m_renderer->GetCurrentCommandBuffer();
        auto texture = m_renderer->GetBackBuffer();

        commandBuffer->Begin();
        commandBuffer->ImageBarrier(texture, D3D12_RESOURCE_STATE_RENDER_TARGET);

        commandBuffer->BindRenderTargets({ texture }, nullptr);
        commandBuffer->ClearRenderTarget(texture, 1.0f, 8.0f, 0.0f, 1.0f);

        m_renderer->BeginImGuiFrame();
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Quit", "Alt+F4")) {
                    m_window->Close();
                }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }
        m_renderer->EndImGuiFrame();

        commandBuffer->ImageBarrier(texture, D3D12_RESOURCE_STATE_PRESENT);
        commandBuffer->End();
        m_renderer->ExecuteCommandBuffers({ commandBuffer }, D3D12_COMMAND_LIST_TYPE_DIRECT);

        m_renderer->EndFrame();
        m_renderer->Present(true);

        m_window->BroadCast();
    }
}

}
