


#include "gf3d_entity.h"


typedef struct
{
    Entity *entity_list; /*Big List of Entities*/
    Uint32 entity_count; /*Upper Limit for active entities*/
}EntityManager;

static EntityManager gf3d_entity = {0};

void gf3d_entity_free(Entity *entity);

void gf3d_entity_close()
{
	int i;
	if (gf3d_entity.entity_list != NULL)
	{
		for (i = 0; i < gf3d_entity.entity_count; i++)
		{
			gf3d_entity_free(&gf3d_entity.entity_list[i]);
		}
		free(gf3d_entity.entity_list);
	}
	memset(&gf3d_entity, 0, sizeof(EntityManager));
	slog("Entity System Closed");
}

void gf3d_entity_init(Uint32 maxEntities)
{
	if (gf3d_entity.entity_list != NULL)
	{
		slog("Warning: entity system already initialized");
		return;
	}
	gf3d_entity.entity_list = gfc_allocate_array(sizeof(Entity), maxEntities);
	if (!gf3d_entity.entity_list)
	{
		slog("Failed to allocate entity list");
		return;
	}
	gf3d_entity.entity_count = maxEntities;
	atexit(gf3d_entity_close);
	slog("Entity System Initialized");
}

void gf3d_entity_free(Entity *entity)
{
	if (!entity)return;
	slog("Entity Freed");
	gf3d_model_free(entity->model);
	memset(entity, 0, sizeof(Entity));
}

Entity *gf3d_entity_new()
{
    int i;
	for (i = 0; i < gf3d_entity.entity_count; i++)
	{
		if (!gf3d_entity.entity_list[i]._inuse)
		{
			gf3d_entity.entity_list[i]._inuse = 1;
			gfc_matrix_identity(gf3d_entity.entity_list[i].modelMatrix);
			return &gf3d_entity.entity_list[i];
		}
	}
	slog("Failed to provide new entity, no unused slots");
	return NULL;
}

void gf3d_entity_think(Entity *self)
{
	if (!self)return;
	if (!self->think)return; //no think function to call
	self->think(self);

}

//gfc_word_cpy, use TextWord for strings
//Most work will be done here

