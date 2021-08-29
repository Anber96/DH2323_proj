#ifndef BOIDS__H 
#define BOIDS__H 
#include <math.h>
#include "Boid.h"

class Boids
{
public:
	Boids(void);
	Boids(int numOfBoids);

	int numOfBoids;
	float separationC;
	float alignmentC;
	float cohesionC;
	float boidSize;

	Boid AllBoids[1];

	void render(void);
};

#endif