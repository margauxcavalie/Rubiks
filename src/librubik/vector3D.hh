#pragma once

#include <iostream>

namespace rubik
{
    template <typename T>
    class Vector3D
    {
    public:
        Vector3D(T x, T y, T z)
            : x(x)
            , y(y)
            , z(z)
        {}

        inline bool operator==(const Vector3D& other)
        {
            if (this->x == other.x && this->y == other.y && this->z == other.z)
                return true;
            return false;
        }

        inline bool operator!=(const Vector3D& other)
        {
            if (this->x == other.x && this->y == other.y && this->z == other.z)
                return false;
            return true;
        }

        T x;
        T y;
        T z;
    };

    template <typename T>
    inline std::ostream& operator<<(std::ostream& os, const Vector3D<T>& v)
    {
        return os << '(' << v.x << ',' << v.y << ',' << v.z << ')';
    }

} // namespace rubik
