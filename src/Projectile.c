#include "Projectile.h"
#include "simple_logger.h"

//Entity *proj; 

void projectile_think(Entity *self);

Entity *create_projectile(Entity *owner)
{
	Entity *proj;
	//When I create an projectile it needs to go in a certain direction, then disappear after a while.
	//I need to know who owns the projectile
	proj = gf3d_entity_new();
	proj->owner = owner;
	proj->model = gf3d_model_load("Sphere");
	proj->model->frameCount = 1;
	proj->radius = 2;
	proj->position.x = owner->position.x;
	proj->position.y = owner->position.y;
	proj->position.z = owner->position.z;
	proj->movespeed = 0.035;
	proj->EntityType = Projectile;
	proj->think = projectile_think;
	proj->DIRECTION = owner->DIRECTION;
	
	//I have an owner and I have a model, now I need to fire in a direction with a speed
	return proj;

}

Entity *create_projectile2(Entity *owner)
{
	Entity *proj;
	// This is the slow
	proj = gf3d_entity_new();
	proj->owner = owner;
	proj->model = gf3d_model_load("Sphere2");
	proj->model->frameCount = 1;
	proj->radius = 6;
	proj->position.x = owner->position.x;
	proj->position.y = owner->position.y;
	proj->position.z = owner->position.z;
	proj->movespeed = 0.045;
	proj->EntityType = Projectile2;
	proj->think = projectile_think;
	proj->DIRECTION = owner->DIRECTION;

	//I have an owner and I have a model, now I need to fire in a direction with a speed
	return proj;

}

Entity *create_projectile3(Entity *owner)
{
	Entity *proj;
	//This is the oneshot
	proj = gf3d_entity_new();
	proj->owner = owner;
	proj->model = gf3d_model_load("Sphere3");
	proj->model->frameCount = 1;
	proj->radius = 1;
	proj->position.x = owner->position.x;
	proj->position.y = owner->position.y;
	proj->position.z = owner->position.z;
	proj->movespeed = 0.095; //was .085
	proj->EntityType = Projectile3;
	proj->think = projectile_think;
	proj->DIRECTION = owner->DIRECTION;

	//I have an owner and I have a model, now I need to fire in a direction with a speed
	return proj;

}

Entity *Projectile_Knockback(Entity *owner)
{
	Entity *proj;
	//This is the oneshot
	proj = gf3d_entity_new();
	proj->owner = owner;
	proj->model = gf3d_model_load("Sphere6");
	proj->model->frameCount = 1;
	proj->radius = 5;
	proj->position.x = owner->position.x;
	proj->position.y = owner->position.y;
	proj->position.z = owner->position.z;
	proj->movespeed = 0.095; //was .085
	proj->EntityType = Knockback;
	proj->think = projectile_think;
	proj->DIRECTION = owner->DIRECTION;
	if (owner->EntityType == Player && owner->experience >= 150)
	{
		proj->Pushback = -40;
	}
	else{
		proj->Pushback = -20;
	}


	//I have an owner and I have a model, now I need to fire in a direction with a speed
	return proj;

}

Entity *Projectile_Poison(Entity *owner)
{
	Entity *proj;
	//This is the oneshot
	proj = gf3d_entity_new();
	proj->owner = owner;
	proj->model = gf3d_model_load("Sphere5");
	proj->model->frameCount = 1;
	proj->radius = 1;
	proj->position.x = owner->position.x;
	proj->position.y = owner->position.y;
	proj->position.z = owner->position.z;
	proj->movespeed = 0.095; //was .085

	if (proj->owner->EntityType == Player && proj->owner->experience >= 175)
	{
		proj->EntityType = PoisonSlow;
	}
	else{
		proj->EntityType = Poison;
	}
	
	proj->think = projectile_think;
	proj->DIRECTION = owner->DIRECTION;
	proj->Pushback = -20;

	//I have an owner and I have a model, now I need to fire in a direction with a speed
	return proj;

}

