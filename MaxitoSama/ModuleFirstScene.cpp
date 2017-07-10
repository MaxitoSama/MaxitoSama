#include "Globals.h"
#include <time.h>
#include <stdlib.h>  
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleFirstScene.h"
#include "Menu.h"
#include "ModuleAudio.h"
#include "ModuleEnemies.h"
#include "ModuleElements1.h"


ModuleFirstScene::ModuleFirstScene()
{}

ModuleFirstScene::~ModuleFirstScene()
{}

// Load assets
bool ModuleFirstScene::Start()
{
	LOG("Loading Background Map 1");
	Background_Map = App->textures->Load("assets/Background_Map_1.png");

	LOG("Loading Player Module");
	App->player->Enable();

	LOG("Loading Colliders Module");
	App->collision->Enable();
	

	//COLLIDERS-------------------------------------------------------------------
	App->collision->AddCollider({ 0,285,1000,10}, COLLIDER_FLOOR);




	return true;
}

// UnLoad assets
bool ModuleFirstScene::CleanUp()
{
	LOG("Unloading Background Map 1");
	App->textures->Unload(Background_Map);

	LOG("Unloading Player Module");
	App->player->Disable();

	LOG("Unloading Colliders Module");
	App->collision->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleFirstScene::Update()
{
	uint w, h;
	App->textures->GetSize(Background_Map, w, h);

	for (int i = -1; i < 10; i++)
	{
		App->render->Blit(Background_Map, i*w, 0, NULL);
	}
	
	return UPDATE_CONTINUE;
}