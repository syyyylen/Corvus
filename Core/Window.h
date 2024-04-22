#pragma once

#include <Windows.h>
#include <functional>

namespace CorvusEngine {

class Window
{

public:
    Window(int width, int height, LPCWSTR name);
    ~Window();

    void BroadCast();
    bool IsRunning() { return m_isRunning; }
    void Close();
    void OnResize(int width, int height);
    void DefineOnResize(std::function<void(int width, int height)> resizeFunc) { m_resize = resizeFunc; }

private:
    bool m_isRunning;
    HWND m_hwnd;

    std::function<void(int width, int height)> m_resize;
};

} // CorvusEngine
