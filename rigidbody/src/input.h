#pragma once
#include "vec2.h"
#include "renderer.h"
#include <SDL.h>

vec2 getMousePosition() {
	int x, y;
	SDL_GetMouseState(&x, &y);
	return Renderer::current->screen_to_world(x, y);
}