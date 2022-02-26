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

    void Piece::do_move(Face face, Direction dir)
    {
        // Coordonates //
        std::array<std::array<int, 3>, 3> R;
        switch (face)
        {
        case Face::UP:
        case Face::DOWN: {
            R = { { { 0, -1, 0 }, { 1, 0, 0 }, { 0, 0, 1 } } };
            break;
        }
        case Face::LEFT:
        case Face::RIGHT: {
            R = { { { 0, 0, 1 }, { 0, 1, 0 }, { -1, 0, 0 } } };
            break;
        }
        case Face::FRONT:
        case Face::BACK: {
            R = { { { 1, 0, 0 }, { 0, 0, -1 }, { 0, 1, 0 } } };
            break;
        }
        }
        Matrix3D<int> my_matrix = Matrix3D<int>(R);
        if (face == Face::FRONT || face == Face::RIGHT || face == Face::UP)
            my_matrix.transpose();
        if (dir == Direction::ANTI_CLOCKWISE)
            my_matrix.transpose();
        Vector3D<int> new_coordonates = my_matrix * this->coords;

        // Colors //
        Vector3D<Color> new_colors =
            Vector3D<Color>(Color::NONE, Color::NONE, Color::NONE);
        switch (face)
        {
        case Face::UP:
        case Face::DOWN: {
            new_colors.x = this->colors.y;
            new_colors.y = this->colors.x;
            break;
        }
        case Face::LEFT:
        case Face::RIGHT: {
            new_colors.x = this->colors.z;
            new_colors.z = this->colors.x;
            break;
        }
        case Face::FRONT:
        case Face::BACK: {
            new_colors.y = this->colors.z;
            new_colors.z = this->colors.y;
            break;
        }
        }

        this->coords = new_coordonates;
        this->colors = new_colors;
    }

    void Piece::do_move(Axis axis, Direction dir)
    {
        switch (axis)
        {
        case Axis::X:
            do_move(Face::RIGHT, dir);
            break;
        case Axis::Y:
            do_move(Face::UP, dir);
            break;
        case Axis::Z:
            do_move(Face::FRONT, dir);
            break;
        }
    }

} // namespace rubik
