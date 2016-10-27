
#include "Engine.h"

SDL_Renderer* Engine::m_pRenderer = nullptr;
SDL_Window* Engine::m_pWindow = nullptr;
Engine* Engine::m_pInstance = nullptr;
int Engine::m_nScreenW = 800;
int Engine::m_nScreenH = 600;
int Engine::PIXEL_PER_METER = 16;
double Engine::MS_PER_UPDATE = 1.0 / 60.0;
float Engine::TIME_STEP = Engine::MS_PER_UPDATE;

Engine::Engine()
{
	m_pInstance = this;
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

	m_pWindow = SDL_CreateWindow("HelloWorld", 100, 100, m_nScreenW, m_nScreenH, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
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

	// Using opengGL
	//SDL_GL_CreateContext(m_pWindow);
	// start making opengl calls here
	//SDL_GL_SwapWindow(m_pWindow);


	return 0;
}

void Engine::ShutDown()
{
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

SDL_Renderer* Engine::GetRenderer()
{
	return m_pRenderer;
}

SDL_Window* Engine::GetMainWindow()
{
	return m_pWindow;
}

void  Engine::SetScreenSize(int w, int h)
{
	m_nScreenW = w;
	m_nScreenH = h;
	SDL_SetWindowSize(m_pWindow, m_nScreenW, m_nScreenH);
}
