#include "pch.h"
#include "app.h"
#include "utils/global.h"

int main(int argc, char* argv[]) {
	App::init("Test", __param_screenWidth, __param_screenHeight, false);
	
	for (int x = -5; x < 6; x += 2) {
		for (int y = -5; y < 6; y += 2) {
			double rad = ((rand() % 6) / 10.0) + 0.4;
			Rigidbody* r = new RigidbodyCircle(vec2(x, y), rad, 0, 12.0, 0.85);
			App::current->push_rb(r);
		}
	}

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