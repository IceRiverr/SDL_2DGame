
#pragma once
#include "Header.h"
#include "Camera.h"

/**
 * 1 游戏世界使用 m 作为单位
 * 2 坐标的原点在左下；
 * 
 *
 *
 */

struct EngineConfig
{
	int PixelSize;
	double FixedUpdateMS;
};

struct WindowInfo
{
	int ScreenW;
	int ScreenH;

	char* Title;
	bool bMouseFocus;
	bool bKeyboardFocus;
};

class Engine
{
public:
	Engine();
	~Engine();

	int Init();
	void ShutDown();

	int CreateCamera(int x, int y, int w, int h);
	int CreateWindowAndRenderer(int w, int h, char* title);

	void SetPixelSize(int pixelPerMeter) { m_EngineConfig.PixelSize = pixelPerMeter; }

	static Engine* GetEngine()			{ return m_pInstance; }
	static Camera* GetCamera()			{ return m_pCamera; }
	static SDL_Window* GetWindow()		{ return m_pWindow; }
	static SDL_Renderer* GetRenderer()	{ return m_pRenderer; }
	WindowInfo& GetWindowInfo()			{ return m_WindowInfo; }
	int ScreenW()						{ return m_WindowInfo.ScreenW; }
	int ScreenH()						{ return m_WindowInfo.ScreenH; }
	int PixelSize()						{ return m_EngineConfig.PixelSize; }
	double FixedUpdateMS()				{ return m_EngineConfig.FixedUpdateMS; }
	
private:
	static Engine* m_pInstance;
	static Camera* m_pCamera;
	static SDL_Window* m_pWindow;
	static SDL_Renderer* m_pRenderer;

	WindowInfo m_WindowInfo;
	EngineConfig m_EngineConfig;
};

void WindowHandleEvent(SDL_Event& e);