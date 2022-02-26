#pragma once

#include <array>

#include "vector3D.hh"

namespace rubik
{
    template <typename T>
    class Matrix3D
    {
    public:
        Matrix3D(std::array<std::array<T, 3>, 3> array)
            : matrix_(array)
        {}

        std::array<std::array<T, 3>, 3> get_matrix()
        {
            return this->matrix_;
        }

        T at(int i, int j)
        {
            return this->matrix_[i][j];
        }

        Vector3D<T> operator*(const Vector3D<T>& v) // matrix-vector product
        {
            int x_coord = this->matrix_[0][0] * v.x + this->matrix_[0][1] * v.y
                + this->matrix_[0][2] * v.z;
            int y_coord = this->matrix_[1][0] * v.x + this->matrix_[1][1] * v.y
                + this->matrix_[1][2] * v.z;
            int z_coord = this->matrix_[2][0] * v.x + this->matrix_[2][1] * v.y
                + this->matrix_[2][2] * v.z;
            return Vector3D<T>(x_coord, y_coord, z_coord);
        }

        void transpose() // flip the matrix over its diagonal
        {
            std::array<std::array<T, 3>, 3> tranposed;
            for (int i = 0; i < 3; i++)
            {
                for (int j = 0; j < 3; j++)
                {
                    tranposed[i][j] = this->matrix_[j][i];
                }
            }

            this->matrix_ = tranposed;
        }

    private:
        std::array<std::array<T, 3>, 3> matrix_;
    };

} // namespace rubik
