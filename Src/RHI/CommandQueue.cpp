#include "CommandQueue.h"

#include "Fence.h"

namespace CorvusEngine {

CommandQueue::CommandQueue(std::shared_ptr<Device> device, D3D12_COMMAND_LIST_TYPE type) : m_device(device), m_type(type)
{
    D3D12_COMMAND_QUEUE_DESC desc = {};
    desc.Type = type;

    HRESULT hr = m_device->GetDevice()->CreateCommandQueue(&desc, IID_PPV_ARGS(&m_commandQueue));
    if(FAILED(hr))
    {
        LOG(Error, "CommandQueue : failed to create command queue !");
        std::string errorMsg = std::system_category().message(hr);
        LOG(Error, errorMsg);
    }
}

CommandQueue::~CommandQueue()
{
    m_commandQueue->Release();
}

void CommandQueue::Wait(std::shared_ptr<Fence> fence, uint64_t value)
{
    m_commandQueue->Wait(fence->GetFence(), value);
}

void CommandQueue::Submit(const std::vector<std::shared_ptr<CommandBuffer>> &buffers)
{
    std::vector<ID3D12CommandList*> lists;
    for (auto& buffer : buffers) {
        lists.push_back(buffer->GetCommandList());
    }

    m_commandQueue->ExecuteCommandLists(lists.size(), lists.data());
}

} // CorvusEngine