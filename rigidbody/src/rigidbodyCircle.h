#pragma once
#include "rigidbody.h"

class RigidbodyCircle : public Rigidbody {
public:
	RigidbodyCircle(vec2 position = vec2(), double radius = 0.5, double rotation = 0, double gravityScale = 9.81,
							double restitution = 0.99, vec2 velocity = vec2()) 
		: Rigidbody{ position, rotation, gravityScale, restitution, velocity }, m_radius(radius)  {
		m_mass = M_PI * radius * radius;
	}
	virtual void on_update() override;
	virtual void on_render() override;
	virtual bool detect_collision(Rigidbody* other, CollisionData* data) override;
protected:
	double m_radius;
};