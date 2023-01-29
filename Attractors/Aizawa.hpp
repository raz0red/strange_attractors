#ifndef Aizawa_hpp
#define Aizawa_hpp

using namespace cmn;

namespace Attractors
{
	class Aizawa : virtual Attractors::Attractor
	{
	private:
		float a = 0.95f;
		float b = 0.7f;
		float c = 0.6f;
		float d = 3.5f;
		float e = 0.25f;
		float f = 0.1f;
		float h = 0.03f;
		float dt = 0.5f;

	public:
		Coordinate3f updateCoordinate(Coordinate3f &coord)
		{
			float dx = ((coord.z - b) * coord.x - d * coord.y) * dt;
			float dy = (d * coord.x + (coord.z - b) * coord.y) * dt;
			float dz = (c + (a * coord.z) - ((coord.z * coord.z * coord.z) / 3) -
									((coord.x * coord.x) + (coord.y * coord.y)) * (1 + (e * coord.z)) + f * coord.z * (coord.x * coord.x * coord.x)) *
								 dt;

			return {
					.x = coord.x + h * dx,
					.y = coord.y + h * dy,
					.z = coord.z + h * dz};
		};
	};
}

#endif