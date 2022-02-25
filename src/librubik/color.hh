#pragma once

#include <iostream>

namespace rubik
{
    enum class Color
    {
        YELLOW,
        WHITE,
        RED,
        BLUE,
        ORANGE,
        GREEN,
        NONE
    };

    inline std::ostream& operator<<(std::ostream& os, const Color& c)
    {
        switch (c)
        {
        case rubik::Color::YELLOW:
            return os << 'Y';
            break;
        case rubik::Color::WHITE:
            return os << 'W';
            break;
        case rubik::Color::RED:
            return os << 'R';
            break;
        case rubik::Color::BLUE:
            return os << 'B';
            break;
        case rubik::Color::ORANGE:
            return os << 'O';
            break;
        case rubik::Color::GREEN:
            return os << 'G';
            break;
        case rubik::Color::NONE:
            return os << 'X';
            break;
        default:
            break;
        }

        return os;
    }

} // namespace rubik
