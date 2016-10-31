
#include "Engine.h"


Engine* Engine::m_pInstance = nullptr;
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

	// Using opengGL
	//SDL_GL_CreateContext(m_pWindow);
	// start making opengl calls here
	//SDL_GL_SwapWindow(m_pWindow);

	return 0;
}

void Engine::ShutDown()
{
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
