
#include "GamePhysics2D.h"

const int GamePhysics2D::m_nSpritePixel = 64;

int mapData[4][4] =
{
	{ 0,1,0,0 },
	{ 0,1,1,0 },
	{ 0,0,1,1 },
	{ 0,1,0,1 }
};

GamePhysics2D::GamePhysics2D() : IGame()
{
	m_pMainWindow = nullptr;
	acceleration = 500.0f;
	speed = 0.0f;
	direction = DirectionType::DOWN;
}

GamePhysics2D::~GamePhysics2D()
{
	Destroy();
}

int GamePhysics2D::Init()
{
	m_pMainWindow = new Window();
	m_pMainWindow->Init(800,600,"Physics2D");

	basePath = std::string(SDL_GetBasePath()) + "Resources\\topdown_shooter\\PNG\\Tiles\\";
	std::string tile1F = basePath + "tile_01.png";
	std::string tile2F = basePath + "tile_05.png";
	std::string backgroundF = basePath + "tile_73.png";
	std::string itemF = basePath + "tile_450.png";
	std::string playerF = basePath + "tile_133.png";
	
	posX = m_pMainWindow->m_nScreenW *0.5f;
	posY = 0.0f;
	m_Camera = { 0,0,m_pMainWindow->m_nScreenW , m_pMainWindow->m_nScreenH };
	m_nCameraMoveSpeed = 1;
	m_bCameraMoveFlag = true;

	try
	{
		tile1T = LoadImage(m_pMainWindow->m_pRenderer, tile1F);
		tile2T = LoadImage(m_pMainWindow->m_pRenderer, tile2F);
		backgroundT = LoadImage(m_pMainWindow->m_pRenderer, backgroundF);
		itemT = LoadImage(m_pMainWindow->m_pRenderer, itemF);
		SDL_SetTextureBlendMode(itemT, SDL_BLENDMODE_BLEND);
		playerT = LoadImage(m_pMainWindow->m_pRenderer,playerF);
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
		return -1;
	}

	tiles[0] = tile1T;
	tiles[1] = tile2T;

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			map[i][j] = mapData[i][j];
		}
	}

	SDL_Rect viewPort = {100,10,630,470};
	SDL_RenderSetViewport(m_pMainWindow->m_pRenderer, &viewPort);

	return 0;
}

void GamePhysics2D::Update(float dt)
{
	if (direction == DirectionType::DOWN && posY > m_pMainWindow->m_nScreenH - 64)
		direction = DirectionType::UP;
	if (direction == DirectionType::UP && posY < 0)
		direction = DirectionType::DOWN;
	
	if (direction == DirectionType::DOWN)
	{
		posY += dt * speed;
		speed = speed + acceleration* dt;
	}
	else if (direction == DirectionType::UP)
	{
		posY -= dt * speed;
		speed = speed - acceleration* dt;
	}

	if (m_bCameraMoveFlag)
	{
		std::cout << "Camera: " << m_Camera.x << "," << m_Camera.y << "." << std::endl;
		m_bCameraMoveFlag = false;
	}

}

