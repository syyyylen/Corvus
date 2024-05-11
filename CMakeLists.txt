cmake_minimum_required(VERSION 3.28)
project(Corvus)

set(CMAKE_CXX_STANDARD 17)

add_executable(Corvus main.cpp
        External/D3D12MA/D3D12MemAlloc.h
        External/D3D12MA/D3D12MemAlloc.cpp
        Src/Window.cpp
        Src/Window.h
        Src/CorvusEditor.cpp
        Src/CorvusEditor.h
        Src/Logger.cpp
        Src/Logger.h
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
        Src/RHI/SwapChain.cpp
        Src/RHI/SwapChain.h
        Src/RHI/Texture.cpp
        Src/RHI/Texture.h
        Src/RHI/CommandList.cpp
        Src/RHI/CommandList.h
        External/ImGui/imconfig.h
        External/ImGui/imgui.cpp
        External/ImGui/imgui.h
        External/ImGui/imgui_demo.cpp
        External/ImGui/imgui_draw.cpp
        External/ImGui/imgui_impl_dx12.cpp
        External/ImGui/imgui_impl_dx12.h
        External/ImGui/imgui_impl_win32.cpp
        External/ImGui/imgui_impl_win32.h
        External/ImGui/imgui_internal.h
        External/ImGui/imgui_tables.cpp
        External/ImGui/imgui_widgets.cpp
        External/ImGui/imstb_rectpack.h
        External/ImGui/imstb_textedit.h
        External/ImGui/imstb_truetype.h
        Src/ShaderCompiler.cpp
        Src/ShaderCompiler.h
        Src/RHI/GraphicsPipeline.cpp
        Src/RHI/GraphicsPipeline.h
        Src/RHI/Buffer.cpp
        Src/RHI/Buffer.h
        Src/RHI/Uploader.cpp
        Src/RHI/Uploader.h)

target_include_directories(Corvus PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/External)
target_include_directories(Corvus PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Core)

target_link_directories(Corvus PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/bin)

target_link_libraries(Corvus PUBLIC
        d3d12.lib
        dxgi.lib
        dxcompiler.lib)