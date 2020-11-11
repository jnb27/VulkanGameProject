#include <SDL.h>            

#include "simple_logger.h"
#include "gfc_vector.h"
#include "gfc_matrix.h"

#include "gf3d_vgraphics.h"
#include "gf3d_pipeline.h"
#include "gf3d_swapchain.h"
#include "gf3d_model.h"
#include "gf3d_camera.h"
#include "gf3d_texture.h"
#include "gf3d_entity.h"
#include "A_Slime.h"
#include "Player.h"

void dino_think(Entity *self);

//WORLD SIZE 102 X 102 

int main(int argc, char *argv[])
{
	//When programming in C all variables must be declared at the top.
	int done = 0;
	int a;
	Uint8 validate = 0;
	const Uint8 * keys;
	Uint32 bufferFrame = 0;
	VkCommandBuffer commandBuffer;
	Entity *ent[6] = { 0 };

	//Disables all Validation Layers at the start
	for (a = 1; a < argc; a++)
	{
		if (strcmp(argv[a], "-disable_validate") == 0)
		{
			validate = 0;
		}
	}

	init_logger("gf3d.log");
	slog("gf3d begin");

	//Vulkan Initialization
	gf3d_vgraphics_init(
		"gf3d",                 //program name
		1200,                   //screen width
		700,                    //screen height
		vector4d(0.51, 0.75, 1, 1),//background color
		0,                      //fullscreen
		validate                //validation
		);
	slog_sync();

	gf3d_entity_init(1024);

	// main game loop
	slog("gf3d main loop begin");
	slog_sync();

	Entity *player = player_spawn(vector3d(0, 0, 0), "dino");
	
	
	
	
	
	Entity *Item = ItemDropHP();
	Entity *Item2 = ItemDropIN();
	Entity *Item3 = ItemDropSPD();
	Entity *Item4 = ItemDropMana();
	Entity *Item5 = ItemDropSpell();





	Entity *world = gf3d_entity_new();
	world->model = gf3d_model_load("Terrain");
	world->position.z -= 10;
	world->radius = 0;
	gfc_matrix_make_translation(world->modelMatrix, world->position);

	gf3d_vgraphics_thirdperson_camera(player->position);

	
	while (!done)
	{
		SDL_PumpEvents();   // update SDL's internal event structures
		keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
		//update game things here

		//gf3d_vgraphics_rotate_camera(0.001);

		
		
		gf3d_entity_think_all();
		//gf3d_entity_follow(player, slime1);

		//gfc_matrix_rotate(
		//	modelMat2,
		//	modelMat2,
		//	0.002,
		//	vector3d(0, 0, 1));

		// configure render command for graphics command pool
		// for each mesh, get a command and configure it from the pool
		bufferFrame = gf3d_vgraphics_render_begin();
		gf3d_pipeline_reset_frame(gf3d_vgraphics_get_graphics_pipeline(), bufferFrame);
		commandBuffer = gf3d_command_rendering_begin(bufferFrame);

		gf3d_entity_draw_all(bufferFrame, commandBuffer);

		//gf3d_model_draw(model, bufferFrame, commandBuffer, modelMat);
		//gf3d_model_draw(model2, bufferFrame, commandBuffer, modelMat2);

		gf3d_command_rendering_end(commandBuffer);

		gf3d_vgraphics_render_end(bufferFrame);

	
		if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition

		//Begin code for assigning movement to the models

		if (keys[SDL_SCANCODE_Y])
		{
			if (SDL_GetTicks() % 3000 == 0)
			{
				Entity *DinoW = DinoWSpawn();
			}
		}
		if (keys[SDL_SCANCODE_U])
		{
			if (SDL_GetTicks() % 3000 == 0)
			{
				Entity *DinoP = DinoPSpawn();
			}
		}
		if (keys[SDL_SCANCODE_I])
		{
			if (SDL_GetTicks() % 3000 == 0)
			{
				Entity *DinoG = DinoGSpawn();
			}
		}
		if (keys[SDL_SCANCODE_O])
		{
			if (SDL_GetTicks() % 3000 == 0)
			{
				Entity *DinoR = DinoRSpawn();
			}
		}
		if (keys[SDL_SCANCODE_P])
		{
			if (SDL_GetTicks() % 3000 == 0)
			{
				Entity *slime1 = a_slime_spawn();
			}
		}
		
	}

	vkDeviceWaitIdle(gf3d_vgraphics_get_default_logical_device());
	//cleanup
	gf3d_entity_close();
	slog("gf3d program end");
	slog_sync();
	return 0;
}

void dino_think(Entity *self)
{
	//gfc_matrix_rotate(self->modelMatrix, self->modelMatrix, 0.002, vector3d(0, 0, 1));
}
/*eol@eof*/