
#ifndef _DRAWDEBUG_H_
#define _DRAWDEBUG_H_

#include <Box2D\Common\b2Draw.h>
#include "Header.h"

class SDL_b2Draw : public b2Draw
{
public:
	SDL_b2Draw() {}
	~SDL_b2Draw() {}

	virtual void DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	virtual void DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color);
	virtual void DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color);
	virtual void DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color);
	virtual void DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color);
	virtual void DrawTransform(const b2Transform& xf);
	virtual void DrawPoint(const b2Vec2& p, float32 size, const b2Color& color);
	
	void SetRenderer(SDL_Renderer* pRenderer) {m_pRenderer = pRenderer;}
	
private:
	SDL_Renderer* m_pRenderer;
};
#endif // !_DRAWDEBUG_H_

