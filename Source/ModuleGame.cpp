#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleGame.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleGame::ModuleGame(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	
}

ModuleGame::~ModuleGame()
{}

// Load assets
bool ModuleGame::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	int bg[130] = {
	246, 1079,
	246, 1065,
	9, 998,
	10, 739,
	17, 724,
	32, 711,
	47, 707,
	66, 707,
	70, 685,
	81, 670,
	97, 661,
	113, 659,
	17, 370,
	10, 335,
	8, 301,
	11, 256,
	20, 215,
	35, 180,
	54, 142,
	81, 107,
	110, 76,
	152, 45,
	197, 24,
	236, 11,
	285, 5,
	328, 5,
	380, 15,
	424, 30,
	460, 51,
	504, 84,
	538, 124,
	565, 163,
	585, 208,
	594, 244,
	599, 278,
	599, 1068,
	540, 1068,
	540, 278,
	534, 240,
	523, 209,
	509, 180,
	487, 148,
	465, 126,
	439, 107,
	421, 94,
	416, 102,
	432, 114,
	459, 134,
	480, 156,
	500, 185,
	513, 213,
	524, 244,
	530, 276,
	530, 330,
	525, 353,
	517, 380,
	461, 546,
	530, 574,
	530, 930,
	406, 965,
	411, 991,
	531, 957,
	531, 1016,
	360, 1066,
	360, 1079
	};
	for (int i = 0; i < 130; i++) {
	
		PIXEL_TO_METERS(bg[i]);
	
	}

	App->physics->CreateChain(0,0,bg, 130);

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

	App->physics->CreateChain(0, 0, palo1, 90);

	int palo2[96] = {
	151, 244,
	158, 230,
	163, 221,
	170, 208,
	184, 191,
	197, 178,
	212, 166,
	236, 153,
	259, 144,
	285, 139,
	318, 139,
	345, 143,
	372, 154,
	397, 168,
	419, 187,
	438, 211,
	450, 232,
	457, 252,
	463, 275,
	465, 301,
	463, 323,
	460, 341,
	455, 356,
	464, 360,
	468, 345,
	472, 325,
	474, 301,
	473, 274,
	469, 259,
	462, 235,
	452, 214,
	439, 195,
	426, 181,
	412, 168,
	392, 154,
	374, 144,
	353, 136,
	332, 131,
	307, 129,
	287, 130,
	263, 134,
	240, 141,
	221, 150,
	202, 162,
	185, 177,
	171, 191,
	160, 206,
	143, 240
	};
	for (int i = 0; i < 96; i++) {

		PIXEL_TO_METERS(palo2[i]);

	}

	App->physics->CreateChain(0, 0, palo2, 96);

	int palo3[14] = { // L en izquierda inferior
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

	App->physics->CreateChain(0, 0, palo3, 14);

	int palo4[20] = {
		133, 786,
		133, 878,
		136, 885,
		143, 891,
		178, 903,
		183, 901,
		184, 896,
		155, 824,
		143, 795,
		136, 780
	};
	for (int i = 0; i < 20; i++) {

		PIXEL_TO_METERS(palo4[i]);

	}

	App->physics->CreateChain(0, 0, palo4, 20);

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

	App->physics->CreateChain(0, 0, palo5, 20);
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


	App->physics->CreateChain(170, 200, rebote, 38);
	App->physics->CreateChain(270, 140, rebote, 38);
	App->physics->CreateChain(370, 200, rebote, 38);

	


	int cohete[114] = {
	6, 66,
	6, 60,
	6, 52,
	7, 46,
	10, 45,
	11, 34,
	12, 25,
	14, 17,
	16, 11,
	20, 5,
	24, 1,
	29, 0,
	33, 2,
	39, 9,
	42, 15,
	45, 23,
	47, 29,
	48, 38,
	48, 45,
	52, 49,
	52, 57,
	52, 66,
	49, 69,
	44, 72,
	41, 74,
	41, 80,
	38, 82,
	38, 93,
	38, 103,
	42, 102,
	48, 100,
	53, 103,
	54, 110,
	57, 115,
	57, 121,
	53, 123,
	47, 125,
	40, 127,
	33, 130,
	27, 130,
	22, 127,
	14, 126,
	10, 121,
	4, 118,
	0, 112,
	1, 106,
	5, 102,
	10, 100,
	16, 102,
	21, 105,
	22, 98,
	22, 92,
	22, 87,
	20, 77,
	16, 72,
	10, 70,
	7, 66
	};

	for (int i = 0; i < 114; i++) {

		PIXEL_TO_METERS(cohete[i]);

	}

	App->physics->CreateChain(540, 950, cohete, 114);
	
	App->physics->CreateCircle(570, 850, 20);

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
	if (IsKeyPressed(KEY_SPACE))
	{
		bodies.push_back(App->physics->CreateCircle(GetMouseX(), GetMouseY(), 10));
	}


	return UPDATE_CONTINUE;
}
