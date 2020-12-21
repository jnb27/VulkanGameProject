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
Entity *TurretDMG(Entity *owner);
Entity *TurretBlindy(Entity *owner);
Entity *TurretPoisony(Entity *owner);
void TurretD_think(Entity *TurretD);
void TurretP_think(Entity *TurretP);
void TurretB_think(Entity *TurretB);

Entity *player;
int fired = 0;
int canCast = 0;
int lastCast[5] = { 0 };
Uint32 CD;
Entity *shots[11] = { 0 };

const Uint8 *keys;

//Original Map Bounds 100 in any direction.

int ForwardMax = -200;
int BackMax  = 200; 
int LeftMax = 200;
int RightMax = -200; 
int Overheal = 0; 


Entity *player_spawn(Vector3D position, const char *modelName, int PlayerType, int hp, int mana)
{
	
	player = gf3d_entity_new();
	player->health = hp;
	player->mana = mana;
	player->radius = 5;
	player->position = position;
	player->experience = 400;
	player->invincible = 0;
	player->EntityType = Player;
	player->PlayerType = PlayerType; 
	player->Pushback = 25;
	
	slog("%f", player->radius);
	if (!player)
	{
		slog("failed to spawn a new player enttity");
		return NULL;
	}

	//Probably make model load change based on player 
	player->model = gf3d_model_load(modelName);
	player->model->frameCount = 1;
	vector3d_copy(player->position, position);
	player->think = player_think;
	player->movespeed = 0.03;
	return player;
}

