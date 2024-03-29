#ifndef GOSU_BUTTONSWIN_HPP
#define GOSU_BUTTONSWIN_HPP

namespace Gosu
{
	enum ButtonName
	{
        kbRangeBegin = 1,
		kbEscape = 0x01,
		kbF1 = 0x3b,
		kbF2 = 0x3c,
		kbF3 = 0x3d,
		kbF4 = 0x3e,
		kbF5 = 0x3f,
		kbF6 = 0x40,
		kbF7 = 0x41,
		kbF8 = 0x42,
		kbF9 = 0x43,
		kbF10 = 0x44,
		kbF11 = 0x57,
		kbF12 = 0x58,
		kb0 = 0x0b,
		kb1 = 0x02,
		kb2 = 0x03,
		kb3 = 0x04,
		kb4 = 0x05,
		kb5 = 0x06,
		kb6 = 0x07,
		kb7 = 0x08,
		kb8 = 0x09,
		kb9 = 0x0a,
		kbTab = 0x0f,
		kbReturn = 0x1c,
		kbSpace = 0x39,
		kbLeftShift = 0x2a,
		kbRightShift = 0x36,
		kbLeftControl = 0x1d,
		kbRightControl = 0x9d,
		kbLeftAlt = 0x38,
		kbRightAlt = 0xb8,
		kbLeftMeta = 0xdb,
		kbRightMeta = 0xdc,
		kbBackspace = 0x0e,
		kbLeft = 0xcb,
		kbRight = 0xcd,
		kbUp = 0xc8,
		kbDown = 0xd0,
		kbHome = 0xc7,
		kbEnd = 0xcf,
		kbInsert = 0xd2,
		kbDelete = 0xd3,
		kbPageUp = 0xc9,
		kbPageDown = 0xd1,
		kbEnter = 0x9c,
		kbNumpad0 = 0x52,
		kbNumpad1 = 0x4f,
		kbNumpad2 = 0x50,
		kbNumpad3 = 0x51,
		kbNumpad4 = 0x4b,
		kbNumpad5 = 0x4c,
		kbNumpad6 = 0x4d,
		kbNumpad7 = 0x47,
		kbNumpad8 = 0x48,
		kbNumpad9 = 0x49,
		kbNumpadAdd = 0x4e,
		kbNumpadSubtract = 0x4a,
		kbNumpadMultiply = 0x37,
		kbNumpadDivide = 0xb5,
		kbRangeEnd = 0xff,

        msRangeBegin,
        msLeft = msRangeBegin,
        msRight,
        msMiddle,
        msWheelUp,
        msWheelDown,
        msRangeEnd,
        
        gpRangeBegin,
        gpLeft = gpRangeBegin,
        gpRight,
        gpUp,
        gpDown,
        gpButton0,
        gpButton1,
        gpButton2,
        gpButton3,
        gpButton4,
        gpButton5,
        gpButton6,
        gpButton7,
        gpButton8,
        gpButton9,
        gpButton10,
        gpButton11,
        gpButton12,
        gpButton13,
        gpButton14,
        gpButton15,
        gpRangeEnd = gpButton15,
        
        kbNum = kbRangeEnd - kbRangeBegin + 1,
        msNum = msRangeEnd - msRangeBegin + 1,
        gpNum = gpRangeEnd - gpRangeBegin + 1,
        
        numButtons = gpRangeEnd,
		noButton = 0xffffffff
	};
}

#endif
