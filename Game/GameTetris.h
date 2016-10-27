

#include "IGame.h"

enum Direction
{
	Left = 0,
	Right,
	Down,
};

class GameTetris : public IGame
{
public:
	GameTetris();
	~GameTetris();

	virtual int Init();
	virtual void Update(float dt);
	virtual void Render();
	virtual void Destroy();
	virtual void HandleEvent(SDL_Event& e);

	void Clamp(int& x, int min, int max);

private:
	int MapW;
	int MapH;
	SDL_Rect* Grid;
	SDL_Rect MapArea;

	int TileSize;
	int PosX;
	int PosY;

	Direction Dir;

	SDL_Texture* TileT;

	float TimeStep;

	bool bCreateEnabled;

	char* table;
	float timerL;
	float timerR;
	float timerD;


};