
#pragma once
#include "IGame.h"
#include <Box2D\Box2D.h>
#include "Texture2D.h"
#include "MyBox.h"
#include "Bridge.h"

class GameBox2D : public IGame
{
public:
	GameBox2D();
	~GameBox2D();

	virtual int Init();
	virtual void Update(float dt);
	virtual void Render();
	virtual void Destroy();
	virtual void HandleEvent(SDL_Event& e);

private:
	SDL_Texture* BoxT;
	b2World* world;
	int32 velocityIterations;
	int32 positionIterations;

	float groundPoxX, groundPoxY;
	float groundBoxW, groundBoxH;

	Textrue2D* m_pBoxTex;

	int boxCount;
	MyBox** boxSet;
	
	float barW, barH;
	b2Vec2 barPos;
	b2Body* bar;
	b2Joint* reJ;
	SDL_Texture* BarT;

	Bridge* bridge;

};