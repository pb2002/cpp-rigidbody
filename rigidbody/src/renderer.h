#pragma once
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

class Renderer {
public:
	static void init(SDL_Window* window);
	static Renderer* current;
public:
	
private:
	SDL_Renderer* m_renderer;
};