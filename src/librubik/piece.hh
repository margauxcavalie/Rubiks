#pragma once

#include <array>
#include <system_error>

#include "color.hh"
#include "matrix3D.hh"
#include "move.hh"
#include "vector3D.hh"

namespace rubik
{
    class Piece
    {
    public:
        Piece(Vector3D<int> coordonates, Vector3D<Color> cols);
        Vector3D<int> coords;
        Vector3D<Color> colors;

        enum class Type
        {
            CORNER,
            CENTER,
            EDGE,
            NONE
        };

        Piece::Type get_type();
        bool operator==(const Piece& other);
        bool operator<(const Piece& other);
        bool operator!=(const Piece& other);
        bool operator>(const Piece& other);
        bool operator<=(const Piece& other);
        bool operator>=(const Piece& other);

        void do_move(Face face, Direction dir);
        void do_move(Axis axis, Direction dir);
    };

    inline std::ostream& operator<<(std::ostream& os, const Piece& p)
    {
        return os << '(' << p.coords.x << ',' << p.coords.y << ',' << p.coords.z
                  << ") (" << p.colors.x << ',' << p.colors.y << ','
                  << p.colors.z << ')';
    }

} // namespace rubik