void gf3d_entity_think_all()
{
	int i;
	for (i = 0; i < gf3d_entity.entity_count; i++)
	{
		if (!gf3d_entity.entity_list[i]._inuse)continue;
		gf3d_entity_think(&gf3d_entity.entity_list[i]);

		int b;
		for (b = 0; b < gf3d_entity.entity_count; b++)
		{
			if (&gf3d_entity.entity_list[b] == &gf3d_entity.entity_list[i])continue;

			if (!&gf3d_entity.entity_list[b] || !&gf3d_entity.entity_list[i])
			{
				slog("Nope nothing here");
			}

		//	B IS THE OBJECT BEING HIT
			if (checkCollision(&gf3d_entity.entity_list[b], &gf3d_entity.entity_list[i]) == 1)
			{		
				//slog("%d", gf3d_entity.entity_list[i].EntityType);
				
				if (&gf3d_entity.entity_list[b] == gf3d_entity.entity_list[i].owner)
				{
					//Works
					//slog("Colliding with parent");
					continue;
				}

				//Case for Damage attack hitting slow Attack
				if (gf3d_entity.entity_list[i].EntityType == Projectile && gf3d_entity.entity_list[b].EntityType == Projectile2)
				{
					gf3d_entity_free(&gf3d_entity.entity_list[b]);
					gf3d_entity_free(&gf3d_entity.entity_list[i]);
				}

				//Case For Player being damaged by slime
				if (gf3d_entity.entity_list[i].EntityType == Mob1 && gf3d_entity.entity_list[b].EntityType == Player )
				{
					if (SDL_GetTicks() % 1000 == 0)
					{
						slog("DAMAGE");
						gf3d_entity.entity_list[b].health -= 2;
					}
				}

				//Case For DinoG healing allies
				if (gf3d_entity.entity_list[i].EntityType == Mob4 && (gf3d_entity.entity_list[b].EntityType == Mob1 || gf3d_entity.entity_list[b].EntityType == Mob2 || gf3d_entity.entity_list[b].EntityType == Mob3 || gf3d_entity.entity_list[b].EntityType == Mob5))
				{
					if (SDL_GetTicks() % 1000 == 0)
					{
						slog("Healed");
						gf3d_entity.entity_list[b].health += 10;
						gf3d_entity_free(&gf3d_entity.entity_list[i]);
					}
				}

				//Case For picking up
				if (gf3d_entity.entity_list[i].EntityType == Player && gf3d_entity.entity_list[b].EntityType == Pickup)
				{
					if (SDL_GetTicks() % 100 == 0)
					{
						switch (gf3d_entity.entity_list[b].ItemType)
						{
						case Health:
							gf3d_entity.entity_list[i].health += 10;
							slog("Health obtained");
							break;
						case Invincible:
							gf3d_entity.entity_list[b].invincible = 1;
							slog("Invincible");
							break;
						case SpeedBoost: 
							gf3d_entity.entity_list[b].movespeed += 0.005;
							slog("Speed");
							break;
						case Mana:
							gf3d_entity.entity_list[b].mana += 50;
							slog("Mana");
							break;
						case Spell:
							gf3d_entity.entity_list[b].radius = 10; 
							slog("Big boy");
							break;
						}
						slog("Yummy item");
						
						//gf3d_entity.entity_list[i].target = 0;
						gf3d_entity_free(&gf3d_entity.entity_list[b]);
					}
				}

				//Case For DinoR stealing pickups
				if (gf3d_entity.entity_list[i].EntityType == Mob5 && gf3d_entity.entity_list[b].EntityType == Pickup)
				{
					if (SDL_GetTicks() % 1000 == 0)
					{
						slog("Yummy item");
						gf3d_entity.entity_list[i].health += 10;
						gf3d_entity.entity_list[i].target = 0;
						gf3d_entity_free(&gf3d_entity.entity_list[b]);
					}
				}

				//Case For Player being damaged by DinoW
				if (gf3d_entity.entity_list[i].EntityType == Mob2 && gf3d_entity.entity_list[b].EntityType == Player)
				{
					if (SDL_GetTicks() % 1000 == 0)
					{
						gf3d_entity.entity_list[b].mana -= 15;
						gf3d_entity_free(&gf3d_entity.entity_list[i]);
					}
				}

				//Case For Player being damaged by DinoP
				if (gf3d_entity.entity_list[i].EntityType == Mob3 && gf3d_entity.entity_list[b].EntityType == Player)
				{
					if (SDL_GetTicks() % 1000 == 0)
					{
						slog("DAMAGE");
						gf3d_entity.entity_list[b].health -= 2;
					}
				}

				//Case for being hit by projectile and freeing projectile on hit
				if (gf3d_entity.entity_list[i].EntityType == Projectile)
				{
					//Works
					slog("Hit by a projectile");
					//Now take damage
						gf3d_entity.entity_list[b].health -= 5;
	
					slog("%d", gf3d_entity.entity_list[b].health);
					gf3d_entity_free(&gf3d_entity.entity_list[i]);
				}

				//This is the player Slow Attack
				if (gf3d_entity.entity_list[i].EntityType == Projectile2)
				{
					//Works
					slog("Hit by a slow");
					//Now take damage
					gf3d_entity.entity_list[b].movespeed /= 2;

					slog("%d", gf3d_entity.entity_list[b].health);
					gf3d_entity_free(&gf3d_entity.entity_list[i]);
				}

				//This is the Player 1 Shot Attack
				if (gf3d_entity.entity_list[i].EntityType == Projectile3)
				{
					//Works
					slog("Hit by a projectile");
					//Now take damage
					gf3d_entity_free(&gf3d_entity.entity_list[b]);
					gf3d_entity_free(&gf3d_entity.entity_list[i]);
				}
				
				

			
			}

			if (checkEnemies(&gf3d_entity.entity_list[b], &gf3d_entity.entity_list[i]) == 1)
			{
				//slog("Found player");
			}
			if (checkEnemies2(&gf3d_entity.entity_list[b], &gf3d_entity.entity_list[i]) == 1)
			{
				//slog("Found player");
			}
			if (checkPickup(&gf3d_entity.entity_list[b], &gf3d_entity.entity_list[i]) == 1)
			{
				//slog("Found player");
			}
		}
	}
}


void gf3d_entity_draw(Entity *self, Uint32 bufferFrame, VkCommandBuffer commandBuffer)
{
	if (!self) return;

	gf3d_model_draw(self->model, bufferFrame, commandBuffer, self->modelMatrix);

}

void gf3d_entity_draw_all(Uint32 bufferFrame, VkCommandBuffer commandBuffer)
{
	int i;
	for (i = 0; i < gf3d_entity.entity_count; i++)
	{
		if (!gf3d_entity.entity_list[i]._inuse)continue;
		gf3d_entity_draw(&gf3d_entity.entity_list[i], bufferFrame, commandBuffer);
	}
}

int checkCollision(Entity *self, Entity *other)
{
	float distance_x = self->position.x - other->position.x;
	float distance_y = self->position.y - other->position.y;
	float distance_z = self->position.z - other->position.z;

	if (self->radius == 0 || other->radius == 0) return 0;
	//slog("%f, %f", self->radius, other->radius);

	float radii_sum = self->radius + other->radius;
	

	//slog("Check collision");
	if ((distance_x * distance_x) + (distance_y * distance_y) + (distance_z * distance_z) <= (radii_sum * radii_sum)) return 1;



	return 0;
}

