#pragma once
#include "Header.h"
#include <Box2D\Box2D.h>
#include "Engine.h"

class Bridge
{
public:
	Bridge()
	{
		bridgeCount = 20;
		bridge = new b2Body*[bridgeCount];
		boxW = 2.0f;
		boxH = 0.5f;
	}

	void SetPos(float x, float y)
	{
		pos = b2Vec2(x, y);
	}

	void Create(b2World* world, b2Body* ground)
	{
		b2PolygonShape boxShap;
		boxShap.SetAsBox(boxW * 0.5f, boxH * 0.5f);

		b2FixtureDef fd;
		fd.shape = &boxShap;
		fd.density = 100.0f;
		fd.friction = 0.5f;

		b2RevoluteJointDef rj;
		b2Vec2 anchor;
		b2Body* preBody = ground;

		for (int i = 0; i < bridgeCount; ++i)
		{
			b2BodyDef bd;
			bd.type = b2_dynamicBody;
			bd.position.Set(pos.x + boxW * 0.5f + i * boxW, pos.y);
			bridge[i] = world->CreateBody(&bd);
			bridge[i]->CreateFixture(&fd);

			anchor = b2Vec2(pos.x + i * boxW, pos.y);
			rj.Initialize(preBody, bridge[i], anchor);
			world->CreateJoint(&rj);

			preBody = bridge[i];
		}
		anchor = b2Vec2(pos.x + bridgeCount* boxW, pos.y);
		rj.Initialize(preBody, ground, anchor);
		world->CreateJoint(&rj);
	}

	void Render(SDL_Renderer* pRen,SDL_Texture* sprite, int screenW, int screenH)
	{
		for (int i = 0; i < bridgeCount; ++i)
		{
			b2Vec2 worldPos = bridge[i]->GetPosition();
			float angle = -bridge[i]->GetAngle() * degreePerRadian;

			SDL_Rect destRect = { (worldPos.x - boxW*0.5f) * Engine::PIXEL_PER_METER, 
									screenH - (worldPos.y + boxH*0.5f) * Engine::PIXEL_PER_METER,
									boxW * Engine::PIXEL_PER_METER, boxH * Engine::PIXEL_PER_METER};

			SDL_Point center = { 0.5f * boxW * Engine::PIXEL_PER_METER, 0.5f * boxH * Engine::PIXEL_PER_METER };
		
			SDL_RenderCopyEx(pRen, sprite, nullptr, &destRect, angle, &center, SDL_FLIP_NONE);
		}
	}

	/*b2Vec2 GetStartAnchor();
	b2Vec2 GetEndAnchor();*/

private:
	b2Vec2 pos;
	int bridgeCount = 20;
	b2Body** bridge;
	float boxW, boxH;
	float degreePerRadian = 57.2775475f;
};