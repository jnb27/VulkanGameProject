#include "gf3d_entity.h"
#include "Item.h"

Entity *Item;

Entity *ItemDropHP()
{

	if (!Item)
	{
		slog("Shid broke yo");
	}
	Item = gf3d_entity_new();
	Item->radius = 5.0;
	Item->ItemType = Health;
	Item->EntityType = Pickup;
	Item->model = gf3d_model_load("Sphere5");
	Item->position = vector3d(50, 50, 0); 
	gfc_matrix_make_translation(Item->modelMatrix, Item->position);

	return Item;
}

Entity *ItemDropIN()
{

	if (!Item)
	{
		slog("Shid broke yo");
	}
	Item = gf3d_entity_new();
	Item->radius = 5.0;
	Item->ItemType = Invincible;
	Item->EntityType = Pickup;
	Item->model = gf3d_model_load("Sphere3");
	Item->position = vector3d(-30, -50, 0);
	gfc_matrix_make_translation(Item->modelMatrix, Item->position);

	return Item;
}

Entity *ItemDropSPD()
{

	if (!Item)
	{
		slog("Shid broke yo");
	}
	Item = gf3d_entity_new();
	Item->ItemType = SpeedBoost;
	Item->radius = 5.0;
	Item->EntityType = Pickup;
	Item->model = gf3d_model_load("Sphere6");
	Item->position = vector3d(-20, -90, 0);
	gfc_matrix_make_translation(Item->modelMatrix, Item->position);

	return Item;
}

Entity *ItemDropMana()
{

	if (!Item)
	{
		slog("Shid broke yo");
	}
	Item = gf3d_entity_new();
	Item->ItemType = Mana;
	Item->radius = 5.0;
	Item->EntityType = Pickup;
	Item->model = gf3d_model_load("Sphere4");
	Item->position = vector3d(50, -50, 0);
	gfc_matrix_make_translation(Item->modelMatrix, Item->position);

	return Item;
}

Entity *ItemDropSpell()
{

	if (!Item)
	{
		slog("Shid broke yo");
	}
	Item = gf3d_entity_new();
	Item->ItemType = Spell;
	Item->radius = 5.0;
	Item->EntityType = Pickup;
	Item->model = gf3d_model_load("Sphere7");
	Item->position = vector3d(85, -50, 0);
	gfc_matrix_make_translation(Item->modelMatrix, Item->position);

	return Item;
}
void ItemThink()
{
	if (!Item)return;

}