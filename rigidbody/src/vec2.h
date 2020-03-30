#pragma once
#include <pch.h>

class vec2 {
public:
	double x, y;

	vec2() :x(0), y(0) {}
	vec2(double x, double y) : x(x), y(y) {}
	vec2(const vec2& v) : x(v.x), y(v.y) {}

	vec2 operator=(const vec2 v) { x = v.x; y = v.y; return *this; }
	
	vec2 operator+=(vec2 v) { x += v.x; y += v.y; return *this; }
	vec2 operator-=(vec2 v) { x -= v.x; y -= v.y; return *this; }
	vec2 operator*=(double s) { x *= s; y *= s; return *this; }
	vec2 operator/=(double s) { x /= s; y /= s; return *this; }

	friend vec2 operator-(vec2& v) { return vec2(-v.x, -v.y); }
	
	friend vec2 operator+(vec2 lhs, vec2 rhs) { return vec2(lhs.x + rhs.x, lhs.y + rhs.y); }
	friend vec2 operator-(vec2 lhs, vec2 rhs) { return vec2(lhs.x - rhs.x, lhs.y - rhs.y); }
	friend vec2 operator*(vec2 lhs, double rhs) { return vec2(lhs.x * rhs, lhs.y * rhs); }
	friend vec2 operator/(vec2 lhs, double rhs) { return vec2(lhs.x / rhs, lhs.y / rhs); }

	friend bool operator==(vec2 lhs, vec2 rhs) { return lhs.x == rhs.x && lhs.y == rhs.y; }
	friend bool operator>(vec2 lhs, vec2 rhs) { return lhs.length() > rhs.length(); }
	friend bool operator<(vec2 lhs, vec2 rhs) { return lhs.length() < rhs.length(); }
	friend bool operator>=(vec2 lhs, vec2 rhs) { return lhs.length() >= rhs.length(); }
	friend bool operator<=(vec2 lhs, vec2 rhs) { return lhs.length() <= rhs.length(); }

	friend std::ostream& operator<<(std::ostream& out, vec2& v) { out << "vec2(" << v.x << ", " << v.y << ")"; return out; }
	
	void set(double x, double y) { this->x = x; this->y = y; }

	void rotate(double deg) { 
		double theta = deg / 180.0 * M_PI; 
		double c = cos(theta); double s = sin(theta);
		double tx = x * c - y * s; double ty = x * s + y * c;
		x = tx; y = ty;
	}

	vec2& normalize() { if (length() == 0) return *this; *this *= (1.0 / length()); return *this; }

	double dist(vec2 v) const { vec2 d(v.x - x, v.y - y); return d.length(); }
	double length() const { return std::sqrt(x * x + y * y); }
	void truncate(double length) {
		double angle = atan2f(y, x);
		x = length * cos(angle);
		y = length * sin(angle);
	}

	vec2 ortho() const { return vec2(y, -x); }
	static double dot(vec2 v1, vec2 v2) { return v1.x * v2.x + v1.y * v2.y; }
	static double cross(vec2 v1, vec2 v2) { return (v1.x * v2.y) - (v1.y * v2.x); }

};
