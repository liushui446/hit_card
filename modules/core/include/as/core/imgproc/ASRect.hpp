#ifndef _AS_TYPE_H_
#define _AS_TYPE_H_

#include <string>
#include <sstream>
#include <limits>
#include <numeric>
#include <algorithm>
#include "as/core/imgproc/ASPoint.hpp"

namespace as
{
    template <typename T>
    class AS_EXPORTS Rect
    {
    public:
        Rect() : x(0), y(0), width(0), height(0)
        {
        }

        Rect(const T &x_in, const T &y_in, const T &width_in, const T &height_in)
            : x(x_in), y(y_in), width(width_in), height(height_in)
        {
        }

        Point2D<T> Center() const
        {
            Point2D<T> p;
            p.x = this->x + this->width / 2;
            p.y = this->y + this->height / 2;
            return p;
        }

        void SetCenter(Point2D<T> p)
        {
            this->x = p.x - this->width / 2;
            this->y = p.y - this->height / 2;
        }

        T Area() const
        {
            return this->width * this->height;
        }

        std::string ToStr() const
        {
            std::stringstream ss;
            ss << "[ " << width << " x " << height << " ] from ( " << x << " , " << y
               << " )";
            return ss.str();
        }

        friend Rect<T> operator&(const Rect<T> &rect1, const Rect<T> &rect2)
        {
            T r1_xmin = rect1.x;
            T r1_xmax = rect1.x + rect1.width;
            T r1_ymin = rect1.y;
            T r1_ymax = rect1.y + rect1.height;
            T r2_xmin = rect2.x;
            T r2_xmax = rect2.x + rect2.width;
            T r2_ymin = rect2.y;
            T r2_ymax = rect2.y + rect2.height;
            if (r2_xmin <= r1_xmax && r2_xmax >= r1_xmin && r2_ymin <= r1_ymax &&
                r2_ymax >= r1_ymin)
            {
                T xmin = std::max(r1_xmin, r2_xmin);
                T ymin = std::max(r1_ymin, r2_ymin);
                T xmax = std::min(r1_xmax, r2_xmax);
                T ymax = std::min(r1_ymax, r2_ymax);
                return Rect<T>(xmin, ymin, xmax - xmin, ymax - ymin);
            }
            else
            {
                return Rect<T>(0, 0, 0, 0);
            }
        }

        friend Rect<T> operator|(const Rect<T> &rect1, const Rect<T> &rect2)
        {
            Rect<T> ret;
            ret.x = std::min(rect1.x, rect2.x);
            ret.y = std::min(rect1.y, rect2.y);
            ret.width = std::max(rect1.x + rect1.width, rect2.x + rect2.width) - ret.x;
            ret.height =
                std::max(rect1.y + rect1.height, rect2.y + rect2.height) - ret.y;

            return ret;
        }

        friend inline bool operator==(const Rect &rect1, const Rect &rect2)
        {
            return (Equal(rect1.x, rect2.x) && Equal(rect1.y, rect2.y) &&
                    Equal(rect1.width, rect2.width) &&
                    Equal(rect1.height, rect2.height));
        }

        friend inline bool operator!=(const Rect &rect1, const Rect &rect2)
        {
            return !(rect1 == rect2);
        }

    public:
        T x = 0; // top-left
        T y = 0; // top-left
        T width = 0;
        T height = 0;
    };

    using RectI = Rect<int>;
    using RectD = Rect<double>;
}

#endif