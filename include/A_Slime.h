#ifndef __A_SLIME_H__
#define __A_SLIME_H__

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

#endif