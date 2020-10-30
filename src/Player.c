#include "Player.h"
#include "simple_logger.h"

void player_think(Entity *self);

Entity *player;

Entity *player_spawn(Vector3D position, const char *modelName)
{
	
	player = gf3d_entity_new();
	player->health = 100;
	player->mana = 100;
	player->position = position;

	if (!player)
	{
		slog("failed to spawn a new player enttity");
		return NULL;
	}

	player->model = gf3d_model_load(modelName);
	vector3d_copy(player->position, position);
	player->think = player_think;
	return player;
}

void player_think(Entity *self)
{
	const Uint8 *keys;
	keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_W])
	{
		self->velocity.y -= 0.01;
		gfc_matrix_make_translation(self->modelMatrix, self->velocity);
		slog("%i", player->health);
	}
	if (keys[SDL_SCANCODE_S])
	{
		self->velocity.y += 0.01;
		gfc_matrix_make_translation(self->modelMatrix, self->velocity);
	}
	if (keys[SDL_SCANCODE_A])
	{
		self->velocity.x += 0.01;
		gfc_matrix_make_translation(self->modelMatrix, self->velocity);
	}
	if (keys[SDL_SCANCODE_D])
	{
		self->velocity.x -= 0.01;
		gfc_matrix_make_translation(self->modelMatrix, self->velocity);
	}
	if (keys[SDL_SCANCODE_E])
	{
		self->rotation.x += 0.01;
		gfc_matrix_rotate(self->model, self->model, 0.125, vector3d(0, 0, 1));
	}
	if (keys[SDL_SCANCODE_Q])
	{
		self->rotation.y -= 0.01;
		gfc_matrix_make_translation(self->modelMatrix, self->rotation);
	}
	if (keys[SDL_SCANCODE_1])
	{
		if (player->mana > 10)
		{
			//Cast spell
			player->mana -= 10;
			slog("%i", player->mana);
		}
	}
	if (keys[SDL_SCANCODE_2])
	{
		if (player->mana > 15)
		{
			//Cast spell
			player->mana -= 15;
		}
	}
	if (keys[SDL_SCANCODE_3])
	{
		if (player->mana > 20)
		{
			//Cast spell
			player->mana -= 20;
		}
	}
	if (keys[SDL_SCANCODE_4])
	{
		if (player->mana > 20)
		{
			//Cast spell
			player->mana -= 20;
		}
	}
	if (keys[SDL_SCANCODE_5])
	{
		if (player->mana > 50)
		{
			//Cast spell
			player->mana -= 50;
		}
	}
}

void player_delete(Entity *self)
{
	PlayerData *pd;
	if (!self)return;
	
}

