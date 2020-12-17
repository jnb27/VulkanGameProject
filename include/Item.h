#ifndef __ITEM_H__
#define __ITEM_H__

#include "gfc_types.h"
#include "gfc_vector.h"
#include "simple_logger.h"
#include "gf3d_model.h"
#include "gfc_matrix.h"
#include "gf3d_entity.h"


//Raise max mana
//Heal
//Increase Speed
//Invincible

void ItemThink();

Entity *ItemDropSpell();

Entity *ItemDropMana();

Entity *ItemDropSPD();

Entity *ItemDropIN();

Entity *ItemDropHP();

#endif // !__Item_H__