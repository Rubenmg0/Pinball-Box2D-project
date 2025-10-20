#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleGame.h"
#include "PhysicEntity.h"

class FlipperLeft
{
public:
	FlipperLeft(int width1, int height1, int width2, int height2,);
	~FlipperLeft();

private:
	PhysBody* paddle1Anchor;
	PhysBody* paddle1;
	b2Vec2 pivot;

	b2RevoluteJoint* joint1;
};

FlipperLeft::FlipperLeft()
{

	paddle1Anchor = App->physics->CreateRectangleNo(150, 625, 5, 2);
	paddle1 = App->physics->CreateRectangle(150, 625, 20, 60);
	pivot = b2Vec2(0, 0);

	b2RevoluteJoint* joint1 = App->physics->CreateJoint(paddle1Anchor->body, paddle1->body, pivot);
}

FlipperLeft::~FlipperLeft()
{
}