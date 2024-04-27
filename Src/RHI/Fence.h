#pragma once
#include "CommandQueue.h"
#include "Device.h"
#include <Core.h>

namespace CorvusEngine {

class Fence 
{
public:
    Fence(std::shared_ptr<Device> device);
    ~Fence();

    uint64_t Signal(std::shared_ptr<CommandQueue> commandQueue);
    void Wait(uint64_t target, uint64_t timeout);

    ID3D12Fence* GetFence() { return m_fence; }
    uint64_t GetValue() { return m_value; }

private:
    std::shared_ptr<Device> m_device;
    uint64_t m_value;
    ID3D12Fence* m_fence;
};

} // CorvusEngine
