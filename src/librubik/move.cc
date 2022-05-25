#include "move.hh"

#include <algorithm>
#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <vector>

namespace rubik
{
    std::vector<Move> parse_moves(std::string input)
    {
        input.erase(remove_if(input.begin(), input.end(), isspace),
                    input.end());
        std::vector<Move> moves_list;
        int counter = 0;
        while (input[counter])
        {
            Move new_move = Move();
            switch (input[counter])
            {
            case 'U':
                new_move.mvt = Face::UP;
                break;
            case 'D':
                new_move.mvt = Face::DOWN;
                break;
            case 'L':
                new_move.mvt = Face::LEFT;
                break;
            case 'R':
                new_move.mvt = Face::RIGHT;
                break;
            case 'F':
                new_move.mvt = Face::FRONT;
                break;
            case 'B':
                new_move.mvt = Face::BACK;
                break;
            case 'x':
                new_move.mvt = Axis::X;
                break;
            case 'y':
                new_move.mvt = Axis::Y;
                break;
            case 'z':
                new_move.mvt = Axis::Z;
                break;
            default:
                throw std::invalid_argument("Unallowed letter");
            }
            counter++;

            if (input[counter] && input[counter] == '2')
            {
                new_move.is_double = true;
                counter++;
            }
            else if (input[counter] && input[counter] == '\'')
            {
                new_move.dir = Direction::ANTI_CLOCKWISE;
                counter++;
            }

            moves_list.push_back(new_move);
        }

        return moves_list;
    }

} // namespace rubik
