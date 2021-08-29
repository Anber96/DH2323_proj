#include "MyVector.h"
#include <iostream>

using namespace std;

MyVector::MyVector(void)
{
	this->x = this->y = 0.0;
}

MyVector::MyVector(float x, float y)
{
	this->x = x; this->y = y;
}

MyVector::MyVector(MyPosition& start, MyPosition& end)
{
	this->x = end.x - start.x;
	this->y = end.y - start.y;
}

void MyVector::add(const MyVector &other)
{
	this->x += other.x;
	this->y += other.y;
}

void MyVector::sub(const MyVector &other)
{
	this->x -= other.x;
	this->y -= other.y;
}

void MyVector::div(const float n)
{
	this->x /= n;
	this->y /= n;
}

void MyVector::mult(const float n)
{
	this->x *= n;
	this->y *= n;
}


void MyVector::setMagnitude(const float m)
{
	if (this->getMagnitude() > 0.0)
	{
		normalise();
		this->uniformScale(m);
	}
}

void MyVector::scaleMod(void){

	float scale = 0.002;
	this->x = fmod(this->x, scale);
	this->y = fmod(this->y, scale);
}

float MyVector::dist(const MyVector &other) const{
	return sqrt((this->x - other.x)*(this->x - other.x) + (this->y - other.y)*(this->y - other.y));
}

void MyVector::limit(float max)
{
	float size = getMagnitude();

	if (size > max) {
		this->x /= size;
		this->y /= size;

	}
}

MyVector MyVector::subtractFrom(const MyVector &other) const
{
	//subtract this vector from other and return the result
	MyVector result;

	result.x = result.x - other.x;
	result.y = result.y - other.y;
	return result;
}
		
float MyVector::getMagnitude(void) const
{
	float result;
	result = sqrt(powf(this->x, 2.0f) + powf(this->y, 2.0f));
	return result;
}

void MyVector::uniformScale(const float m)
{
	//your code here
	//set the length of the vector
	this->x *= m;
	this->y *= m;
}
void MyVector::normalise(void)
{
	float result;
	//normalise this vector (set its length to 1)
	result = sqrt((powf(this->x, 2.0f)) + (powf(this->y, 2.0f)));

	this->x = (this->x) / result;
	this->y = (this->y) / result;
}

	