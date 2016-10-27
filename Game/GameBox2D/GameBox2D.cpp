
#include "GameBox2D.h"

GameBox2D::GameBox2D() : IGame()
{
	groundPoxX = 25.0f;
	groundPoxY = 2.0f;
	groundBoxW = 50.0f;
	groundBoxH = 4.0f;

	velocityIterations = 3;
	positionIterations = 8;

	barW = 8.0f;
	barH = 1.6f;
}

GameBox2D::~GameBox2D()
{
	Destroy();
}

int GameBox2D::Init()
{
	Engine::SetScreenSize(800, 600);
	SDL_SetWindowTitle(Engine::GetMainWindow(),"Box2D");

	std::string BoxP = std::string(SDL_GetBasePath()) + "Resources\\topdown_shooter\\PNG\\Tiles\\tile_196.png";
	BoxT = LoadImage(Engine::GetRenderer(), BoxP);

	m_pBoxTex = new Textrue2D(BoxP);

	b2Vec2 gravity(0.0f, -10.0f);
	bool doSleep = true;
	world = new b2World(gravity);
	world->SetAllowSleeping(doSleep);

	b2BodyDef groundBodyDef; 
	groundBodyDef.position.Set(groundPoxX, groundPoxY);
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	b2PolygonShape groundBox;
	groundBox.SetAsBox(groundBoxW*0.5f, groundBoxH*0.5f);
	groundBody->CreateFixture(&groundBox, 0.0f);

	boxCount = 3;
	boxSet = new MyBox*[boxCount];
	boxSet[0] = new MyBox(20.0f, 30.0f, 2.0f, 2.0f);
	boxSet[1] = new MyBox(15.0f, 30.0f, 2.0f, 2.0f);
	boxSet[2] = new MyBox(20.0f, 25.0f, 2.0f, 2.0f);

	for (int i = 0; i < boxCount; ++i)
	{
		boxSet[i]->Init(world); 
		boxSet[i]->SetSprite(m_pBoxTex);
	}
	// distance Joint
	b2DistanceJointDef disJD;
	disJD.frequencyHz = 20.0f;
	disJD.dampingRatio = 0.1f;
	disJD.Initialize(boxSet[0]->body, boxSet[1]->body, boxSet[0]->body->GetWorldCenter(), boxSet[1]->body->GetWorldCenter());
	world->CreateJoint(&disJD);
	disJD.Initialize(boxSet[2]->body, boxSet[1]->body, boxSet[2]->body->GetWorldCenter(), boxSet[1]->body->GetWorldCenter());
	world->CreateJoint(&disJD);
	disJD.Initialize(boxSet[2]->body, boxSet[0]->body, boxSet[2]->body->GetWorldCenter(), boxSet[0]->body->GetWorldCenter());
	world->CreateJoint(&disJD);

	// bar
	barPos = b2Vec2(40.0f, 20.0f);
	b2BodyDef barDef;
	barDef.type = b2BodyType::b2_dynamicBody;
	barDef.position = barPos;
	barDef.linearDamping = 0.3f;
	barDef.angularDamping = 0.2f;
	barDef.allowSleep = true;
	bar = world->CreateBody(&barDef);
	b2PolygonShape barShape;
	barShape.SetAsBox(barW * 0.5f, barH * 0.5f);
	b2FixtureDef barFixture;
	barFixture.density = 100.0f;
	barFixture.shape = &barShape;
	barFixture.friction = 0.2f;
	bar->CreateFixture(&barFixture);

	b2Vec2 anchor = b2Vec2(barPos.x - barW * 0.5f, barPos.y);
	b2RevoluteJointDef reJD;
	reJD.enableMotor = true;
	reJD.motorSpeed = 0.0f;
	reJD.maxMotorTorque = 10.0f;
	reJD.Initialize(groundBody, bar, anchor);
	reJ = world->CreateJoint(&reJD);

	std::string BarP = std::string(SDL_GetBasePath()) + "Resources\\Other\\red_button00.png";
	BarT = LoadImage(Engine::GetRenderer(),BarP);

	bridge = new Bridge();
	bridge->SetPos(1.0f, 10.0f);
	bridge->Create(world, groundBody);

	return 0;
}

void GameBox2D::Update(float dt)
{
	world->Step(Engine::TIME_STEP, velocityIterations, positionIterations);
}

void GameBox2D::Render()
{
	SDL_Renderer* pRen = Engine::GetRenderer();
	SDL_SetRenderDrawColor(pRen, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderClear(pRen);

	SDL_SetRenderDrawColor(pRen, 0xFF, 0, 0, 0);
	SDL_Rect groundRect = { static_cast<int>((groundPoxX - groundBoxW *0.5f) * Engine::PIXEL_PER_METER),  static_cast<int>(Engine::m_nScreenH - (groundPoxY + groundBoxH * 0.5f)* Engine::PIXEL_PER_METER),  static_cast<int>(groundBoxW* Engine::PIXEL_PER_METER),  static_cast<int>(groundBoxH* Engine::PIXEL_PER_METER) };
	SDL_Rect fakeRect = {0, 500, 800, 32};
	SDL_RenderFillRect(pRen,&groundRect);

	for (int i = 0; i < boxCount; ++i)
	{
		boxSet[i]->Render();
	}

	float angle = -bar->GetAngle() * 57.2775475f;
	SDL_Point center= { barW * 0.5f * Engine::PIXEL_PER_METER , barH * 0.5f * Engine::PIXEL_PER_METER };
	SDL_Rect barRect = { (bar->GetPosition().x - barW * 0.5f) * Engine::PIXEL_PER_METER ,Engine::m_nScreenH - (bar->GetPosition().y + barH * 0.5f) *  Engine::PIXEL_PER_METER , barW * Engine::PIXEL_PER_METER , barH* Engine::PIXEL_PER_METER};
	SDL_RenderCopyEx(pRen, BarT, nullptr, &barRect, angle, &center, SDL_FLIP_HORIZONTAL);

	bridge->Render(BarT);
	
	SDL_RenderPresent(pRen);
}

void GameBox2D::Destroy()
{
	SDL_DestroyTexture(BoxT);
	for (int i = 0; i < boxCount; ++i)
	{
		delete boxSet[i];
		boxSet[i] = nullptr;
	}
	delete[] boxSet;
	delete world;

	m_pBoxTex->Release();
	delete m_pBoxTex;
}

void GameBox2D::HandleEvent(SDL_Event& e)
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
