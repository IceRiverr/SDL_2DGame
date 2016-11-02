
#include "GameTemplate.h"

GameTemplate::GameTemplate() : IGame()
{
	DotX = DotY = 0;
	VelX = VelY = 0;
	DotVel = 8;
	DotSize = 64;

	DotAngle = 0.0f;
	AngleVel = 180.0f;
}

GameTemplate::~GameTemplate()
{
	Destroy();
}

int GameTemplate::Init()
{
	Engine::GetEngine()->CreateWindowAndRenderer(640, 480, "Template");

	Camera.x = 0;
	Camera.y = 0;
	Camera.w = Engine::GetEngine()->ScreenW();
	Camera.h = Engine::GetEngine()->ScreenH();

	
	std::string Path = std::string(SDL_GetBasePath()) + "Resources\\Other\\bg.jpg";
	BgT = LoadImage(Engine::GetRenderer(), Path);
	SDL_QueryTexture(BgT, nullptr, nullptr, &MapW, &MapH);

	Path = std::string(SDL_GetBasePath()) + "Resources\\Other\\tile_134.png";
	DotT = LoadImage(Engine::GetRenderer(),Path);

	return 0;
}

void GameTemplate::Update(float dt)
{
	// Dot Move
	DotX += VelX;
	if (DotX < 0 || DotX + DotSize > MapW)
		DotX -= VelX;
	DotY += VelY;
	if (DotY < 0 || DotY + DotSize > MapH)
		DotY -= VelY;

	// Dot Rotate
	DotAngle += dt * AngleVel;
	if (DotAngle > 360.0f)
		DotAngle -= 360.0f;

	// Camera
	Camera.x = DotX + DotSize / 2 - Engine::GetEngine()->ScreenW() / 2;
	Camera.y = DotY + DotSize / 2 - Engine::GetEngine()->ScreenH()/ 2;
	if (Camera.x < 0) 
		Camera.x = 0;
	if (Camera.y < 0)
		Camera.y = 0;
	if (Camera.x > MapW - Camera.w)
		Camera.x = MapW - Camera.w;
	if (Camera.y > MapH - Camera.h)
		Camera.y = MapH - Camera.h;
}

void GameTemplate::Render()
{
	SDL_Renderer* pRen= Engine::GetRenderer();
	SDL_SetRenderDrawColor(pRen, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(pRen);

	SDL_RenderCopy(pRen,BgT,&Camera,nullptr);
	SDL_Rect destRect = {DotX - Camera.x,DotY - Camera.y ,DotSize,DotSize };
	//SDL_RenderCopy(pRen,DotT, nullptr, &destRect);

	SDL_Point center = { DotSize / 2, DotSize / 2 };
	SDL_RenderCopyEx(pRen, DotT, nullptr, &destRect, DotAngle, &center, SDL_FLIP_NONE);

	SDL_RenderPresent(pRen);
}

void GameTemplate::Destroy()
{

}

void GameTemplate::HandleEvent(SDL_Event& e)
{
	// If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			VelY -= DotVel;
			//std::cout << "Key Down" << std::endl;
			break;
		case SDLK_DOWN:	VelY += DotVel; break;
		case SDLK_LEFT: VelX -= DotVel; break;
		case SDLK_RIGHT: VelX += DotVel; break;
		}
	}
	else if (e.type == SDL_KEYDOWN && e.key.repeat == 1)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			std::cout << "Key Hold" << std::endl;
			break;
		}
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			VelY += DotVel;
			std::cout << "Key Up" << std::endl;
			break;
		case SDLK_DOWN:	VelY -= DotVel; break;
		case SDLK_LEFT: VelX += DotVel; break;
		case SDLK_RIGHT: VelX -= DotVel; break;
		}
	}
}

