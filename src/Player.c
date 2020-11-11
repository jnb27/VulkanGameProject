#include "Player.h"
#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"
#include "Projectile.h"

void player_think();

void CooldownCheck(int time, int x);
void ManaRegen(Entity *self);
void CheckBounds();
void player_delete();

Entity *player;
int fired = 0;
int canCast = 0;
int lastCast[5] = { 0 };
Uint32 CD;

const Uint8 *keys;




Entity *player_spawn(Vector3D position, const char *modelName)
{
	
	player = gf3d_entity_new();
	player->health = 100;
	player->mana = 100;
	player->radius = 5;
	player->position = position;
	player->experience = 0;
	player->invincible = 0;
	player->EntityType = Player;
	

	if (!player)
	{
		slog("failed to spawn a new player enttity");
		return NULL;
	}

	player->model = gf3d_model_load(modelName);
	vector3d_copy(player->position, position);
	player->think = player_think;
	player->movespeed = 0.03;
	return player;
}

void player_think()
{
	keys = SDL_GetKeyboardState(NULL);
	if ((player->position.x >= -84.0 && player->position.y <= -50.0) && (player->position.x  <= -43 && player->position.y >= -89.0 ))
	{
		if (SDL_GetTicks() % 1000 == 0)
		{
			//Take damage
			slog("MANA");
			player->mana = 100;
		}
	}

	if ((player->position.x >= 42.0 && player->position.y <= -44.0) && (player->position.x <= 83 && player->position.y >= -90.0))
	{
		//Take damage
		if (SDL_GetTicks() % 1000 == 0)
		{
			slog("DAMAGE");
			player->health -= 2;
		}

	}

	if (keys[SDL_SCANCODE_W])
	{
		if (player->position.y >= -100.0)
		{
			CheckBounds();
			player->position.y -= player->movespeed;
			gfc_matrix_make_translation(player->modelMatrix, player->position);
			gfc_matrix_rotate(player->modelMatrix, player->modelMatrix, 6.28319, vector3d(0, 0, 1));
			player->DIRECTION = Forward;
		}

		//slog("%i", player->health);
	}
	if (keys[SDL_SCANCODE_S])
	{	
		if (player->position.y <= 100.0)
		{
			CheckBounds();
			player->position.y += player->movespeed;
			gfc_matrix_make_translation(player->modelMatrix, player->position);
			gfc_matrix_rotate(player->modelMatrix, player->modelMatrix, 3.14159, vector3d(0, 0, 1));
			player->DIRECTION = Back;
		}
		
	}
	if (keys[SDL_SCANCODE_A])
	{
		if (player->position.x <= 100)
		{
			CheckBounds();
			player->position.x += player->movespeed;
			gfc_matrix_make_translation(player->modelMatrix, player->position);
			gfc_matrix_rotate(player->modelMatrix, player->modelMatrix, 1.5708, vector3d(0, 0, 1));
			player->DIRECTION = Left;
		}

		
	}
	if (keys[SDL_SCANCODE_D])
	{
		if (player->position.x >= -100.0)
		{
			CheckBounds();
		player->position.x -= player->movespeed;
		gfc_matrix_make_translation(player->modelMatrix, player->position);
		gfc_matrix_rotate(player->modelMatrix, player->modelMatrix, -1.5708, vector3d(0, 0, 1));
		player->DIRECTION = Right;

		}

	}

	//Rotation cases for holding both buttons
	if (keys[SDL_SCANCODE_W] && keys[SDL_SCANCODE_A] )
	{
		//slog("Holding both");
		gfc_matrix_make_translation(player->modelMatrix, player->position);
		gfc_matrix_rotate(player->modelMatrix, player->modelMatrix, 0.785398, vector3d(0, 0, 1));
		player->DIRECTION = ForwardLeft;
	}

	if (keys[SDL_SCANCODE_W] && keys[SDL_SCANCODE_D])
	{
		//slog("Holding both");
		gfc_matrix_make_translation(player->modelMatrix, player->position);
		gfc_matrix_rotate(player->modelMatrix, player->modelMatrix, -0.785398, vector3d(0, 0, 1));
		player->DIRECTION = ForwardRight;
	}
	if (keys[SDL_SCANCODE_S] && keys[SDL_SCANCODE_A])
	{
		//slog("Holding both");
		gfc_matrix_make_translation(player->modelMatrix, player->position);
		gfc_matrix_rotate(player->modelMatrix, player->modelMatrix, 2.35619, vector3d(0, 0, 1));
		player->DIRECTION = BackLeft;
	}
	if (keys[SDL_SCANCODE_S] && keys[SDL_SCANCODE_D])
	{
		//slog("Holding both");
		gfc_matrix_make_translation(player->modelMatrix, player->position);
		gfc_matrix_rotate(player->modelMatrix, player->modelMatrix, -2.35619, vector3d(0, 0, 1));
		player->DIRECTION = BackRight;
	}


	/*if (SDL_GetTicks() <= 1000)
	{
		slog("%d", SDL_GetTicks());
	}
*/


	//if (keys[SDL_SCANCODE_P])
	//{
	//	if (SDL_GetTicks() == 0 || SDL_GetTicks() % 1000 == 0)
	//	{
	//		slog("%f", player->position.x);
	//		slog("%f", player->position.y);
	//		slog("%f", player->position.z);
	//		create_projectile2(player);
	//	}

	//}


	if (keys[SDL_SCANCODE_1])
	{
		CooldownCheck(1000, 0);
		if (player->mana > 5 && canCast == 1)
		{
			//fire projectile 
			slog("%d", SDL_GetTicks());
			create_projectile(player);
			canCast == 0;
			slog("I casted");
		}
	}
	

	if (keys[SDL_SCANCODE_2])
	{
		CooldownCheck(5000, 1);
		if (player->mana > 15 && canCast == 1 )
		{
				//fire projectile 
				create_projectile2(player);
				player->mana -= 15;	

				slog("ATTACK 2");
				slog("%d", player->mana);	
				canCast == 0;
		}
		else{
			slog("Spell on cooldown!");
		}
	}


	if (keys[SDL_SCANCODE_3])
	{
		CooldownCheck(5000, 2);
		if (player->mana > 50 && canCast == 1)
		{
			player->mana -= 20;
			create_projectile3(player);
			canCast == 0;
			slog("SOMETHING");

		}
		else{
			slog("Spell on cooldown!");
		}
	}


	if (keys[SDL_SCANCODE_4])
	{
		CooldownCheck(1000, 3 );
		if (player->mana > 20 && canCast == 1)
		{
				player->mana -= 20;

				player->movespeed *= 1.5;

				slog("HASTE");
				canCast == 0;
		}
		else{
			slog("Spell on cooldown!");
		}
	}


	if (keys[SDL_SCANCODE_5])
	{
		CooldownCheck(15000, 4);
		if (player->mana > 50 && canCast == 1)
		{
				player->mana -= 50;

				player->health = 100;

				slog("HEAL");
				canCast == 0;
				slog("%i", player->health);

		}
		else{
			slog("Spell on cooldown!");
		}
	}

	if (keys[SDL_SCANCODE_M])
	{
		player->health = 1;
	}

	if (player->invincible == 1)
	{
		player->health = 100;
	}

	ManaRegen(player);

	if (player->health <= 0)
	{
		player_delete();
	}
	
}


void ManaRegen(Entity *self)
{
	if (!self)return;
	if (SDL_GetTicks() % 5000 == 0 && self->mana <= 95)
	{
		self->mana += 5;
		slog("MANA REGEND");
		slog("%d", player->mana);
	}
}

void CooldownCheck(int time, int x)
{
	CD = SDL_GetTicks();
	if ((CD - lastCast[x] > time) || lastCast[x] == 0)
	{
		canCast = 1;
		lastCast[x] = SDL_GetTicks();
	}
	else{
		canCast = 0;
	}
}

void CheckBounds()
{
	if (player->position.x >= 95 && player->position.x <= 100 || player->position.x <= -95 && player->position.x >= -100 )
	{
		player->movespeed = 0.005;
	}
	else{
		player->movespeed = 0.03;
	}

}

void player_delete()
{
	if (!player)return;
	gf3d_entity_free(player);
	slog("Game Over");
	
}

