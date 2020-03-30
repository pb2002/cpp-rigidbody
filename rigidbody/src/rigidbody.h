#pragma once
#include "vec2.h"

class Rigidbody {

public:
	Rigidbody(double mass, vec2 position, double radius);
	Rigidbody(double mass, vec2 position, double radius, double gravityScale);

	void add_force(vec2 force);
	void add_force_at_pos(vec2 force, vec2 pos);
	void set_velocity(vec2 vel);

	virtual void on_update();
	virtual void on_render();

	virtual vec2 world_to_local(vec2 v);
	static void check_collision(Rigidbody& a, Rigidbody& b);

	friend class Rigidbody;
private:
	vec2 m_position;
	vec2 m_velocity;
	vec2 m_acceleration;
	vec2 m_force;

	double m_mass;
	double m_restitution;
	double m_radius;
	double m_gravityScale;
};