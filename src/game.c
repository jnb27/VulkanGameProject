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
#include "Player.h"

void dino_think(Entity *self);

int main(int argc, char *argv[])
{
	//When programming in C all variables must be declared at the top.
	int done = 0;
	int a, i;
	Uint8 validate = 0;
	const Uint8 * keys;
	Uint32 bufferFrame = 0;
	VkCommandBuffer commandBuffer;
	//Model *model;
	//Matrix4 modelMat;
	//Model *model2;
	//Matrix4 modelMat2;
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
	
	/*for (i = 0; i < 1; i++)
	{
		ent[i] = gf3d_entity_new();
		if (!ent[i])continue;
		ent[i]->model = gf3d_model_load("dino");
		ent[i]->think = dino_think;
	}*/

	/*Loading 2 Dino Models to start doing stuff
	model = gf3d_model_load("dino");
	gfc_matrix_identity(modelMat);
	model2 = gf3d_model_load("dino");
	gfc_matrix_identity(modelMat2);
	/*gfc_matrix_make_translation(
		modelMat2,
		vector3d(10, 0, 0)
		);*/
	while (!done)
	{
		SDL_PumpEvents();   // update SDL's internal event structures
		keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
		//update game things here

		//gf3d_vgraphics_rotate_camera(0.001);

		

		gf3d_entity_think_all();


		/*gfc_matrix_rotate(
			modelMat2,
			modelMat2,
			0.002,
			vector3d(0, 0, 1));*/

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