#ifndef __A_SLIME_H__
#define __A_SLIME_H__

#include "gfc_types.h"
#include "gfc_vector.h"
#include "simple_logger.h"
#include "gf3d_model.h"
#include "gfc_matrix.h"
#include "gf3d_entity.h"

/*
@purpose this file is to start making a basic enemy 
*/

typedef struct Slime_S
{
	Uint8 _inuse; //Check to make sure it's not rewritten
	Model *model;
	Matrix4 modelMatrix;
	int Health;
	void(*think)(struct Slime_S *self);
} Slime;

/*
*@brief a void to initialize basic variables of any slime, hp, model and etc
*@param a pointer to itself
*/
void a_slime_init(Slime *self);


#endif