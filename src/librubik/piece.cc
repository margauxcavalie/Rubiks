#include "piece.hh"

namespace rubik
{
    Piece::Piece(Vector3D<int> coordonates, Vector3D<Color> cols)
        : coords(coordonates)
        , colors(cols)
    {}

        Piece::Type Piece::get_type()
    {
        int number_nones = 0;
        if (this->colors.x == Color::NONE)
            number_nones += 1;
        if (this->colors.y == Color::NONE)
            number_nones += 1;
        if (this->colors.z == Color::NONE)
            number_nones += 1;

        if (number_nones == 0)
            return Piece::Type::CORNER;
        if (number_nones == 1)
            return Piece::Type::EDGE;
        if (number_nones == 2)
            return Piece::Type::CENTER;

        return Piece::Type::NONE;
    }

    bool Piece::operator==(const Piece& other)
    {
        if (this->colors.x == other.colors.x && this->colors.y == other.colors.y
            && this->colors.z == other.colors.z
            && this->coords.x == other.coords.x
            && this->coords.y == other.coords.y
            && this->coords.z == other.coords.z)
            return true;

        else
            return false;
    }

    bool Piece::operator<(const Piece& other)
    {
        if (this->coords.x >= other.coords.x && this->coords.y >= other.coords.y
            && this->coords.z >= other.coords.z)
            return false;
        else
            return true;
    }

    bool Piece::operator!=(const Piece& other)
    {
        if (operator==(other))
            return false;
        else
            return true;
    }

    bool Piece::operator>(const Piece& other)
    {
        if (operator<(other))
            return false;
        else
            return true;
    }

    bool Piece::operator<=(const Piece& other)
    {
        if (operator<(other) || operator==(other))
            return true;
        else
            return false;
    }

    bool Piece::operator>=(const Piece& other)
    {
        if (operator>(other) || operator==(other))
            return true;
        else
            return false;
    }

} // namespace rubik
