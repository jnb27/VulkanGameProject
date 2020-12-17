#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__

#include "gfc_types.h"
#include "gfc_vector.h"
#include "simple_logger.h"
#include "gf3d_model.h"
#include "gfc_matrix.h"
#include "gf3d_entity.h"

/*What does a projectile need to know?
	1. Who owns me
	2. Who I touch
	3. Which way I'm going and how far I should go
	4. 
	



*/
Entity *create_projectile(Entity *owner, Entity *self);
Entity *create_projectile2(Entity *owner, Entity *self);
Entity *create_projectile3(Entity *owner, Entity *self);

void update();

#endif