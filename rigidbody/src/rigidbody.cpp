#pragma once
#include <pch.h>
#include "rigidbody.h"
#include "utils/global.h"
#include "renderer.h"

Rigidbody::Rigidbody(double mass, vec2 position, double radius)
	: m_mass(mass), m_position(position), m_radius(radius), m_gravityScale(1.0) {
	m_velocity = vec2();
	m_acceleration = vec2();
	m_force = vec2();
	m_restitution = 0.95;
}

Rigidbody::Rigidbody(double mass, vec2 position, double radius, double gravityScale) 
	: m_mass(mass), m_position(position), m_radius(radius), m_gravityScale(gravityScale) {
	m_velocity = vec2();
	m_acceleration = vec2();
	m_force = vec2();
	m_restitution = 0.95;
} 

void Rigidbody::add_force(vec2 force) {
	m_force += force;
}

void Rigidbody::add_force_at_pos(vec2 force, vec2 pos) {
	m_force += force;
}

vec2 Rigidbody::world_to_local(vec2 v) {
	auto new_v = v - m_position;
	return new_v;
}

void Rigidbody::set_velocity(vec2 vel) {
	m_velocity = vel;
}

void Rigidbody::on_update() {
	vec2 tl = Renderer::current->topleft();
	vec2 br = Renderer::current->bottomright();
	// Wall Collision -------------------------------------------------------------------
	if (m_position.x - m_radius < tl.x) {
		// seperate from wall
		m_position.x = tl.x + m_radius;
		// see check-collision function for details.
		double j = -(1 + m_restitution) * m_velocity.x;
		// wall has infinite mass so 1/b.mass -> 0 as b.mass -> infinity.
		// all multiplications and divisions by a.mass also cancel out so we're left with
		// the following (note: the normal is just the x axis here).
		m_velocity.x += j;
	}
	else if (m_position.x + m_radius > br.x) {
		m_position.x = br.x - m_radius;
		double j = -(1 + m_restitution) * m_velocity.x;
		m_velocity.x += j;
	}
	if (m_position.y - m_radius < tl.y) {
		m_position.y = tl.y + m_radius;
		double j = -(1 + m_restitution) * m_velocity.y;
		m_velocity.y += j;
	}
	else if (m_position.y + m_radius > br.y) {
		m_position.y = br.y - m_radius;
		double j = -(1 + m_restitution) * m_velocity.y;
		m_velocity.y += j;
	}
	// ----------------------------------------------------------------------------------

	// Apply general physics rules (acceleration -> velocity -> position)
	m_acceleration = m_force / m_mass;
	m_acceleration += vec2(0,-m_gravityScale);

	m_velocity += m_acceleration * _param_delta_time;
	m_position += m_velocity * _param_delta_time;
}

void Rigidbody::on_render() {
	Renderer::current->set_color(255, 32, 64, 255);
	Renderer::current->draw_circle(m_position, m_radius);
}

void Rigidbody::check_collision(Rigidbody& a, Rigidbody& b) {
	vec2 normal = a.m_position - b.m_position; // collision normal

	double center_distance = normal.length(); // distance between centers
	double hit_distance = center_distance - a.m_radius - b.m_radius; // distance between circles
	
	if (hit_distance < 0) { // circles are intersecting
		// seperate circles
		a.m_position -= normal.normalize()/2 * hit_distance;
		b.m_position += normal.normalize()/2 * hit_distance;

		// relative velocity between A and B
		vec2 relative_velocity = a.m_velocity - b.m_velocity;
		
		// relative velocity along normal
		double velocity_along_normal = vec2::dot(relative_velocity, normal);
		// do not resolve collision when objects are moving away from eachother
		if (velocity_along_normal > 0) return;
		// get smallest restitution factor
		double restitution = a.m_restitution > b.m_restitution ? b.m_restitution : a.m_restitution;
		// See https://gamedevelopment.tutsplus.com/tutorials/how-to-create-a-custom-2d-physics-engine-the-basics-and-impulse-resolution--gamedev-6331.
		double impulse_magnitude = -(1 + a.m_restitution) * (-velocity_along_normal);
		impulse_magnitude /= (1 / a.m_mass) + (1 / b.m_mass);
		
		// get impulse vector
		vec2 impulse = normal * impulse_magnitude;
		
		// impulse = mass * velocity
		a.m_velocity -= impulse / a.m_mass;
		b.m_velocity += impulse / b.m_mass;
	}
}
