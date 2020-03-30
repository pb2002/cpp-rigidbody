#include "pch.h"
#include "app.h"
#include "utils/global.h"
int main(int argc, char* argv[]) {
	App::init("Test", __param_screenWidth, __param_screenHeight, false);
	
	Rigidbody* rb1 = new Rigidbody(1, vec2(0,3), 0.8, 5.0);
	rb1->set_velocity(vec2(4, 0));
	App::current->push_rb(rb1);

	Rigidbody* rb2 = new Rigidbody(2, vec2(-3, 2.5), 0.9, 5.0);
	rb2->set_velocity(vec2(-4, 0));
	App::current->push_rb(rb2);
	
	Rigidbody* rb3 = new Rigidbody(1.25, vec2(3, 2), 0.85, 5.0);
	rb3->set_velocity(vec2(5, -3));
	App::current->push_rb(rb3);
	
	unsigned int frameStart;
	unsigned int frameTime;
	
	while (App::current->is_running()) {
		frameStart = SDL_GetTicks();
	
		App::current->on_event();
		App::current->on_update();
		App::current->on_render();
		
		frameTime = SDL_GetTicks() - frameStart;
		if (_param_delta_time * 1000 > frameTime) {
			SDL_Delay(1000 * _param_delta_time - frameTime);
		}
	}
	return 0;
}