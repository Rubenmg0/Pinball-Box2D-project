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

class FlipperLeft
{
public:
	FlipperLeft(PhysBody* paddleAnchor, PhysBody* paddle1, b2Vec2 pivot, b2RevoluteJoint* joint1) {
		this->paddle1 = paddle1;
		this->paddle1Anchor = paddleAnchor;
		this->joint1 = joint1;
		this->pivot = pivot; //le metemos todo lo que necesitaría durante la creación
	}
	PhysBody* paddle1Anchor;
	PhysBody* paddle1;
	b2Vec2 pivot;

	b2RevoluteJoint* joint1;

	void Activate() {
		joint1->EnableMotor(true);
		joint1->SetMotorSpeed(1000.0f);

	}
	void Deactivate() {
		joint1->EnableMotor(true);
		joint1->SetMotorSpeed(-1000.0f);

	}
};

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
	bool touchedGreen = false;
	bool touchedRed = false;
	int greenTime = 0;   
	int redTime = 0;
	int comboStartTime = 0;

	int record = 0;
	int pastScore = 0;

	bool showAltBumperTexture;
	bool showAltRolloverTexture;

	float animationTimer;
	float animationInterval;
};
