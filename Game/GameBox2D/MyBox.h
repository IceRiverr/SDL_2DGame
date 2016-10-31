
#pragma once
#include "Header.h"
#include <Box2D\Box2D.h>
#include "Texture2D.h"
#include "Engine.h"

class MyBox
{
public:
	float x, y;
	float w, h;
	b2World* world;
	b2Body* body;
	Textrue2D* sprite;
	MyBox() :x(0), y(0), w(0), h(0) {}

	MyBox(float x_, float y_, float w_, float h_)
		: x(x_), y(y_), w(w_), h(h_)
	{

	}

	~MyBox()
	{
		sprite->Release();
		world->DestroyBody(body);
	}

	void Init(b2World* world_)
	{
		world = world_;

		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(x, y);
		bodyDef.angle = 0.0f;
		bodyDef.linearDamping = 0.0f;
		bodyDef.angularDamping = 0.0f;
		bodyDef.allowSleep = true;
		bodyDef.awake = true;
		//bodyDef.userData = sprite;

		body = world->CreateBody(&bodyDef);

		b2PolygonShape bodyShape;
		bodyShape.SetAsBox(w / 2, h / 2);

		b2FixtureDef fixtureDef;
		fixtureDef.shape = &bodyShape;
		fixtureDef.density = 1.0f;
		fixtureDef.friction = 0.3f;
		fixtureDef.restitution = 1.0f;// 恢复力
		//fixtureDef.filter.categoryBits = 0x0001;//碰撞属性
		//fixtureDef.filter.maskBits = 0x0002;	// 和其他属性的碰撞mask
		//fixtureDef.filter.groupIndex = 1;// 同样组索引内的body都会碰撞；-1不会碰撞；
		body->CreateFixture(&fixtureDef);

		/*b2MassData massData;
		massData.mass = 1.0f;
		massData.center = b2Vec2(0.0f, 0.0f);
		massData.I = 1.0f;
		body->SetMassData(&massData);*/
	}

	void SetSprite(Textrue2D* pSprite)
	{
		sprite = pSprite;
		pSprite->AddRef();
	}

	SDL_Rect GetRenderRect(int screenW, int screenH)
	{
		b2Vec2 position = body->GetPosition();
		SDL_Rect rt = { static_cast<int>((position.x - w / 2) * Engine::PIXEL_PER_METER), static_cast<int>(screenH - (position.y + h / 2) *Engine::PIXEL_PER_METER), static_cast<int>(w * Engine::PIXEL_PER_METER), static_cast<int>(h*Engine::PIXEL_PER_METER) };
		return rt;
	}

	float GetAngle()
	{
		float angle = body->GetAngle() * 57.29577951f;
		return angle;
	}

	SDL_Point GetCenter()
	{
		SDL_Point center = { static_cast<int>(w * 0.5f * Engine::PIXEL_PER_METER), static_cast<int>(h * 0.5f * Engine::PIXEL_PER_METER) };
		return center;
	}

	void Render(SDL_Renderer* pRen, int screenW, int screenH)
	{
		SDL_RenderCopyEx(pRen, sprite->m_pTex, nullptr, &GetRenderRect(screenW, screenH), GetAngle(), &GetCenter(), SDL_FLIP_NONE);
	}
};
