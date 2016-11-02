
#include "Engine.h"

Engine* Engine::m_pInstance = nullptr;
Camera* Engine::m_pCamera = nullptr;
SDL_Window* Engine::m_pWindow = nullptr;
SDL_Renderer* Engine::m_pRenderer = nullptr;

Engine::Engine()
{
	m_pInstance = this;
	m_EngineConfig.PixelSize = 16;
	m_EngineConfig.FixedUpdateMS = 1.0 / 60.0;
}

Engine::~Engine()
{

}

int Engine::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO |SDL_INIT_TIMER) != 0)
	{
		std::cout << SDL_GetError() << std::endl;
		return -1;
	}

	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP) == 0)
	{
		std::cout << SDL_GetError() << std::endl;
		return -1;
	}

	if (TTF_Init() == -1)
	{
		std::cout << SDL_GetError() << std::endl;
		return -1;
	}
	return 0;
}

void Engine::ShutDown()
{
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);

	ENGINE_DELETE(m_pCamera);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int Engine::CreateCamera(int x, int y, int w, int h)
{
	m_pCamera = new Camera(x, y, w, h);
	return 0;
}

int Engine::CreateWindowAndRenderer(int w, int h, char * title)
{
	m_WindowInfo.ScreenW = w;
	m_WindowInfo.ScreenH = h;
	m_WindowInfo.Title = title;
	
	m_pWindow = SDL_CreateWindow(title, 100, 100, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
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
}

void WindowHandleEvent(SDL_Event& e)
{
	WindowInfo& winInfo = Engine::GetEngine()->GetWindowInfo();

	if (e.type == SDL_WINDOWEVENT)
	{
		switch (e.window.event)
		{
		case SDL_WINDOWEVENT_SIZE_CHANGED:
			winInfo.ScreenW = e.window.data1;
			winInfo.ScreenH = e.window.data2;
			SDL_RenderPresent(Engine::GetRenderer());
			break;

		case SDL_WINDOWEVENT_EXPOSED:
			SDL_RenderPresent(Engine::GetRenderer());
			break;

		case SDL_WINDOWEVENT_ENTER:
			winInfo.bMouseFocus = true;
			break;

		case SDL_WINDOWEVENT_LEAVE:
			winInfo.bMouseFocus = false;
			break;

		case SDL_WINDOWEVENT_FOCUS_GAINED:
			winInfo.bKeyboardFocus = true;
			break;

		case SDL_WINDOWEVENT_FOCUS_LOST:
			winInfo.bKeyboardFocus = false;
			break;
		}
	}
}
