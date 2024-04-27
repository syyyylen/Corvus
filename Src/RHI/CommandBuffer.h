#pragma once
#include <Core.h>

#include "Device.h"
#include "Texture.h"

namespace CorvusEngine {

class CommandBuffer 
{
public:
    CommandBuffer(std::shared_ptr<Device> device, D3D12_COMMAND_LIST_TYPE commandQueueType);
    ~CommandBuffer();

    void Begin();
    void End();

    void ImageBarrier(std::shared_ptr<Texture> texture, D3D12_RESOURCE_STATES state);
    void BindRenderTargets(const std::vector<std::shared_ptr<Texture>> renderTargets, std::shared_ptr<Texture> depthTarget);
    void ClearRenderTarget(std::shared_ptr<Texture> renderTarget, float r, float g, float b, float a);

    ID3D12GraphicsCommandList* GetCommandList() { return m_commandList; }

private:
    ID3D12CommandAllocator* m_commandAllocator;
    ID3D12GraphicsCommandList* m_commandList;
    D3D12_COMMAND_LIST_TYPE m_type;
};

} // CorvusEngine
