#include <stdio.h>
#include <stdlib.h>
#include "Boid.h"
#include <iostream>
using namespace std;

#define WIN32_LEAN_AND_MEAN

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(linker, "/subsystem:console")

#include <glut.h>

GLdouble width, height;   /* window width and height */

Boid allBoids[100];

float elapasedTime = 0.0f;


int arrSize = sizeof(allBoids) / sizeof(allBoids[0]);


/* Callback functions for GLUT */

/* Draw the window - this is where all the GL actions are */

void draw(void)
{
	//clear the current window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glTranslatef(0.0, 0.0, -30.0);

	glPushMatrix();
		glLineWidth(5.0f);
		glColor3f(1.0f, 0.0f, 0.0f);
		glBegin(GL_LINES);
			glVertex2f(10.f, -10.f);
			glVertex2f(10.f,10.f);
		glEnd();
		glBegin(GL_LINES);
			glVertex2f(-10.f, 10.f);
			glVertex2f(10.f, 10.f);
		glEnd();
		glBegin(GL_LINES);
			glVertex2f(-10.f, -10.f);
			glVertex2f(-10.f, 10.f);
		glEnd();
		glBegin(GL_LINES);
			glVertex2f(10.f, -10.f);
			glVertex2f(-10.f, -10.f);
		glEnd();
	glPopMatrix();

	for (int i = 0; i < arrSize; i++){
		allBoids[i].Borders();
		allBoids[i].flock(allBoids, arrSize);
		allBoids[i].update();
		allBoids[i].render();
	}

	//flush what we've drawn to the buffer
	glFlush();
	//swap the back buffer with the front buffer
	glutSwapBuffers();
}

//Passiv incrementations of the boids
//Animations goes here
void idle(void)
{
	draw();
}

/* Called when window is resized,
also when window is first created,
before the first call to display(). */
void reshape(int width, int height)
{
	//set the viewport to be the same width and height as the window
	glViewport(0, 0, width, height);
	//make changes to the projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//set up our projection type
	//we'll be using a perspective projection, with a 90 degree 
	//field of view
	gluPerspective(45.0, (float)width / (float)height, 1.0, 100.0);
	//redraw the view during resizing
	draw();
}


void kbd(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:    /* ESC */
		exit(0);
	case 'p':
		for (int i = 0; i < arrSize; i++){
				if (allBoids[i].pos.x > 10.0f || allBoids[i].pos.x < -10.0f || allBoids[i].pos.y < -10.0f || allBoids[i].pos.y > 10.0f){
					cout << "Current position: " << "x: " << allBoids[i].pos.x << " y:" << allBoids[i].pos.y << "\n";
					cout << "Current velocity: " << "x: " << allBoids[i].vel.x << " y:" << allBoids[i].vel.y << "\n";
				}
			}
	default:
		break;
	}

	return;
}

void init_drawing(void)
{
	//blend colours across the surface of the polygons
	//another mode to try is GL_FLAT which is flat shading
	glShadeModel(GL_SMOOTH);
	//turn lighting off
	glDisable(GL_LIGHTING);
	//enable OpenGL hidden surface removal
	glDepthFunc(GL_LEQUAL);
	glEnable(GL_DEPTH_TEST);
}

MyVector generateRandomVec(float s, float e){
	MyVector res;

	res.x = ((float(rand()) / float(RAND_MAX)) * (e - s)) + s;
	res.y = ((float(rand()) / float(RAND_MAX)) * (e - s)) + s;

	//res.normalise();
	//cout << "x: " << res.x << "y: " << res.y << "z: " << res.z;
	return res;
}

float generateRandomPos(float s, float e){

	return ((float(rand()) / float(RAND_MAX)) * (e - s)) + s;
}

void main(int argc, char *argv[])
{

	/* initialize GLUT, let it extract command-line
	GLUT options that you may provide
	- NOTE THE '&' BEFORE argc */
	glutInit(&argc, argv);

	/* specify the display to be single
	buffered and color as RGBA values */
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

	glutCreateWindow("Basic Glut Application");

	init_drawing();
	/* set the initial window size */
	glutInitWindowSize((int)width, (int)height);

	/* --- register callbacks with GLUT --- */

	/* register function to handle window resizes */
	glutReshapeFunc(reshape);

	/* register keyboard event processing function */
	glutKeyboardFunc(kbd);

	/* register function for idle event */
	glutIdleFunc(idle);

	/* register function that draws in the window */
	glutDisplayFunc(draw);

	/* init GL */
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 1.0);

	//request a window size of 600 x 600
	glutInitWindowSize(600, 600);
	glutReshapeWindow(600, 600);

	/*Innit pos of boids*/

	float s = -10.0f;
	float e = 10.0f;

	float sVel = -0.001f;
	float eVel = 0.001f;


	for (int i = 0; i < arrSize; i++){
		allBoids[i].pos.x = generateRandomPos(s,e);
		allBoids[i].pos.y = generateRandomPos(s,e);
		allBoids[i].vel = generateRandomVec(sVel, eVel);
	}
	/* start the GLUT main loop */
	glutMainLoop();

	exit(0);
}

