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

enum class GameScreen {START, MENU, GAMEPLAY, DEATH, ENDING };

class ModuleGame : public Module
{
public:
	ModuleGame(Application* app, bool start_enabled = true);
	~ModuleGame();

	bool Start();
	update_status Update();
	bool CleanUp();

	void OnCollision(PhysBody* bodyA, PhysBody* bodyB) override;

public:
	GameScreen currentScreen;
	FlipperLeft* flipper1;
	PhysBody* sensor;
	bool sensed;

	int remainingBalls = 3;

	std::vector<PhysBody*> bodies;
	std::vector<Circle*> ball;
};
