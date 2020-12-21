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



Entity *DinoPSpawn(int level)
{
	Entity *DinoP;
	DinoP = gf3d_entity_new();
	//make sure to properly use entity system w/ gf3d_entity_new
	if (!DinoP)
	{
		slog("failed to spawn a new DinoP enttity");
		return NULL;
	}
	if (level >= 5)
	{
		DinoP->model = gf3d_model_load("DinoP");
	}
	else{
		DinoP->model = gf3d_model_load("DinoP");
	}

	DinoP->health = 50;
	DinoP->experience = 25;
	DinoP->movespeed = 0.0075;
	DinoP->STATE = PASSIVE;
	DinoP->radius = 5.0;
	DinoP->EntityType = Mob3;
	DinoP->range = 35;
	DinoP->target = 0;
	DinoP->DIRECTION = Back;
	DinoP->position = vector3d((rand() % 102) * -1, rand() % 102, 0);
	DinoP->think = DinoP_think;
	gfc_matrix_make_translation(DinoP->modelMatrix, DinoP->position);

	slog("DinoP was spawned");

	return DinoP;

}

void DinoP_think(Entity *DinoP)
{
	if (!DinoP)return;

	if (DinoP->isPoisoned)
	{
		if (SDL_GetTicks() % 1000 == 0)
		{
			DinoP->health -= 1;
			DinoP->PoisonTaken++;
			slog("%d", DinoP->health);
			slog("Poison Tick");

		}

		if (DinoP->PoisonTaken == 15)
		{
			DinoP->isPoisoned = 0;
			DinoP->PoisonTaken = 0;
		}
	}

	if (DinoP->position.x > 100 || DinoP->position.x < -100 || DinoP->position.y > 100 || DinoP->position.y < -100)
	{
		gf3d_entity_free(DinoP);
	}

	if (DinoP->isBlinded)
	{
		DinoP->target = 0;
		if (SDL_GetTicks() % 1000 == 0)
		{	
			DinoP->BlindTime++;
		}


		if (DinoP->BlindTime == 10)
		{
			DinoP->isBlinded = 0;
			DinoP->BlindTime = 0; 
		}
	}

	if (DinoP->target != 0)
	{
		gf3d_entity_follow(DinoP->target, DinoP);
	}


	if (DinoP->health <= 0)
	{
		if (DinoP->target->EntityType == Player)
		{
			DinoP->target->experience += DinoP->experience;
			DinoP->target->Slayed += 1;
			slog("Death by player");
		}

		gf3d_entity_free(DinoP);
	}

}