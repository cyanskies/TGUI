/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus' Graphical User Interface
// Copyright (C) 2012-2017 Bruno Van de Velde (vdv_b@tgui.eu)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#ifndef TGUI_CLIPBOARD_HPP
#define TGUI_CLIPBOARD_HPP


#include <TGUI/Config.hpp>
#include <SFML/System/String.hpp>
#include <SFML/Window/WindowHandle.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    class TGUI_API Clipboard
    {
      public:
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Returns the contents of the clipboard
        ///
        /// @return Contents of the clipboard
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static sf::String get();


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Changes the contents of the clipboard
        ///
        /// @param contents  New contents of the clipboard
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static void set(const sf::String& contents);

#if SFML_VERSION_MAJOR == 2 && SFML_VERSION_MINOR < 5
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        /// @brief Sets the window handle which is needed to access the system clipboard on windows
        ///
        /// @param windowHandle  Handle to the window
        ///
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        static void setWindowHandle(const sf::WindowHandle& windowHandle);


        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    protected:

        static sf::String m_contents;
        static sf::WindowHandle m_windowHandle;
        static bool m_isWindowHandleSet;
#endif
        /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // TGUI_CLIPBOARD_HPP
