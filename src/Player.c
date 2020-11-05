#include "Player.h"
#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "Projectile.h"

void player_think(Entity *self);

Entity *player;
int fired = 0;
int canCast = 0;
int lastCast = 0; 


Entity *player_spawn(Vector3D position, const char *modelName)
{
	
	player = gf3d_entity_new();
	player->health = 100;
	player->mana = 100;
	player->position = position;
	player->experience = 0;
	player->invincible = 0;
	//gfc_matrix_identity(player->modelMatrix);

	if (!player)
	{
		slog("failed to spawn a new player enttity");
		return NULL;
	}

	player->model = gf3d_model_load(modelName);
	vector3d_copy(player->position, position);
	player->think = player_think;
	player->movespeed = 0.01;
	return player;
}

void player_think(Entity *self)
{
	const Uint8 *keys;
	keys = SDL_GetKeyboardState(NULL);
	Uint32 CD = SDL_GetTicks();





	if (keys[SDL_SCANCODE_W])
	{
		if (fired < 1)
		{
			fired += 1; 
			Entity *bullet = create_projectile(player);
			slog("Bullet made");
		}
		self->position.y -= player->movespeed;
		gfc_matrix_make_translation(self->modelMatrix, self->position);
		//slog("%i", player->health);
	}
	if (keys[SDL_SCANCODE_S])
	{	
		if (fired < 2)
		{
			fired += 1;
			Entity *bullet = create_projectile(player);
			slog("Bullet made");
		}
		self->position.y += player->movespeed;
		gfc_matrix_make_translation(self->modelMatrix, self->position);
	}
	if (keys[SDL_SCANCODE_A])
	{
		self->position.x += player->movespeed;
		//gfc_matrix_rotate(player->modelMatrix, player->modelMatrix, 0.2, vector3d(0, 1, 0));
		gfc_matrix_make_translation(self->modelMatrix, self->position);
		
	}
	if (keys[SDL_SCANCODE_D])
	{
		self->position.x -= player->movespeed;
		gfc_matrix_make_translation(self->modelMatrix, self->position);
	}













	if (keys[SDL_SCANCODE_1])
	{


		if ((CD - lastCast > 1000))
		{
			canCast = 1;
		}
		else{
			canCast = 0;
		}


		if (player->mana > 10 && canCast == 1)
		{
			//Cast spell
			//player->mana -= 10;
			lastCast = SDL_GetTicks();
			slog("I casted");
		}
		else{
			slog("Spell on cooldown!");
		}
	}










	if (keys[SDL_SCANCODE_2])
	{

		if (player->mana > 15 && canCast == 1)
		{
			//Cast spell

			//player->mana -= 15;
			//slog("%i", timeout);
		}
	}
	if (keys[SDL_SCANCODE_3])
	{
		if (player->mana > 20)
		{
			//Cast spell
			player->mana -= 20;
			slog("%i", player->mana);
		}
	}
	if (keys[SDL_SCANCODE_4])
	{
		if (player->mana > 20)
		{
			//Grant Haste makes fast
			player->mana -= 20;
			player->movespeed += 0.005;
			slog("%i", player->mana);
		}
	}
	if (keys[SDL_SCANCODE_5])
	{
		if (player->mana > 50)
		{
			//Cast full heal
			player->mana -= 50;
			player->health = 100;
			slog("%i", player->mana);
		}
	}

	if (player->invincible == 1)
	{
		player->health = 100;
	}
	
}

void player_delete(Entity *self)
{
//	PlayerData *pd;
	if (!self)return;
	
}