void GamePhysics2D::Render()
{
	SDL_Renderer* pRen = m_pMainWindow->m_pRenderer;

#if 1
	SDL_SetRenderDrawColor(pRen, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(pRen);

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			int x = 100 + j * m_nSpritePixel - m_Camera.x;
			int y = 100 + i * m_nSpritePixel - m_Camera.y;

			RenderTexture(pRen, x, y,tiles[map[i][j]]);
		}
	}

	//SDL_RenderCopy(pRen, backgroundT, nullptr, nullptr);
	SDL_Rect itemPos = { 100 - m_Camera.x, 10 - m_Camera.y, m_nSpritePixel, m_nSpritePixel };
	SDL_RenderCopy(pRen, itemT, nullptr, &itemPos);

	RenderTexture(pRen, (int)posX - m_Camera.x, (int)posY - m_Camera.y, itemT);

	RenderTexture(pRen, (m_pMainWindow->m_nScreenW - m_nSpritePixel) / 2 , (m_pMainWindow->m_nScreenH - m_nSpritePixel) / 2, playerT);

	{
		SDL_Rect rect = { 10,10,50,50 };
		SDL_SetRenderDrawColor(pRen, 0xFF, 0, 0, 0xFF);
		SDL_RenderFillRect(pRen, &rect);

		SDL_Rect rect1 = { 10,70,50,50 };
		SDL_RenderDrawRect(pRen, &rect1);

		SDL_RenderDrawLine(pRen, 10, 129, 200, 129);
		SDL_RenderDrawLine(pRen, 10, 130, 200, 130);
		SDL_RenderDrawLine(pRen, 10, 131, 200, 131);

		/*SDL_RenderDrawLine(pRen, 10, 130, 200, 130);

		SDL_Point p1 = { 10, 140 };
		SDL_RenderDrawPoint(pRen, p1.x, p1.y);

		SDL_Point points[16];
		for (int i = 0; i < 16; ++i)
		{
			points[i].x = i % 4 + p1.x + 10;
			points[i].y = i / 4 + p1.y;
		}
		SDL_RenderDrawPoints(pRen, points, 16);*/
	}

	SDL_RenderPresent(pRen);

#endif

#if 0 // render to texture
	SDL_Texture* pRenderTarget = SDL_CreateTexture(pRen, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Engine::GetEngine()->m_nWidth, Engine::GetEngine()->m_nHeight);
	SDL_SetRenderTarget(pRen,pRenderTarget);
	SDL_SetRenderDrawColor(pRen, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(pRen);

	// draw...
	SDL_Rect rect = { 10,10,50,50 };
	SDL_SetRenderDrawColor(pRen, 0xFF, 0, 0, 0xFF);
	SDL_RenderFillRect(pRen, &rect);

	SDL_SetRenderTarget(pRen,nullptr);
	SDL_RenderCopy(pRen, pRenderTarget, nullptr, nullptr);
	SDL_RenderPresent(pRen);
#endif

}

void GamePhysics2D::Destroy()
{
	SDL_DestroyTexture(tile1T);
	SDL_DestroyTexture(backgroundT);
	SDL_DestroyTexture(itemT);
}

void GamePhysics2D::HandleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN)
	{
		switch (e.key.keysym.sym)
		{

		case SDLK_a:
			m_Camera.x -= m_nCameraMoveSpeed;
			m_bCameraMoveFlag = true;

		/*	std::cout << e.key.timestamp << std::endl;
			std::cout << SDL_GetTicks() << std::endl;
			std::cout << e.key.state << std::endl;
			std::cout << e.key.repeat << std::endl;*/
			
			break;

		case SDLK_d:
			m_Camera.x += m_nCameraMoveSpeed;
			m_bCameraMoveFlag = true;

			break;

		case SDLK_w:
			m_Camera.y -= m_nCameraMoveSpeed;
			m_bCameraMoveFlag = true;

			break;

		case SDLK_s:
			m_Camera.y += m_nCameraMoveSpeed;
			m_bCameraMoveFlag = true;

			break;

		default:
			break;
		}
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		/*if (e.button.clicks == 1)
			std::cout << "Mosue click 1" << std::endl;
		else if (e.button.clicks == 2)
			std::cout << "Mouse click 2" << std::endl;
		
		std::cout << "Mouse pos:" << e.button.x << "," << e.button.y << std::endl;*/
	}
	else if (e.type == SDL_MOUSEMOTION)
	{
		//SDL_Log("Mouse motion: %d, %d, %d, %d\n",e.motion.x, e.motion.y,e.motion.xrel,e.motion.yrel);
	}
	else if (e.type == SDL_MOUSEWHEEL)
	{
		//SDL_Log("Mouse wheel: dir %d, %d, %d\n", e.wheel.direction, e.wheel.x, e.wheel.y);
	}

}

