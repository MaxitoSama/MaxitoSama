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
	App->player->Enable();
	
	return true;
}

// UnLoad assets
bool ModuleFirstScene::CleanUp()
{
	LOG("Unloading Background Map 1");
	App->textures->Unload(Background_Map);
	App->player->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleFirstScene::Update()
{
	App->render->Blit(Background_Map,0,0,NULL);
	
	return UPDATE_CONTINUE;
}