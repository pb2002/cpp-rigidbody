#pragma once
#include <SDL.h>
#include "rigidbody.h"
#include "rigidbodyCircle.h"
class App {
public:
	static void init(const char* title, int width, int height, bool fullscreen);
	static App* current;

	void on_event();
	void on_update();
	void on_render();

	void push_rb(Rigidbody* rb);
	Rigidbody const* get_rb(int index);

	void quit();
	const bool is_running() const { return m_running; }
private:
	bool m_running;
	SDL_Window* m_Window;
	std::vector<Rigidbody*> m_rigidbodies;
};