#ifndef BOID__H 
#define BOID__H 
#include <math.h>
#include "myVector.h"

class Boid
{
	public:
		MyVector pos;
		MyVector vel;
		MyVector acc;
		float maxForce;
		float maxSpeed;

		//These are the radius of the search area
		float aPerception;
		float cPerception;
		float sPerception;

		Boid(void);
		Boid(MyVector inPos, MyVector inVel);

		MyVector generateRandomVel(void);
		void render(void);
		void renderSearchArea(void);
		void update(void);

		void Borders(void);
		void flock(Boid flock[], int arrSize);
		//Three rules

		MyVector Separation(Boid flock[], int arrSize);
		MyVector Alignment(Boid flock[], int arrSize);
		MyVector Cohesion(Boid flock[], int arrSize);

};

#endif