#include "GameTetris.h"

GameTetris::GameTetris() : IGame()
{
	MapW = 10;
	MapH = 20;

	Grid = new SDL_Rect[(MapW + 1)*(MapH + 1)];
	TileSize = 32;
	TimeStep = 0.5f;

	Dir = Direction::Down;
	bCreateEnabled = false;
	table = new char[MapW*MapH];

	timerL = 0.0f;
	timerR = 0.0f;
	timerD = 0.0f;

}

GameTetris::~GameTetris()
{
	Destroy();
}

int GameTetris::Init()
{
	SDL_SetWindowSize(Engine::GetMainWindow(), 540, 720);
	SDL_SetWindowTitle(Engine::GetMainWindow(), "Tetris");

	MapArea = { 10,10, MapW * TileSize, MapH * MapH};
	PosX = MapW / 2;
	PosY = -1;
	bCreateEnabled = true;

	// Create grid
	for (int i = 0; i < MapW + 1; ++i)
	{
		SDL_Rect line = { i*TileSize + MapArea.x, 0 + MapArea.y, i*TileSize + MapArea.x, MapH*TileSize + MapArea.y };
		Grid[i] = line;
	}
	for (int i = 0; i < MapH + 1; ++i)
	{
		SDL_Rect line = { 0 + MapArea.x, i*TileSize + MapArea.y, MapW*TileSize + MapArea.x, i*TileSize + MapArea.y };
		Grid[MapW + 1 + i] = line;
	}

	// Tile 
	SDL_Renderer* pRen = Engine::GetRenderer();
	std::string TileP = std::string(SDL_GetBasePath()) + "Resources\\topdown_shooter\\PNG\\Tiles\\tile_196.png";
	TileT = LoadImage(pRen, TileP);

	// Table
	for (int i = 0; i < MapW*MapH; ++i)
		table[i] = 0;

	return 0;
}

void GameTetris::Update(float dt)
{
	if (bCreateEnabled == true)
	{
		PosX = MapW / 2;
		PosY = 0;
		bCreateEnabled = false;
		timerD = 0.0f;
	}

	// 玩家应该产生确定的反馈 此处在 ad同时按下的话，必然先处理a键的事件





	if (Dir == Direction::Left || Dir == Direction::Right)
	{
		timerD = 0.0f;
		timerL += dt;
		timerR += dt;
	}
	else if(Dir == Direction::Down)
	{
		timerD += dt;
		if (timerD > TimeStep)
		{
			timerD = 0.0f;
			PosY += 1;
		}
	}

	// check x y
	Clamp(PosX, 0, MapW - 1);
	/*if (Dir == Direction::Left)
	{
		if (table[PosY*MapW + PosX] == 1)
		{
			PosX += 1;
			Dir = Direction::Down;
		}
	}
	else if (Dir == Direction::Right)
	{
		if (table[PosY*MapW + PosX] == 1)
		{
			PosX -= 1;
			Dir = Direction::Down;
		}
	}*/
	
	Clamp(PosY, -1, MapH - 1);
	if (PosY == MapH - 1)
	{
		table[PosY * MapW + PosX] = 1;
		bCreateEnabled = true;
	}
	else
	{
		if (table[(PosY + 1) * MapW + PosX] == 1)
		{
			table[PosY * MapW + PosX] = 1;
			bCreateEnabled = true;
		}
	}

	
	
}

void GameTetris::Render()
{
	SDL_Renderer* pRen = Engine::GetRenderer();
	SDL_SetRenderDrawColor(pRen, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(pRen);

	SDL_Rect GameVP = { 0,0,540 - 200,720 };
	SDL_RenderSetViewport(pRen,&GameVP);

	SDL_SetRenderDrawColor(pRen, 0, 0xFF, 0, 0xFF);
	for (int i = 0; i < (MapW + 1) * (MapH + 1); ++i)
		SDL_RenderDrawLine(pRen,Grid[i].x,Grid[i].y, Grid[i].w,Grid[i].h);

	// Move Table
	SDL_Rect DestRect = { MapArea.x + PosX *TileSize, MapArea.y + PosY*TileSize, TileSize, TileSize };
	SDL_RenderCopy(pRen, TileT, nullptr, &DestRect);

	// Table
	for (int i = 0; i < MapW * MapH; ++i)
	{
		SDL_Rect tileRect = { MapArea.x + (i % MapW) * TileSize , MapArea.y + (i / MapW) * TileSize, TileSize, TileSize };
		if (table[i] == 1)
		{
			SDL_RenderCopy(pRen, TileT, nullptr, &tileRect);
		}
	}

	// Info ViewPort
	SDL_Rect InfoVP;
	InfoVP = { 540-200,0,100,720 };
	SDL_RenderSetViewport(pRen, &InfoVP);
	SDL_Rect TestRect = {0,0,80,30};
	SDL_RenderFillRect(pRen, &TestRect);

	SDL_RenderPresent(pRen);
}

void GameTetris::Destroy()
{
	SDL_DestroyTexture(TileT);
}

void GameTetris::HandleEvent(SDL_Event & e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			//SDL_Log("keyA:repeat-%d,state-%d,type-%d\n",e.key.repeat,e.key.state,e.key.type);
			Dir = Direction::Left;
			if (!e.key.repeat)
			{
				PosX -= 1;
			}
			else
			{
				if (timerL > TimeStep * 0.5f)
				{
					PosX -= 1;
					timerL = 0.0f;
				}
			}
			break;

		case SDLK_d:
			Dir = Direction::Right;
			if (!e.key.repeat)
			{
				PosX += 1;
			}
			else
			{
				if (timerR > TimeStep * 0.5f)
				{
					PosX += 1;
					timerR = 0.0f;
				}
			}
			break;

		case SDLK_s:
			{
				int tableIndex = (MapH - 1)* MapW + PosX;
				if (table[tableIndex] == 0)
				{
					PosY = MapH - 1;
					table[tableIndex] = 1;
				}
			}

			for (int i = PosY + 1; i < MapH; ++i)
			{
				int	tableIndex = i * MapW + PosX;
				if (table[tableIndex] == 1)
				{
					PosY = i - 1;
					break;
				}
			}
			break;

		default:
			break;
		}
	}
	else if (e.type == SDL_KEYUP)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_a:
			Dir = Direction::Down;
			break;

		case SDLK_d:
			Dir = Direction::Down;
			break;

		default:
			break;
		}
	}
}

void GameTetris::Clamp(int& x, int min, int max)
{
	x = x < min ? min : x;
	x = x > max ? max : x;
}


