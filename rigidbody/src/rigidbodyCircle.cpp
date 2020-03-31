#include <pch.h>
#include "rigidbodyCircle.h"

#include "utils/global.h"
#include "renderer.h"
#include "input.h"

void RigidbodyCircle::on_update() {
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
	} else if (m_position.x + m_radius > br.x) {
		m_position.x = br.x - m_radius;
		double j = -(1 + m_restitution) * m_velocity.x;
		m_velocity.x += j;
	}
	if (m_position.y + m_radius > tl.y) {
		m_position.y = tl.y - m_radius;
		double j = -(1 + m_restitution) * m_velocity.y;
		m_velocity.y += j;
	} else if (m_position.y - m_radius < br.y) {
		m_position.y = br.y + m_radius;
		double j = -(1 + m_restitution) * m_velocity.y;
		m_velocity.y += j;
	}
	// The interactive and satisfying part    c:
	// simply apply gravity in reverse, the mouse has a weight of -8.
	auto mouse = getMousePosition();
	vec2 norm = mouse - m_position;
	double dst = norm.length() - m_radius;
	if (dst < 0.5) {
		dst = 0.35;
	}
	if (dst < 2) {
		add_force(norm.normalize() * -5 * m_mass / (dst * dst * dst));
	}
	// ----------------------------------------------------------------------------------


}
void RigidbodyCircle::on_render() {
	Renderer::current->set_color(255, 32, 64, 255);
	Renderer::current->draw_circle(m_position, m_radius);
}

bool RigidbodyCircle::detect_collision(Rigidbody* other, CollisionData* data) {
	
	if (typeid(*other) == typeid(RigidbodyCircle)) {
		RigidbodyCircle* o = (RigidbodyCircle*)other;
		vec2 normal = m_position - o->m_position; // collision normal

		double center_distance = normal.length(); // distance between centers
		double hit_distance = center_distance - m_radius - o->m_radius; // distance between circles
		if (hit_distance < 0) {
			data->normal = normal;
			data->position = m_position + normal / 2;
			data->distance = hit_distance;
			return true;
		}
		return false;
	}
	return false;
}
