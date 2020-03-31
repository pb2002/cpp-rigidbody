#pragma once
#include <pch.h>
#include "rigidbody.h"

#include "utils/global.h"
#include "renderer.h"


void Rigidbody::add_force(vec2 force) {
	m_force += force;
}

void Rigidbody::add_force_at_pos(vec2 force, vec2 pos) {
	m_force += force;
}


vec2 Rigidbody::world_to_local(vec2 v) {
	auto new_v = v - m_position;
	new_v.rotate(-m_rotation);
	return new_v;
}

void Rigidbody::set_velocity(vec2 vel) {
	m_velocity = vel;
}

void Rigidbody::impulse_at_position(vec2 imp, vec2 pos) {
	m_velocity += imp / m_mass;
	m_angularVelocity += vec2::cross(pos, imp / m_mass);
}

void Rigidbody::on_update() {

}

// on_post_update() is called for each object in a seperate for-loop.
void Rigidbody::on_post_update() {
	// Apply general physics rules (acceleration -> velocity -> position)
	m_acceleration = m_force / m_mass; // F = m * a -> a = F / m
	m_acceleration += vec2(0, -m_gravityScale);
	m_angularAcceleration = m_torque / m_mass;

	m_angularVelocity += m_angularAcceleration * _param_delta_time;
	m_rotation += m_angularVelocity * _param_delta_time;
	
	m_velocity += m_acceleration * _param_delta_time; // a = dv/dt -> dv = a * dt
	m_position += m_velocity * _param_delta_time; // v = dx / dt -> dx = v * dt
	m_force.set(0, 0); // set the force to 0 for next iteraion (forces are non-persistent)
}

void Rigidbody::on_render() {}

void Rigidbody::handle_collision(Rigidbody& a, Rigidbody& b) {

	CollisionData data;

	if (a.detect_collision(&b, &data)) { // circles are intersecting
		// seperate circles
		a.m_position -= data.normal.normalize() / 2 * data.distance;
		b.m_position += data.normal.normalize() / 2 * data.distance;

		// relative velocity between A and B
		vec2 relative_velocity = a.m_velocity - b.m_velocity;
		// relative velocity along normal
		double velocity_along_normal = vec2::dot(relative_velocity, data.normal);
		// do not resolve collision when objects are moving away from eachother
		if (velocity_along_normal > 0) return;
		// get smallest restitution factor
		double restitution = a.m_restitution > b.m_restitution ? b.m_restitution : a.m_restitution;
		// See https://gamedevelopment.tutsplus.com/tutorials/how-to-create-a-custom-2d-physics-engine-the-basics-and-impulse-resolution--gamedev-6331.
		double impulse_magnitude = -(1 + a.m_restitution) * (-velocity_along_normal);
		impulse_magnitude /= (1 / a.m_mass) + (1 / b.m_mass);

		// get impulse vector
		vec2 impulse = data.normal * impulse_magnitude;

		// impulse = mass * velocity
		a.m_velocity -= impulse / a.m_mass;
		b.m_velocity += impulse / b.m_mass;
	}

}
