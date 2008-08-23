#ifndef H_MAINWINDOW
#define H_MAINWINDOW

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

#include "Piece.hpp"

class MainWindow : public Gosu::Window {
	public:
	//functions
	MainWindow(); //constructor - set the title and variables here
	~MainWindow(); //destructor - frees stuff
	void update(); //update function - most processing here
	void draw(); //draw function - have a guess what this does (NO PROCESSING ALLOWED)
	void shapeDragging(void);
	
	//images
	std::wstring backgroundPath;
	boost::scoped_ptr<Gosu::Image> backgroundImage;
	std::wstring cursorPath;
	boost::scoped_ptr<Gosu::Image> cursorImage;
	
	//variables
	cpSpace *space; //NOTE: scoped pointers aren't appropriate for chipmunk objects because chipmunk is C based (not C++)
	boost::scoped_ptr<Piece> pieces[7];
	cpShape *selectedShape;
	cpVect selectedShapeOffset;
	cpFloat selectedShapeAngOffset;
	bool mouseDown, f1Down; //these are so we can tell if a key was just pressed or is being held down
};

#endif
