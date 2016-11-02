
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
	m_pMainWindow = nullptr;

	DotX = DotY = 0;
	VelX = VelY = 0;
	DotVel = 8;
	DotSize = 64;
	
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
	m_pMainWindow = new Window();
	m_pMainWindow->Init(800, 600, "ARPG");

	Engine::GetEngine().CreateCamera(0,0, m_pMainWindow->m_nScreenW, m_pMainWindow->m_nScreenH);

	TestBtn.Area.y = 10;
	TestBtn.Area.w = 100;
	TestBtn.Area.h = 40;
	TestBtn.Area.x = m_pMainWindow->m_nScreenW - 10 - TestBtn.Area.w;
	TestBtn.Name = "Exit";
	TestBtn.CallBack = QuitGame;

	std::string Path = std::string(SDL_GetBasePath()) + "Resources\\Other\\bg.jpg";
	BgT = LoadImage(m_pMainWindow->m_pRenderer, Path);
	SDL_QueryTexture(BgT, nullptr, nullptr, &MapW, &MapH);

	Path = std::string(SDL_GetBasePath()) + "Resources\\Other\\tile_134.png";
	DotT = LoadImage(m_pMainWindow->m_pRenderer,Path);

	FontPath = std::string(SDL_GetBasePath()) + "Resources\\SourceSansPro-Regular.ttf";
	Font = TTF_OpenFont(FontPath.c_str(), FontSize);
	if (Font == nullptr)
		throw std::runtime_error("Failed to load font: " + FontPath + TTF_GetError());

	FontColor = { 0x12,0x1a, 0x2a,0xff }; //ÇàºÖ 121a2a
	TextT = RenderText(m_pMainWindow->m_pRenderer, Font, TestBtn.Name,  FontColor, FontSize);
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
	Camera& camera = Engine::GetCamera();
	camera.x = DotX + DotSize / 2 - m_pMainWindow->m_nScreenW / 2;
	camera.y = DotY + DotSize / 2 - m_pMainWindow->m_nScreenH / 2;
	if (camera.x < 0)
		camera.x = 0;
	if (camera.y < 0)
		camera.y = 0;
	if (camera.x > MapW - camera.w)
		camera.x = MapW - camera.w;
	if (camera.y > MapH - camera.h)
		camera.y = MapH - camera.h;

	if (bInputFlag)
	{
		InputTextT = RenderText(m_pMainWindow->m_pRenderer, Font, InputText, FontColor, FontSize);
		bInputFlag = false;
		SDL_QueryTexture(InputTextT, nullptr, nullptr, &InputTextW, &InputTextH);
	}
}

void GameARPG::Render()
{
	SDL_Renderer* pRen = m_pMainWindow->m_pRenderer;
	SDL_SetRenderDrawColor(pRen, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(pRen);

	SDL_RenderCopy(pRen,BgT,&Engine::GetCamera().GetCameraRect(),nullptr);
	SDL_Rect destRect = {DotX - Engine::GetCamera().x,DotY - Engine::GetCamera().y ,DotSize,DotSize };
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

