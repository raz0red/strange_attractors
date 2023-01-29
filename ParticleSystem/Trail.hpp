#ifndef Trail_hpp
#define Trail_hpp

const int PARTICLE_TRAIL_LENGTH = 40;
const int MAX_TRAIL_WIDTH = 8;
const int MAX_TRAIL_OPACITY = 50;
const float TRAIL_OPACITY_FADE_DISTANCE = 0.3; // 0.0 - 1.0
const float TRAIL_WIDTH_FADE_DISTANCE = 0.8;	 // 0.0 - 1.0

using namespace cmn;

class Trail
{
private:
	ColorRGB3f color;
	std::vector<Coordinate3f> coordinates;

public:
	Trail(Coordinate3f &pos, ColorRGB3f &rgb)
	{
		color = rgb;
		coordinates.push_back(pos);
	};
	Trail(ColorRGB3f &rgb)
	{
		color = rgb;
	};

	// do not forget a custom copy ctor...
	Trail(const Trail &other)
	{
		color = other.color;
		coordinates = other.coordinates;
	};

	~Trail(){};

	Coordinate3f last()
	{
		return *coordinates.end();
	};

	void update(Coordinate3f &pos)
	{
		coordinates.push_back(pos);
		// if the trail length exceeds constant, remove the first element
		if (coordinates.size() > PARTICLE_TRAIL_LENGTH)
		{
			coordinates.erase(coordinates.begin());
		}
	};

	void draw()
	{
		const int size = coordinates.size();
		for (int i = 1; i < size - 1; i++)
		{

			glColor4f(
					color.r, color.g, color.b,
					normalize(i, 0.1, size / TRAIL_OPACITY_FADE_DISTANCE));
			glLineWidth(
					normalize(i, 0.1, size / TRAIL_WIDTH_FADE_DISTANCE) * MAX_TRAIL_WIDTH);
			glBegin(GL_LINES);
			glVertex3f(coordinates[i - 1].x, coordinates[i - 1].y, coordinates[i - 1].z);
			glVertex3f(coordinates[i].x, coordinates[i].y, coordinates[i].z);
			glEnd();
		}
	};
};

#endif