Entity *Projectile_Blind(Entity *owner)
{
	Entity *proj;
	//This is the oneshot
	proj = gf3d_entity_new();
	proj->owner = owner;
	proj->model = gf3d_model_load("Sphere4");
	proj->model->frameCount = 1;
	proj->radius = 1;
	proj->position.x = owner->position.x;
	proj->position.y = owner->position.y;
	proj->position.z = owner->position.z;
	proj->movespeed = 0.095; //was .085
	proj->EntityType = Blind;
	proj->think = projectile_think;
	proj->DIRECTION = owner->DIRECTION;
	//proj->Pushback = -20;

	//I have an owner and I have a model, now I need to fire in a direction with a speed
	return proj;

}

Entity *TurretFire(Entity *owner, int Direction)
{
	Entity *proj;
	//When I create an projectile it needs to go in a certain direction, then disappear after a while.
	//I need to know who owns the projectile
	proj = gf3d_entity_new();
	proj->owner = owner;
	proj->model = gf3d_model_load("Sphere");
	proj->model->frameCount = 1;
	proj->radius = 1;
	proj->position.x = owner->position.x;
	proj->position.y = owner->position.y + 2;
	proj->position.z = owner->position.z;
	proj->movespeed = 0.035;
	proj->EntityType = Projectile;
	proj->think = projectile_think;
	proj->DIRECTION = Direction;

	//I have an owner and I have a model, now I need to fire in a direction with a speed
	return proj;

}

Entity *TurretPoison(Entity *owner, int Direction)
{
	Entity *proj;
	//When I create an projectile it needs to go in a certain direction, then disappear after a while.
	//I need to know who owns the projectile
	proj = gf3d_entity_new();
	proj->owner = owner;
	proj->model = gf3d_model_load("Sphere6");
	proj->model->frameCount = 1;
	proj->radius = 1;
	proj->position.x = owner->position.x;
	proj->position.y = owner->position.y + 2;
	proj->position.z = owner->position.z;
	proj->movespeed = 0.035;
	proj->EntityType = Poison;
	proj->think = projectile_think;
	proj->DIRECTION = Direction;

	//I have an owner and I have a model, now I need to fire in a direction with a speed
	return proj;

}

Entity *TurretBlind(Entity *owner, int Direction)
{
	Entity *proj;
	//When I create an projectile it needs to go in a certain direction, then disappear after a while.
	//I need to know who owns the projectile
	proj = gf3d_entity_new();
	proj->owner = owner;
	proj->model = gf3d_model_load("Sphere7");
	proj->model->frameCount = 1;
	proj->radius = 1;
	proj->position.x = owner->position.x;
	proj->position.y = owner->position.y + 2;
	proj->position.z = owner->position.z;
	proj->movespeed = 0.035;
	proj->EntityType = Blind;
	proj->think = projectile_think;
	proj->DIRECTION = Direction;

	//I have an owner and I have a model, now I need to fire in a direction with a speed
	return proj;

}



void projectile_think(Entity *self)
{
	
	if (!self)return;
	if (self->owner == 0)return; // If I don't have an owner than i cannot think rn

	if (self->position.x >= 100 || self->position.y >= 100 || self->position.x <= -100 || self->position.y <= -100 )
	{
		//slog("I have died");
		gf3d_entity_free(self);
	}

	switch (self->DIRECTION)
	{
		case Forward:
			self->position.y -= self->movespeed;
			break;
		case ForwardLeft:
			self->position.y -= self->movespeed;
			self->position.x += self->movespeed;
			break;
		case ForwardRight:
			self->position.y -= self->movespeed;
			self->position.x -= self->movespeed;
			break;
		case Left: 
			self->position.x += self->movespeed;
			break;
		case BackLeft:
			self->position.y += self->movespeed;
			self->position.x += self->movespeed;
			break;
		case Back:
			self->position.y += self->movespeed;
			break;
		case BackRight: 
			self->position.y += self->movespeed;
			self->position.x -= self->movespeed;
			break;
		case Right:
			self->position.x -= self->movespeed;
			break;

	}
	


	
	gfc_matrix_make_translation(self->modelMatrix, self->position);
	

}