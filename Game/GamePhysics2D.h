
#include "IGame.h"
#include <vector>

enum DirectionType
{
	UP = 0,
	DOWN,
};

class GamePhysics2D : public IGame
{
public:
	GamePhysics2D();
	~GamePhysics2D();

	virtual int Init();
	virtual void Update(float dt);
	virtual void Render();
	virtual void Destroy();
	virtual void HandleEvent(SDL_Event& e);

private:
	std::string basePath;
	SDL_Texture* tile1T;
	SDL_Texture* tile2T;
	SDL_Texture* backgroundT;
	SDL_Texture* itemT;
	SDL_Texture* playerT;

	float speed;
	float acceleration;
	float posX, posY;

	DirectionType direction;

	SDL_Rect m_Camera;
	int m_nCameraMoveSpeed;
	bool m_bCameraMoveFlag;

	const static int m_nSpritePixel;

	SDL_Texture* tiles[2];
	int map[4][4];
};