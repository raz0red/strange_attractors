#ifndef Thomas_hpp
#define Thomas_hpp

using namespace cmn;

namespace Attractors
{
	class Thomas : virtual Attractors::Attractor
	{
	private:
		float h = 0.027f;
		float b = 0.208186f;
		float dt = 6.0f;

	public:
		Coordinate3f updateCoordinate(Coordinate3f &coord)
		{
			float dx = (sin(coord.y) - b * coord.x) * dt;
			float dy = (sin(coord.z) - b * coord.y) * dt;
			float dz = (sin(coord.x) - b * coord.z) * dt;

			return {
					.x = coord.x + h * dx,
					.y = coord.y + h * dy,
					.z = coord.z + h * dz};
		};
	};
}
#endif