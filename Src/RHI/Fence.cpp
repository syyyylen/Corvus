#include "Fence.h"

namespace CorvusEngine {
Fence::Fence(std::shared_ptr<Device> device) : m_device(device), m_value(0)
{
    HRESULT hr = device->GetDevice()->CreateFence(m_value, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence));
    if(FAILED(hr))
    {
        LOG(Error, "Fence : failed to create fence !");
        std::string errorMsg = std::system_category().message(hr);
        LOG(Error, errorMsg);
    }
}

Fence::~Fence()
{
    m_fence->Release();
}

uint64_t Fence::Signal(std::shared_ptr<CommandQueue> commandQueue)
{
    m_value++;
    commandQueue->GetCommandQueue()->Signal(m_fence, m_value);
    return m_value;
}

void Fence::Wait(uint64_t target, uint64_t timeout)
{
    if (m_fence->GetCompletedValue() < target)
    {
        HANDLE event = CreateEvent(nullptr, false, false, nullptr);
        m_fence->SetEventOnCompletion(target, event);

        if(WaitForSingleObject(event, timeout) == WAIT_TIMEOUT)
            LOG(Error, "Fence : GPU Timeout !");
    }
}

} // CorvusEngine