#ifndef Halvorsen_hpp
#define Halvorsen_hpp

using namespace cmn;

namespace Attractors
{
	class Halvorsen : virtual Attractors::Attractor
	{
	private:
		float a = 1.89f;
		float h = 0.7f;
		float dt = 0.007f;

	public:
		Coordinate3f updateCoordinate(Coordinate3f &coord)
		{
			float dx = (-a * coord.x - 4 * coord.y - 4 * coord.z - (coord.y * coord.y)) * dt;
			float dy = (-a * coord.y - 4 * coord.z - 4 * coord.x - (coord.z * coord.z)) * dt;
			float dz = (-a * coord.z - 4 * coord.x - 4 * coord.y - (coord.x * coord.x)) * dt;

			return {
					.x = coord.x + h * dx,
					.y = coord.y + h * dy,
					.z = coord.z + h * dz};
		};
	};
}

#endif