void player_think()
{
	keys = SDL_GetKeyboardState(NULL);
	
	CheckBounds();

	if (keys[SDL_SCANCODE_W])
	{
		if (player->position.y >= ForwardMax)
		{
			//CheckBounds();
			player->position.y -= player->movespeed;
			gfc_matrix_make_translation(player->modelMatrix, player->position);
			gfc_matrix_rotate(player->modelMatrix, player->modelMatrix, 6.28319, vector3d(0, 0, 1));
			player->DIRECTION = Forward;
		}

		//slog("%i", player->health);
	}
	if (keys[SDL_SCANCODE_S])
	{	
		if (player->position.y <= BackMax)
		{
			//CheckBounds();
			player->position.y += player->movespeed;
			gfc_matrix_make_translation(player->modelMatrix, player->position);
			gfc_matrix_rotate(player->modelMatrix, player->modelMatrix, 3.14159, vector3d(0, 0, 1));
			player->DIRECTION = Back;
		}
		
	}
	if (keys[SDL_SCANCODE_A])
	{
		if (player->position.x <= LeftMax)
		{
			//CheckBounds();
			player->position.x += player->movespeed;
			gfc_matrix_make_translation(player->modelMatrix, player->position);
			gfc_matrix_rotate(player->modelMatrix, player->modelMatrix, 1.5708, vector3d(0, 0, 1));
			player->DIRECTION = Left;
		}

		
	}
	if (keys[SDL_SCANCODE_D])
	{
		if (player->position.x >= RightMax)
		{
		//CheckBounds();
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



	if (keys[SDL_SCANCODE_1] /*&& player->PlayerType == 1*/)
	{

		if (player->experience >= 150)
		{
			CooldownCheck(250, 1);
		}
		else{
			CooldownCheck(500, 1);
		}


		if (player->mana > 5 && canCast == 1)
		{
			//fire projectile 
			slog("%d", SDL_GetTicks());
			if (player->PlayerType == 1)
			{
				create_projectile(player);    /*Default Projectile*/
			}

			if (player->PlayerType == 2)
			{
				Projectile_Poison(player);
			}

			if (player->PlayerType == 3)
			{
				TurretDMG(player);
			}
			


			//Projectile_Knockback(player); /*Knockback Projectile*/


			canCast = 0;
			slog("I casted");
		}

	}



	//if (keys[SDL_SCANCODE_1] && player->PlayerType == 2)
	//{

	//}
	

	if (keys[SDL_SCANCODE_2])
	{
		if (player->experience >= 150)
		{
			CooldownCheck(2500, 1);
		}
		else{
			CooldownCheck(5000, 1);
		}
		
		if (player->mana > 15 && canCast == 1 )
		{
				//fire projectile 
			if (player->PlayerType == 1)
			{
				create_projectile2(player);
				player->mana -= 15;	
			}

			if (player->PlayerType == 2)
			{
				Projectile_Blind(player);
			}

			if (player->PlayerType == 3)
			{
				TurretPoisony(player);
			}
				canCast = 0;
		}
		else{
			slog("Spell on cooldown!");
		}
	}


	if (keys[SDL_SCANCODE_3])
	{
		
		if (player->experience >= 150)
		{
			CooldownCheck(500, 1);
		}
		else{
			CooldownCheck(1000, 1);
		}
		
		if (player->mana > 50 && canCast == 1)
		{
			if (player->PlayerType == 1)
			{
				create_projectile3(player);
			}

			if (player->PlayerType == 2)
			{
				Projectile_Knockback(player); /*Knockback Projectile*/
			}

			if (player->PlayerType == 3)
			{
				TurretBlindy(player);
			}

			canCast = 0;
			slog("SOMETHING");

		}
		else{
			slog("Spell on cooldown!");
		}
	}


	if (keys[SDL_SCANCODE_4])
	{

		if (player->experience >= 150)
		{
			CooldownCheck(500, 1);
		}
		else{
			CooldownCheck(1000, 1);
		}

		if (player->mana > 20 && canCast == 1)
		{
				player->mana -= 20;

				player->movespeed *= 1.5;

				slog("HASTE");
				canCast = 0;
		}
		else{
			slog("Spell on cooldown!");
		}
	}


	if (keys[SDL_SCANCODE_5])
	{
		if (player->experience >= 150)
		{
			CooldownCheck(7500, 1);
		}
		else{
			CooldownCheck(15000, 1);
		}

		if (player->mana > 50 && canCast == 1)
		{
				player->mana -= 50;

				player->health = 100;

				slog("HEAL");
				canCast = 0;
				slog("%i", player->health);

		}
		else{
			slog("Spell on cooldown!");
		}
	}

	if (keys[SDL_SCANCODE_M])
	{
		player->health = 1;



		//slog("%f", player->radius);
		slog("%f", player->position.x); //x >= 70
		slog("%f", player->position.y); //y >= 42
		slog("%f", player->position.z);
	}

	if (player->invincible == 1)
	{
		player->health = 100;
	}

	if (player->experience >= 300)
	{
		player->radius = 5;
	}

	if (player->Slayed >= 15)
	{
		Overheal = 1;
	}


	ManaRegen(player);
	Overhealing(player);

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

void Overhealing(Entity *self)
{
	if (!self)return;
	if (SDL_GetTicks() % 5000 == 0 && Overheal == 1)
	{
		self->health += 5;
		slog("Autoheal");
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
	/*if (player->position.x >= 95 && player->position.x <= 100 || player->position.x <= -95 && player->position.x >= -100 )
	{
		player->movespeed = 0.005;
	}
	else{
		player->movespeed = 0.03;
	}*/

	if (player->position.x >= 70 && player->position.y >= 42)
	{
		player->position.z = 6;
	}
	else
	{
		player->position.z = 0;
	}

	//Map1 special effects 
	if ((player->position.x >= -84.0 && player->position.y <= -50.0) && (player->position.x <= -43 && player->position.y >= -89.0))
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
}

void player_delete()
{
	if (!player)return;
	gf3d_entity_free(player);
	slog("Game Over");
	
}

Entity *TurretDMG(Entity *owner)
{
	Entity *TurretD;
	TurretD = gf3d_entity_new();
	int level = (owner->experience / 4);
	//make sure to properly use entity system w/ gf3d_entity_new
	if (!TurretD)
	{
		slog("failed to spawn a new TurretD enttity");
		return NULL;
	}

	TurretD->model = gf3d_model_load("TurretDMG");
	TurretD->model->frameCount = 1;
	TurretD->health = 30 * level;
	TurretD->movespeed = 0.0075;
	TurretD->radius = 1;
	TurretD->EntityType = PlayerTurretDMG;
	TurretD->range = 20;
	TurretD->target = 0;
	TurretD->position.x = owner->position.x + 10;
	TurretD->position.y = owner->position.y + 10;
	TurretD->position.z = owner->position.z;
	TurretD->think = TurretD_think;
	gfc_matrix_make_translation(TurretD->modelMatrix, TurretD->position);

	slog("TurretD was spawned");

	return TurretD;

}

Entity *TurretPoisony(Entity *owner)
{
	Entity *TurretD;
	TurretD = gf3d_entity_new();
	int level = (owner->experience / 4);
	//make sure to properly use entity system w/ gf3d_entity_new
	if (!TurretD)
	{
		slog("failed to spawn a new TurretD enttity");
		return NULL;
	}

	TurretD->model = gf3d_model_load("TurretP");
	TurretD->model->frameCount = 1;
	TurretD->health = 30 * level;
	TurretD->movespeed = 0.0075;
	TurretD->radius = 1;
	TurretD->EntityType = PlayerTurretDMG;
	TurretD->range = 20;
	TurretD->target = 0;
	TurretD->position.x = owner->position.x + 10;
	TurretD->position.y = owner->position.y + 10;
	TurretD->position.z = owner->position.z;
	TurretD->think = TurretP_think;
	gfc_matrix_make_translation(TurretD->modelMatrix, TurretD->position);

	slog("TurretD was spawned");

	return TurretD;

}

Entity *TurretBlindy(Entity *owner)
{
	Entity *TurretD;
	TurretD = gf3d_entity_new();
	int level = (owner->experience / 4);
	//make sure to properly use entity system w/ gf3d_entity_new
	if (!TurretD)
	{
		slog("failed to spawn a new TurretD enttity");
		return NULL;
	}

	TurretD->model = gf3d_model_load("TurretB");
	TurretD->model->frameCount = 1;
	TurretD->health = 30 * level;
	TurretD->movespeed = 0.0075;
	TurretD->radius = 1;
	TurretD->EntityType = PlayerTurretDMG;
	TurretD->range = 20;
	TurretD->target = 0;
	TurretD->position.x = owner->position.x + 10;
	TurretD->position.y = owner->position.y + 10;
	TurretD->position.z = owner->position.z;
	TurretD->think = TurretB_think;
	gfc_matrix_make_translation(TurretD->modelMatrix, TurretD->position);

	slog("TurretD was spawned");

	return TurretD;

}

void TurretD_think(Entity *TurretD)
{
	if (!TurretD)return;


	if (TurretD->isPoisoned)
	{
		if (SDL_GetTicks() % 1000 == 0)
		{
			TurretD->health -= 1;
			TurretD->PoisonTaken++;
			slog("%d", TurretD->health);
			slog("Poison Tick");

		}

		if (TurretD->PoisonTaken == 15)
		{
			TurretD->isPoisoned = 0;
			TurretD->PoisonTaken = 0;
		}
	}

		if (SDL_GetTicks() == 0 || SDL_GetTicks() % 1000 == 0)
		{
			//fire projectile 
			TurretFire(TurretD, player->DIRECTION);
		}

	if (TurretD->health <= 0)
	{
		gf3d_entity_free(TurretD);
	}

}

void TurretP_think(Entity *TurretP)
{
	if (!TurretP)return;


	if (TurretP->isPoisoned)
	{
		if (SDL_GetTicks() % 1000 == 0)
		{
			TurretP->health -= 1;
			TurretP->PoisonTaken++;
			slog("%d", TurretP->health);
			slog("Poison Tick");

		}

		if (TurretP->PoisonTaken == 15)
		{
			TurretP->isPoisoned = 0;
			TurretP->PoisonTaken = 0;
		}
	}

	if (SDL_GetTicks() == 0 || SDL_GetTicks() % 1000 == 0)
	{
		//fire projectile 
		TurretPoison(TurretP, player->DIRECTION);
	}

	if (TurretP->health <= 0)
	{
		gf3d_entity_free(TurretP);
	}

}

void TurretB_think(Entity *TurretB)
{
	if (!TurretB)return;

	if (TurretB->isPoisoned)
	{
		if (SDL_GetTicks() % 1000 == 0)
		{
			TurretB->health -= 1;
			TurretB->PoisonTaken++;
			slog("%d", TurretB->health);
			slog("Poison Tick");

		}

		if (TurretB->PoisonTaken == 15)
		{
			TurretB->isPoisoned = 0;
			TurretB->PoisonTaken = 0;
		}
	}

	if (SDL_GetTicks() == 0 || SDL_GetTicks() % 1000 == 0)
	{
		//fire projectile 
		TurretBlind(TurretB, player->DIRECTION);
	}

	if (TurretB->health <= 0)
	{
		gf3d_entity_free(TurretB);
	}

}