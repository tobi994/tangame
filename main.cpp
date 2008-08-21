/*
 Tangram
 Copyright 2008 Lucas Levin
 */

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

#include "MainWindow.hpp"
#include "Piece.hpp"

boost::scoped_ptr<MainWindow> win;

void mouseQueryCallback(cpShape *shape, void *data);

int main(int argc, char** argv)
{
	win.reset(new MainWindow);
	win->show();
	return 0;
}

void mouseQueryCallback(cpShape *shape, void *data) {
	win->selectedShape = shape;
}
