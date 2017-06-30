#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleFirstScene.h"
#include "ModuleInput.h"
#include "ModuleFadeToBlack.h"
#include "ModuleAudio.h"
#include "ModuleInit.h"
#include "ModuleElements1.h"

ModuleInit::ModuleInit()
{}

ModuleInit::~ModuleInit()
{}

// Load assets
bool ModuleInit::Start()
{
	LOG("Loading space scene");
	//background_texture = App->textures->Load("assets/First_Scene.png");


	background.PushBack({ 1, 1, 220, 256 });
	background.PushBack({ 222, 1, 220, 256 });
	background.speed = 0.03f;

	LOG("Loading audio scene");
	//music = App->music->LoadChunk("assets/Commando_01_Credit.wav");


	return true;
}

// UnLoad assets
bool ModuleInit::CleanUp()
{
	LOG("Unloading space scene");

	App->textures->Unload(background_texture);
	
	return true;
}

// Update: draw background
update_status ModuleInit::Update()
{
	// Move camera forward -----------------------------


	// Draw everything --------------------------------------

	//App->render->Blit(background_texture, 0, 0, NULL);

	App->render->Blit(background_texture, 0, 0, &(background.GetCurrentFrame()), 0.75f);


	return UPDATE_CONTINUE;
}