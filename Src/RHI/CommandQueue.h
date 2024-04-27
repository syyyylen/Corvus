#pragma once
#include <Core.h>

#include "CommandBuffer.h"
#include "Device.h"

namespace CorvusEngine {
class Fence;

class CommandQueue
{
public:
    CommandQueue(std::shared_ptr<Device> device, D3D12_COMMAND_LIST_TYPE type);
    ~CommandQueue();

    ID3D12CommandQueue* GetCommandQueue() { return m_commandQueue; }

    void Wait(std::shared_ptr<Fence> fence, uint64_t value);
    void Submit(const std::vector<std::shared_ptr<CommandBuffer>>& buffers);

    D3D12_COMMAND_LIST_TYPE GetType() { return m_type; }

private:
    std::shared_ptr<Device> m_device;
    D3D12_COMMAND_LIST_TYPE m_type;
    ID3D12CommandQueue* m_commandQueue;
};

} // CorvusEngine