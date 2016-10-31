
#pragma once
#include "IGame.h"
#include <vector>
#include "Window.h"

struct Triangle
{
	float x;
	float y;
	float scale;
};

struct Point
{
	float x;
	float y;
};

class GameFractal : public IGame
{
public:
	GameFractal();
	~GameFractal();

	virtual int Init();
	virtual void Update(float dt);
	virtual void Render();
	virtual void Destroy();
	virtual void HandleEvent(SDL_Event& e);

	void Test1();
	void DrawTri(SDL_Renderer* pRen, const Triangle& t);
	void GenTri(const Triangle& t, int step);

private:
	Window* m_pMainWindow;
	SDL_Texture* BoxT;
	const static int BOX_SIZE;


	std::vector<Triangle> Trs;
};