#pragma once

#include <SDL.h>



extern SDL_Window* main_window;
extern SDL_Renderer* main_renderer;
extern SDL_Texture* main_texture;

extern int screenwidth;
extern int screenheight;

extern int framecount;



// Initialize system setup
// \returns 1 on success, 0 on failure
int system_init();



void update_window();



void system_quit();



void show_errorbox(const char* title, const char* message);
void show_sdlerrorbox();
