#include "gf3d_entity.h"
#include "DinoP.h"

/*
Let's Program some states !
State 1: Passive - Do nothing maybe just walk left and right for fun
State 2: Angry, only triggered if touched become hostile
State 3: If I am angry, chase the player
State 4: If I am near the player hit the player
State 5: Dead?
*/

Entity *DinoP;

Entity *DinoPSpawn()
{
	DinoP = gf3d_entity_new();
	//make sure to properly use entity system w/ gf3d_entity_new
	if (!DinoP)
	{
		slog("failed to spawn a new DinoP enttity");
		return NULL;
	}

	DinoP->model = gf3d_model_load("DinoP");
	DinoP->health = 50;
	DinoP->experience = 5;
	DinoP->movespeed = 0.0075;
	DinoP->STATE = PASSIVE;
	DinoP->radius = 5.0;
	DinoP->EntityType = Mob3;
	DinoP->range = 35;
	DinoP->target = 0;
	DinoP->DIRECTION = Back;
	DinoP->position = vector3d(60, 60, 0);
	DinoP->think = DinoP_think;
	gfc_matrix_make_translation(DinoP->modelMatrix, DinoP->position);

	slog("DinoP was spawned");

	return DinoP;

}

void DinoP_think()
{
	if (!DinoP)return;



	if (DinoP->target != 0)
	{
		gf3d_entity_follow(DinoP->target, DinoP);
	}


	if (DinoP->health <= 0)
	{
		gf3d_entity_free(DinoP);
	}

}