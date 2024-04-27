#include "CommandBuffer.h"

namespace CorvusEngine {
CommandBuffer::CommandBuffer(std::shared_ptr<Device> device, D3D12_COMMAND_LIST_TYPE commandQueueType) : m_type(commandQueueType)
{
    HRESULT hr = device->GetDevice()->CreateCommandAllocator(m_type, IID_PPV_ARGS(&m_commandAllocator));
    if(FAILED(hr))
    {
        LOG(Error, "CommandBuffer : failed to create command allocator !");
        std::string errorMsg = std::system_category().message(hr);
        LOG(Error, errorMsg);
    }

    hr = device->GetDevice()->CreateCommandList(0, m_type, m_commandAllocator, nullptr, IID_PPV_ARGS(&m_commandList));
    if(FAILED(hr))
    {
        LOG(Error, "CommandBuffer : failed to create command list !");
        std::string errorMsg = std::system_category().message(hr);
        LOG(Error, errorMsg);
    }

    hr = m_commandList->Close();
    if(FAILED(hr))
    {
        LOG(Error, "CommandBuffer : failed to close command list !");
        std::string errorMsg = std::system_category().message(hr);
        LOG(Error, errorMsg);
    }
}

CommandBuffer::~CommandBuffer()
{
    m_commandList->Release();
    m_commandAllocator->Release();
}

void CommandBuffer::Begin()
{
    m_commandAllocator->Reset();
    m_commandList->Reset(m_commandAllocator, nullptr);
}

void CommandBuffer::End()
{
    m_commandList->Close();
}

void CommandBuffer::ImageBarrier(std::shared_ptr<Texture> texture, D3D12_RESOURCE_STATES state)
{
    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Transition.pResource = texture->GetResource().Resource;
    barrier.Transition.StateBefore = texture->GetState();
    barrier.Transition.StateAfter = state;
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

    if (barrier.Transition.StateBefore == barrier.Transition.StateAfter)
        return;

    m_commandList->ResourceBarrier(1, &barrier);

    texture->SetState(state);
}

void CommandBuffer::BindRenderTargets(const std::vector<std::shared_ptr<Texture>> renderTargets, std::shared_ptr<Texture> depthTarget)
{
    std::vector<D3D12_CPU_DESCRIPTOR_HANDLE> rtvDescriptors;
    D3D12_CPU_DESCRIPTOR_HANDLE dsvDescriptor;

    for (auto& renderTarget : renderTargets) {
        rtvDescriptors.push_back(renderTarget->m_rtv.CPU);
    }
    if (depthTarget) {
        dsvDescriptor = depthTarget->m_dsv.CPU;
    }

    m_commandList->OMSetRenderTargets(rtvDescriptors.size(), rtvDescriptors.data(), false, depthTarget ? &dsvDescriptor : nullptr);
}

void CommandBuffer::ClearRenderTarget(std::shared_ptr<Texture> renderTarget, float r, float g, float b, float a)
{
    float clearValues[4] = { r, g, b, a };
    m_commandList->ClearRenderTargetView(renderTarget->m_rtv.CPU, clearValues, 0, nullptr);
}
} // CorvusEngine