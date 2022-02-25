#pragma once

#include <vector>

#include "piece.hh"
#include "vector3D.hh"

namespace rubik
{
    class Cube
    {
    public:
        Cube();

        std::vector<Piece> get_pieces() const
        {
            return this->pieces_;
        }

    private:
        std::vector<Piece> pieces_;
    };

    inline std::ostream& operator<<(std::ostream& os, const Cube& c)
    {
        std::vector<Piece> pieces = c.get_pieces();
        for (size_t i = 0; i < pieces.size(); i++)
        {
            os << pieces.at(i) << '\n';
        }

        return os;
    }

} // namespace rubik