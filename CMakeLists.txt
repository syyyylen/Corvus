cmake_minimum_required(VERSION 3.28)
project(Corvus)

set(CMAKE_CXX_STANDARD 17)

add_executable(Corvus main.cpp
        Src/Window.cpp
        Src/Window.h
        Src/CorvusEditor.cpp
        Src/CorvusEditor.h
        Src/Logger.cpp
        Src/Logger.h
        External/D3D12MA/D3D12MemAlloc.h
        External/D3D12MA/D3D12MemAlloc.cpp
        Src/RHI/Renderer.cpp
        Src/RHI/Renderer.h
        Src/RHI/Device.cpp
        Src/RHI/Device.h
        Src/RHI/CommandQueue.cpp
        Src/RHI/CommandQueue.h
        Core/Core.h
        Src/RHI/DescriptorHeap.cpp
        Src/RHI/DescriptorHeap.h
        Src/RHI/Allocator.cpp
        Src/RHI/Allocator.h
        Src/RHI/Fence.cpp
        Src/RHI/Fence.h
        Src/RHI/SwapChain.cpp
        Src/RHI/SwapChain.h
        Src/RHI/Texture.cpp
        Src/RHI/Texture.h
        Src/RHI/CommandBuffer.cpp
        Src/RHI/CommandBuffer.h)

target_include_directories(Corvus PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/External)
target_include_directories(Corvus PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Core)

target_link_libraries(Corvus
        d3d12.lib
        dxgi.lib
        dxguid.lib)