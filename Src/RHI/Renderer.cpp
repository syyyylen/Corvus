#include "Renderer.h"
#include <ImGui/imgui_impl_dx12.h>
#include <ImGui/imgui_impl_win32.h>
#include <ImGui/imgui.h>

namespace CorvusEngine{

Renderer::Renderer(HWND hwnd) : m_frameIndex(0)
{
    m_device = std::make_shared<Device>();
    m_directCommandQueue = std::make_shared<CommandQueue>(m_device, D3D12_COMMAND_LIST_TYPE_DIRECT);
    m_rtvHeap = std::make_shared<DescriptorHeap>(m_device, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, 512);
    m_shaderHeap = std::make_shared<DescriptorHeap>(m_device, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, 2048);
    m_allocator = std::make_shared<Allocator>(m_device);
    m_swapChain = std::make_shared<SwapChain>(m_device, m_directCommandQueue, m_rtvHeap, hwnd);

    LOG(Debug, "Renderer Initialization Completed");

    for (int i = 0; i < FRAMES_IN_FLIGHT; i++) {
        m_commandBuffers[i] = std::make_shared<CommandBuffer>(m_device, D3D12_COMMAND_LIST_TYPE_DIRECT);
        m_frameValues[i] = 0;
    }

    m_fontDescriptor = m_shaderHeap->Allocate();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    ImGui::StyleColorsDark();

    ImGui_ImplWin32_EnableDpiAwareness();
    ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplDX12_Init(m_device->GetDevice(), FRAMES_IN_FLIGHT, DXGI_FORMAT_R8G8B8A8_UNORM, m_shaderHeap->GetHeap(), m_fontDescriptor.CPU, m_fontDescriptor.GPU);
}

Renderer::~Renderer()
{
    WaitForPreviousFrame();

    ImGui_ImplDX12_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
    m_shaderHeap->Free(m_fontDescriptor);
}

void Renderer::Resize(uint32_t width, uint32_t height)
{
    WaitForPreviousFrame();

    if(m_swapChain)
        m_swapChain->Resize(width, height);
}

void Renderer::BeginFrame()
{
    m_frameIndex = m_swapChain->AcquireImage();
    m_directCommandQueue->Wait(m_frameValues[m_frameIndex], 10'000'000);

    m_allocator->GetAllocator()->SetCurrentFrameIndex(m_frameIndex);
}

void Renderer::EndFrame()
{
    m_frameValues[m_frameIndex] = m_directCommandQueue->GetFenceValue();
}

void Renderer::Present(bool vsync)
{
    m_swapChain->Present(vsync);
}

void Renderer::BeginImGuiFrame()
{
    ImGui_ImplDX12_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}

void Renderer::EndImGuiFrame()
{
    auto cmdList = m_commandBuffers[m_frameIndex]->GetCommandList();

    ID3D12DescriptorHeap* pHeaps[] = { m_shaderHeap->GetHeap() };
    cmdList->SetDescriptorHeaps(1, pHeaps);

    ImGui::Render();
    ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), cmdList);
}

void Renderer::ExecuteCommandBuffers(const std::vector<std::shared_ptr<CommandBuffer>>& buffers, D3D12_COMMAND_LIST_TYPE type)
{
    if(type == D3D12_COMMAND_LIST_TYPE_DIRECT)
    {
        m_directCommandQueue->Submit(buffers);
        m_directCommandQueue->Signal();
    }
}

void Renderer::WaitForPreviousFrame()
{
    uint64_t wait = m_directCommandQueue->Signal();
    m_directCommandQueue->Wait(wait, 10'000'000);
}

}
