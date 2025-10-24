#pragma once

#include "Module.h"
#include "Globals.h"
#include <vector>
#include "box2d\box2d.h"

#define GRAVITY_X 0.0f
#define GRAVITY_Y -7.0f

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

class PhysBody
{
public:
	PhysBody() : body(NULL), listener(nullptr)
	{}

	void GetPhysicPosition(int& x, int& y) const;
	float GetRotation() const;
	bool Contains(int x, int y) const;

public:
	int width, height;
	b2Body* body;
	Module* listener;
};

// Module --------------------------------------
class ModulePhysics : public Module, public b2ContactListener // TODO
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();
	
	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

	b2World* GetWorld() { return world; }
	PhysBody* CreateCircle(int x, int y, int radius, float rebote);
	PhysBody* CreateRectangle(int x, int y, int width, int height);
	PhysBody* CreateRectangleNo(int x, int y, int width, int height);
	PhysBody* CreateRectangleSensor(int x, int y, int width, int height);
	PhysBody* CreateChain(int x, int y, const int* points, int size);
	b2RevoluteJoint* CreateJoint(b2Body* paddleAnchor, b2Body* paddle, b2Vec2 pivot);
	b2RevoluteJoint* CreateJoint1(b2Body* paddleAnchor, b2Body* paddle, b2Vec2 pivot);
	void DestroyBody(PhysBody* body);
	void ModulePhysics::UpdateJoint(b2RevoluteJoint* flipperJoint);
	/*PhysBody* CreatePaddle(int x, int y);*/

	void BeginContact(b2Contact* contact) override;

private:

	bool debug;
	b2World* world;
	b2MouseJoint* mouse_joint;
	b2Body* ground;
};

