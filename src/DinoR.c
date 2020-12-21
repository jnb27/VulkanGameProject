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

//Entity *DinoR;

Entity *DinoRSpawn(int level)
{
	Entity *DinoR;
	DinoR = gf3d_entity_new();
	//make sure to properly use entity system w/ gf3d_entity_new
	if (!DinoR)
	{
		slog("failed to spawn a new DinoR enttity");
		return NULL;
	}
	if (level >= 5)
	{
		DinoR->model = gf3d_model_load("DinoR2");
	}
	else{
		DinoR->model = gf3d_model_load("DinoR");
	}
	
	DinoR->health = 50;
	DinoR->experience = 15;
	DinoR->movespeed = 0.01;
	DinoR->STATE = PASSIVE;
	DinoR->radius = 5.0;
	DinoR->EntityType = Mob5;
	DinoR->range = 300;
	DinoR->target = 0;
	DinoR->DIRECTION = Back;
	DinoR->position = vector3d( (rand() % 102) * -1, rand() % 102 , 0);
	DinoR->think = DinoR_think;
	gfc_matrix_make_translation(DinoR->modelMatrix, DinoR->position);

	slog("DinoR was spawned");

	//switch (worldLevel)
	//{
	//case 1: 
	//	break;
	//case 2: 

	//}

	return DinoR;

}

void DinoR_think(Entity *DinoR)
{
	if (!DinoR)return;

	if (DinoR->target != 0 /*&& DinoR->target->EntityType == Pickup*/)
	{
		gf3d_entity_follow(DinoR->target, DinoR);
	}


	if (DinoR->health <= 0)
	{

		if (DinoR->target->EntityType == Player)
		{
			DinoR->target->experience += DinoR->experience;
			DinoR->target->Slayed += 1;
			slog("Death by player");
		}

		gf3d_entity_free(DinoR);
	}

	if (DinoR->isPoisoned)
	{
		if (SDL_GetTicks() % 1000 == 0)
		{
			DinoR->health -= 1;
			DinoR->PoisonTaken++;
			slog("%d", DinoR->health);
			slog("Poison Tick");

		}

		if (DinoR->PoisonTaken == 15)
		{
			DinoR->isPoisoned = 0;
			DinoR->PoisonTaken = 0;
		}
	}

}