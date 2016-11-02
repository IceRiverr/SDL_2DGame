
#pragma once
#include "Header.h"
#include "Camera.h"

/**
 * 1 ��Ϸ����ʹ�� m ��Ϊ��λ
 * 2 �����ԭ�������£�
 * 
 *
 *
 */


class Engine
{
public:
	Engine();
	~Engine();

	// 0 ok -1 error
	int Init();
	void ShutDown();

	void CreateCamera(int x, int y, int w, int h);

	static Engine& GetEngine() { return *m_pInstance; }
	static Camera& GetCamera() { return *m_pCamera; }


private:
	static Engine* m_pInstance;
	static Camera* m_pCamera;

public:
	static int PIXEL_PER_METER;
	static double MS_PER_UPDATE;
	static float TIME_STEP;
};