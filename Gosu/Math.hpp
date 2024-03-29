//! \file Math.hpp
//! Contains simple math functionality.

#ifndef GOSU_MATH_HPP
#define GOSU_MATH_HPP

namespace Gosu
{
    //! Pi.
    const double pi = 3.1415926536;

    //! Truncates the fractional part of a real value. Equivalent to
    //! static_cast<long>.
    inline long trunc(double value)
    {
        return static_cast<long>(value);
    }

    //! Rounds a real value towards the next integer.
    inline long round(double value)
    {
        if (value >= 0)
            return static_cast<long>(value + 0.5);
        else
            return static_cast<long>(value - 0.5);
    }

    //! Returns a real value between min and max. Uses std::rand (so you have
    //! to call std::srand before using it).
    double random(double min, double max);

    //! Returns the horizontal distance between the origin and the point to
    //! which you would get if you moved radius pixels in the direction
    //! specified by angle.
    //! \param angle Angle in degrees where 0.0 means upwards.
    double offsetX(double angle, double radius);
    //! Returns the vertical distance between the origin and the point to
    //! which you would get if you moved radius pixels in the direction
    //! specified by angle.
    //! \param angle Angle in degrees where 0.0 means upwards.
    double offsetY(double angle, double radius);
    //! Returns the angle between two points in degrees, where 0.0 means
    //! upwards. Returns def if both points are equal.
    double angle(double fromX, double fromY, double toX, double toY,
        double def = 0);
    //! Returns the smallest positive angle between two angles.
    double angleDiff(double angle1, double angle2);
    //! Normalizes an angle to fit into the range [0; 360[.
    double normalizeAngle(double angle);

    //! Returns value * value.
    template<typename T>
    T square(T value)
    {
        return value * value;
    }

    //! Returns min if value is smaller than min, max if value is larger than
    //! max and value otherwise.
    template<typename T>
    T boundBy(T value, T min, T max)
    {
        if (value < min)
            return min;
        if (value > max)
            return max;
        return value;
    }

    //! Returns the square of the distance between two points.
    inline double distanceSqr(double x1, double y1, double x2, double y2)
    {
        return square(x1 - x2) + square(y1 - y2);
    }

    //! Returns the distance between two points.
    double distance(double x1, double y1, double x2, double y2);
}

#endif
