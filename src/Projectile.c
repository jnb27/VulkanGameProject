#include "Projectile.h"
#include "simple_logger.h"

Entity *proj; 

void projectile_think(Entity *self);

Entity *create_projectile(Entity *owner)
{
	//When I create an projectile it needs to go in a certain direction, then disappear after a while.
	//I need to know who owns the projectile
	proj = gf3d_entity_new();
	proj->owner = owner;
	proj->model = gf3d_model_load("dino");
	proj->movespeed = 0.001;
	proj->think = projectile_think;
	
	//I have an owner and I have a model, now I need to fire in a direction with a speed


}

void projectile_think(Entity *self)
{
	if (!self)return;
	if (proj->owner == NULL)return; // If I don't have an owner than i cannot think rn
	slog("I'm thonkin");
	self->position.x += proj->movespeed;
	self->position.y += proj->movespeed;
	gfc_matrix_make_translation(self->modelMatrix, self->position);
}