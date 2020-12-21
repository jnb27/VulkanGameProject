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
#include "gf3d_sprite.h"
#include "A_Slime.h"
#include "Player.h"
#include "Item.h"
#include "DinoR.h"
#include "DinoG.h"
#include "DinoP.h"
#include "DinoW.h"
#include "simple_json.h"




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
	const Uint32 frame = 0;
	VkCommandBuffer commandBuffer;
	VkCommandBuffer commandBuffer2;
	//Uint32 bufferFrame2 = 0;
	Sprite *mouse;
	Uint32 mouseFrame = 0;
	int mousex;
	int mousey;
	int checkthis = 1;
	int PlayerMana = 0;
	int PlayerHP = 0; 
	int Toggle = 0;
	Entity *test = 0;
	int loaded = 0;
	
	
	
	Entity *ent[6] = { 0 };
	int Wave = 0;

	int GCount = 0;
	int RCount = 0;
	int PCount = 0;
	int SCount = 0;
	int WCount = 0;
	Entity *Garry[10] = { 0 };
	Entity *Rarry[10] = { 0 };
	Entity *Parry[10] = { 0 };
	Entity *Sarry[10] = { 0 };
	Entity *Warry[10] = { 0 };

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
		vector4d(0, 0, 1, 1),//background color
		0,                      //fullscreen
		validate                //validation
		);
	slog_sync();

	gf3d_entity_init(1024);
	//gf3d_sprite_manager_init(5, gf3d_swapchain_get_chain_length(), gf3d_vgraphics_get_default_logical_device());

	// main game loop
	slog("gf3d main loop begin");
	slog_sync();



	/*Entity *Item = ItemDropHP();
	Entity *Item2 = ItemDropIN();
	Entity *Item3 = ItemDropSPD();
	Entity *Item4 = ItemDropMana();
	Entity *Item5 = ItemDropSpell();
*/

	//ent[0] = DinoRSpawn(5);

	//There are 2 world names, World(type2) and Terrain(type1)
	Entity *world = gf3d_entity_new();
	world->model = gf3d_model_load("Terrain");
	world->model->frameCount = 1;
	slog("%d", world->model->frameCount);
	world->position.z -= 10;
	world->radius = 0;
	gfc_matrix_make_translation(world->modelMatrix, world->position);

	
	mouse = gf3d_sprite_load("images/Menu.png",-1,-1,0);

	SJson *config = sj_load("config/configuration.json");

	if (!config)
	{
		//defaults
		slog("Where da file at doe");
	}
	else{
		slog("Ladies and gentleman we got em");
		SJson *playerArray_config = sj_object_get_value(config, "Player");
		SJson *config_playerData;

		for (int x = 0; x < sj_array_get_count(playerArray_config); x++)
		{
			config_playerData = sj_array_get_nth(playerArray_config, x);
			sj_echo(config_playerData);

			SJson *Healthvalues = sj_object_get_value(config_playerData, "Health");
			sj_echo(Healthvalues);

			SJson *ManaValues = sj_object_get_value(config_playerData, "Mana");
			sj_echo(ManaValues);

			sj_get_integer_value(Healthvalues, &PlayerHP);
			sj_get_integer_value(ManaValues, &PlayerMana);

		}
	}

	//This is where the player is spawned, pick the player based on the config file.
	Entity *player = player_spawn(vector3d(0, 0, 0), "dino", 3, PlayerHP, PlayerMana);
	slog("%i", player->health);

	gf3d_vgraphics_thirdperson_camera(player->position);


	while (!done)
	{
		SDL_PumpEvents();   // update SDL's internal event structures
		keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
		SDL_GetMouseState(&mousex, &mousey);
		//update game things here
		if (Toggle == 1 && loaded == 0)
		{
			//test->model = gf3d_model_load_animated("SphereAnim", 1,30 );
			loaded = 1;
		}

		if (Toggle == 1)
		{
			gf3d_entity_think_all();
		}
			mouseFrame = (mouseFrame + 1) % 16;

			// configure render command for graphics command pool
			// for each mesh, get a command and configure it from the pool
			bufferFrame = gf3d_vgraphics_render_begin();
			gf3d_pipeline_reset_frame(gf3d_vgraphics_get_graphics_model_pipeline(), bufferFrame);
			gf3d_pipeline_reset_frame(gf3d_vgraphics_get_graphics_overlay_pipeline(), bufferFrame);



			//2D pipe
			commandBuffer = gf3d_command_rendering_begin(bufferFrame, gf3d_vgraphics_get_graphics_overlay_pipeline());
			//2D rendering goes in here I guess
			//gf3d_sprite_draw_all(bufferFrame, commandBuffer2);
			gf3d_sprite_draw(mouse, vector2d(0, 0), vector2d(10, 10), 0, bufferFrame, commandBuffer);
			gf3d_command_rendering_end(commandBuffer);
		

		if (keys[SDL_SCANCODE_RETURN] || Toggle == 1)
		{
		commandBuffer = gf3d_command_rendering_begin(bufferFrame, gf3d_vgraphics_get_graphics_model_pipeline());
				gf3d_entity_draw_all(bufferFrame, commandBuffer);
			gf3d_command_rendering_end(commandBuffer);
			Toggle = 1;
		}
	
		if (keys[SDL_SCANCODE_GRAVE])
		{
			Toggle = 0;
		}

		gf3d_vgraphics_render_end(bufferFrame);


		if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition






		if (keys[SDL_SCANCODE_8])
		{
			if (player != 0)
			{
				gf3d_entity_free(player);
				player = player_spawn(vector3d(0, 0, 0), "dino", 1, PlayerHP, PlayerMana);
			}
		}

		if (keys[SDL_SCANCODE_9])
		{
			if (player != 0)
			{
				gf3d_entity_free(player);
				player = player_spawn(vector3d(0, 0, 0), "dino", 2, PlayerHP, PlayerMana);
			}
		}

		if (keys[SDL_SCANCODE_0])
		{
			if (player != 0)
			{
				gf3d_entity_free(player);
				player = player_spawn(vector3d(0, 0, 0), "dino", 3, PlayerHP, PlayerMana);
			}
		}

		if (SDL_GetTicks() % 10000 == 0 /*&& player->Slayed >= 15*/ && checkthis == 1)
		{
			world->model = gf3d_model_load("World");
			world->model->frameCount = 1;
				checkthis = 0;
		}

		//Begin code for assigning movement to the models
		if (SDL_GetTicks() >= 15000 && SDL_GetTicks() % 3000 == 0 && Wave == 1)
		{
			//If the game has been up for 10 seconds, every ten seconds do something THIS IS HORRIBLE


			if (WCount < 10 && Warry[WCount + 1] == 0)
			{
				
				Warry[WCount] = DinoWSpawn(WCount+1);
				slog("%i", WCount);
				WCount++;
			}
			else if (WCount == 9 && Warry[0] == 0)
			{
				WCount = 0;
				slog("We hit max number and we're moving on to the beginning again");
			}

			if (PCount < 10 && Parry[PCount + 1] == 0)
			{
				Parry[PCount] = DinoPSpawn(PCount+1);
				PCount++;
			}
			else if (PCount == 9 && Parry[0] == 0)
			{
				PCount = 0;
			}

			if (GCount < 10 && Garry[GCount + 1] == 0)
			{
				Garry[GCount] = DinoGSpawn(GCount+1);
				GCount++;
			}
			else if (GCount == 9 && Garry[0] == 0)
			{
				GCount = 0;
			}

			if (RCount < 10 && Rarry[RCount + 1] == 0)
			{
				Rarry[RCount] = DinoRSpawn(RCount+1);
				RCount++;
			}
			else if (RCount == 9 && Rarry[0] == 0)
			{
				RCount = 0;
			}

			if (SCount < 10 && Sarry[SCount + 1] == 0)
			{
				Sarry[SCount] = a_slime_spawn(SCount+1);
				SCount++;
			}
			else if (SCount == 9 && Sarry[0] == 0)
			{
				SCount = 0;
			}
		}

		if (keys[SDL_SCANCODE_Y])
		{
			if (SDL_GetTicks() % 3000 == 0)
			{
				Entity *DinoW = DinoWSpawn(5);
			}
		}
		if (keys[SDL_SCANCODE_U])
		{
			if (SDL_GetTicks() % 3000 == 0)
			{
				Entity *DinoP = DinoPSpawn(5);
			}
		}
		if (keys[SDL_SCANCODE_I])
		{
			if (SDL_GetTicks() % 3000 == 0)
			{
				Entity *DinoG = DinoGSpawn(5);
			}
		}
		if (keys[SDL_SCANCODE_O])
		{
			if (SDL_GetTicks() % 3000 == 0)
			{
				Entity *DinoR = DinoRSpawn(5);
			}
		}
		if (keys[SDL_SCANCODE_P])
		{
			Wave = 1;
		}

		if (player->model == NULL)
		{
			Toggle = 0;
			mouse = gf3d_sprite_load("images/GameOver.png", -1, -1, 0);
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