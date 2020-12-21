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



Entity *DinoGSpawn(int level)
{
	Entity *DinoG;
	DinoG = gf3d_entity_new();
	//make sure to properly use entity system w/ gf3d_entity_new
	if (!DinoG)
	{
		slog("failed to spawn a new DinoG enttity");
		return NULL;
	}
	if (level >= 5)
	{
		DinoG->model = gf3d_model_load("DinoG2");
		DinoG->model->frameCount = 1;
	}
	else{
		DinoG->model = gf3d_model_load("DinoG");
		DinoG->model->frameCount = 1;
	}

	DinoG->health = 50;
	DinoG->experience = 5;
	DinoG->movespeed = 0.015;
	DinoG->STATE = PASSIVE;
	DinoG->radius = 5.0;
	DinoG->EntityType = Mob4;
	DinoG->range = 100;
	DinoG->target = 0;
	DinoG->DIRECTION = Back;
	DinoG->position = vector3d((rand() % 102) * -1, rand() % 102, 0);
	DinoG->think = DinoG_think;
	gfc_matrix_make_translation(DinoG->modelMatrix, DinoG->position);

	slog("DinoG was spawned");

	return DinoG;

}

void DinoG_think(Entity *DinoG)
{
	if (!DinoG)return;



	if (DinoG->target != 0)
	{
		gf3d_entity_follow(DinoG->target, DinoG);
	}


	if (DinoG->health <= 0)
	{
		if (DinoG->target->EntityType == Player)
		{
			DinoG->target->experience += DinoG->experience;
			DinoG->target->Slayed += 1;
			slog("Death by player");
		}

		gf3d_entity_free(DinoG);
	}

	if (DinoG->isPoisoned)
	{
		if (SDL_GetTicks() % 1000 == 0)
		{
			DinoG->health -= 1;
			DinoG->PoisonTaken++;
			slog("%d", DinoG->health);
			slog("Poison Tick");

		}

		if (DinoG->PoisonTaken == 15)
		{
			DinoG->isPoisoned = 0;
			DinoG->PoisonTaken = 0;
		}
	}
}