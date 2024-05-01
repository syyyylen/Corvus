#pragma once
#include <Core.h>

#include "Allocator.h"
#include "CommandBuffer.h"
#include "CommandQueue.h"
#include "DescriptorHeap.h"
#include "Device.h"
#include "SwapChain.h"

namespace CorvusEngine{

class Renderer
{
public:
    Renderer(HWND hwnd);
    ~Renderer();

    void Resize(uint32_t width, uint32_t height);
    void BeginFrame();
    void EndFrame();
    void Present(bool vsync);

    void BeginImGuiFrame();
    void EndImGuiFrame();

    void ExecuteCommandBuffers(const std::vector<std::shared_ptr<CommandBuffer>>& buffers, D3D12_COMMAND_LIST_TYPE type);

    std::shared_ptr<CommandBuffer> GetCurrentCommandBuffer() { return m_commandBuffers[m_frameIndex]; }
    std::shared_ptr<Texture> GetBackBuffer() { return m_swapChain->GetTexture(m_frameIndex); }

private:
    // void FlushQueues();
    void WaitForPreviousFrame();

private:
    std::shared_ptr<Device> m_device;
    std::shared_ptr<CommandQueue> m_directCommandQueue;
    std::shared_ptr<DescriptorHeap> m_rtvHeap;
    std::shared_ptr<DescriptorHeap> m_shaderHeap;
    std::shared_ptr<Allocator> m_allocator;
    std::shared_ptr<SwapChain> m_swapChain;

    uint64_t m_frameIndex;
    uint64_t m_frameValues[FRAMES_IN_FLIGHT];
    std::shared_ptr<CommandBuffer> m_commandBuffers[FRAMES_IN_FLIGHT];

    DescriptorHandle m_fontDescriptor;
};

}
