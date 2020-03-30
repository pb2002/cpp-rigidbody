#pragma once
#include <pch.h>
#include "renderer.h"

Renderer* Renderer::current;

void Renderer::init(SDL_Window* window) {
	current = new Renderer();
	current->m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	current->m_world = new World(_param_coord_scale, vec2(0,0));
}

void Renderer::set_color(int r, int g, int b, int a) {
	m_drawingColor = { r, g, b, a };
}

void Renderer::draw_circle(vec2 pos, double radius) {
	int x, y;
	std::tie(x,y) = m_world->world_to_screen(pos);
	filledCircleRGBA(m_renderer, x, y, m_world->world_to_screen(radius), m_drawingColor.r, m_drawingColor.g, m_drawingColor.b, m_drawingColor.a);
}
void Renderer::show() {
	SDL_RenderPresent(m_renderer);
}

void Renderer::fill_color(int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
	SDL_RenderClear(m_renderer);
}
