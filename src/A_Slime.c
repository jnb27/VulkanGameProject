#include "gf3d_entity.h"
#include "A_Slime.h"
/*
	Let's Program some states ! 
	State 1: Passive - Do nothing maybe just walk left and right for fun
	State 2: Angry, only triggered if touched become hostile
	State 3: If I am angry, chase the player
	State 4: If I am near the player hit the player
	State 5: Dead?
*/

Entity *Slime; 

Entity *a_slime_spawn()
{
	Slime = gf3d_entity_new();
	//make sure to properly use entity system w/ gf3d_entity_new
	if (!Slime)
	{
		slog("failed to spawn a new slime enttity");
		return NULL;
	}

	Slime->model = gf3d_model_load("dino");
	Slime->health = 30;
	Slime->experience = 5;
	Slime->think = slime_think;
	Slime->STATE = PASSIVE;

	slog("Slime was spawned");

	return Slime;

}

void slime_think(Entity *self)
{

	if (Slime->STATE == PASSIVE)
	{
		//slog("I am currently passive");
	}
	if (Slime->STATE == AGGRO)
	{
		//Fight the thing
	}
	if (Slime->STATE == SEARCHING)
	{
		//Look for thing
	}
	
}