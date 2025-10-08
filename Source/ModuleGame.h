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

	GameScreen currentScreen;
	bool Start();
	update_status Update();
	bool CleanUp();

public:
	Texture2D circle;
	Texture2D box;
	Texture2D rick;

	std::vector<PhysBody*> bodies;
};
