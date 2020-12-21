#ifndef __DINOR_H__
#define __DINOR_H__

#include "gfc_types.h"
#include "gfc_vector.h"
#include "simple_logger.h"
#include "gf3d_model.h"
#include "gfc_matrix.h"
#include "gf3d_entity.h"

/*
@purpose this file is to start making a basic enemy
*/


/*
*@brief a void to initialize basic variables of any slime, hp, model and etc
*@param a pointer to itself
*/
Entity *DinoRSpawn(int level);


void DinoR_think();


#endif