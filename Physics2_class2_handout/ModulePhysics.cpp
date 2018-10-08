#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModulePhysics.h"
#include "math.h"

#include "Box2D/Box2D/Box2D.h"

#ifdef _DEBUG
#pragma comment( lib, "Box2D/libx86/Debug/Box2D.lib" )
#else
#pragma comment( lib, "Box2D/libx86/Release/Box2D.lib" )
#endif

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

	// big static circle as "ground" in the middle of the screen
	int x = SCREEN_WIDTH / 2;
	int y = SCREEN_HEIGHT / 1.5f;
	int diameter = SCREEN_WIDTH / 2;

	b2BodyDef body;
	body.type = b2_staticBody;
	body.position.Set(PIXEL_TO_METERS(x), PIXEL_TO_METERS(y));

	b2Body* b = world->CreateBody(&body);

	b2CircleShape shape;
	shape.m_radius = PIXEL_TO_METERS(diameter) * 0.5f;

	b2FixtureDef fixture;
	fixture.shape = &shape;
	b->CreateFixture(&fixture);

	return true;
}

// 
update_status ModulePhysics::PreUpdate()
{
	world->Step(1.0f / 60.0f, 6, 2);

	return UPDATE_CONTINUE;
}

// 
update_status ModulePhysics::PostUpdate()
{
	// On space bar press, create a circle on mouse position
	if(App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
	{
		b2BodyDef body;
		body.type = b2_dynamicBody;
		float radius = PIXEL_TO_METERS(25);
		body.position.Set(PIXEL_TO_METERS(App->input->GetMouseX()), PIXEL_TO_METERS(App->input->GetMouseY()));

		b2Body* b = world->CreateBody(&body);

		b2CircleShape shape;
		shape.m_radius = radius;
		b2FixtureDef fixture;
		fixture.shape = &shape;

		b->CreateFixture(&fixture);
	}

	if(App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
	{
		// TODO 1: When pressing 2, create a box on the mouse position
		// To have the box behave normally, set fixture's density to 1.0f
		b2BodyDef rectangle;
		rectangle.type = b2_dynamicBody;
		rectangle.position.Set(PIXEL_TO_METERS(App->input->GetMouseX()), PIXEL_TO_METERS(App->input->GetMouseY()));

		b2Body* rect = world->CreateBody(&rectangle); 

		b2PolygonShape shape2;
		shape2.SetAsBox(1, 1); 
		b2FixtureDef fixture2;
		fixture2.shape = &shape2;

		rect->CreateFixture(&fixture2);

	}

	if(App->input->GetKey(SDL_SCANCODE_3) == KEY_DOWN)
	{
		// TODO 2: Create a chain shape using those vertices
		// remember to convert them from pixels to meters!
		
		int points[24] = {
			-38, 80,
			-44, -54,
			-16, -60,
			-16, -17,
			19, -19,
			19, -79,
			61, -77,
			57, 73,
			17, 78,
			20, 16,
			-25, 13,
			-9, 72
		};
	
		b2Vec2 chain[12]; 

		for (int i = 0; i < 12; i++)
		{
			chain[i].x = PIXEL_TO_METERS(points[i*2]);
			chain[i].y = PIXEL_TO_METERS(points[2*i+1]); 
		}

		b2BodyDef chain2;
		chain2.type = b2_dynamicBody;
		chain2.position.Set(PIXEL_TO_METERS(App->input->GetMouseX()), PIXEL_TO_METERS(App->input->GetMouseY()));

		b2Body* CHAIN = world->CreateBody(&chain2);

		b2ChainShape shape2;
		shape2.CreateLoop(chain, 12); 
		b2FixtureDef fixture2;
		fixture2.shape = &shape2;

		CHAIN->CreateFixture(&fixture2);
		 
	}

	if (App->input->GetKey(SDL_SCANCODE_4) == KEY_DOWN)
	{
		int Doraemon[182] = {
			361, -1,
			412, 3,
			466, 14,
			510, 34,
			548, 63,
			576, 95,
			596, 132,
			611, 178,
			615, 221,
			615, 258,
			602, 310,
			584, 357,
			560, 398,
			536, 426,
			540, 440,
			540, 452,
			564, 471,
			584, 490,
			604, 508,
			627, 507,
			647, 512,
			664, 527,
			676, 558,
			670, 583,
			648, 607,
			620, 612,
			587, 598,
			571, 570,
			545, 556,
			543, 597,
			538, 656,
			543, 691,
			543, 725,
			571, 736,
			581, 757,
			578, 773,
			567, 787,
			548, 794,
			515, 800,
			490, 801,
			460, 798,
			437, 795,
			407, 788,
			386, 775,
			378, 755,
			385, 737,
			396, 726,
			377, 711,
			355, 707,
			336, 717,
			328, 730,
			343, 744,
			350, 762,
			343, 780,
			322, 791,
			288, 797,
			241, 801,
			195, 793,
			161, 780,
			150, 748,
			164, 725,
			190, 718,
			191, 684,
			193, 647,
			188, 590,
			187, 522,
			142, 465,
			73, 383,
			43, 381,
			18, 363,
			4, 341,
			3, 313,
			10, 292,
			26, 273,
			47, 264,
			71, 263,
			88, 271,
			106, 283,
			117, 300,
			120, 317,
			121, 334,
			130, 344,
			145, 355,
			114, 274,
			111, 226,
			123, 170,
			144, 113,
			185, 64,
			232, 31,
			287, 7,
			347, -1
		};

		b2Vec2 chain[91];

		for (int i = 0; i < 91; i++)
		{
			chain[i].x = PIXEL_TO_METERS(Doraemon[i * 2]);
			chain[i].y = PIXEL_TO_METERS(Doraemon[2 * i + 1]);
		}

		b2BodyDef chain2;
		chain2.type = b2_dynamicBody;
		chain2.position.Set(PIXEL_TO_METERS(App->input->GetMouseX()), PIXEL_TO_METERS(App->input->GetMouseY()));

		b2Body* CHAIN = world->CreateBody(&chain2);

		b2ChainShape shape_doraemon;
		shape_doraemon.CreateLoop(chain, 91);
		b2FixtureDef fixture_doraemon;
		fixture_doraemon.shape = &shape_doraemon;

		CHAIN->CreateFixture(&fixture_doraemon);
	}

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(!debug)
		return UPDATE_CONTINUE;

	// Bonus code: this will iterate all objects in the world and draw the circles
	// You need to provide your own macro to translate meters to pixels
	for(b2Body* b = world->GetBodyList(); b; b = b->GetNext())
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
					App->renderer->DrawCircle(METERS_TO_PIXELS(pos.x), METERS_TO_PIXELS(pos.y), METERS_TO_PIXELS(shape->m_radius), 255, 255, 255);
				}
				break;

				// Draw polygons ------------------------------------------------
				case b2Shape::e_polygon:
				{
					b2PolygonShape* polygonShape = (b2PolygonShape*)f->GetShape();
					int32 count = polygonShape->GetVertexCount();
					b2Vec2 prev, v;

					for(int32 i = 0; i < count; ++i)
					{
						v = b->GetWorldPoint(polygonShape->GetVertex(i));
						if(i > 0)
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);

						prev = v;
					}

					v = b->GetWorldPoint(polygonShape->GetVertex(0));
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 255, 100, 100);
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
							App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
						prev = v;
					}

					v = b->GetWorldPoint(shape->m_vertices[0]);
					App->renderer->DrawLine(METERS_TO_PIXELS(prev.x), METERS_TO_PIXELS(prev.y), METERS_TO_PIXELS(v.x), METERS_TO_PIXELS(v.y), 100, 255, 100);
				}
				break;

				// Draw a single segment(edge) ----------------------------------
				case b2Shape::e_edge:
				{
					b2EdgeShape* shape = (b2EdgeShape*)f->GetShape();
					b2Vec2 v1, v2;

					v1 = b->GetWorldPoint(shape->m_vertex0);
					v1 = b->GetWorldPoint(shape->m_vertex1);
					App->renderer->DrawLine(METERS_TO_PIXELS(v1.x), METERS_TO_PIXELS(v1.y), METERS_TO_PIXELS(v2.x), METERS_TO_PIXELS(v2.y), 100, 100, 255);
				}
				break;
			}
		}
	}

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModulePhysics::CleanUp()
{
	LOG("Destroying physics world");

	// Delete the whole physics world!
	delete world;

	return true;
}
