#include "gf3d_entity.h"
#include "DinoW.h"

/*
Let's Program some states !
State 1: Passive - Do nothing maybe just walk left and right for fun
State 2: Angry, only triggered if touched become hostile
State 3: If I am angry, chase the player
State 4: If I am near the player hit the player
State 5: Dead?
*/

Entity *DinoW;

Entity *DinoWSpawn()
{
	DinoW = gf3d_entity_new();
	//make sure to properly use entity system w/ gf3d_entity_new
	if (!DinoW)
	{
		slog("failed to spawn a new DinoW enttity");
		return NULL;
	}

	DinoW->model = gf3d_model_load("DinoW");
	DinoW->health = 150;
	DinoW->experience = 5;
	DinoW->movespeed = 0.0075;
	DinoW->STATE = PASSIVE;
	DinoW->radius = 5.0;
	DinoW->EntityType = Mob2;
	DinoW->range = 35;
	DinoW->target = 0;
	DinoW->DIRECTION = Back;
	DinoW->position = vector3d(-40, -40, 0);
	DinoW->think = DinoW_think;
	gfc_matrix_make_translation(DinoW->modelMatrix, DinoW->position);

	slog("DinoW was spawned");

	return DinoW;

}

void DinoW_think()
{
	if (!DinoW)return;



	if (DinoW->target != 0)
	{
		gf3d_entity_follow(DinoW->target, DinoW);
	}


	if (DinoW->health <= 0)
	{
		gf3d_entity_free(DinoW);
	}

}