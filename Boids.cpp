#include "Boids.h"
#include "Boid.h"
#include "stdio.h"
#include "glaux.h"
#include "glext.h"


Boids::Boids(void){
	numOfBoids = 1;
	separationC = 1.0;
	alignmentC = 1.0;
	cohesionC = 1.0;
	boidSize = 10.0;
	AllBoids[1];
}

Boids::Boids(int numBoids){
	numOfBoids = numBoids;
	separationC = 1.0;
	alignmentC = 1.0;
	cohesionC = 1.0;
	boidSize = 10.0;
	AllBoids[numBoids];
}


void Boids::render(void){
	glPointSize(boidSize);
	glBegin(GL_POINTS);
	glVertex2f(10.0, 10.0);
	glEnd();
}

