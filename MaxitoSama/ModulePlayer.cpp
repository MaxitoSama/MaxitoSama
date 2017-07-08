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
	position.x = 0;
	position.y = 0;
	

	// idle animation 
	idleUP.PushBack({ 0, 0, 48, 70 });
	idleDown.PushBack({ 0, 0, 48, 70 });
	idleRight.PushBack({ 0, 0, 48, 70 });
	idleLeft.PushBack({ 0, 0, 48, 70 });
	idleRightUP.PushBack({ 0, 0, 48, 70 });
	idleRightDOWN.PushBack({ 0, 0, 48, 70 });
	idleLeftUP.PushBack({ 0, 0, 48, 70 });
	idleLeftDOWN.PushBack({ 0, 0, 48, 70 });

	// Move up
	up.PushBack({ 331, 28, 29, 26 });
	up.PushBack({361, 28, 29, 26 });
	up.PushBack({ 331, 28, 29, 26 });
	up.PushBack({391, 28, 29, 26 });
	up.loop = true;  
	up.speed = 0.1f;

	// Move down
	down.PushBack({ 421, 28, 29, 26 });
	down.PushBack({ 451, 28, 29, 26 });
	down.PushBack({421, 28, 29, 26 });
	down.PushBack({ 481, 28, 29, 26 });
	down.loop = true;
	down.speed = 0.1f;

	// Move Right
	right.PushBack({ 0,0,48,70 });
	right.PushBack({0,0,48,70 });
	right.PushBack({0,0,48,70 });
	right.PushBack({ 0,0,48,70 });

	right.loop = true;
	right.speed = 0.1f;

	// Move Left
	left.PushBack({421,1,29,26 });
	left.PushBack({451,1,29,26 });
	left.PushBack({421,1,29,26 });
	left.PushBack({ 481,1,29,26 });

	left.loop = true;
	left.speed = 0.1f;

	// Move RightUP;
	rightUP.PushBack({ 361, 82, 29,26 });
	rightUP.PushBack({ 391, 82,29,26 });
	rightUP.PushBack({ 361,82, 29,26 });
	rightUP.PushBack({ 421,82,29,26 });
	rightUP.loop = true;
	rightUP.speed = 0.1f;

	// Move LeftUP
	leftUP.PushBack({ 361,55, 29,26 });
	leftUP.PushBack({ 391, 55,29,26 });
	leftUP.PushBack({ 361,55,29,26 });
	leftUP.PushBack({ 421,55,29,26 });
	leftUP.loop = true;
	leftUP.speed = 0.1f;

	// Move RightDOWN
	rightDOWN.PushBack({ 361,109, 29,26 });
	rightDOWN.PushBack({ 391, 109,29,26 });
	rightDOWN.PushBack({ 361,109,29,26 });
	rightDOWN.PushBack({ 421,109,29,26 });
	rightDOWN.loop = true;
	rightDOWN.speed = 0.1f;

	// Move LeftDOWN
	leftDOWN.PushBack({ 361,136, 29,26 });
	leftDOWN.PushBack({ 391, 136,29,26 });
	leftDOWN.PushBack({ 361,136,29,26 });
	leftDOWN.PushBack({ 421,136,29,26 });
	leftDOWN.loop = true;
	leftDOWN.speed = 0.1f;

	//DIE
	die.PushBack({331,190,29,26});
	die.PushBack({ 361,190,29,26 });
	die.PushBack({ 391,190,29,26 });
	die.loop = false;
	die.speed = 0.05f;	

	//lake death
	waterDie.PushBack({ 421,190,29,26 });
	waterDie.PushBack({ 451,190,29,26 });
	waterDie.PushBack({ 481,190,29,26 });
	waterDie.loop = false;
	waterDie.speed = 0.1f;

	//grenade throw
	grenadeThrow.PushBack({ 331,163,29,26 });
	grenadeThrow.PushBack({ 361,163,29,26 });
	grenadeThrow.PushBack({ 391,163,29,26 });	
	grenadeThrow.loop = false;
	grenadeThrow.speed = 0.1f;


	open_doors.PushBack({ 511,1,98,42 });
	open_doors.PushBack({ 511,44,98,56 });
	open_doors.PushBack({ 511,101,98,59 });
	open_doors.speed = 0.1f;
	open_doors.loop = false;

	close_doors.PushBack({ 511,44,98,56 });
	close_doors.PushBack({ 511,1,98,42 });
	close_doors.speed = 0.04f;
	close_doors.loop = false;

	bridgerino.PushBack({ 1,449,64,70 });
	bridgerino.speed = 0.1f;
	bridgerino.loop = false;

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");



	graphics = App->textures->Load("assets/Player_sheet.png");
	//graphics2= App->textures->Load("assets/Superjoes12.png");
	
	//playercoll = App->collision->AddCollider({ position.x+7, position.y, 14, 23 }, COLLIDER_PLAYER,this);
	//feetcoll= App->collision->AddCollider({ position.x+7, position.y, 14, 10 }, COLLIDER_FEET, this);
	//font_score = App->fonts->Load("fonts/Lletres_1.png", "ABCDEFGHIJKLMNOPQRSTUVWXYZ./\ ", 2);
	//textures = App->textures->Load("assets/PlaceHolder_Sprites.png");

	
	position.x = 0;
	position.y = 0;

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
	LOG("Unloading player");

	App->textures->Unload(graphics);
	App->fonts->UnLoad(font_score);
	App->textures->Unload(textures);
	if (playercoll != nullptr)
		playercoll->to_delete = true;

	return true;
}
// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 1;
	if (App->input->keyboard[SDL_SCANCODE_LEFT] == KEY_STATE::KEY_REPEAT)
	{
		if (position.x > 0) {
			position.x -= speed;
		}
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
		if (position.x < SCREEN_WIDTH - 20) {
			position.x += speed;
		}
		if (current_animation != &right)
		{
			right.Reset();
			current_animation = &right;
		}
		player_last_direction = RIGHT;
	}
	//DOWN
	if (App->input->keyboard[SDL_SCANCODE_DOWN] == KEY_STATE::KEY_REPEAT)
	{
		if (position.y <SCREEN_HEIGHT - 20) {
			position.y += speed;
		}
		if (current_animation != &down)
		{
			down.Reset();
			current_animation = &down;
		}
		player_last_direction = DOWN;
	}
	//UP
	if (App->input->keyboard[SDL_SCANCODE_UP] == KEY_STATE::KEY_REPEAT)
	{
		if (position.y > -1864 + SCREEN_HEIGHT) {
			position.y -= speed;
		}
		if (current_animation != &up)
		{
			up.Reset();
			current_animation = &up;
		}
		player_last_direction = UP;
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
			current_animation = &idleUP;
			break;
		case ModulePlayer::DOWN:
			current_animation = &idleDown;
			break;
		case ModulePlayer::LEFT:
			current_animation = &idleLeft;
			break;
		case ModulePlayer::RIGHT:
			current_animation = &idleRight;
			break;
		default:
			break;
		}
	}

// Player Colliders Position
	//playercoll->SetPos(position.x + 7, position.y);
	//feetcoll->SetPos(position.x+7 , position.y + 13);


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
	if (c2->type == COLLIDER_LAKE && god==false)
	{
		if (alive) {
			alive = false;
			App->elements1->num_lives_play_1--;
			water = true;
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
	if (c2->type == COLLIDER_BULLET_BEHIND_COVER && god == false)
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
	if (c2->type == COLLIDER_GRENADE_BOX)
	{
		if (App->elements1->num_grenades < 100) { //ADDS GRENADES 
			if (c2->rect.x == App->first_scene->box->rect.x && c2->rect.y == App->first_scene->box->rect.y ) { //CHECKING WHICH BOX IT IS, HOW MANY GRENADES ARE IN IT
				for (int i = 0; i < 3; ++i) {
					++App->elements1->num_grenades; 
				}
			}			
		}			
	}

		if (c2->rect.x == App->first_scene->box->rect.x && c2->rect.y == App->first_scene->box->rect.y) { //MOVES THE GRENADE BOX TEXTURE AND COLLIDER AWAY FROM WINDOW
			App->first_scene->box->SetPos(2000, 0);
			App->elements1->pickupBox = true;
		
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
