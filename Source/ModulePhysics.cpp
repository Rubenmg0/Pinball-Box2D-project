#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"

#include "p2Point.h"

#include <math.h>

#define PIXELS_PER_METER 50.0f // if touched change METER_PER_PIXEL too
#define METER_PER_PIXEL 0.02f // this is 1 / PIXELS_PER_METER !

#define METERS_TO_PIXELS(m) ((int) floor(PIXELS_PER_METER * m))
#define PIXEL_TO_METERS(p)  ((float) METER_PER_PIXEL * p)

ModulePhysics::ModulePhysics(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	world = NULL;
	debug = true;
}

// Destructor
ModulePhysics::~ModulePhysics()
{
}

bool ModulePhysics::Start()
{
	LOG("Creating Physics 2D environment");
	
	world = new b2World(b2Vec2(GRAVITY_X, -GRAVITY_Y));

	int x = SCREEN_WIDTH;
	int y = SCREEN_HEIGHT;

	//Ground
	b2BodyDef groundBody;
	groundBody.type = b2_staticBody;
	groundBody.position.Set(PIXEL_TO_METERS(0), PIXEL_TO_METERS(y));

	b2Body* gb = world->CreateBody(&groundBody);

	b2PolygonShape gshape;
	gshape.SetAsBox(PIXEL_TO_METERS(x), PIXEL_TO_METERS(1));

	gb->CreateFixture(&gshape,0);

	//Left
	b2BodyDef leftBody;
	leftBody.type = b2_staticBody;
	leftBody.position.Set(PIXEL_TO_METERS(0), PIXEL_TO_METERS(0));

	b2Body* lb = world->CreateBody(&leftBody);

	b2PolygonShape lshape;
	lshape.SetAsBox(PIXEL_TO_METERS(1), PIXEL_TO_METERS(y));

	lb->CreateFixture(&lshape,0);

	//Right
	b2BodyDef rightBody;
	rightBody.type = b2_staticBody;
	rightBody.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(0));

	b2Body* rb = world->CreateBody(&rightBody);

	b2PolygonShape rshape;
	rshape.SetAsBox(PIXEL_TO_METERS(1), PIXEL_TO_METERS(y));

	rb->CreateFixture(&rshape, 0);

	//Ceiling
	b2BodyDef ceilBody;
	ceilBody.type = b2_staticBody;
	ceilBody.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(0));

	b2Body* cb = world->CreateBody(&ceilBody);

	b2PolygonShape cshape;
	cshape.SetAsBox(PIXEL_TO_METERS(1), PIXEL_TO_METERS(y));

	cb->CreateFixture(&cshape, 0);

	return true;
}

update_status ModulePhysics::PreUpdate()
{
	world->Step(1.0f / 60.0f, 6, 2);

	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	if (IsKeyPressed(KEY_F1))
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

					App->renderer->Draw(App->renderer->pinball_Ball, METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), 0, 0,16,16); //Dibuixat de texura pinball_Ball

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
						if(i > 0)
							DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), GREEN);
						prev = v;
					}

					v = b->GetWorldPoint(shape->m_vertices[0]);
					DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), GREEN);
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


PhysBody* ModulePhysics::CreateCircle(int x, int y, int radius)
{
	b2BodyDef body;
	body.type = b2_dynamicBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(radius);
	b2FixtureDef fixture;
	fixture.shape = &shape;
	fixture.density = 1.0f;
	fixture.restitution = 1.0f;

	b->CreateFixture(&fixture);

	PhysBody* pbody = new PhysBody();
	pbody->body = b;

	return pbody;
}

void ModulePhysics::CreateRectangle(int x, int y, int width, int height)
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
}

void ModulePhysics::CreateChain(int x, int y, const int* points, int size)
{
	b2Vec2* vertices = new b2Vec2[size / 2];
	for (int i = 0; i < size / 2; ++i) {
		vertices[i] = b2Vec2(PIXEL_TO_METERS(points[i * 2]), PIXEL_TO_METERS(points[i * 2 + 1]));
	}

	b2BodyDef bodyDef;
	bodyDef.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* body = world->CreateBody(&bodyDef);

	b2ChainShape chainShape;
	chainShape.CreateLoop(vertices, size / 2);

	delete[] vertices;

	b2FixtureDef fixture;
	fixture.shape = &chainShape;
	fixture.density = 1.0f;

	body->CreateFixture(&fixture);
}

void PhysBody::GetPosition(int& x, int& y) const
{
	b2Vec2 pos = body->GetPosition();
	x = METERS_TO_PIXELS(pos.x);
	y = METERS_TO_PIXELS(pos.y);
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!


	return true;
}