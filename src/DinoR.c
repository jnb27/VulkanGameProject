#include "gf3d_entity.h"
#include "DinoR.h"

/*
Let's Program some states !
State 1: Passive - Do nothing maybe just walk left and right for fun
State 2: Angry, only triggered if touched become hostile
State 3: If I am angry, chase the player
State 4: If I am near the player hit the player
State 5: Dead?
*/

Entity *DinoR;

Entity *DinoRSpawn()
{
	DinoR = gf3d_entity_new();
	//make sure to properly use entity system w/ gf3d_entity_new
	if (!DinoR)
	{
		slog("failed to spawn a new DinoR enttity");
		return NULL;
	}

	DinoR->model = gf3d_model_load("DinoR");
	DinoR->health = 50;
	DinoR->experience = 5;
	DinoR->movespeed = 0.001;
	DinoR->STATE = PASSIVE;
	DinoR->radius = 5.0;
	DinoR->EntityType = Mob5;
	DinoR->range = 125;
	DinoR->target = 0;
	DinoR->DIRECTION = Back;
	DinoR->position = vector3d(-60, 60, 0);
	DinoR->think = DinoR_think;
	gfc_matrix_make_translation(DinoR->modelMatrix, DinoR->position);

	slog("DinoR was spawned");

	return DinoR;

}

void DinoR_think()
{
	if (!DinoR)return;



	if (DinoR->target != 0)
	{
		gf3d_entity_follow(DinoR->target, DinoR);
	}


	if (DinoR->health <= 0)
	{
		gf3d_entity_free(DinoR);
	}

}