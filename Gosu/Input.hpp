//! \file Input.hpp
//! Interface of the Input class.

#ifndef GOSU_INPUT_HPP
#define GOSU_INPUT_HPP

#include <Gosu/Fwd.hpp>
#include <Gosu/Platform.hpp>

#ifdef GOSU_IS_WIN
#include <Gosu/ButtonsWin.hpp>
#include <windows.h>
#endif

#ifdef GOSU_IS_MAC
#include <Gosu/ButtonsMac.hpp>
#endif

#ifdef GOSU_IS_X
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <Gosu/ButtonsX.hpp>
#endif

#include <Gosu/Platform.hpp>
#include <Gosu/Fwd.hpp>
#include <boost/function.hpp>
#include <boost/scoped_ptr.hpp>

namespace Gosu
{
	//! Very lightweight class that identifies a button (keyboard, mouse or other device).
	class Button
	{
		unsigned id;
		
	public:
		//! For internal use.
		explicit Button(unsigned id) : id(id) {}
		//! For internal use.
		unsigned getId() const { return id; }

		//! Default constructor; == noButton.
		Button() : id(noButton) {}

		//! Conversion from ButtonName constants.
		Button(ButtonName name) : id(name) {}
	};
	
	//! Tests whether two Buttons identify the same physical button.
	inline bool operator==(Button lhs, Button rhs)
	{
		return lhs.getId() == rhs.getId();
	}
	inline bool operator!=(Button lhs, Button rhs)
	{
		return !(lhs == rhs);
	}
	
    //! Manages initialization and shutdown of the input system; only one Input
	//! instance can live per application. (Should this limitation ever get into
	//! anyone's way, I will happily remove it; until then, I practice YAGNI.)
    class Input
    {
        struct Impl;
        boost::scoped_ptr<Impl> pimpl;

	public:
        #ifdef GOSU_IS_WIN
        Input(HWND window);
        #endif
        
        #ifdef GOSU_IS_MAC
        Input(void* nswindow);
        bool feedNSEvent(void* event);
        #endif
        
        #ifdef GOSU_IS_X
        Input(::Display* dpy);
        bool feedXEvent(::XEvent& event, Window* window);
        #endif
        
        ~Input();

        //! Returns the character a button usually produces, or 0.
        static wchar_t idToChar(Button btn);
        //! Returns the button that has to be pressed to produce the
        //! given character, or noButton.
        static Button charToId(wchar_t ch);
        
		//! Returns true if a button is currently pressed.
		bool down(Button btn) const;

        //! Returns the horizontal position of the mouse relative to the top
        //! left corner of the window given to Input's constructor.
        double mouseX() const;
        //! See mouseX.
        double mouseY() const;
        // See comments on virtual resolutions in Graphics.hpp.
        void setMouseResolution(double width, double height);
        
        //! Collects new information about which buttons are pressed, where the
        //! mouse is and calls onButtonUp/onButtonDown, if assigned.
        void update();
        
		//! Assignable events that are called by update. You can bind these to your own functions.
		//! If you use the Window class, it will assign forward these to its own methods.
        boost::function<void (Button)> onButtonDown, onButtonUp;
        
        TextInput* textInput() const;
        void setTextInput(TextInput* input);
    };
}

#endif
