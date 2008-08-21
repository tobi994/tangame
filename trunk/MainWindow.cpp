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

#include "MainWindow.hpp"

extern void mouseQueryCallback(cpShape *shape, void *data);

MainWindow::MainWindow() : Gosu::Window(640, 480, false) {
	setCaption(L"Tangram");
	selectedShape = NULL;
	
	cpInitChipmunk();
	space = cpSpaceNew();
	
	//load images
	backgroundPath = Gosu::sharedResourcePrefix() + L"media/bg.png";
	backgroundImage.reset(new Gosu::Image(graphics(), backgroundPath, false));
	cursorPath = Gosu::sharedResourcePrefix() + L"media/cursor.png";
	cursorImage.reset(new Gosu::Image(graphics(), cursorPath, false));
	
	//create pieces
	pieces[0].reset(new Piece(graphics(), space, 0, 200, 100));
	pieces[1].reset(new Piece(graphics(), space, 0));
	pieces[2].reset(new Piece(graphics(), space, 1));
	pieces[3].reset(new Piece(graphics(), space, 1));
	pieces[4].reset(new Piece(graphics(), space, 2));
	pieces[5].reset(new Piece(graphics(), space, 3));
	pieces[6].reset(new Piece(graphics(), space, 4));
}

MainWindow::~MainWindow() {
	cpSpaceFree(space);
}

void MainWindow::update() {
	for (int i = 0; i < 7; i++) {
		pieces[i]->update();
	}
	
	if (input().down(Gosu::kbLeft)) cpBodyApplyImpulse(pieces[6]->body, cpv(-100,0), cpvzero);
	if (input().down(Gosu::kbRight)) cpBodyApplyImpulse(pieces[6]->body, cpv(100,0), cpvzero);
	if (input().down(Gosu::kbUp)) cpBodyApplyImpulse(pieces[6]->body, cpv(0,-100), cpvzero);
	if (input().down(Gosu::kbDown)) cpBodyApplyImpulse(pieces[6]->body, cpv(0,100), cpvzero);
	
	if (input().down(Gosu::msLeft)) { //if the mouse is down
		//set selectedShape to what was pressed (test if the mouse was just pressed or is just down by seeing if it was down last step
		if (!mouseDown) {
			mouseQueryCallback(NULL, NULL); //reset the current shape
			cpSpaceShapePointQuery(space, cpv(input().mouseX(), input().mouseY()), mouseQueryCallback, NULL);
			if (selectedShape) selectedShapeOffset = cpBodyWorld2Local(selectedShape->body, cpv(input().mouseX(), input().mouseY()));
		}
		if (selectedShape) {
			//apply a force on the selected shape toward the mouse
			cpVect force = cpvsub(cpBodyWorld2Local(selectedShape->body, cpv(input().mouseX(), input().mouseY())), selectedShapeOffset); //the force to apply is the distance to the mouse minus the offset from the body's centre
			cpBodyApplyForce(selectedShape->body, cpvrotate(cpvmult(cpv(force.x, force.y), 100.0f), selectedShape->body->rot), cpvrotate(selectedShapeOffset, selectedShape->body->rot)); //here we make the force stronger and rotate the force to match the body
		}
		mouseDown = true;
	} else {
		mouseDown = false;
	}
	
	int substeps = 5; //collision detection isn't great in chipmunk; divide it up
	cpFloat dt = (1.0f/60.0f) / (cpFloat)substeps;//change substeps into amount of time
	
	for (int i = 0; i<substeps; i++) cpSpaceStep(space, dt);//next step
}

void MainWindow::draw() {
	backgroundImage->draw(0, 0, -1);
	
	for (int i = 0; i < 7; i++) {
		pieces[i]->draw();
	}
	cursorImage->draw(input().mouseX(), input().mouseY(), 99);
}
