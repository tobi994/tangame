//! \file Utility.hpp
//! General purpose utility functions.

#ifndef GOSU_UTILITY_HPP
#define GOSU_UTILITY_HPP

#include <string>
#include <vector>

namespace Gosu
{
    //! Converts an std::string into an std::wstring.
    std::wstring widen(const std::string& s);
    //! Converts an std::wstring into an std::string.
    std::string narrow(const std::wstring& ws);
    
    // Undocumented, temporary: Please ignore. ;)
    std::wstring utf8ToWstring(const std::string& utf8);
    std::string wstringToUTF8(const std::wstring& ws);
}

#endif
