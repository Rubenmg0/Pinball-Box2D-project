#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleGame.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "box2d/b2_world.h"

class PhysicEntity
{
protected:

	PhysicEntity(PhysBody* _body, Module* listener)
		: body(_body), listener(listener)
	{
		body->listener = listener;
	}

public:
	virtual ~PhysicEntity() = default;
	virtual void Update() = 0;

protected:
	PhysBody* body;
	Module* listener = nullptr;
};

class Circle : public PhysicEntity
{
public:
	Circle(ModulePhysics* physics, int _x, int _y, Module* listener, Texture2D _texture)
		: PhysicEntity(physics->CreateCircle(_x, _y, 14, 0.95f), listener) //Radio
		, texture(_texture)
	{	}

	int getPosY() {		int x, y; body->GetPhysicPosition(x, y); return y;	}
	PhysBody* GetBody() { return body; }

	void Update() override
	{
		int x, y;
		body->GetPhysicPosition(x, y);
		Vector2 position{ (float)x, (float)y };
		float scale = 1.0f;
		Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
		Rectangle dest = { position.x, position.y, (float)texture.width * scale, (float)texture.height * scale };
		Vector2 origin = { (float)texture.width / 2.0f, (float)texture.height / 2.0f };
		float rotation = body->GetRotation() * RAD2DEG;
		DrawTexturePro(texture, source, dest, origin, rotation, WHITE);
	}
	void ShootBall(const b2Vec2& force) { //Funcion para impulsar la bola
		body->body->ApplyLinearImpulseToCenter(force, true);
	}
	bool impulso_inicial = true;
private:
	Texture2D texture;
};



ModuleGame::ModuleGame(Application* app, bool start_enabled) : Module(app, start_enabled), currentScreen(GameScreen::START)
{
	
}

ModuleGame::~ModuleGame()
{
}

