#include "Boid.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <iostream>
#include <glut.h>

const float DEG2RAD = 3.14159 / 180;

using namespace std;

Boid::Boid(void)
{
	pos = MyVector(0.0f, 0.0f);
	vel = MyVector(0.0f, 0.0f);
	acc = MyVector(0.0f, 0.0f);
	maxForce = 0.2f;
	maxSpeed = 1.0f;
	aPerception = 1.0f;
	cPerception = 1.0f;
	sPerception = 1.5f;

}


Boid::Boid(MyVector inPos, MyVector inVel)
{
	pos = inPos;
	vel = inVel;
	acc = MyVector(0.0f, 0.0f);
	maxForce = 0.2f;
	maxSpeed = 1.0f;

	aPerception = 1.0f;
	cPerception = 1.0f;
	sPerception = 1.5f;

}


void Boid::Borders(void){
	if (pos.x > 10.0f){ pos.x = -10.0f; }
	if (pos.x < -10.0f){ pos.x = 10.0f; }
	if (pos.y > 10.0f){ pos.y = -10.0f; }
	if (pos.y < -10.0f){ pos.y = 10.0f; }
}


MyVector Boid::Alignment(Boid flock[], int arrSize){

	float total = 0.0f;


	MyVector avg(0.0f, 0.0f);

	for (int i = 0; i < arrSize; i++){
		float d = pos.dist(flock[i].pos); 
		if (d > 0 && d < aPerception){
			avg.add(flock[i].vel);
			total++;
		}
	}


	if (total > 0.0f){

		//cout << "avg:" << "x: " << avg.x << " y: " << avg.y << " z: " << avg.z << "\n";
		avg.div(total);
		avg.setMagnitude(maxSpeed);
		avg.sub(vel);
		avg.limit(maxForce);

	}
	total = 0.0f;

	return avg;

}


MyVector Boid::Cohesion(Boid flock[], int arrSize){

	float total = 0.0f;
	MyVector avg(0.0f, 0.0f);

	for (int i = 0; i < arrSize; i++){
		float d = pos.dist(flock[i].pos);
		if (d > 0 && d < cPerception){
			avg.add(flock[i].pos);
			total = total + 1.0f;
		}
	}


	if (total > 0.0f){
		//cout << "avg:" << "x: " << avg.x << " y: " << avg.y << " z: " << avg.z << "\n";
		avg.div(total);
		avg.sub(pos);
		avg.setMagnitude(maxSpeed);
		avg.sub(vel);
		avg.limit(maxForce);

	}
	total = 0.0f;

	return avg;


}

MyVector Boid::Separation(Boid flock[], int arrSize){

	float total = 0.0f;
	MyVector avg(0.0f, 0.0f);

	for (int i = 0; i < arrSize; i++){
		float d = pos.dist(flock[i].pos);
		if (d > 0 && d < sPerception){
			MyVector diff = pos.subtractFrom(flock[i].pos);
			diff.normalise();
			diff.div(d*d);
			avg.add(diff);
			total += 1.0f;
		}
	}

	if (total > 0.0f){
		avg.div(total);
		avg.setMagnitude(maxSpeed);
		avg.sub(vel);
		avg.limit(maxForce);
	}
	total = 0.0f;

	return avg;
}


void Boid::flock(Boid flock[], int arrSize){

	MyVector a = Alignment(flock, arrSize);
	MyVector c = Cohesion(flock, arrSize);
	MyVector s = Separation(flock, arrSize);

	a.mult(1.0f);
	c.mult(1.0f);
	s.mult(1.5f);

	acc.add(a);
	acc.add(c);
	acc.add(s);

}


void Boid::update(void){
	//cout << "x: " << acc.x << "y: " << acc.y << "z: " << acc.z << "\n";

	pos.add(vel);
	vel.add(acc);
	vel.limit(maxSpeed);
	vel.scaleMod();

}

void Boid::render(void)
{
	glPushMatrix();
		glPointSize(5.0);
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_POINTS);
			glVertex2f(pos.x, pos.y); //This is the center of the square
		glEnd();
		//renderSearchArea();
	glPopMatrix();
}

void Boid::renderSearchArea(void)
{
	float num_segments = 10.f;
	glPushMatrix();
		glColor3f(1.0f, 1.0f, 1.0f);
		glBegin(GL_LINE_LOOP);
		for (int ii = 0; ii < num_segments; ii++)
		{
			float theta = 2.0f * 3.1415926f * float(ii) / float(num_segments);//get the current angle 

			float x = aPerception * cosf(theta);//calculate the x component 
			float y = aPerception * sinf(theta);//calculate the y component 

			glVertex2f(x + pos.x, y + pos.y);//output vertex 

		}
		glEnd();
	glPopMatrix();
}


