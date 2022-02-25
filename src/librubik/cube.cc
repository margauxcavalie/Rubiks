#include "cube.hh"

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

} // namespace rubik
