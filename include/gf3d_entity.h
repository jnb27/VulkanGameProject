#ifndef __GF3D_ENTITY_H__
#define __GF3D_ENTITY_H__

#include "gfc_types.h"
#include "gfc_vector.h"

#include "gf3d_model.h"

/**
* @purpose this is the file to acces the entity management system
*/

typedef struct Entity_S
{
    Uint8 _inuse;
    Vector3D position;
    Model *model;
    void (*think)(struct Entity_S *self);
}Entity;


#endif

