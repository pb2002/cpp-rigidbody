#pragma once
#include <pch.h>

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>

#include "vec2.h"
#include "world.h"


// Renderer is a Singleton class that keeps track of the World and SDL_Renderer objects
// and implements drawing methods to prevent unneccesary reliance on the SDL library.
class Renderer {
public:
	// Singleton ------------------------
	/// <summary>
	/// Initializes the renderer (Singleton constructor).
	/// </summary>
	/// <param name="window">The current application window.</param>
	static void init(SDL_Window* window);
	static Renderer* current;
	// ----------------------------------
	
	// Sets the drawing color (RGBA).
	void set_color(int r, int g, int b, int a);
	// Draws a circle at the given position with the given radius, 
	// using the current drawing color.
	void draw_circle(vec2 pos, double radius);
	// Fills the screen with the given color (RGBA).
	void fill_color(int r, int g, int b, int a);
	// Shows the screen.
	void show();
	// Returns the top-left corner in world space coordinates.
	inline vec2 topleft() { return m_world->screen_to_world(0, 0); }
	// Returns the bottom-right corner in world space coordinates.
	inline vec2 bottomright() { return m_world->screen_to_world(__param_screenWidth, __param_screenHeight); }

private:
	World* m_world;
	SDL_Renderer* m_renderer;
	struct {
		int r, g, b, a;
	} m_drawingColor;
};