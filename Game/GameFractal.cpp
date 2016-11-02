
#include "GameFractal.h"
#include "math.h"

const int GameFractal::BOX_SIZE = 32;
const float EDGE = 500;
const float SIN60 = 0.8660254f;



GameFractal::GameFractal() : IGame()
{
}

GameFractal::~GameFractal()
{
	Destroy();
}

int GameFractal::Init()
{
	Engine::GetEngine()->CreateWindowAndRenderer(1600, 1000, "Fractal");
	
	std::string BoxP = std::string(SDL_GetBasePath()) + "Resources\\topdown_shooter\\PNG\\Tiles\\tile_196.png";
	BoxT = LoadImage(Engine::GetRenderer(), BoxP);

	Triangle t = {800,900,1};
	GenTri(t, 7);

	return 0;
}

void GameFractal::Update(float dt)
{
	
}

void GameFractal::Render()
{
	SDL_Renderer* pRen = Engine::GetRenderer();
	SDL_SetRenderDrawColor(pRen, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(pRen);

	SDL_Rect destRect = {0,0,BOX_SIZE,BOX_SIZE };
	SDL_Point Center = { BOX_SIZE / 2,BOX_SIZE / 2 };
	SDL_RenderCopyEx(pRen,BoxT,nullptr, &destRect, 0, &Center, SDL_FLIP_NONE);

	SDL_SetRenderDrawColor(pRen, 0xff, 0, 0, 0xFF);

	for (int i = 0; i <  static_cast<int>(Trs.size()); ++i)
	{
		Triangle t = Trs[i];
		DrawTri(pRen, t);
	}

	SDL_RenderPresent(pRen);
}

void GameFractal::Destroy()
{

}

void GameFractal::HandleEvent(SDL_Event& e)
{
	// If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:break;
			
		case SDLK_DOWN: break;
		case SDLK_LEFT:  break;
		case SDLK_RIGHT: break;
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
			break;
		case SDLK_DOWN:	
			break;
		case SDLK_LEFT:
			break;
		case SDLK_RIGHT: 
			break;
		}
	}
}

void GameFractal::Test1()
{
	
}

void GameFractal::DrawTri(SDL_Renderer* pRen, const Triangle& t)
{
	Point P1 = { t.x,t.y };
	Point P2 = { (P1.x - EDGE / 2 / t.scale), (t.y - SIN60 * EDGE / t.scale)  };
	Point P3 = { (P1.x + EDGE / 2 / t.scale) ,(t.y - SIN60 * EDGE / t.scale) };

	Point pp[4] = { P1 ,P2 ,P3 ,P1 };
	SDL_Point spp[4];
	for (int i = 0; i < 4; ++i)
	{
		spp[i] = {(int)pp[i].x,(int)pp[i].y};
	}

	SDL_RenderDrawLines(pRen, &spp[0], 4);
}

void GameFractal::GenTri(const Triangle& tri, int step)
{
	std::vector<Triangle> TrsFather;
	std::vector<Triangle> TrsSon;

	TrsFather.push_back(tri);

	for (int i = 0; i < step; ++i)
	{
		for (int f = 0; f <  static_cast<int>(TrsFather.size()); ++f)
		{
			Triangle t = TrsFather[f];
			Point P1 = { t.x,t.y };
			Point P2 = { (P1.x - EDGE / 2 / t.scale), (t.y - SIN60 * EDGE / t.scale) };
			Point P3 = { (P1.x + EDGE / 2 / t.scale) ,(t.y - SIN60 * EDGE / t.scale) };

			Triangle t1 = { P2.x ,P1.y, t.scale * 2 };
			Triangle t2 = { P1.x, P2.y, t.scale * 2 };
			Triangle t3 = { P3.x, P1.y, t.scale * 2 };

			TrsSon.push_back(t1);
			TrsSon.push_back(t2);
			TrsSon.push_back(t3);
			Trs.push_back(t);
		}

		TrsFather.clear();

		for (int s = 0; s <  static_cast<int>(TrsSon.size()); ++s)
		{
			Triangle t = TrsSon[s];
			TrsFather.push_back(t);
		}
		TrsSon.clear();
	}
	TrsFather.clear();
	TrsSon.clear();
}
	
