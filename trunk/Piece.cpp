#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp> // Makes life easier for Windows users compiling this.
#include <chipmunk/chipmunk.h>
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp> // Learn them, they're moving into standard C++!
#include <boost/lexical_cast.hpp> // Could also use <sstream>, just for int <-> string conversion

#include <cmath>
#include <cstdlib>
#include <list>
#include <vector>
#include <iostream>

#include "Piece.hpp"

Piece::Piece(Gosu::Graphics& g, cpSpace *s, int t, cpFloat x, cpFloat y, cpFloat a) {
	type = t;
	space = s;
	graphics = &g;
	imagePath = Gosu::sharedResourcePrefix() + L"media/piece" + boost::lexical_cast<std::wstring>(type) + L".png"; //media/piece0.png, piece1.png, etc
	image.reset(new Gosu::Image(g, imagePath, false)); //load the image
	
	//shape vertices - I really need to fix this, its messy and makes me sad.
	cpVect verts0[3] = {cpv(0, -75), cpv(-150, 75), cpv(150, 75)};
	cpVect verts1[3] = {cpv(0, -37.5), cpv(-75, 37.5f), cpv(75, 37.5f)};
	cpVect verts2[4] = {cpv(0, -75), cpv(-75, 0), cpv(0, 75), cpv(75, 0)};
	cpVect verts3[4] = {cpv(-37.5f, -37.5f), cpv(-112.5f, 37.5f), cpv(37.5f, 37.5f), cpv(112.5f, -37.5)};
	cpVect verts4[3] = {cpv(0, -53.03f), cpv(-106.07f, 53.03f), cpv(106.07f, 53.03f)};
	
	//the verts are set so that all shapes have pointy bits facing up, except the parallelogram (bits facing left and right)
	switch(type) { 
		case 0: //big triangle
		mass = 4; //mass relative to a small triangle equaling 1
		moment = cpMomentForPoly(mass, 3, verts0, cpvzero); //moment of inertia, calculated with the chipmunk helper function
		body = cpBodyNew(mass, moment); //create the body with the mass and moment of inertia
		shape = cpPolyShapeNew(body, 3, verts0, cpvzero); //create the shape
		break;
		
		case 1: //small triangle
		mass = 1; //mass relative to a small triangle equaling 1
		moment = cpMomentForPoly(mass, 3, verts1, cpvzero); //moment of inertia, calculated with the chipmunk helper function
		body = cpBodyNew(mass, moment); //create the body with the mass and moment of inertia
		shape = cpPolyShapeNew(body, 3, verts1, cpvzero); //create the shape
		break;
		
		case 2: //diamond
		mass = 2; //mass relative to a small triangle equaling 1
		moment = cpMomentForPoly(mass, 4, verts2, cpvzero); //moment of inertia, calculated with the chipmunk helper function
		body = cpBodyNew(mass, moment); //create the body with the mass and moment of inertia
		shape = cpPolyShapeNew(body, 4, verts2, cpvzero); //create the shape
		break;
		
		case 3: //paralellogram
		mass = 2; //mass relative to a small triangle equaling 1
		moment = cpMomentForPoly(mass, 4, verts3, cpvzero); //moment of inertia, calculated with the chipmunk helper function
		body = cpBodyNew(mass, moment); //create the body with the mass and moment of inertia
		shape = cpPolyShapeNew(body, 4, verts3, cpvzero); //create the shape
		reflected = false;
		break;
		
		case 4: //medium triangle
		mass = 2; //mass relative to a small triangle equaling 1
		moment = cpMomentForPoly(mass, 3, verts4, cpvzero); //moment of inertia, calculated with the chipmunk helper function
		body = cpBodyNew(mass, moment); //create the body with the mass and moment of inertia
		shape = cpPolyShapeNew(body, 3, verts4, cpvzero); //create the shape
		break;
	}
	friction = 0.5f;
	rotFriction = 0.95f;
	body->p = cpv(x, y);
	body->a = a*Gosu::pi/180;
	body->data = (void *)this;//reference to self for shape picking
	cpSpaceAddBody(space, body);
	cpSpaceAddShape(space, shape);
	locked = false;
}

Piece::~Piece(void) {
	cpShapeFree(shape);
	cpBodyFree(body);
}

void Piece::update(void) {
	body->v = cpvmult(body->v, friction);
	body->w *= rotFriction;
	cpBodyResetForces(body);
}

void Piece::draw(void) {
	if (type != 3 or reflected == false) image->drawRot(body->p.x, body->p.y, 1, body->a*180/Gosu::pi); //draw the normal image if it is a normal shape or unreflected paralellogram
	else image->drawRot(body->p.x, body->p.y, 1, body->a*180/Gosu::pi, 0.5, 0.5, -1); //Otherwise, draw a the same image, reflected
	
	//draw a red cross on the piece if it is locked
	if (locked) {
		graphics->drawLine(body->p.x-5, body->p.y-5, 0xffff0000, body->p.x+5, body->p.y+5, 0xffff0000, 2);
		graphics->drawLine(body->p.x+5, body->p.y-5, 0xffff0000, body->p.x-5, body->p.y+5, 0xffff0000, 2);
	}
}

void Piece::toggleReflection(void) {
	if (type != 3) return; //only do this function for the paralellogram.
	//another sad, messy bit... *cries*
	cpVect verts[4] = {cpv(-37.5f, -37.5f), cpv(-112.5f, 37.5f), cpv(37.5f, 37.5f), cpv(112.5f, -37.5)};
	cpVect vertsR[4] = {cpv(-112.5f, -37.5f), cpv(-37.5f, 37.5f), cpv(112.5f, 37.5f), cpv(37.5f, -37.5)};
	cpSpaceRemoveShape(space, shape);
	cpShapeFree(shape);
	if (reflected) shape = cpPolyShapeNew(body, 4, verts, cpvzero); //create the shape
	else if (!reflected) shape = cpPolyShapeNew(body, 4, vertsR, cpvzero); //create the reflected shape
	cpSpaceAddShape(space, shape);
	reflected = !reflected;
}

void Piece::lock(void) {
	cpBodySetMass(body, INFINITY);
	cpBodySetMoment(body, INFINITY);
	locked = true;
}

void Piece::unlock(void) {
	cpBodySetMass(body, mass);
	cpBodySetMoment(body, moment);
	locked = false;
}

void Piece::toggleLock(void) {
	if (locked) unlock();
	else if (!locked) lock();
}
