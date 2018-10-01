#pragma once
#include "Module.h"
#include "Globals.h"

#define PIXEL_TO_METERS(pixels) {(float) (pixels / 100.0f)}
#define METERS_TO_PIXELS(meters) {(int) (meters * 100)}

class b2World; 

class ModulePhysics : public Module
{
public:
	ModulePhysics(Application* app, bool start_enabled = true);
	~ModulePhysics();

	bool Start();
	update_status PreUpdate();
	update_status PostUpdate();
	bool CleanUp();

private:

	b2World * my_world;
	bool debug;
};