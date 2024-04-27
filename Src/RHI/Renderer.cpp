#include "Renderer.h"

namespace CorvusEngine{

Renderer::Renderer(HWND hwnd) : m_frameIndex(0)
{
    m_device = std::make_shared<Device>();
    m_directCommandQueue = std::make_shared<CommandQueue>(m_device, D3D12_COMMAND_LIST_TYPE_DIRECT);
    m_rtvHeap = std::make_shared<DescriptorHeap>(m_device, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, 512);
    m_allocator = std::make_shared<Allocator>(m_device);
    m_directFence = std::make_shared<Fence>(m_device);
    m_directFenceValue = 0;
    m_swapChain = std::make_shared<SwapChain>(m_device, m_directCommandQueue, m_rtvHeap, hwnd);

    LOG(Debug, "Renderer Initialization Completed");

    for (int i = 0; i < FRAMES_IN_FLIGHT; i++) {
        m_commandBuffers[i] = std::make_shared<CommandBuffer>(m_device, D3D12_COMMAND_LIST_TYPE_DIRECT);
        m_frameValues[i] = 0;
    }
}

Renderer::~Renderer()
{
    WaitForPreviousFrame();
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
    m_directFence->Wait(m_frameValues[m_frameIndex], 10'000'000);

    m_allocator->GetAllocator()->SetCurrentFrameIndex(m_frameIndex);
}

void Renderer::EndFrame()
{
    m_frameValues[m_frameIndex] = m_directFence->GetValue();
}

void Renderer::Present(bool vsync)
{
    m_swapChain->Present(vsync);
}

void Renderer::WaitForPreviousHostSubmit(D3D12_COMMAND_LIST_TYPE type)
{
    if(type == D3D12_COMMAND_LIST_TYPE_DIRECT)
        m_directFence->Wait(m_directFenceValue, 10'000'000);
}

void Renderer::WaitForPreviousDeviceSubmit(D3D12_COMMAND_LIST_TYPE type)
{
    if(type == D3D12_COMMAND_LIST_TYPE_DIRECT)
        m_directCommandQueue->Wait(m_directFence, 10'000'000);
}

void Renderer::ExecuteCommandBuffers(const std::vector<std::shared_ptr<CommandBuffer>> &buffers, D3D12_COMMAND_LIST_TYPE type)
{
    if(type == D3D12_COMMAND_LIST_TYPE_DIRECT)
    {
        m_directCommandQueue->Submit(buffers);
        m_directFenceValue = m_directFence->Signal(m_directCommandQueue);
    }
}

void Renderer::FlushQueues()
{
    WaitForPreviousHostSubmit(D3D12_COMMAND_LIST_TYPE_DIRECT);
}

void Renderer::WaitForPreviousFrame()
{
    uint64_t wait = m_directFence->Signal(m_directCommandQueue);
    m_directFence->Wait(wait, 10'000'000);
}
}
