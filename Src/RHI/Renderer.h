#pragma once
#include <Core.h>

#include "Allocator.h"
#include "Buffer.h"
#include "CommandList.h"
#include "CommandQueue.h"
#include "DescriptorHeap.h"
#include "Device.h"
#include "GraphicsPipeline.h"
#include "SwapChain.h"
#include "Uploader.h"

namespace CorvusEngine{

struct Heaps
{
    std::shared_ptr<DescriptorHeap> RtvHeap;
    std::shared_ptr<DescriptorHeap> DsvHeap;
    std::shared_ptr<DescriptorHeap> ShaderHeap;
    std::shared_ptr<DescriptorHeap> SamplerHeap;
};

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

    void ExecuteCommandBuffers(const std::vector<std::shared_ptr<CommandList>>& buffers, D3D12_COMMAND_LIST_TYPE type);

    std::shared_ptr<CommandList> GetCurrentCommandList() { return m_commandBuffers[m_frameIndex]; }
    std::shared_ptr<Texture> GetBackBuffer() { return m_swapChain->GetTexture(m_frameIndex); }

    std::shared_ptr<GraphicsPipeline> CreateGraphicsPipeline(GraphicsPipelineSpecs& specs);
    std::shared_ptr<Buffer> CreateBuffer(uint64_t size, uint64_t stride, BufferType type, bool readback);
    Uploader CreateUploader();

    void FlushUploader(Uploader& uploader);

private:
    void WaitForPreviousFrame();
    void WaitForPreviousDeviceSubmit(D3D12_COMMAND_LIST_TYPE type);

private:
    std::shared_ptr<Device> m_device;
    std::shared_ptr<CommandQueue> m_directCommandQueue;
    std::shared_ptr<CommandQueue> m_computeCommandQueue;
    std::shared_ptr<CommandQueue> m_copyCommandQueue;
    std::shared_ptr<Allocator> m_allocator;
    std::shared_ptr<SwapChain> m_swapChain;
    Heaps m_heaps;

    uint64_t m_frameIndex;
    uint64_t m_frameValues[FRAMES_IN_FLIGHT];
    std::shared_ptr<CommandList> m_commandBuffers[FRAMES_IN_FLIGHT];

    DescriptorHandle m_fontDescriptor;
};

}
