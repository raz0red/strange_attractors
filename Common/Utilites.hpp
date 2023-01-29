#ifndef Utilities_hpp
#define Utilities_hpp

namespace cmn
{
	float degToRad(float degrees)
	{
		return degrees * (M_PI / 180);
	}

	float normalize(float x, float min, float max)
	{

		return (x - min) / (max - min);
	};

	float randf()
	{
		return normalize(rand(), 0, RAND_MAX);
	}

	std::vector<Coordinate3f> genCoordinates(float maxX, float maxY, float maxZ, float delta)
	{
		std::vector<Coordinate3f> coordinates;

		for (float y = maxY * -1 / 2; y < maxY / 2; y += delta)
		{
			for (float x = maxX * -1 / 2; x < maxX / 2; x += delta)
			{
				for (float z = maxZ * -1 / 2; z < maxZ / 2; z += delta)
				{
					coordinates.push_back((Coordinate3f){x, y, z});
				}
			}
		}

		return coordinates;
	};

	ColorRGB3f genRandomPastel()
	{
		return {
				.r = normalize((rand() % 128) + 127, 0, 255),
				.g = normalize((rand() % 128) + 127, 0, 255),
				.b = normalize((rand() % 128) + 127, 0, 255)};
	};

	// std::vector<Particle> genParticles()
	// {
	// 	std::vector<Particle> particles;
	// 	auto initialPoints = genCoordinates(5, 5, 5, 1.5);
	// 	for (int i = 0; i < initialPoints.size(); i++)
	// 	{
	// 		ColorRGB3f color = genRandomPastel();
	// 		Particle newParticle = Particle(initialPoints[i], color);
	// 		particles.push_back(newParticle);
	// 	}
	// 	return particles;
	// }
}

#endif