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

class PhysBody {
public:
	PhysBody() {}

	void GetPosition(int& x, int& y) const;

public:
	b2Body* body;
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

	PhysBody* CreateCircle(int x, int y, int radius);
	PhysBody* CreateRectangle(int x, int y, int width, int height);
	PhysBody* CreateRectangleNo(int x, int y, int width, int height);
	void CreateChain(int x, int y, const int* points, int size);
	b2RevoluteJoint* CreateJoint(b2Body* paddleAnchor, b2Body* paddle, b2Vec2 pivot);

	/*PhysBody* CreatePaddle(int x, int y);*/
	

private:

	bool debug;
	b2World* world;
};