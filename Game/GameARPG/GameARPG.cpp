
#include "GameARPG.h"

void PrintValue(Button& btn)
{
	std::cout << btn.Area.x << btn.Area.y << std::endl;
}

void QuitGame(Button& btn)
{
	std::cout << "Game Quit!--"<< std::endl;
	SDL_Event newEvent;
	newEvent.type = SDL_QUIT;
	SDL_PushEvent(&newEvent);
}

GameARPG::GameARPG() : IGame()
{
	DotX = DotY = 0;
	VelX = VelY = 0;
	DotVel = 8;
	DotSize = 64;
	ScreenW = Engine::GetEngine()->m_nScreenW;
	ScreenH = Engine::GetEngine()->m_nScreenH;

	DotAngle = 0.0f;
	AngleVel = 180.0f;
	bInputFlag = false;
	FontSize = 24;
}

bool IsClicked(int mx, int my, const SDL_Rect& r)
{
	if (mx > r.x && mx < r.x + r.w && my >r.y && my < r.y + r.h)
		return true;
	else
		return false;
}

GameARPG::~GameARPG()
{
	Destroy();
}

int GameARPG::Init()
{
	SDL_SetWindowSize(Engine::GetMainWindow(), 800, 600);
	SDL_SetWindowTitle(Engine::GetMainWindow(), "ARPG");

	Camera.x = 0;
	Camera.y = 0;
	Camera.w = ScreenW;
	Camera.h = ScreenH;

	TestBtn.Area.y = 10;
	TestBtn.Area.w = 100;
	TestBtn.Area.h = 40;
	TestBtn.Area.x = ScreenW - 10 - TestBtn.Area.w;
	TestBtn.Name = "Exit";
	TestBtn.CallBack = QuitGame;

	std::string Path = std::string(SDL_GetBasePath()) + "Resources\\Other\\bg.jpg";
	BgT = LoadImage(Engine::GetRenderer(), Path);
	SDL_QueryTexture(BgT, nullptr, nullptr, &MapW, &MapH);

	Path = std::string(SDL_GetBasePath()) + "Resources\\Other\\tile_134.png";
	DotT = LoadImage(Engine::GetRenderer(),Path);

	FontPath = std::string(SDL_GetBasePath()) + "Resources\\SourceSansPro-Regular.ttf";
	Font = TTF_OpenFont(FontPath.c_str(), FontSize);
	if (Font == nullptr)
		throw std::runtime_error("Failed to load font: " + FontPath + TTF_GetError());

	FontColor = { 0x12,0x1a, 0x2a,0xff }; //ÇàºÖ 121a2a
	TextT = RenderText(Engine::GetRenderer(), Font, TestBtn.Name,  FontColor, FontSize);
	SDL_QueryTexture(TextT, nullptr, nullptr, &fontW, &fontH);

	// InputFields
	InputField = {100,100,200,50};
	
	return 0;
}

void GameARPG::Update(float dt)
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
	Camera.x = DotX + DotSize / 2 - ScreenW / 2;
	Camera.y = DotY + DotSize / 2 - ScreenH / 2;
	if (Camera.x < 0) 
		Camera.x = 0;
	if (Camera.y < 0)
		Camera.y = 0;
	if (Camera.x > MapW - Camera.w)
		Camera.x = MapW - Camera.w;
	if (Camera.y > MapH - Camera.h)
		Camera.y = MapH - Camera.h;

	if (bInputFlag)
	{
		InputTextT = RenderText(Engine::GetRenderer(), Font, InputText, FontColor, FontSize);
		bInputFlag = false;
		SDL_QueryTexture(InputTextT, nullptr, nullptr, &InputTextW, &InputTextH);
	}
}

void GameARPG::Render()
{
	SDL_Renderer* pRen= Engine::GetRenderer();
	SDL_SetRenderDrawColor(pRen, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(pRen);

	SDL_RenderCopy(pRen,BgT,&Camera,nullptr);
	SDL_Rect destRect = {DotX - Camera.x,DotY - Camera.y ,DotSize,DotSize };
	SDL_Point center = { DotSize / 2, DotSize / 2 };
	SDL_RenderCopyEx(pRen, DotT, nullptr, &destRect, DotAngle, &center, SDL_FLIP_NONE);

	SDL_SetRenderDrawColor(pRen, 0x1d, 0x95, 0x3f, 0xFF);//#±¡¾v#1d953f
	SDL_RenderFillRect(pRen, &TestBtn.Area);

	SDL_Rect fontDest = { TestBtn.Area.x + (TestBtn.Area.w - fontW) / 2, TestBtn.Area.y + (TestBtn.Area.h - fontH) / 2, fontW ,fontH };
	SDL_RenderCopy(pRen, TextT, nullptr, &fontDest);

	// InputField
	SDL_SetRenderDrawColor(pRen, 0xff, 0, 0, 0xff);
	SDL_RenderDrawRect(pRen, &InputField);
	SDL_Rect InputDest = { InputField.x, InputField.y, InputTextW, InputTextH };
	SDL_RenderCopy(pRen, InputTextT, nullptr, &InputDest);

	SDL_RenderPresent(pRen);
}

void GameARPG::Destroy()
{
	
}

void GameARPG::HandleEvent(SDL_Event& e)
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

		case SDLK_s:
			/*MainWindowSurf = SDL_GetWindowSurface(Engine::GetMainWindow());
			std::string outPath = std::string(SDL_GetBasePath()) +  "test.png";
			IMG_SavePNG(MainWindowSurf, outPath.c_str());*/
			break;
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
	else if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		if (IsClicked(e.button.x,e.button.y,TestBtn.Area))
		{
			TestBtn.CallBack(TestBtn);
		}

		if(IsClicked(e.button.x, e.button.y, InputField))
		{
			SDL_StartTextInput();
			SDL_SetTextInputRect(&InputField);
		}
		else
		{
			SDL_StopTextInput();
		}
		
	}
	else if (e.type == SDL_MOUSEBUTTONUP)
	{
		
	}
	else if (e.type == SDL_TEXTINPUT)
	{
		bInputFlag = true;
		InputText = e.text.text;
		std::cout << e.text.text << std::endl;
	}
	else if (e.type == SDL_TEXTEDITING)
	{
		/*bInputFlag = true;
		InputText = e.edit.text;
		InputLength = e.edit.start;*/
	}
}

