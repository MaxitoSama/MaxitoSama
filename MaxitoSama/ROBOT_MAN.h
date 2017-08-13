#pragma once
#ifndef _ROBOT_MAN_
#define _ROBOT_MAN_

#include "Enemy.h"
#include "Path.h"
#include "ModuleEnemies.h"

#define RIFLEMAN_WALKSPEED 0.5

class Robot_man : public Enemy
{
private:
	Path path;
	Path path2;
	Animation moveLeft;
	iPoint original_pos;
	fPoint move = { 0.0f,0.0f };
	Animation death_animation;
	Collider* collider2;

	int counter;

public:
	int shot_current_delay = ENEMY_SHOT_DELAY - 1;
	Robot_man(int x, int y);
	void Move();

};

#endif 
