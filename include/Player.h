#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "gf3d_entity.h"

typedef struct
{
	char *modelName;
	int heatlh;
}PlayerData;

Entity *player_spawn(Vector3D position, const char *modelName, int PlayerType, int hp, int mana);

void Overhealing(Entity *self);

#endif // !__Player_H__
