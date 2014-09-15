/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// TGUI - Texus's Graphical User Interface
// Copyright (C) 2012-2014 Bruno Van de Velde (vdv_b@tgui.eu)
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


#include <TGUI/Signal.hpp>

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace tgui
{
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int                          Signal::m_int = 0;
    sf::Vector2f                 Signal::m_vector2f;
    sf::String                   Signal::m_string;
    sf::String                   Signal::m_string2;
    std::vector<sf::String>      Signal::m_stringList;
    std::shared_ptr<ChildWindow> Signal::m_childWindowPtr;

    unsigned int SignalWidgetBase::m_lastId = 0;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Signal::disconnect(unsigned int id)
    {
        return !!m_functions.erase(id);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Signal::disconnectAll()
    {
        m_functions.clear();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool Signal::isEmpty()
    {
        return m_functions.empty();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Signal::operator()()
    {
        for (auto& function : m_functions)
            function.second();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void Signal::checkCompatibleParameterType(const std::string& type)
    {
        throw Exception{"Could not bind optional parameter type '" + type + "'"};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    SignalWidgetBase::SignalWidgetBase(const SignalWidgetBase& copy)
    {
        for (auto& signal : copy.m_signals)
            m_signals[signal.first] = std::make_shared<Signal>(*signal.second);
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    SignalWidgetBase& SignalWidgetBase::operator=(const SignalWidgetBase& right)
    {
        if (this != &right)
        {
            for (auto& signal : right.m_signals)
                m_signals[signal.first] = std::make_shared<Signal>(*signal.second);
        }

        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void SignalWidgetBase::disconnect(unsigned int id)
    {
        for (auto& signal : m_signals)
        {
            if (signal.second->disconnect(id))
                return;
        }

        throw Exception{"Failed to disconnect signal handler. There is no function bound to the given id " + tgui::to_string(id) + "."};
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void SignalWidgetBase::disconnectAll(const std::string& signalName)
    {
        for (auto& name : extractSignalNames(signalName))
            m_signals.at(toLower(name))->disconnectAll();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    void SignalWidgetBase::disconnectAll()
    {
        for (auto& signal : m_signals)
            signal.second->disconnectAll();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    bool SignalWidgetBase::isSignalBound(const std::string& name)
    {
        assert(m_signals[toLower(name)]);
        return !m_signals[toLower(name)]->isEmpty();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    std::vector<std::string> SignalWidgetBase::extractSignalNames(std::string input)
    {
        // A space is used for binding multiple signals at once
        std::vector<std::string> names;
        std::string::size_type pos = 0;
        while ((pos = input.find(" ")) != std::string::npos)
        {
            std::string token = input.substr(0, pos);
            if (token != "")
                names.push_back(token);

            input.erase(0, pos+1);
        }

        if (input != "")
            names.push_back(input);

        return names;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////