#include "gf3d_entity.h"
#include "A_Slime.h"

void a_slime_init(Slime *self)
{
	self->model = gf3d_model_load("Robot");
	self->Health = 100;
	//self->modelMatrix = 
}