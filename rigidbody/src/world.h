#pragma once
#include <pch.h>

#include "vec2.h"
#include "utils/global.h"

// World contains world space information and conversion methods
struct World {
	World(double coordScale, vec2 offset) {
		this->m_coordScale = coordScale;
		this->m_offset = offset;
	}
	std::tuple<int, int> world_to_screen(vec2 v) {
		vec2 t = v + m_offset;
		t *= (__param_screenHeight / m_coordScale);
		return { t.x + __param_screenWidth / 2, -t.y + __param_screenHeight / 2 };
	}
	double world_to_screen(double d) {
		return (__param_screenHeight / m_coordScale) * d;
	}
	vec2 screen_to_world(int x, int y) {
		int offsetx = x - __param_screenWidth / 2;
		int offsety = y - __param_screenHeight / 2;
		return vec2(offsetx * m_coordScale / __param_screenHeight,
					-offsety * m_coordScale / __param_screenHeight) - m_offset;
	}
private:
	double m_coordScale;
	vec2 m_offset;
};