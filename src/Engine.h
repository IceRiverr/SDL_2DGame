
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

	static Engine* GetEngine() { return m_pInstance; }

private:
	static Engine* m_pInstance;

public:
	static int PIXEL_PER_METER;
	static double MS_PER_UPDATE;
	static float TIME_STEP;
};