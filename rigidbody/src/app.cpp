#include <pch.h>
#include "app.h"

#include "renderer.h"

void App::init(const char* title, int width, int height, bool fullscreen) {
	if (SDL_Init(SDL_INIT_EVERYTHING)) {
		log_crit("Could not initialize SDL.");
		log_crit(SDL_GetError());
	}
	current = new App();
	current->m_Window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
											  width, height, SDL_WINDOW_ALLOW_HIGHDPI | (fullscreen ? SDL_WINDOW_FULLSCREEN : 0));
	if (!current->m_Window) {
		log_crit("Could not create SDL window.");
		log_crit(SDL_GetError());
	}
	Renderer::init(current->m_Window);

	current->m_running = true;
}

void App::on_event() {}

void App::on_update() {}

void App::on_render() {}
