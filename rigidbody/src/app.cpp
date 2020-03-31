#include <pch.h>
#include "app.h"

#include "renderer.h"

App* App::current;

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
	current->m_rigidbodies = std::vector<Rigidbody*>();
	current->m_running = true;
}

void App::on_event() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) quit();
	}
}

void App::on_update() {
	
	for (int i = 0; i < m_rigidbodies.size(); i++) {
		for (int j = i+1; j < m_rigidbodies.size(); j++) {
			Rigidbody::handle_collision(*m_rigidbodies[i], *m_rigidbodies[j]);
		}
		
		m_rigidbodies[i]->on_update();
	}
	for (Rigidbody* rb : m_rigidbodies) {
		rb->on_post_update();
	}
}

void App::on_render() {
	Renderer::current->fill_color(32, 48, 64, 255);
	for (Rigidbody* rb : m_rigidbodies) {
		rb->on_render();
	}
	Renderer::current->show();
}

void App::push_rb(Rigidbody* rb) {
	m_rigidbodies.push_back(rb);
}

Rigidbody const* App::get_rb(int index) {
	assert(index < m_rigidbodies.size());
	return m_rigidbodies[index];
}

void App::quit() {
	m_running = false;
	SDL_Quit();
}
