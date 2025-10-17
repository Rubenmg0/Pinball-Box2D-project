#pragma once

#include "Globals.h"
#include "Module.h"

#include "p2Point.h"

#include "raylib.h"
#include <vector>

class PhysBody;
class PhysicEntity;

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

	PhysBody* sensor;
	bool sensed;

	std::vector<PhysBody*> bodies;
	std::vector<PhysicEntity*> ball;
};