// Load assets
bool ModuleGame::Start() 
{
	LOG("Loading Intro assets");
	/*b2Vec2 anchorPoint = ->GetWorldPoint(b2Vec2(150, 625)); */// left end

	//firstFlipper
	PhysBody* paddle1 = App->physics->CreateRectangle(430, 360, 10, 30);;
	float half_w_m = PIXEL_TO_METERS(paddle1->width);
	float half_h_m = PIXEL_TO_METERS(paddle1->height);

	b2Vec2 localPivotRight(half_w_m, half_h_m);

	PhysBody* paddle1Anchor = App->physics->CreateRectangleNo(40, 20, 5, 2);

	b2RevoluteJoint* joint1 = App->physics->CreateJoint(paddle1Anchor->body, paddle1->body, localPivotRight);
	flipper1 = new FlipperLeft(paddle1Anchor, paddle1, localPivotRight, joint1);

	//secondFlipper
	PhysBody* paddle2 = App->physics->CreateRectangle(368, 1000, 10, 45);;
	float half_w_m2 = PIXEL_TO_METERS(paddle2->width);
	float half_h_m2 = PIXEL_TO_METERS(paddle2->height);

	b2Vec2 localPivotRight2(half_w_m2, half_h_m2);

	PhysBody* paddle1Anchor2 = App->physics->CreateRectangleNo(40, 20, 5, 2);

	b2RevoluteJoint* joint2 = App->physics->CreateJoint(paddle1Anchor2->body, paddle2->body, localPivotRight2);
	flipper2 = new FlipperLeft(paddle1Anchor2, paddle2, localPivotRight2, joint2);

	// third flipper
	PhysBody* paddle3 = App->physics->CreateRectangle(235, 980, 10, 45);
	float half_w_m3 = PIXEL_TO_METERS(paddle3->width);
	float half_h_m3 = PIXEL_TO_METERS(paddle3->height);

	b2Vec2 localPivotRight3(-half_w_m3, -half_h_m3);

	PhysBody* paddle1Anchor3 = App->physics->CreateRectangleNo(40, 20, 5, 2);

	b2RevoluteJoint* joint3 = App->physics->CreateJoint1(paddle1Anchor3->body, paddle3->body, localPivotRight3);
	flipper3 = new FlipperLeft(paddle1Anchor3, paddle3, localPivotRight3, joint3);
	// fourth flipper

	PhysBody* paddle4 = App->physics->CreateRectangle(200, 640, 10, 30);
	float half_w_m4 = PIXEL_TO_METERS(paddle4->width);
	float half_h_m4 = PIXEL_TO_METERS(paddle4->height);

	b2Vec2 localPivotRight4(-half_w_m4, -half_h_m4);

	PhysBody* paddle1Anchor4 = App->physics->CreateRectangleNo(40, 20, 5, 2);

	b2RevoluteJoint* joint4 = App->physics->CreateJoint1(paddle1Anchor4->body, paddle4->body, localPivotRight4);
	flipper4 = new FlipperLeft(paddle1Anchor4, paddle4, localPivotRight4, joint4);


//---------------------------------CREACIÓN FISICAS MAPA----------------------------------------//
		int bg[200] ={
	360, 1500,
	360, 1066,
	531, 1016,
	531, 958,
	412, 992,
	405, 966,
	532, 927,
	532, 574,
	462, 547,
	510, 399,

	529, 327,
	531, 312,
	531, 294,
	529, 273,
	527, 255,
	522, 235,
	515, 215,
	506, 198,
	495, 178,
	480, 157,
	465, 140,
	450, 126,
	435, 115,
	417, 103,
	421, 94,
	437, 103,
	452, 115,
	466, 127,
	478, 139,
	488, 150,
	496, 161,
	503, 172,
	514, 190,
	521, 205,
	529, 226,
	533, 239,
	537, 257,
	539, 274,
	540, 285,
	540, 935,
	597, 935,
	597, 268,
	594, 248,
	588, 227,
	582, 207,
	574, 187,
	564, 165,
	550, 140,
	535, 119,
	516, 96,
	493, 75,
	473, 59,
	452, 45,
	428, 33,
	401, 21,
	375, 13,
	348, 9,
	331, 7,
	310, 5,
	286, 6,
	258, 8,
	235, 13,
	213, 19,
	195, 26,
	177, 34,
	156, 45,
	139, 56,
	123, 67,
	104, 83,
	91, 97,
	79, 111,
	67, 125,
	55, 144,
	45, 160,
	37, 176,
	29, 193,
	22, 213,
	17, 235,
	12, 258,
	10, 279,
	9, 300,
	10, 327,
	13, 352,
	21, 383,
	112, 660,
	100, 662,
	89, 666,
	79, 673,
	72, 682,
	67, 693,
	66, 706,
	53, 706,
	41, 708,
	28, 713,
	21, 720,
	13, 732,
	9, 740,
	9, 997,
	246, 1068,
	246, 1500
	};
	for (int i = 0; i < 200; i++) 
	{
		PIXEL_TO_METERS(bg[i]);
	}

	App->physics->CreateChain(0,0,bg, 200); //BackGround

	int palo1[90] = {
	185, 106,
	173, 114,
	162, 122,
	151, 131,
	135, 147,
	125, 159,
	112, 177,
	100, 198,
	92, 216,
	85, 236,
	79, 256,
	77, 285,
	76, 302,
	77, 331,
	82, 352,
	88, 374,
	96, 400,
	104, 423,
	112, 448,
	125, 488,
	143, 541,
	156, 580,
	168, 617,
	176, 641,
	167, 644,
	146, 583,
	134, 544,
	116, 491,
	103, 450,
	94, 424,
	86, 400,
	78, 375,
	72, 353,
	68, 330,
	66, 301,
	67, 276,
	71, 252,
	76, 231,
	84, 211,
	92, 193,
	105, 171,
	118, 152,
	141, 126,
	155, 114,
	178, 98
	};
	for (int i = 0; i < 90; i++) 
	{
		PIXEL_TO_METERS(palo1[i]);
	}

	App->physics->CreateChain(0, 0, palo1, 90);  //First loop

	int palo2[150] = {
	143, 241,
	149, 228,
	153, 218,
	160, 206,
	170, 192,
	178, 183,
	188, 174,
	198, 165,
	208, 158,
	218, 151,
	232, 144,
	247, 138,
	259, 134,
	275, 131,
	289, 130,
	303, 129,
	313, 129,
	326, 130,
	338, 132,
	352, 136,
	367, 141,
	380, 146,
	390, 152,
	401, 159,
	412, 168,
	423, 178,
	432, 188,
	442, 200,
	449, 211,
	456, 224,
	463, 240,
	467, 252,
	470, 263,
	472, 278,
	473, 292,
	473, 316,
	471, 331,
	468, 344,
	464, 360,
	454, 356,
	458, 343,
	461, 330,
	463, 316,
	464, 302,
	464, 288,
	462, 270,
	458, 256,
	452, 240,
	446, 227,
	441, 217,
	433, 205,
	424, 193,
	416, 185,
	404, 174,
	394, 167,
	383, 159,
	370, 153,
	355, 147,
	340, 142,
	324, 139,
	310, 138,
	298, 138,
	284, 139,
	271, 141,
	256, 145,
	243, 150,
	228, 157,
	216, 164,
	204, 173,
	193, 182,
	181, 195,
	172, 207,
	163, 221,
	159, 229,
	152, 244
	};
	for (int i = 0; i < 150; i++) 
	{
		PIXEL_TO_METERS(palo2[i]);
	}

	App->physics->CreateChain(0, 0, palo2, 150); //Second loop -Mid-

	int palo3[14] = { 
		76, 789,
		76, 860,
		76, 928,
		203, 966,
		192, 991,
		66, 953,
		66, 789
	};
	for (int i = 0; i < 14; i++) 
	{
		PIXEL_TO_METERS(palo3[i]);
	}

	App->physics->CreateChain(0, 0, palo3, 14); // Left down "L" 

	int palo4[16] = {
		138, 784,
		183, 894,
		183, 900,
		176, 902,
		142, 891,
		134, 885,
		133, 875,
		133, 782
	};
	for (int i = 0; i < 16; i++) 
	{
		PIXEL_TO_METERS(palo4[i]);
	}

	App->physics->CreateChain(0, 0, palo4, 16); //Left down "triangle"

	int palo5[20] = {
		474, 783,
		474, 807,
		474, 877,
		471, 885,
		464, 891,
		448, 897,
		430, 902,
		424, 901,
		423, 894,
		469, 783
	};
	for (int i = 0; i < 20; i++)
	{
		PIXEL_TO_METERS(palo5[i]);
	}
	App->physics->CreateChain(0, 0, palo5, 20); //Right down "triangle"
	 
	PhysBody* redCircle = App->physics->CreateCircle(205, 220, 30, 0.2f);
	redCircle->body->SetType(b2_staticBody);
	PhysBody* redCircle2 = App->physics->CreateCircle(305, 170, 30, 0.2f);
	redCircle2->body->SetType(b2_staticBody);
	PhysBody* redCircle3 = App->physics->CreateCircle(405, 220, 30, 0.2f);
	redCircle3->body->SetType(b2_staticBody);

	PhysBody* greenCircle = App->physics->CreateCircleSensor(220, 60, 25);
	PhysBody* greenCircle2 = App->physics->CreateCircleSensor(300, 40, 25);
	PhysBody* greenCircle3 = App->physics->CreateCircleSensor(380, 60, 25);

	PhysBody* greenCircle4 = App->physics->CreateCircleSensor(190, 470, 25);
	PhysBody* greenCircle5 = App->physics->CreateCircleSensor(310, 350, 25);
	PhysBody* greenCircle6 = App->physics->CreateCircleSensor(420, 470, 25);
	PhysBody* greenCircle7 = App->physics->CreateCircleSensor(310, 600, 25);
	
	sensorWall = App->physics->CreateRectangleNo(420, 65,3, 40);


	LOG("LOAD SOUNDS");
	App->audio->LoadFx("Assets/sounds/pinball-collision.wav");

	if (App->audio->musicOn)
	{
		App->audio->PlayMusic("Assets/sounds/music.wav");
	}
	
	showAltBumperTexture = false;
	showAltRolloverTexture = false;
	animationTimer = 0.0f;
	animationInterval = 0.15f; //Cambiará cada 0.5 segundos

	return true;
}

