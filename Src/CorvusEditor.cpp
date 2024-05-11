#include "CorvusEditor.h"
#include "Logger.h"
#include <ImGui/imgui.h>
#include "ShaderCompiler.h"

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

    Shader shader;
    ShaderCompiler::CompileShader("../../Shaders/SimpleVertex.hlsl", ShaderType::Vertex, shader);
    ShaderCompiler::CompileShader("../../Shaders/SimplePixel.hlsl", ShaderType::Pixel, shader);
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

        auto commandList = m_renderer->GetCurrentCommandList();
        auto texture = m_renderer->GetBackBuffer();

        commandList->Begin();
        commandList->ImageBarrier(texture, D3D12_RESOURCE_STATE_RENDER_TARGET);

        commandList->BindRenderTargets({ texture }, nullptr);
        commandList->ClearRenderTarget(texture, 1.0f, 8.0f, 0.0f, 1.0f);

        m_renderer->BeginImGuiFrame();

        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit", "Alt+F4")) {
                    m_window->Close();
                }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        ImGui::Begin("FrameRate");
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        m_renderer->EndImGuiFrame();

        commandList->ImageBarrier(texture, D3D12_RESOURCE_STATE_PRESENT);
        commandList->End();
        m_renderer->ExecuteCommandBuffers({ commandList }, D3D12_COMMAND_LIST_TYPE_DIRECT);

        m_renderer->EndFrame();
        m_renderer->Present(true);

        m_window->BroadCast();
    }
}

}
