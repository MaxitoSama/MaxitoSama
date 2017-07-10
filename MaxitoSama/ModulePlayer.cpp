#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include "ModuleElements1.h"
#include "ModuleFonts.h"
#include "ModuleAudio.h"
#include "Menu.h"
#include "ModuleFirstScene.h"
#include "ModuleEnemies.h" 
	
ModulePlayer::ModulePlayer()
{
	graphics = NULL;
	current_animation = NULL;
	
	//idle animation
	idle_Stop.PushBack({6,80,46,70});
	idle_Stop.PushBack({ 116,81,46,70 });
	idle_Stop.PushBack({ 63,81,46,70 });
	idle_Stop.PushBack({ 116,81,46,70 });

	idle_Stop.loop = true;
	idle_Stop.speed = 0.09f;

	// Move Right
	right.PushBack({ 6,2,46,70 });
	right.PushBack({61,2,42,70 });
	right.PushBack({117,2,42,70 });
	right.PushBack({ 172,2,42,70 });

	right.loop = true;
	right.speed = 0.1f;

	// Move Left
	left.PushBack({ 6,2,46,70 });
	left.PushBack({ 61,2,42,70 });
	left.PushBack({ 117,2,42,70 });
	left.PushBack({ 172,2,42,70 });

	left.loop = true;
	left.speed = 0.1f;

	//DIE
	die.PushBack({331,190,29,26});
	die.PushBack({ 361,190,29,26 });
	die.PushBack({ 391,190,29,26 });
	die.loop = false;
	die.speed = 0.05f;	

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading Player Sheet");
	graphics = App->textures->Load("assets/Player_sheet.png");
	
	LOG("Loading Player Collider");
	Player_Coll = App->collision->AddCollider({ position.x, position.y, 46, 70 }, COLLIDER_PLAYER,this);
	//font_score = App->fonts->Load("fonts/Lletres_1.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZ./\ ", 2);

	
	position.x = SCREEN_WIDTH/2;
	position.y = 215;

	stop = false;
	anim = false;
	water = false;
	grenade = false;
	god = false;
	counter = 0;
	only = true;
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player Sheet");
	App->textures->Unload(graphics);
	//App->fonts->UnLoad(font_score);
	//App->textures->Unload(textures);

	LOG("Destroying Player Collider");
	if (Player_Coll != nullptr)
		Player_Coll->to_delete = true;

	return true;
}
// Update: draw background
update_status ModulePlayer::Update()
{
	speed = 2;

	//LEFT
	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
	{
		position.x -= speed;
		if (current_animation != &left)
		{
			left.Reset();
			current_animation = &left;
		}
		player_last_direction = LEFT;
	}
	//RIGHT
	if (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT)
	{
		position.x += speed;
		if (current_animation != &right)
		{
			right.Reset();
			current_animation = &right;
		}
		player_last_direction = RIGHT;
	}

	//JUMP
	if (App->input->keyboard[SDL_SCANCODE_SPACE] == KEY_STATE::KEY_REPEAT)
	{
		position.y -= 10;
		Jump = true;
	}
	//DOWN
	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
	{
		/*if (position.y <SCREEN_HEIGHT - 20) {
			position.y += speed;
		}
		if (current_animation != &down)
		{
			down.Reset();
			current_animation = &down;
		}
		player_last_direction = DOWN;*/
	}
	//UP
	if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
	{
		/*if (position.y > -1864 + SCREEN_HEIGHT) {
			position.y -= speed;
		}
		if (current_animation != &up)
		{
			up.Reset();
			current_animation = &up;
		}
		player_last_direction = UP;*/
	}
	////LEFT  <- Oye ho he canviat perque el d'abans era tot lios, crec que ara es mes eficient (pol)
	//if ((App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT || App->input->controll[3] == KEY_STATE::KEY_REPEAT))
	//{
	//	if (current_animation != &left && App->input->keyboard[SDL_SCANCODE_UP] != KEY_STATE::KEY_REPEAT
	//		&& App->input->keyboard[SDL_SCANCODE_DOWN] != KEY_STATE::KEY_REPEAT  && grenade == false)
	//		{
	//			left.Reset();
	//			current_animation = &left;
	//		}
	//	direction = transitionToDirection(direction, M_PI);
	//	position.x -= speed;
	//	player_last_direction = LEFT;

	//}

	////RIGHT
	//else if ((App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT || App->input->controll[2] == KEY_STATE::KEY_REPEAT)
	//	&& position.x<=SCREEN_WIDTH-23 && anim == false && water == false)
	//{
	//	if (current_animation != &right  && grenade == false)
	//	{
	//		right.Reset();
	//		current_animation = &right;
	//	}
	//	direction = transitionToDirection(direction, 2*M_PI);
	//	position.x += speed;
	//	player_last_direction = RIGHT;
	//
	//}
	////UP
	//else if ((App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT || App->input->controll[0] == KEY_STATE::KEY_REPEAT)
	//	&& anim == false && water == false)
	//{
	//	if (current_animation != &up && grenade == false)
	//	{
	//		up.Reset();
	//		current_animation = &up;
	//	}
	//	direction = transitionToDirection(direction,  1.5 * M_PI);
	//	
	//	if(distance == false)
	//	{
	//		position.y -= speed;
	//	}
	//	player_last_direction = UP;

	//}

	//SHOT 
	App->particles->bullet.speed.y = sin(direction) * BULLET_SPEED;
	App->particles->bullet.speed.x = cos(direction) * BULLET_SPEED;
	shot();

	if (App->input->keyboard[SDL_SCANCODE_O] == KEY_STATE::KEY_DOWN ||
		App->input->controll[4] == KEY_STATE::KEY_REPEAT)
	{   //Mes maco que lo de dalt no? (lo de dalt es pot borrar ja que ja no funciona )
		shooting = true;
	}
	if (Jump == true)
	{
		position.y += 1;
	}


	/*if (anim == true)
	{
		current_animation = &die;
		if (current_animation->Finished() == true)
		{
			current_animation->Reset();
				anim = false;
				alive = true;
				only = true;
		}
	}
	else
	{
		anim = false;	
		Disable();
	}

	
	*/
	
	// Special attack

	/*if (App->input->keyboard[SDL_SCANCODE_P] == KEY_STATE::KEY_DOWN ||
		App->input->controll[5] == KEY_STATE::KEY_DOWN) {   //Mes maco que lo de dalt no? (lo de dalt es pot borrar ja que ja no funciona )
		if (App->elements1->num_grenades > 0){
			current_animation = &grenadeThrow;
			if (grenade == false)
			App->particles->AddParticle(App->particles->grenade, position.x + 11, position.y + 3, COLLIDER_NONE);
		}
		grenade = true;
	}
	if (grenade) {
		if (current_animation->Finished() == true) {
			current_animation->Reset();
			grenade = false;
		}
	}*/

	//IDLE ANIMATIONS
	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_IDLE
		&& App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_IDLE)
	{
		switch (player_last_direction)
		{
		case ModulePlayer::UP:
			current_animation = &idle_Stop;
			break;
		case ModulePlayer::DOWN:
			current_animation = &idle_Stop;
			break;
		case ModulePlayer::LEFT:
			current_animation = &idle_Stop;
			break;
		case ModulePlayer::RIGHT:
			current_animation = &idle_Stop;
			break;
		default:
			break;
		}
	}

	// Player Colliders Position
	Player_Coll->SetPos(position.x, position.y);


	// Draw everything --------------------------------------
	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
	
	return UPDATE_CONTINUE;
}

