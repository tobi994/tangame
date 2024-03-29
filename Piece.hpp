#ifndef H_PIECE
#define H_PIECE

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

//All the tangram pieces. I don't think there is a need for inherited classes, because all the pieces do the same thing (except maybe the paralellogram).
class Piece {
	public:
	//functions
	Piece(Gosu::Graphics& g, cpSpace *s, int t, cpFloat x = 320, cpFloat y = 240, cpFloat a = 0); //constructor
	~Piece(void); //destructor
	void update(void);
	void draw(void);
	
	void toggleReflection(void); //only for paralellogram
	void toggleLock(void); //if anything is locked, unlock everything. if everything is unlocked, lock everything
	void lock(int what); //what = 1: lock position, what = 2: lock rotation, what = anything else: lock all
	void unlock(int what);
	
	//variables
	Gosu::Graphics *graphics;
	int type; //types: 0-big triangle, 1-small triangle, 2-diamond, 3-parallelogram, 4-medium triangle
	std::wstring imagePath; //path to the image. Just media/piece0.png, piece1.png, etc
	boost::scoped_ptr<Gosu::Image> image; //the image
	cpBody *body; //the physics body - NOTE: scoped pointers aren't appropriate for chipmunk objects because chipmunk is C based (not C++)
	cpShape *shape; //the physics shape
	cpSpace *space;
	cpFloat mass, moment; //although these are in the body, we need to store them seperately for locking
	float friction, rotFriction;
	bool reflected; //only useful for paralellogram
	bool locked;
};

#endif
