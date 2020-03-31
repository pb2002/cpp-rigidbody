#pragma once
#include "vec2.h"
struct CollisionData {
	CollisionData() { normal = vec2(); position = vec2(); distance = 0; }
	CollisionData(vec2 normal, vec2 position, double dst) : normal(normal), position(position), distance(dst) { }
	vec2 normal;
	vec2 position;
	double distance;
};