void ModulePlayer::OnCollision(Collider* c1, Collider* c2) {
	if (c2->type == COLLIDER_WALL)
	{
		if (c1 == feetcoll && (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT
			|| App->input->controll[0] == KEY_STATE::KEY_REPEAT))
		{
			position.y += 1;
		}
		if (c1 == feetcoll && (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT
			|| App->input->controll[1] == KEY_STATE::KEY_REPEAT))
		{
			position.y -= 1;
		}
		if (c1 == feetcoll && (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT
			|| App->input->controll[3] == KEY_STATE::KEY_REPEAT))
		{
			position.x += 1;
		}
		if (c1 == feetcoll && (App->input->keyboard[SDL_SCANCODE_RIGHT] == KEY_STATE::KEY_REPEAT
			|| App->input->controll[2] == KEY_STATE::KEY_REPEAT))
		{
			position.x -= 1;
		}
	}
	
	if (c2->type == COLLIDER_ENEMY_SHOT && god == false)
	{
		if (alive) {
			alive = false;
			App->elements1->num_lives_play_1--;
			anim = true;
		}
	}
	
	if (c2->type == COLLIDER_ENEMY && god == false)
	{
		if (alive) {
			alive = false;
			App->elements1->num_lives_play_1--;
			anim = true;
		}
	}

	if (c2->rect.x == App->first_scene->box->rect.x && c2->rect.y == App->first_scene->box->rect.y) { //MOVES THE GRENADE BOX TEXTURE AND COLLIDER AWAY FROM WINDOW
		App->first_scene->box->SetPos(2000, 0);
		App->elements1->pickupBox = true;
	}

	if (c2->type == COLLIDER_FLOOR)
	{
		Jump = false;
	}

	//Jump methode
	if (c2->type == COLLIDER_FLOOR && Jump==true)
	{
		Jump = false;
	}
		
}

float ModulePlayer::transitionToDirection(float current_direction, float final_direction) {
	float speed = 0.1;
	float closer_direction;
	float margin = 0.15;

	if ((final_direction - current_direction) >= M_PI) {
		final_direction += 2* M_PI;
	}
	if (fabsf(current_direction - final_direction) < margin) {
		closer_direction = final_direction;
	}
	else if (current_direction > (final_direction)  )
		closer_direction = current_direction - speed;
	else if (current_direction < (final_direction) )
		closer_direction = current_direction + speed;
	else
  		closer_direction = final_direction;

 	return closer_direction;
}

void ModulePlayer::shot() {
	if (shots_fired < SHOTS_PER_BURST && shooting == true) {
		LOG("ShOOTTOODAAA!!!!");
		if (shot_current_delay < SHOT_DELAY)
			shot_current_delay++;
		else {
			App->particles->AddParticle(App->particles->bullet, position.x + 11, position.y + 3, COLLIDER_PLAYER_SHOT);
			shots_fired++;
			shot_current_delay = 0;
		}
	}
	else {
		shots_fired = 0;
		shooting = false;
	}
}
