
#include "Header.h"
#include "Tool.h"
#include "Engine.h"
#include "GameLearn.h"
#include "GamePhysics2D.h"
#include "GameTetris.h"
#include "GameTemplate.h"
#include "GameARPG.h"
#include "GameBox2D.h"
#include "GameFractal.h"

#ifdef main
#undef main

int main(int, char**) 
{
	Engine* pEngine = new Engine();
	pEngine->Init();

	IGame* pGame = new GameBox2D();
	pGame->Init();

	Uint32 currentTime = SDL_GetTicks();
	Uint32 previousTime = currentTime;
	double deltaTime = 0.0f;
	double lag = 0.0;
	
	SDL_Event event;
	bool bQuit = false;
	while (!bQuit)
	{
		while (SDL_PollEvent(&event))
		{
			if (SDL_QUIT == event.type)
			{
				bQuit = true;
			}
			
			pGame->HandleEvent(event);
		}

		currentTime = SDL_GetTicks();
		deltaTime = (currentTime - previousTime) * 0.001f;
		previousTime = currentTime;
		lag += deltaTime;

		while (lag >= Engine::MS_PER_UPDATE)
		{
			pGame->Update(Engine::MS_PER_UPDATE);
			lag -= Engine::MS_PER_UPDATE;
		}

		pGame->Render();
	}
	
	delete pGame;
	pEngine->ShutDown();
	delete pEngine;

	return 0;
}

#endif // main