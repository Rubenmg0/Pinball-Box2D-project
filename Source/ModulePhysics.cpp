#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "ModuleGame.h"

#include "p2Point.h"

#include <math.h>


ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	world = NULL;
	debug = false;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");
	
	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));
	world->SetContactListener(this);

	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(150, 625);

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = 1 * 0.5f;

	b2FixtureDef fixture;
	fixture.shape = &shape;
	b->CreateFixture(&fixture);

	return true;
}

update_status ModulePhysics::PreUpdate()
{
	world->Step(1.0f / 60.0f, 6, 2);

	// TODO: HomeWork
	/*
	for(b2Contact* c = world->GetContactList(); c; c = c->GetNext())
	{
	}
	*/

	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	if (IsKeyPressed(KEY_F1) && App->scene_intro->currentScreen == GameScreen::GAMEPLAY)
	{
		debug = !debug;
	}

	//if (!debug)
	//{
	//	return UPDATE_CONTINUE;
	//}

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		for(b2Fixture* f = b->GetFixtureList(); f; f = f->GetNext())
		{
			switch(f->GetType())
			{
				// Draw circles ------------------------------------------------
				case b2Shape::e_circle:
				{
					b2CircleShape* shape = (b2CircleShape*)f->GetShape();
					b2Vec2 pos = f->GetBody()->GetPosition();
					Rectangle sec = {};
					sec.x = METERS_TO_PIXELS(0);
					sec.y = METERS_TO_PIXELS(0);
					sec.width = shape->m_radius;
					sec.height = shape->m_radius;

					double angle = f->GetBody()->GetAngle();

					Rectangle sourceRec = { 0.0f, 0.0f, (float)App->renderer->pinball_Ball.width, (float)App->renderer->pinball_Ball.height };
					Rectangle destRec = { METERS_TO_PIXELS(pos.x)- sec.width/2 ,METERS_TO_PIXELS(pos.y)-sec.height/2, METERS_TO_PIXELS(pos.x)+sec.width/2, METERS_TO_PIXELS(pos.y)+sec.height/2 };
					Vector2 origin= { (float)App->renderer->pinball_Ball.width/2, (float)App->renderer->pinball_Ball.height/2 };
					//App->renderer->Draw(App->renderer->pinball_Ball, METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), 0, angle,16,16); //Dibuixat de texura pinball_Ball
					if (f->GetBody()->GetType() != b2_staticBody)
					{
						App->renderer->Draw(App->renderer->pinball_Ball, METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), 0, angle, 16, 16);
					}
					//DrawTexturePro(App->renderer->pinball_Ball, sourceRec, destRec, origin, angle, WHITE);


					if (debug) // Si en debug
					{
						DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), (float)METERS_TO_PIXELS(shape->m_radius), RED);
					}

				}
				break;

				// Draw polygons ------------------------------------------------
				case b2Shape::e_polygon:
				{
					b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
					int32 count = polygonShape->m_count;
					b2Vec2 prev, v;

					for(int32 i = 0; i < count; ++i)
					{
						v = b->GetWorldPoint(polygonShape->m_vertices[i]);
						if(i > 0)
							DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), RED);

						prev = v;
					}

					v = b->GetWorldPoint(polygonShape->m_vertices[0]);
					DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), RED);
				}
				break;

				// Draw chains contour -------------------------------------------
				case b2Shape::e_chain:
				{
					b2ChainShape* shape = (b2ChainShape*)f->GetShape();
					b2Vec2 prev, v;

					for(int32 i = 0; i < shape->m_count; ++i)
					{
						v = b->GetWorldPoint(shape->m_vertices[i]);
						if(i > 0 && debug)
							DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), GREEN);
						prev = v;
					}

					v = b->GetWorldPoint(shape->m_vertices[0]);

					//DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), YELLOW); // ESTO NO SIRVE
				}
				break;

				// Draw a single segment(edge) ----------------------------------
				case b2Shape::e_edge:
				{
					b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
					b2Vec2 v1, v2;

					v1 = b->GetWorldPoint(shape->m_vertex0);
					v1 = b->GetWorldPoint(shape->m_vertex1);
					DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), BLUE);
				}
				break;
			}	
		}
	}

	return UPDATE_CONTINUE;
}


