#include "gf3d_entity.h"
#include "A_Slime.h"
#include "Projectile.h"
/*
	Let's Program some states ! 
	State 1: Passive - Do nothing maybe just walk left and right for fun
	State 2: Angry, only triggered if touched become hostile
	State 3: If I am angry, chase the player
	State 4: If I am near the player hit the player
	State 5: Dead?
*/

Entity *ent[10] = { 0 };

Entity *a_slime_spawn(Entity *Slime)
{
	Slime = gf3d_entity_new();
	//make sure to properly use entity system w/ gf3d_entity_new
	if (!Slime)
	{
		slog("failed to spawn a new slime enttity");
		return NULL;
	}

	Slime->model = gf3d_model_load("DinoB");
	Slime->health = 30;
	Slime->experience = 5;
	Slime->movespeed = 0.0075;
	Slime->STATE = PASSIVE;
	Slime->radius = 5.0;
	Slime->EntityType = Mob1;
	Slime->range = 20;
	Slime->target = 0;
	Slime->position = vector3d((rand() % 102) * -1, rand() % 102, 0);
	Slime->think = slime_think;
	gfc_matrix_make_translation(Slime->modelMatrix, Slime->position);

	slog("Slime was spawned");

	return Slime;

}

void slime_think(Entity *Slime)
{
	if (!Slime)return;
	if (Slime->STATE == PASSIVE)
	{
		if (Slime->target != 0)
		{
			//slog("I have something");
			Slime->STATE = AGGRO;
		}
	}
	if (Slime->STATE == AGGRO)
	{
		//Fight the thing
		gf3d_entity_follow(Slime->target, Slime);

		if (SDL_GetTicks() == 0 || SDL_GetTicks() % 500 == 0)
		{
			//fire projectile 
			slog("%d", SDL_GetTicks());
			create_projectile(Slime, ent[0]);
		}
	}
	
	if (Slime->health <= 0)
	{
		gf3d_entity_free(Slime);
	}
	
}