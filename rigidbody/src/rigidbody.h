#pragma once
#include "vec2.h"
#include "collisionData.h"
class Rigidbody {
public:
	// Constructor
	Rigidbody(vec2 position = vec2(), double rotation = 0, double gravityScale = 9.81, 
			  double restitution = 0.99, vec2 velocity = vec2())
		: m_position(position), m_gravityScale(gravityScale), m_restitution(restitution), m_velocity(velocity) {
		m_acceleration = vec2();
		m_force = vec2();

		m_rotation = rotation;
		m_angularVelocity = 0;
		m_angularAcceleration = 0;
		m_torque = 0;
	}

	void add_force(vec2 force);
	void add_force_at_pos(vec2 force, vec2 pos);
	void set_velocity(vec2 vel);
	void impulse_at_position(vec2 imp, vec2 pos);
	virtual void on_update();
	virtual void on_post_update();
	virtual void on_render();

	virtual vec2 world_to_local(vec2 v);
	virtual bool detect_collision(Rigidbody* other, CollisionData* data) = 0;
	static void handle_collision(Rigidbody& a, Rigidbody& b);
	
	friend class RigidbodyCircle;
	friend class Rigidbody;
protected:
	vec2 m_position;
	vec2 m_velocity;
	vec2 m_acceleration;
	vec2 m_force;

	double m_rotation;
	double m_angularVelocity;
	double m_angularAcceleration;
	double m_torque;

	double m_mass;
	double m_restitution;
	double m_gravityScale;
};