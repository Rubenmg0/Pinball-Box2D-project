#pragma once
#include "Module.h"
#include "Globals.h"

#include <limits.h>

class ModuleRender : public Module
{
public:
	ModuleRender(Application* app, bool start_enabled = true);
	~ModuleRender();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

    void SetBackgroundColor(Color color);
	bool Draw(Texture2D texture, int x, int y, const Rectangle* section = NULL, double angle = 0, int pivot_x = 0, int pivot_y = 0) const;
    bool DrawText(const char* text, int x, int y, Font font, int spacing, Color tint) const;

public:

	Color background;
    Rectangle camera;
	Texture pinball_Ball;
	Texture fondo;
	Texture inicio;
	Texture play;
	Texture sound_on;
	Texture sound_off;
	Texture music_on;
	Texture music_off;
	Texture menu;
	Texture gameover;
	Texture restartButton;
	Texture ballBlocker;
	Texture cohete;

	Texture bumper;
	Texture bumper1;

	Texture rollover;
	Texture rollover1;

	Texture flipperR;
	Texture flipperL;

	Texture coins;
};