// Load assets
bool ModuleGame::CleanUp()
{
	LOG("Unloading Intro scene");
	/*
	App->physics->DestroyBody(start);
	App->physics->DestroyBody(menu);
	App->physics->DestroyBody(sound);
	App->physics->DestroyBody(music);
	App->physics->DestroyBody(restartbutt);
	App->physics->DestroyBody(flipper1->paddle1);
	App->physics->DestroyBody(flipper2->paddle1);
	App->physics->DestroyBody(flipper3->paddle1);
	App->physics->DestroyBody(flipper4->paddle1);
	App->physics->DestroyBody(flipper1->paddle1Anchor);
	App->physics->DestroyBody(flipper2->paddle1Anchor);
	App->physics->DestroyBody(flipper3->paddle1Anchor);
	App->physics->DestroyBody(flipper4->paddle1Anchor);*/
	/*App->physics->DestroyBody(sensorWall);*/
	for (auto body : bodies)
	{
		if (body != nullptr)
		{
			App->physics->DestroyBody(body);
		}
	}
	bodies.clear();

	delete flipper1;
	delete flipper2;
	delete flipper3;
	delete flipper4;
	flipper1 = flipper2 = flipper3 = flipper4 = nullptr;

	return true;

}

// Update: draw background
update_status ModuleGame::Update()
{
	//Animaciones de los botones
	animationTimer += GetFrameTime();

	if (animationTimer >= animationInterval)
	{
		showAltBumperTexture = !showAltBumperTexture;
		showAltRolloverTexture = !showAltRolloverTexture;

		animationTimer = 0.0f;
	}

	if (IsKeyPressed(KEY_N)) //Encender/Apagar Sonidos
	{
		App->audio->soundsOn = !App->audio->soundsOn;
	}
	if (IsKeyPressed(KEY_M)) //Encender/Apagar Musica
	{
		App->audio->musicOn = !App->audio->musicOn;
	}

	if (App->audio->musicOn) //Reproducir musica
	{
		UpdateMusicStream(App->audio->GetMusic());
	}

	switch (currentScreen) {
	case GameScreen::START:
		if (restartbutt != nullptr)
		{
			App->physics->GetWorld()->DestroyBody(restartbutt->body);
			restartbutt = nullptr;
		}
		if (start == nullptr && sound == nullptr && music == nullptr)
		{
			start = App->physics->CreateRectangle(304, 405, 208, 29);
			start->body->SetType(b2_staticBody);
			sound = App->physics->CreateRectangle(302, 495, 87, 22);
			sound->body->SetType(b2_staticBody);
			music = App->physics->CreateRectangle(301, 550, 77, 22);
			music->body->SetType(b2_staticBody);
		}

		if (IsKeyPressed(KEY_ENTER)) 
		{
			currentScreen = GameScreen::MENU;
		}
		break;

	case GameScreen::MENU:
		if (start != nullptr)
		{
			App->physics->GetWorld()->DestroyBody(start->body);
			start = nullptr;
			App->physics->GetWorld()->DestroyBody(sound->body);
			sound = nullptr;
			App->physics->GetWorld()->DestroyBody(music->body);
			music = nullptr;
		}

		if (IsKeyPressed(KEY_ENTER) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
		{
			TraceLog(LOG_INFO, "Menu --> Game : Correcto");
			currentScreen = GameScreen::GAMEPLAY;
		}
		break;

	case GameScreen::GAMEPLAY:
	
		sensorWall->body->SetEnabled(inGame);


		if (ball.empty() && remainingBalls != 0) //Verificamos queno hay ningun pinball en pantalla
		{
			ball.emplace_back(new Circle(App->physics, 568, 920, this, App->renderer->pinball_Ball));
			remainingBalls--;
		}

		if (IsKeyPressed(KEY_DOWN) && !ball.empty() && ball.front()->impulso_inicial) // 2. Verificamos que la pelota exista para evitar errores
		{
			b2Vec2 launchForce(0.0f, -9.0f);

			ball.front()->ShootBall(launchForce);
			ball.front()->impulso_inicial = false;
		}

		int x, y;
		ball.front()->GetBody()->GetPhysicPosition(x, y);
		if (x < 420)
		{
			inGame = true;
		}

		for (Circle* b : ball)
		{
		float y = b->getPosY();
			
			if (y > 1085 && !ball.empty())
			{
				App->physics->DestroyBody(b->GetBody());
				ball.pop_back();
				
				inGame = false;

				if (!ball.empty())
					LOG("Aún hay pelotas en el vector\n")
				else
					LOG("No queda ninguna pelota\n")
			}
		}
		if(IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT) || IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && GetMousePosition().x <= App->renderer->camera.width / 2) {
			flipper1->Activate();
			flipper2->Activate();
		}
		else {
			flipper1->Deactivate();
			flipper2->Deactivate();
		}
		if (!IsKeyDown(KEY_A) && !IsKeyDown(KEY_LEFT)) {
			flipper3->Activate();
			flipper4->Activate();
			
		}
		else {
			flipper3->Deactivate();
			flipper4->Deactivate();
			
		}
		//Caso para si la bola se queda atascada reinciarla
		if (IsKeyPressed(KEY_R) && !ball.empty()) {
			for (Circle* b : ball)
			{
				App->physics->DestroyBody(b->GetBody());
				ball.pop_back();
				inGame = false;
			}
		}

		if (ball.empty() && remainingBalls == 0)
		{
			currentScreen = GameScreen::ENDING;
		}

		break;
	case GameScreen::ENDING:
		if (restartbutt == nullptr)
		{
			restartbutt = App->physics->CreateCircle(296, 604, 52, 52);
			restartbutt->body->SetType(b2_staticBody);
		}
		if (IsKeyPressed(KEY_ENTER)) {
			Reset();
			ScoreRefresh();
			currentScreen = GameScreen::START;
		}
		break;
	}
	
	
	return UPDATE_CONTINUE;
}

void ModuleGame::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	
	if (App->audio->soundsOn)
	{
		App->audio->PlayFx(0); //Cambiar Numero para canviar audio de rebote
	}
	
	if (bodyB != NULL)
	{
		if (bodyB->body->GetFixtureList()->IsSensor()) { //Detecta Sensores (Circulos Verdes)
			score += 1000;
			touchedGreen = true;
		}
		else if (true) // Detectar circulos rojos (TODO)
		{
			score += 500;
			touchedRed = true;
		}
	}

	if (touchedGreen && touchedRed)
	{
		// Combo activado, bonificación extra o efecto
		score += 2000;  // Añadimos una bonificación por el combo
		App->audio->PlayFx(0);

		// Reseteamos los flags para el próximo combo
		touchedGreen = false;
		touchedRed = false;
	}
}

void ModuleGame::Reset()
{
	remainingBalls = 4;
}

void ModuleGame::ScoreRefresh()
{
	pastScore = score;
	if (score > record)
	{
		record = score;
	}
	score = 0;
}
