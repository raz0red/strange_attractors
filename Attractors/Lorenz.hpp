#ifndef Lorenz_hpp
#define Lorenz_hpp
// void lorenz() {
// float a = 19;
// float b = 28;
// float c = 9/3;

//    float dt = 0.01;
//    float dx = (a * (y - x)) * dt;
//    float dy = (x * (b - z) - y) * dt;
//    float dz = (x * y - c * z) * dt;
//
//    x = x + dx;
//    y = y + dy;
//    z = z + dz;
//}
namespace Attractors
{
	class Lorenz : virtual Attractors::Attractor
	{
	private:
		float dt = 0.5f;

		float p = 10.0f;
		float r = 28.0f;
		float b = 8 / 3;
		float h = 0.01f;

	public:
		Coordinate3f updateCoordinate(Coordinate3f &coord)
		{
			float dx = (p * (-coord.x + coord.y)) * dt;
			float dy = (-coord.x * coord.z + r * coord.x - coord.y) * dt;
			float dz = (coord.x * coord.y - b * coord.z) * dt;

			return {
					.x = (coord.x + h * dx),
					.y = (coord.y + h * dy),
					.z = (coord.z + h * dz)};
		};
	};
}
#endif