PhysBody* ModulePhysics::CreateCircle(int x, int y, int radius, float rebote)
{
	PhysBody* pbody = new PhysBody();

	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	body.userData.pointer = reinterpret_cast<uintptr_t>(pbody);

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;
	/*fixture.restitution = 0.95f;*/ //Rebote
	fixture.restitution = rebote;

	b->CreateFixture(&fixture);

	pbody->body = b;
	pbody->width = pbody->height = radius;

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangle(int x, int y, int width, int height)
{
	b2BodyDef boxBodyDef;
	boxBodyDef.type = b2_dynamicBody;
	boxBodyDef.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&boxBodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(PIXEL_TO_METERS(width), PIXEL_TO_METERS(height));

	b2FixtureDef boxFixture;
	boxFixture.shape = &boxShape;
	boxFixture.density = 1.0f;

	b->CreateFixture(&boxFixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	pbody->width = (int)(width * 0.5f);
	pbody->height = (int)(height * 0.5f);

	boxBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(pbody);

	return pbody;
}

PhysBody* ModulePhysics::CreateRectangleNo(int x, int y, int width, int height)
{
	b2BodyDef boxBodyDef;
	boxBodyDef.type = b2_staticBody;
	boxBodyDef.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&boxBodyDef);

	b2PolygonShape boxShape;
	boxShape.SetAsBox(PIXEL_TO_METERS(width), PIXEL_TO_METERS(height));

	b2FixtureDef boxFixture;
	boxFixture.shape = &boxShape;
	boxFixture.density = 1.0f;

	b->CreateFixture(&boxFixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;
	pbody->width = (int)(width * 0.5f);
	pbody->height = (int)(height * 0.5f);

	boxBodyDef.userData.pointer = reinterpret_cast<uintptr_t>(pbody);

	return pbody;
}

b2RevoluteJoint* ModulePhysics::CreateJoint(b2Body* paddleAnchor, b2Body* paddle, b2Vec2 pivot) {

	
	float restAngle = -30.0f * DEG2RAD;  // Bottom resting position

	paddleAnchor->SetTransform(paddleAnchor->GetPosition(), restAngle);
	paddle->SetTransform(paddle->GetPosition(), restAngle);
	b2RevoluteJointDef jointDef;
	b2Vec2 worldPivot = paddle->GetWorldPoint(pivot);
	jointDef.Initialize(paddleAnchor, paddle, worldPivot);
	

	jointDef.enableLimit = true;
	jointDef.lowerAngle = 0.0f * DEG2RAD;
	jointDef.upperAngle = 60.0f * DEG2RAD;

	jointDef.enableMotor = true;
	jointDef.motorSpeed = 0.0f; 
	jointDef.maxMotorTorque = 100000.0f;

	b2RevoluteJoint* flipperJoint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);


	return flipperJoint ;
}
void ModulePhysics::UpdateJoint(b2RevoluteJoint* flipperJoint) {

	if (IsKeyDown(KEY_A)) {
	
		flipperJoint->SetMotorSpeed(20.0f);
	
	}
	else {
		flipperJoint->SetMotorSpeed(0.0f);
	}

}

PhysBody* ModulePhysics::CreateChain(int x, int y, const int* points, int size)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));
	
	b2Body* body = world->CreateBody(&bodyDef);

	b2ChainShape chainShape;
	b2Vec2* vertices = new b2Vec2[size / 2];

	for (int i = 0; i < size / 2; ++i) {
		vertices[i] = b2Vec2(PIXEL_TO_METERS(points[i * 2]), PIXEL_TO_METERS(points[i * 2 + 1]));
	}

	chainShape.CreateLoop(vertices, size / 2);

	delete[] vertices;

	b2FixtureDef fixture;
	fixture.shape = &chainShape;
	fixture.density = 1.0f;

	body->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = body;
	pbody->width = pbody->height = 0;

	bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(pbody);

	return pbody;

}

void PhysBody::GetPhysicPosition(int& x, int& y) const
{
	b2Vec2 pos = body->GetPosition();
	x = METERS_TO_PIXELS(pos.x);
	y = METERS_TO_PIXELS(pos.y);
}

float PhysBody::GetRotation() const
{
	return body->GetAngle();
}

bool PhysBody::Contains(int x, int y) const
{
	b2Vec2 p(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	// Return true in case the point is inside ANY of the shapes contained by this body

	b2Fixture* fixture = body->GetFixtureList();
	while (fixture != nullptr) {
		if (fixture->GetShape()->TestPoint(body->GetTransform(), p))
			return true;

		fixture = fixture->GetNext();
	}


	return false;
}

void ModulePhysics::BeginContact(b2Contact* contact)
{
	PhysBody* a = (PhysBody*)contact->GetFixtureA()->GetBody()->GetUserData().pointer;
	PhysBody* b = (PhysBody*)contact->GetFixtureB()->GetBody()->GetUserData().pointer;

	if (a && a->listener) {
		a->listener->OnCollision(a, b);
	}

	if (b && b->listener) {
		b->listener->OnCollision(b, a);
	}
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// TODO Delete the whole physics world!


	return true;
}

void ModulePhysics::DestroyBody(PhysBody* body)
{
	if (body != nullptr && body->body != nullptr)
	{
		world->DestroyBody(body->body); // lo quita del mundo
		body->body = nullptr;
	}
}



