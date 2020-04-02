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
void Renderer::draw_rect(vec2 pos, vec2 size, double rotation) {
	int16_t* x = new int16_t[4];
	int16_t* y = new int16_t[4];

	vec2 v1 = vec2(-size.x / 2, -size.y / 2);
	v1.rotate(rotation);
	std::tie(x[0], y[0]) = m_world->world_to_screen(pos + v1);
	vec2 v2 = vec2(size.x / 2, -size.y / 2);
	v2.rotate(rotation);
	std::tie(x[1], y[1]) = m_world->world_to_screen(pos + v2);
	vec2 v3 = vec2(size.x / 2, size.y / 2);
	v3.rotate(rotation);
	std::tie(x[2], y[2]) = m_world->world_to_screen(pos + v3);
	vec2 v4 = vec2(-size.x / 2, size.y / 2);
	v4.rotate(rotation);
	std::tie(x[3], y[3]) = m_world->world_to_screen(pos + v4);
	
	filledPolygonRGBA(m_renderer, x, y, 4, m_drawingColor.r, m_drawingColor.g, m_drawingColor.b, m_drawingColor.a);
}
void Renderer::show() {

	SDL_RenderPresent(m_renderer);
}

vec2 Renderer::screen_to_world(int x, int y) { return m_world->screen_to_world(x, y); }

// Returns the top-left corner in world space coordinates.

vec2 Renderer::topleft() { return m_world->screen_to_world(0, 0); }

// Returns the bottom-right corner in world space coordinates.

vec2 Renderer::bottomright() { return m_world->screen_to_world(__param_screenWidth, __param_screenHeight); }

void Renderer::fill_color(int r, int g, int b, int a) {
	SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
	SDL_RenderClear(m_renderer);
}
