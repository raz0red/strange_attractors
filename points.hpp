#ifndef points_hpp
#define points_hpp

struct Coordinate3f
{
	float x;
	float y;
	float z;
};

class Point
{
	static std::set<Point *> instances;

private:
	float Color[3];
	Coordinate3f Position;

public:
	Point(Coordinate3f &pos, float r, float g, float bl)
	{
		Position = pos;
		Color[0] = r;
		Color[1] = g;
		Color[2] = bl;
		instances.insert(this);
	};
	// do not forget a custom copy ctor...
	Point(const Point &other)
	{
		Position = other.Position;
		Color[0] = other.Color[0];
		Color[1] = other.Color[1];
		Color[2] = other.Color[2];
		instances.insert(this);
	}
	~Point()
	{
		instances.erase(this);
	}
	static const std::set<Point *> &getInstances()
	{
		return instances;
	}
	void update(Coordinate3f &position)
	{
		Position = position;
	}
	Coordinate3f getPosition()
	{
		return Position;
	}
	void draw()
	{
		glColor3f(Color[0], Color[1], Color[2]);
		glPointSize(20.0f);
		glBegin(GL_POINTS);
		glVertex3f(Position.x, Position.y, Position.z);
		glEnd();
	};
};

Coordinate3f thomas(Coordinate3f &pos)
{
	float b = 0.208186;
	float h = 0.027;
	float dt = 9.0;

	float dx = (sin(pos.y) - b * pos.x) * dt;
	float dy = (sin(pos.z) - b * pos.y) * dt;
	float dz = (sin(pos.x) - b * pos.z) * dt;

	float x = pos.x + h * dx;
	float y = pos.y + h * dy;
	float z = pos.z + h * dz;
	Coordinate3f nextPoint = {x, y, z};

	return nextPoint;
}

class Points
{
public:
	void Tick();
};

void Points::Tick()
{
	for (Point *point : Point::getInstances())
	{
		std::cout << point->getPosition().x << std::endl;
		Coordinate3f currPos = point->getPosition();
		Coordinate3f newPos = thomas(currPos);
		point->update(newPos);
		point->draw();
	}
}
#endif
