#pragma once

#include "Globals.h"
#include "Module.h"
#include "ModulePhysics.h"
#include "p2Point.h"

#include "raylib.h"
#include <vector>

class PhysBody;
class PhysicEntity;
class Circle;
class FlipperLeft;

enum class GameScreen {START, MENU, GAMEPLAY, ENDING };

class ModuleGame : public Module
{
public:
	ModuleGame(Application* app, bool start_enabled = true);
	~ModuleGame();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB) override;
	void Reset();
	void ScoreRefresh();
public:
	GameScreen currentScreen;

	PhysBody* start = nullptr;
	PhysBody* sound = nullptr;
	PhysBody* music = nullptr;
	PhysBody* menu = nullptr;
	PhysBody* restartbutt = nullptr;

	FlipperLeft* flipper1;
	FlipperLeft* flipper2;
	FlipperLeft* flipper3;
	FlipperLeft* flipper4;

	PhysBody* sensorWall;
	bool inGame = false;

	int remainingBalls = 4;
	float maxvX = 50;
	float maxvY = 50;

	std::vector<PhysBody*> bodies;
	std::vector<Circle*> ball;

	int score = 0;
	int record = 0;
	int pastScore = 0;

	bool showAltBumperTexture;
	bool showAltRolloverTexture;

	float animationTimer;
	float animationInterval;
};
