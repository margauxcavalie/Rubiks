#include "cube.hh"

#include <stdexcept>
#include <vector>

namespace rubik
{
    Cube::Cube()
    {
        this->pieces_ = std::vector<Piece>();
        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                for (int k = -1; k < 2; k++)
                {
                    Vector3D<int> coordonates = Vector3D<int>(k, j, i);
                    Color x_color;
                    if (k == -1)
                        x_color = Color::BLUE;
                    if (k == 0)
                        x_color = Color::NONE;
                    if (k == 1)
                        x_color = Color::GREEN;

                    Color y_color;
                    if (j == -1)
                        y_color = Color::ORANGE;
                    if (j == 0)
                        y_color = Color::NONE;
                    if (j == 1)
                        y_color = Color::RED;

                    Color z_color;
                    if (i == -1)
                        z_color = Color::YELLOW;
                    if (i == 0)
                        z_color = Color::NONE;
                    if (i == 1)
                        z_color = Color::WHITE;

                    Vector3D<Color> colors =
                        Vector3D<Color>(x_color, y_color, z_color);

                    Piece new_piece = Piece(coordonates, colors);
                    this->pieces_.push_back(new_piece);
                }
            }
        }
    }

    void check_char(int* counter, std::string line, char c)
    {
        if (line[*counter] != c)
            throw std::invalid_argument("Invalid syntax");
        *counter += 1;
    }

    int get_number(int* counter, std::string line)
    {
        int res = 1;
        if (line[*counter] == '-')
        {
            res = -1;
            *counter += 1;
        }

        if (line[*counter] == '0')
            res = 0;

        else if (line[*counter] != '1')
            throw std::invalid_argument("Invalid number");

        *counter += 1;
        return res;
    }

    Color get_color(int* counter, std::string line)
    {
        Color color = Color::NONE;
        switch (line[*counter])
        {
        case 'Y':
            color = Color::YELLOW;
            break;
        case 'R':
            color = Color::RED;
            break;
        case 'W':
            color = Color::WHITE;
            break;
        case 'B':
            color = Color::BLUE;
            break;
        case 'O':
            color = Color::ORANGE;
            break;
        case 'G':
            color = Color::GREEN;
            break;
        case 'X':
            break;
        default:
            throw std::invalid_argument("Invalid color");
        }

        *counter += 1;
        return color;
    }

    Cube Cube::from_stream(std::istream& is)
    {
        Cube new_cube = Cube();
        std::string line;
        int counter_cube = 0;
        while (getline(is, line))
        {
            /*if (line.size() < 1)
                throw std::invalid_argument("Line not long enough");*/

            int counter = 0;

            int x_coord;
            int y_coord;
            int z_coord;
            check_char(&counter, line, '(');
            x_coord = get_number(&counter, line);
            check_char(&counter, line, ',');
            y_coord = get_number(&counter, line);
            check_char(&counter, line, ',');
            z_coord = get_number(&counter, line);
            check_char(&counter, line, ')');
            check_char(&counter, line, ' ');

            Color x_color;
            Color y_color;
            Color z_color;
            check_char(&counter, line, '(');
            x_color = get_color(&counter, line);
            check_char(&counter, line, ',');
            y_color = get_color(&counter, line);
            check_char(&counter, line, ',');
            z_color = get_color(&counter, line);
            check_char(&counter, line, ')');

            /*if (line[counter] != '\0') // peut etre bug
                throw std::invalid_argument("Invalid ending syntax");*/

            Vector3D<Color> colors = Vector3D<Color>(x_color, y_color, z_color);
            Vector3D<int> coordonates =
                Vector3D<int>(x_coord, y_coord, z_coord);
            Piece new_piece = Piece(coordonates, colors);

            new_cube.set_piece(new_piece, counter_cube);
            counter_cube++;
        }

        return new_cube;
    }

    Piece Cube::find_piece(Vector3D<int> coords) const
    {
        size_t index = 0;
        while (index != this->pieces_.size() - 1)
        {
            if (this->pieces_[index].coords.x == coords.x)
            {
                if (this->pieces_[index].coords.y == coords.y)
                {
                    if (this->pieces_[index].coords.z == coords.z)
                    {
                        return this->pieces_[index];
                    }
                }
            }

            index += 1;
        }

        throw std::invalid_argument("Piece from coords not found");
    }

    Piece Cube::find_piece(Vector3D<Color> colors) const
    {
        Vector3D<Color> perm1 = Vector3D<Color>(colors.x, colors.y, colors.z);
        Vector3D<Color> perm2 = Vector3D<Color>(colors.x, colors.z, colors.y);
        Vector3D<Color> perm3 = Vector3D<Color>(colors.y, colors.x, colors.z);
        Vector3D<Color> perm4 = Vector3D<Color>(colors.y, colors.z, colors.x);
        Vector3D<Color> perm5 = Vector3D<Color>(colors.z, colors.x, colors.y);
        Vector3D<Color> perm6 = Vector3D<Color>(colors.z, colors.y, colors.x);
        size_t index = 0;
        while (index != this->pieces_.size())
        {
            Vector3D<Color> current = this->pieces_[index].colors;
            if (current.x == perm1.x && current.y == perm1.y
                && current.z == perm1.z)
                return this->pieces_[index];

            if (current.x == perm2.x && current.y == perm2.y
                && current.z == perm2.z)
                return this->pieces_[index];

            if (current.x == perm3.x && current.y == perm3.y
                && current.z == perm3.z)
                return this->pieces_[index];

            if (current.x == perm4.x && current.y == perm4.y
                && current.z == perm4.z)
                return this->pieces_[index];

            if (current.x == perm5.x && current.y == perm5.y
                && current.z == perm5.z)
                return this->pieces_[index];

            if (current.x == perm6.x && current.y == perm6.y
                && current.z == perm6.z)
                return this->pieces_[index];

            index += 1;
        }

        throw std::invalid_argument("Piece from colors not found");
    }

    void Cube::do_move(Move move)
    {
        int type = move.mvt.index();
        if (type == 0) // face
        {
            switch (std::get<Face>(move.mvt))
            {
            case Face::UP: // z == 1
            {
                for (size_t i = 0; i < this->pieces_.size(); i++)
                {
                    if (this->pieces_[i].coords.z == 1)
                    {
                        this->pieces_[i].do_move(std::get<Face>(move.mvt),
                                                 move.dir);
                        if (move.is_double)
                            this->pieces_[i].do_move(std::get<Face>(move.mvt),
                                                     move.dir);
                    }
                }
                break;
            }
            case Face::DOWN: // z == -1
            {
                for (size_t i = 0; i < this->pieces_.size(); i++)
                {
                    if (this->pieces_[i].coords.z == -1)
                    {
                        this->pieces_[i].do_move(std::get<Face>(move.mvt),
                                                 move.dir);
                        if (move.is_double)
                            this->pieces_[i].do_move(std::get<Face>(move.mvt),
                                                     move.dir);
                    }
                }
                break;
            }
            case Face::LEFT: // y == -1
            {
                for (size_t i = 0; i < this->pieces_.size(); i++)
                {
                    if (this->pieces_[i].coords.y == -1)
                    {
                        this->pieces_[i].do_move(std::get<Face>(move.mvt),
                                                 move.dir);
                        if (move.is_double)
                            this->pieces_[i].do_move(std::get<Face>(move.mvt),
                                                     move.dir);
                    }
                }
                break;
            }
            case Face::RIGHT: // y == 1
            {
                for (size_t i = 0; i < this->pieces_.size(); i++)
                {
                    if (this->pieces_[i].coords.y == 1)
                    {
                        this->pieces_[i].do_move(std::get<Face>(move.mvt),
                                                 move.dir);
                        if (move.is_double)
                            this->pieces_[i].do_move(std::get<Face>(move.mvt),
                                                     move.dir);
                    }
                }
                break;
            }
            case Face::FRONT: // x == 1
            {
                for (size_t i = 0; i < this->pieces_.size(); i++)
                {
                    if (this->pieces_[i].coords.x == 1)
                    {
                        this->pieces_[i].do_move(std::get<Face>(move.mvt),
                                                 move.dir);
                        if (move.is_double)
                            this->pieces_[i].do_move(std::get<Face>(move.mvt),
                                                     move.dir);
                    }
                }
                break;
            }
            case Face::BACK: // x == -1
            {
                for (size_t i = 0; i < this->pieces_.size(); i++)
                {
                    if (this->pieces_[i].coords.x == -1)
                    {
                        this->pieces_[i].do_move(std::get<Face>(move.mvt),
                                                 move.dir);
                        if (move.is_double)
                            this->pieces_[i].do_move(std::get<Face>(move.mvt),
                                                     move.dir);
                    }
                }
                break;
            }
            }
        }

        else // axis
        {
            for (size_t i = 0; i < this->pieces_.size(); i++)
            {
                this->pieces_[i].do_move(std::get<Axis>(move.mvt), move.dir);
                if (move.is_double)
                    this->pieces_[i].do_move(std::get<Axis>(move.mvt),
                                             move.dir);
            }
        }
    }

    void Cube::do_moves(std::vector<Move> moves)
    {
        for (size_t i = 0; i < moves.size(); i++)
        {
            this->do_move(moves[i]);
        }
    }

    void Cube::undo_move(Move move)
    {
        if (move.dir == Direction::CLOCKWISE)
            move.dir = Direction::ANTI_CLOCKWISE;
        else
            move.dir = Direction::CLOCKWISE;

        this->do_move(move);
    }

    void Cube::undo_moves(std::vector<Move> moves)
    {
        for (int i = moves.size() - 1; i >= 0; i--)
        {
            this->undo_move(moves[i]);
        }
    }

} // namespace rubik
