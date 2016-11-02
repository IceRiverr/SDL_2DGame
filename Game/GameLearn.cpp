
#include "GameLearn.h"
#include "Tool.h"
#include "Engine.h"

GameLearn::GameLearn():IGame()
{
	clipIndex = 0;
	posX = 0;
	posY = 0;
	angle = 0;
	deltaTime = 0.0f;
}

GameLearn::~GameLearn()
{
	Destroy();
}

int GameLearn::Init()
{
	Engine::GetEngine()->CreateWindowAndRenderer(800, 600, "SDL_Learn");
	
	std::string resourcePath = std::string(SDL_GetBasePath()) + "Resources\\";
	std::string BackgroundPath = resourcePath + "background.png";
	std::string imagePath = resourcePath + "image.png";
	std::string image1Path = resourcePath + "image1.png";
	std::string imageSheetPath = resourcePath + "image_sheet.png";
	fontPath = resourcePath + "SourceSansPro-Regular.ttf";

	try
	{
		pBackgroundTex = LoadImage(Engine::GetRenderer(), BackgroundPath);
		pImageTex = LoadImage(Engine::GetRenderer(), imagePath);
		pImage1Tex = LoadImage(Engine::GetRenderer(), image1Path);
		pImageSheetTex = LoadImage(Engine::GetRenderer(), imageSheetPath);

		SDL_Color fontColor = { 0,0, 0,255 };
		pTextTex = RenderText(Engine::GetRenderer(), "TTF font is cool!!! HHH", fontPath, fontColor, 32);
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
		return -1;
	}

	time = SDL_GetTicks();

	const int step = 100;
	for (int i = 0; i < 4; ++i)
	{
		clips[i].x = step * (i % 2);
		clips[i].y = step * (i / 2);
		clips[i].w = step;
		clips[i].h = step;
	}

	pCurrImageTex = pImageTex;

	return 0;
}

void GameLearn::Update(float dt)
{
	Uint32 currTime = SDL_GetTicks();
	deltaTime = (currTime - time) * 0.001f;
	time = currTime;
}

void GameLearn::Render()
{
	SDL_RenderClear(Engine::GetRenderer());
	int w, h;
	SDL_QueryTexture(pBackgroundTex, NULL, NULL, &w, &h);
	RenderTexture(Engine::GetRenderer(), 0, 0, pBackgroundTex);
	RenderTexture(Engine::GetRenderer(), w, 0, pBackgroundTex);
	RenderTexture(Engine::GetRenderer(), 0, h, pBackgroundTex);
	RenderTexture(Engine::GetRenderer(), w, h, pBackgroundTex);

	SDL_QueryTexture(pCurrImageTex, NULL, NULL, &w, &h);
	int x = Engine::GetEngine()->ScreenW() / 2 - w / 2;
	int y = Engine::GetEngine()->ScreenH() / 2 - h / 2;

	RenderTexture(Engine::GetRenderer(), x, y, pCurrImageTex);

	RenderTexture(Engine::GetRenderer(), posX, posY, pImageSheetTex, &clips[clipIndex]);
	RenderTexture(Engine::GetRenderer(), posX, posY, pTextTex);

	float deltaTime = time / 1000.0f;
	deltaTime = ((int)(deltaTime * 10.0f)) / 10.0f;
	std::stringstream ss;
	ss << deltaTime;

	std::string currTime = "Time: " + ss.str();
	SDL_Color fontColor = { 0,0, 0,255 };
	pTimeTex = RenderText(Engine::GetRenderer(), currTime, fontPath, fontColor, 32);

	RenderTexture(Engine::GetRenderer(), posX, posY + 100, pTimeTex);

	SDL_Rect destRect = { 100, 100, 200, 200 };
	SDL_Point pivot = { 100, 100 };

	SDL_RenderCopyEx(Engine::GetRenderer(), pImageTex, NULL, &destRect, angle, &pivot, SDL_FLIP_NONE);
	

	SDL_RenderPresent(Engine::GetRenderer());
}

void GameLearn::Destroy()
{
	SDL_DestroyTexture(pBackgroundTex);
	SDL_DestroyTexture(pImageTex);
	SDL_DestroyTexture(pImage1Tex);
	SDL_DestroyTexture(pImageSheetTex);
	SDL_DestroyTexture(pTextTex);
	SDL_DestroyTexture(pTimeTex);
}

void GameLearn::HandleEvent(SDL_Event& e)
{
	if (SDL_KEYDOWN == e.type)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_ESCAPE:
			break;

		case SDLK_a:
			//pCurrImageTex = pImageTex;
			clipIndex++;
			if (clipIndex == 4) clipIndex = 0;
			posX -= 10;
			angle += 10;

			break;

		case SDLK_d:
			//pCurrImageTex = pImage1Tex;
			clipIndex++;
			if (clipIndex == 4) clipIndex = 0;
			posX += 10;
			break;

		case SDLK_w:
			posY -= 10;
			break;

		case SDLK_s:
			posY += 10;
			break;

		default:
			break;
		}
	}
}
