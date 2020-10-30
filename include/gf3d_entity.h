#ifndef __GF3D_ENTITY_H__
#define __GF3D_ENTITY_H__

#include "gfc_types.h"
#include "gfc_vector.h"
#include "simple_logger.h"
#include "gf3d_model.h"
#include "gfc_matrix.h"

/**
* @purpose this is the file to acces the entity management system
*/


typedef struct Entity_S
{
	Uint8			_inuse;   /**<flag to make sure entities are not re-assigned while active*/
	Model			*model;
	Matrix4			modelMatrix;
	Vector3D		position; 
	Vector3D		velocity;
	Vector3D		scale;
	Vector3D		rotation;
	int				health;
	int				mana;
	int				experience;

	//ItemData		*itemdata; // NULL if not Item
	//MonsterData	*monsterdata; // NULL if not a monster
	//ClientData	*clientdata;  // NULL if not a player

	void(*think)(struct Entity_S *self);
} Entity;

/**
*@brief initializes the internal structures for managing the entity system
*@param maxEntities this will be the maximum number of concurrent entities that will be supported
**/
void gf3d_entity_init(Uint32 maxEntities);

/**
*@brief search for an empty entity slot and return a pointer to the blank entity
*@param NULL on error or a pointer to an entity otherwise
**/
Entity  *gf3d_entity_new();

/**
*@brief queues up the entity to be drawn for the given draw command
*@param self the entity to draw
*@param bufferFrame the renderFrame to draw with
*@param commandBuffer the command to populate with this draw command
**/
void gf3d_entity_draw(Entity *self, Uint32 bufferFrame, VkCommandBuffer commandBuffer);

/**
*@brief draw all active entities for a draw command
*@param bufferFrame the renderFrame to draw with
*@param commandBuffer the command to populate with this draw command
**/
void gf3d_entity_draw_all(Uint32 bufferFrame, VkCommandBuffer commandBuffer);

/**
*@brief free an entity so it can be reused by the system
*@param self the entity to free
*@note the pointer should be set to zero and no longer used.
**/
void gf3d_entity_free(Entity *entity);

void gf3d_entity_think_all();

void gf3d_entity_close(); 

#endif

