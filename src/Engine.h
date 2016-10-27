
#pragma once
#include "Header.h"

class Engine
{
public:
	Engine();
	~Engine();

	// 0 ok -1 error
	int Init();
	void ShutDown();

	static SDL_Renderer*  GetRenderer();
	static SDL_Window* GetMainWindow();
	static Engine* GetEngine() { return m_pInstance; }

	static void SetScreenSize(int w, int h);

private:
	static SDL_Renderer* m_pRenderer;
	static SDL_Window* m_pWindow;
	static Engine* m_pInstance;

public:
	static int m_nScreenW;
	static int m_nScreenH;

	static int PIXEL_PER_METER;
	static double MS_PER_UPDATE;
	static float TIME_STEP;
};