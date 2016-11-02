
#include "Window.h"

Window::Window()
{
	m_pWindow = nullptr;
	m_pRenderer = nullptr;
	m_Title = nullptr;
	m_nScreenW = 0;
	m_nScreenH = 0;

	m_bMouseFocus = false;
	m_bKeyboardFocus = false;
}

Window::~Window()
{
	Destroy();
}

void Window::Destroy()
{
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
}

int Window::Init(int w, int h, char* title)
{
	m_nScreenW = w;
	m_nScreenH = h;
	m_Title = title;

	m_pWindow = SDL_CreateWindow(m_Title, 100, 100, m_nScreenW, m_nScreenH, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (!m_pWindow)
	{
		std::cout << SDL_GetError() << std::endl;
		return -1;
	}

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!m_pRenderer)
	{
		std::cout << SDL_GetError() << std::endl;
		return -1;
	}
	return 0;
}

void  Window::HandleEvent(SDL_Event& e)
{
	if (e.type == SDL_WINDOWEVENT)
	{
		switch (e.window.event)
		{
			case SDL_WINDOWEVENT_SIZE_CHANGED:
				m_nScreenW = e.window.data1;
				m_nScreenH = e.window.data2;
				SDL_RenderPresent(m_pRenderer);
				break;

			case SDL_WINDOWEVENT_EXPOSED:
				SDL_RenderPresent(m_pRenderer);
				break;

			case SDL_WINDOWEVENT_ENTER:
				m_bMouseFocus = true;
				break;

			case SDL_WINDOWEVENT_LEAVE:
				m_bMouseFocus = false;
				break;

			case SDL_WINDOWEVENT_FOCUS_GAINED:
				m_bKeyboardFocus = true;
				break;

			case SDL_WINDOWEVENT_FOCUS_LOST:
				m_bKeyboardFocus = false;
				break;
		}
			
	}
}