int checkEnemies(Entity *self, Entity *other)
{
	if (self->EntityType == Mob4)return 0;
	if (other->EntityType != Player)return 0;
	int EnemyFound = 0;
	float distance_x = self->position.x - other->position.x;
	float distance_y = self->position.y - other->position.y;
	float distance_z = self->position.z - other->position.z;

	if (self->radius == 0 || other->radius == 0) return 0;
	//slog("%f, %f", self->radius, other->radius);

	float rangesum = self->range + other->radius;

	//slog("Check collision");
	if ((distance_x * distance_x) + (distance_y * distance_y) + (distance_z * distance_z) <= (rangesum * rangesum) && other->EntityType == Player)
	{
		//ENEMY CHASER
		self->target = other;
		return 1;
	}

	return 0;
}

int checkEnemies2(Entity *self, Entity *other)
{
	if (self->EntityType != Mob4)return 0;
	if (other->EntityType != Mob1 && other->EntityType != Mob2 && other->EntityType != Mob3 && other->EntityType != Mob5)return 0;
	if (self->target != 0)return 0;
	int EnemyFound = 0;
	float distance_x = self->position.x - other->position.x;
	float distance_y = self->position.y - other->position.y;
	float distance_z = self->position.z - other->position.z;

	if (self->radius == 0 || other->radius == 0) return 0;
	//slog("%f, %f", self->radius, other->radius);

	float rangesum = self->range + other->radius;

	//slog("Check collision");
	if ((distance_x * distance_x) + (distance_y * distance_y) + (distance_z * distance_z) <= (rangesum * rangesum) && (other->EntityType == Mob1 || other->EntityType == Mob2 || other->EntityType == Mob3 || other->EntityType == Mob5))
	{
		//ENEMY CHASER
		self->target = other;
		return 1;
	}

	return 0;
}

int checkPickup(Entity *self, Entity *other)
{
	if (self->EntityType != Mob5)return 0;
	if (other->EntityType != Pickup)return 0;
	if (self->target != 0)return 0;
	int EnemyFound = 0;
	float distance_x = self->position.x - other->position.x;
	float distance_y = self->position.y - other->position.y;
	float distance_z = self->position.z - other->position.z;

	if (self->radius == 0 || other->radius == 0) return 0;
	//slog("%f, %f", self->radius, other->radius);

	float rangesum = self->range + other->radius;

	//slog("Check collision");
	if ((distance_x * distance_x) + (distance_y * distance_y) + (distance_z * distance_z) <= (rangesum * rangesum) && other->EntityType == Pickup)
	{
		//ENEMY CHASER
		slog("Pickup found");
		self->target = other;
		return 1;
	}

	return 0;
}

void gf3d_entity_follow(Entity *target, Entity *self)
{
	//Vector3D Destination = target->position;
	if (self->position.y >= target->position.y && self->position.y >= -100)
	{
		self->DIRECTION = Forward; 
		self->position.y -= self->movespeed;
		gfc_matrix_make_translation(self->modelMatrix, self->position);
		
	}
	if (self->position.y <= target->position.y && self->position.y <= 100)
	{
		self->DIRECTION = Back;
		self->position.y += self->movespeed;
		gfc_matrix_make_translation(self->modelMatrix, self->position);
		
	}
	if (self->position.x >= target->position.x && self->position.x <= 100)
	{
		self->position.x -= self->movespeed;
		self->DIRECTION = Right; 
		gfc_matrix_make_translation(self->modelMatrix, self->position);
		
	}
	if (self->position.x <= target->position.x && self->position.x >= -100)
	{
		self->DIRECTION = Left; 
		self->position.x += self->movespeed;
		gfc_matrix_make_translation(self->modelMatrix, self->position);
		
	}



	
	/*if (self->position.y < target->position.y && self->position.x > target->position.x)
	{
		self->DIRECTION = BackRight;
	}
	else if (self->position.y < target->position.y && self->position.x < target->position.x)
	{
		self->DIRECTION = BackLeft;
	}
	else if (self->position.y > target->position.y && self->position.x > target->position.x)
	{
		self->DIRECTION = ForwardRight;
	}
	else if (self->position.y > target->position.y && self->position.x < target->position.x)
	{
		self->DIRECTION = ForwardLeft;
	}*/
	/*if (self->position.y < target->position.y && self->position.x == target->position.x)
	{
		slog("Forward");
		self->DIRECTION = Forward; 
	}
	
	if (self->position.y > target->position.y && self->position.x == target->position.x)
	{
		slog("Back");
		self->DIRECTION = Back;
	}*/


}

/*eolf@eof*/
