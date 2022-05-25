#pragma once

#include <istream>
#include <variant>
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

        void set_piece(Piece p, int index)
        {
            this->pieces_[index] = p;
        }

        static Cube from_stream(std::istream& is);

        std::vector<Piece>::iterator begin()
        {
            return this->pieces_.begin();
        };
        std::vector<Piece>::iterator end()
        {
            return this->pieces_.end();
        };

        Piece find_piece(Vector3D<int> coords) const;
        Piece find_piece(Vector3D<Color> colors) const;

        void do_move(Move move);
        void do_moves(std::vector<Move> moves);
        void undo_move(Move move);
        void undo_moves(std::vector<Move> moves);

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