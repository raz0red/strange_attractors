#ifndef Attractor_hpp
#define Attractor_hpp

using namespace cmn;

namespace Attractors
{
	struct Attractor
	{
		Coordinate3f updateCoordinate(Coordinate3f &coord);
	};

}

#endif