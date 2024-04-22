#include "Window.h"

#include <iostream>

namespace CorvusEngine {

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    Window* window = reinterpret_cast<Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

    switch(msg)
    {
        case WM_CLOSE:
        {
            window->Close();
            break;
        }

        case WM_SIZE:
        {
            int width = LOWORD(lparam);
            int height = HIWORD(lparam);
            window->OnResize(width, height);
            break;
        }

        case WM_DESTROY:
        {
            window->Close();
            break;
        }

        default:
            return ::DefWindowProcW(hwnd, msg, wparam, lparam);
    }

    return 0;
}

Window::Window(int width, int height, LPCWSTR name)
{
    WNDCLASSEXW wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpszClassName = L"CorvusEngineWindowClass";
    wc.lpfnWndProc = &WndProc;

    if(!::RegisterClassExW(&wc))
        std::cout << "Error, window class not created" << std::endl;

    m_hwnd = ::CreateWindowExW(WS_EX_OVERLAPPEDWINDOW, wc.lpszClassName, name, WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, width, height, nullptr, nullptr, nullptr, this);

    if(!m_hwnd)
        std::cout << "Error, window not created" << std::endl;

    SetWindowLongPtr(m_hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

    ::ShowWindow(m_hwnd, SW_SHOW);
    ::UpdateWindow(m_hwnd);

    m_isRunning = true;
}

Window::~Window()
{
    ::DestroyWindow(m_hwnd);
}

void Window::BroadCast()
{
    MSG msg;
    while(PeekMessageW(&msg, NULL, 0, 0, PM_REMOVE) > 0)
    {
        ::TranslateMessage(&msg);
        ::DispatchMessageW(&msg);
    }
}

void Window::Close()
{
    m_isRunning = false;
}

void Window::OnResize(int width, int height)
{
    if(m_resize)
        m_resize(width, height);
}
} // CorvusEngine