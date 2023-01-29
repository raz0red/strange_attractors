#ifndef Particle_hpp
#define Particle_hpp

const float PARTICLE_SIZE = 10.0f;

using namespace cmn;

class Particle
{
	static std::set<Particle *> instances;

private:
	ColorRGB3f color;
	Coordinate3f position;
	Trail *trail;

public:
	Particle(Coordinate3f &pos, ColorRGB3f &rgb)
	{
		position = pos;
		color = rgb;
		trail = new Trail(rgb);
		instances.insert(this);
	};

	// do not forget a custom copy ctor...
	Particle(const Particle &other)
	{
		position = other.position;
		color = other.color;
		trail = other.trail;
		instances.insert(this);
	}

	~Particle()
	{
		instances.erase(this);
	}

	static const std::set<Particle *> &getInstances()
	{
		return instances;
	}

	void update(Coordinate3f &pos)
	{
		position = pos;
		trail->update(pos);
	}

	Coordinate3f getPosition()
	{
		return position;
	}

	void draw()
	{
		glColor3f(color.r, color.g, color.b);
		glPointSize(PARTICLE_SIZE);
		glBegin(GL_POINTS);
		glVertex3f(position.x, position.y, position.z);
		glEnd();
		trail->draw();
	};
};
#endif
