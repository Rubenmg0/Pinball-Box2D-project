#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleGame.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleGame::ModuleGame(Application* app, bool start_enabled) : Module(app, start_enabled), currentScreen(GameScreen::START)
{
	
}

ModuleGame::~ModuleGame()
{}

// Load assets
bool ModuleGame::Start() 
{

	LOG("Loading Intro assets");
	bool ret = true;
	
	//---------------------------------CREACIÓN FISICAS MAPA----------------------------------------//
	int bg[210] ={
	360, 1079,
	360, 1066,
	531, 1016,
	531, 958,
	412, 992,
	405, 966,
	532, 927,
	532, 574,
	462, 547,
	510, 399,
	523, 357,
	527, 343,
	529, 327,
	531, 312,
	531, 294,
	529, 273,
	527, 255,
	522, 235,
	515, 215,
	506, 198,
	495, 178,
	480, 157,
	465, 140,
	450, 126,
	435, 115,
	417, 103,
	421, 94,
	437, 103,
	452, 115,
	466, 127,
	478, 139,
	488, 150,
	496, 161,
	503, 172,
	514, 190,
	521, 205,
	529, 226,
	533, 239,
	537, 257,
	539, 274,
	540, 285,
	540, 304,
	540, 323,
	540, 935,
	597, 935,
	597, 288,
	597, 268,
	594, 248,
	588, 227,
	582, 207,
	574, 187,
	564, 165,
	550, 140,
	535, 119,
	516, 96,
	493, 75,
	473, 59,
	452, 45,
	428, 33,
	401, 21,
	375, 13,
	348, 9,
	331, 7,
	310, 5,
	286, 6,
	258, 8,
	235, 13,
	213, 19,
	195, 26,
	177, 34,
	156, 45,
	139, 56,
	123, 67,
	104, 83,
	91, 97,
	79, 111,
	67, 125,
	55, 144,
	45, 160,
	37, 176,
	29, 193,
	22, 213,
	17, 235,
	12, 258,
	10, 279,
	9, 300,
	10, 327,
	13, 352,
	21, 383,
	112, 660,
	100, 662,
	89, 666,
	79, 673,
	72, 682,
	67, 693,
	66, 706,
	53, 706,
	41, 708,
	28, 713,
	21, 720,
	13, 732,
	9, 740,
	9, 997,
	246, 1068,
	246, 1079
	};
	for (int i = 0; i < 210; i++) {
	
		PIXEL_TO_METERS(bg[i]);
	
	}

	App->physics->CreateChain(0,0,bg, 210); //BackGround

	int palo1[90] = {
	185, 106,
	173, 114,
	162, 122,
	151, 131,
	135, 147,
	125, 159,
	112, 177,
	100, 198,
	92, 216,
	85, 236,
	79, 256,
	77, 285,
	76, 302,
	77, 331,
	82, 352,
	88, 374,
	96, 400,
	104, 423,
	112, 448,
	125, 488,
	143, 541,
	156, 580,
	168, 617,
	176, 641,
	167, 644,
	146, 583,
	134, 544,
	116, 491,
	103, 450,
	94, 424,
	86, 400,
	78, 375,
	72, 353,
	68, 330,
	66, 301,
	67, 276,
	71, 252,
	76, 231,
	84, 211,
	92, 193,
	105, 171,
	118, 152,
	141, 126,
	155, 114,
	178, 98
	};
	for (int i = 0; i < 90; i++) {

		PIXEL_TO_METERS(palo1[i]);

	}

	App->physics->CreateChain(0, 0, palo1, 90);  //First loop

	int palo2[150] = {
	143, 241,
	149, 228,
	153, 218,
	160, 206,
	170, 192,
	178, 183,
	188, 174,
	198, 165,
	208, 158,
	218, 151,
	232, 144,
	247, 138,
	259, 134,
	275, 131,
	289, 130,
	303, 129,
	313, 129,
	326, 130,
	338, 132,
	352, 136,
	367, 141,
	380, 146,
	390, 152,
	401, 159,
	412, 168,
	423, 178,
	432, 188,
	442, 200,
	449, 211,
	456, 224,
	463, 240,
	467, 252,
	470, 263,
	472, 278,
	473, 292,
	473, 316,
	471, 331,
	468, 344,
	464, 360,
	454, 356,
	458, 343,
	461, 330,
	463, 316,
	464, 302,
	464, 288,
	462, 270,
	458, 256,
	452, 240,
	446, 227,
	441, 217,
	433, 205,
	424, 193,
	416, 185,
	404, 174,
	394, 167,
	383, 159,
	370, 153,
	355, 147,
	340, 142,
	324, 139,
	310, 138,
	298, 138,
	284, 139,
	271, 141,
	256, 145,
	243, 150,
	228, 157,
	216, 164,
	204, 173,
	193, 182,
	181, 195,
	172, 207,
	163, 221,
	159, 229,
	152, 244

	};
	for (int i = 0; i < 150; i++) {

		PIXEL_TO_METERS(palo2[i]);

	}

	App->physics->CreateChain(0, 0, palo2, 150); //Second loop -Mid-

	int palo3[14] = { 
		76, 789,
		76, 860,
		76, 928,
		203, 966,
		192, 991,
		66, 953,
		66, 789
	};
	for (int i = 0; i < 14; i++) {

		PIXEL_TO_METERS(palo3[i]);

	}

	App->physics->CreateChain(0, 0, palo3, 14); // Left down "L" 

	int palo4[16] = {
		138, 784,
		183, 894,
		183, 900,
		176, 902,
		142, 891,
		134, 885,
		133, 875,
		133, 782
	};
	for (int i = 0; i < 16; i++) {

		PIXEL_TO_METERS(palo4[i]);

	}

	App->physics->CreateChain(0, 0, palo4, 16); //Left down "triangle"

	int palo5[20] = {
		474, 783,
		474, 807,
		474, 877,
		471, 885,
		464, 891,
		448, 897,
		430, 902,
		424, 901,
		423, 894,
		469, 783
	};
	for (int i = 0; i < 20; i++) {

		PIXEL_TO_METERS(palo5[i]);

	}
	App->physics->CreateChain(0, 0, palo5, 20); //Right down "triangle"
	//--------------------------------------------------------------------------------------------------------------//

	// ESTO SE TIENE QE HACER UN LA FUNCION DE CREAR CIRCULOS EN VEZ DE HACERLO A MANO
	int rebote[38] = {
	6, 14,
	9, 10,
	17, 4,
	27, 1,
	35, 1,
	46, 3,
	56, 9,
	61, 17,
	64, 28,
	63, 41,
	58, 49,
	50, 58,
	40, 62,
	28, 62,
	17, 58,
	8, 49,
	2, 38,
	1, 31,
	2, 22
	};
	for (int i = 0; i < 38; i++) {

		PIXEL_TO_METERS(rebote[i]);

	}

	//Posiciones correctas ***
	App->physics->CreateChain(170, 200, rebote, 38);
	App->physics->CreateChain(270, 140, rebote, 38);
	App->physics->CreateChain(370, 200, rebote, 38);
	
	App->physics->CreateCircle(570, 920, 10); //Pelota inicial ///////////////////////////////////////////////////////////////

	return ret;
}

// Load assets
bool ModuleGame::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update: draw background
update_status ModuleGame::Update()
{
	switch (currentScreen) {
	case GameScreen::START:
		if (IsKeyPressed(KEY_ENTER)) {
			currentScreen = GameScreen::GAMEPLAY;
		}
		break;

	case GameScreen::DEATH:
		currentScreen = GameScreen::GAMEPLAY;
		App->physics->CreateCircle(570, 920, 10);
	}

	if (IsKeyPressed(KEY_SPACE))
	{
		bodies.push_back(App->physics->CreateCircle(GetMouseX(), GetMouseY(), 10));
	}


	return UPDATE_CONTINUE;
}
