#include "gf3d_entity.h"
#include "DinoG.h"

/*
Let's Program some states !
State 1: Passive - Do nothing maybe just walk left and right for fun
State 2: Angry, only triggered if touched become hostile
State 3: If I am angry, chase the player
State 4: If I am near the player hit the player
State 5: Dead?
*/

Entity *DinoG;

Entity *DinoGSpawn()
{
	DinoG = gf3d_entity_new();
	//make sure to properly use entity system w/ gf3d_entity_new
	if (!DinoG)
	{
		slog("failed to spawn a new DinoG enttity");
		return NULL;
	}

	DinoG->model = gf3d_model_load("DinoG");
	DinoG->health = 50;
	DinoG->experience = 5;
	DinoG->movespeed = 0.001;
	DinoG->STATE = PASSIVE;
	DinoG->radius = 5.0;
	DinoG->EntityType = Mob4;
	DinoG->range = 100;
	DinoG->target = 0;
	DinoG->DIRECTION = Back;
	DinoG->position = vector3d(-60, -60, 0);
	DinoG->think = DinoG_think;
	gfc_matrix_make_translation(DinoG->modelMatrix, DinoG->position);

	slog("DinoG was spawned");

	return DinoG;

}

void DinoG_think()
{
	if (!DinoG)return;



	if (DinoG->target != 0)
	{
		gf3d_entity_follow(DinoG->target, DinoG);
	}


	if (DinoG->health <= 0)
	{
		gf3d_entity_free(DinoG);
	}

}