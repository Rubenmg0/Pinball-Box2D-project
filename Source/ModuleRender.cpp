#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleGame.h"
#include <math.h>

ModuleRender::ModuleRender(Application* app, bool start_enabled) : Module(app, start_enabled)
{
    background = GRAY;
}

// Destructor
ModuleRender::~ModuleRender()
{}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");
	bool ret = true;

    //Colocar texturas
    pinball_Ball = LoadTexture("Assets/gadgets/pinball_Ball.png");
    cohete = LoadTexture("Assets/background/ship.png");
    fondo = LoadTexture("Assets/background/bg.png");
    inicio = LoadTexture("Assets/background/metal-pinball_resized.png");
    menu = LoadTexture("Assets/background/menu.png");

    //Texturas con animación
    bumper = LoadTexture("Assets/scores/bumper.png");
    rollover = LoadTexture("Assets/scores/rollover.png");

    //coins = LoadTexture("Assets/scores/.png");

	return ret;
}

// PreUpdate: clear buffer
update_status ModuleRender::PreUpdate()
{

	return UPDATE_CONTINUE;
}

// Update: debug camera
update_status ModuleRender::Update()
{
    ClearBackground(background);

	switch (App->scene_intro->currentScreen) {

	case GameScreen::START:

		DrawTextureEx(inicio, { (-55), (0) }, 0.0f, 1, WHITE);
		break;

    case GameScreen::MENU:

        DrawTextureEx(menu, { (0), (0) }, 0.0f, 1, WHITE);
        break;

	case GameScreen::GAMEPLAY:

		DrawTextureEx(fondo, { (0), (0) }, 0.0f, 1, WHITE);
		DrawTextureEx(cohete, { (540), (935) }, 0.0f, 1, WHITE);
		break;

	case GameScreen::DEATH:

		break;

	case GameScreen::ENDING:

		
		break;
	}

    // NOTE: This function setups render batching system for
    // maximum performance, all consecutive Draw() calls are
    // not processed until EndDrawing() is called
    BeginDrawing();

	return UPDATE_CONTINUE;
}

// PostUpdate present buffer to screen
update_status ModuleRender::PostUpdate()
{
    // Draw everything in our batch!
    DrawFPS(10, 10);

    EndDrawing();

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	return true;
}

void ModuleRender::SetBackgroundColor(Color color)
{
	background = color;
}

// Draw to screen
bool ModuleRender::Draw(Texture2D texture, int x, int y, const Rectangle* section, double angle, int pivot_x, int pivot_y) const
{
	bool ret = true;

	float scale = 1.0f;
    Vector2 position = { (float)x, (float)y };
    Rectangle rect = { 0.f, 0.f, (float)texture.width, (float)texture.height };

    if (section != NULL) rect = *section;

    position.x = (float)(x-pivot_x) * scale + camera.x;
    position.y = (float)(y-pivot_y) * scale + camera.y;

	rect.width *= scale;
	rect.height *= scale;

    DrawTextureRec(texture, rect, position, WHITE);

	return ret;
}

bool ModuleRender::DrawText(const char * text, int x, int y, Font font, int spacing, Color tint) const
{
    bool ret = true;

    Vector2 position = { (float)x, (float)y };

    DrawTextEx(font, text, position, (float)font.baseSize, (float)spacing, tint);

    return ret;
}
