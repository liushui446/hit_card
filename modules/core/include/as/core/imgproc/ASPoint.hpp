#ifndef _AS_POINT_H_
#define _AS_POINT_H_

#include <memory>
#include <vector>
#include "as/core/def.h"

namespace as
{
template <typename T>
struct  alignas(16) PointB {
	T x = 0;
	T y = 0;
	T z = 0;
	T m = 0; //modularity
	typedef T type;
	//EIGEN_MAKE_ALIGNED_OPERATOR_NEW
};

template <typename T>
struct PointXYZMRGB : public PointB<T> {
	uint8_t r = 255; //texture
	uint8_t g = 255;
	uint8_t b = 255;
};

template <typename T>
struct PointXYZMRGBH : public PointXYZMRGB<T> {
	T height = 0.0;
};

template <typename T>
struct PointXYZMRGBHL : public PointXYZMRGBH<T> {
	uint8_t label = 0;
};

using PointF = PointB<float>;
using PointD = PointB<double>;

using PointXYZMF = PointB<float>;
using PointXYZMD = PointB<double>;
using PointXYZMRGBHF = PointXYZMRGBH<float>;
using PointXYZMRGBHD = PointXYZMRGBH<double>;
using PointXYZMRGBHLF = PointXYZMRGBHL<float>;
using PointXYZMRGBHLD = PointXYZMRGBHL<double>;

const std::size_t kDefaultReservePointNum = 50000;
struct PointIndices {
	PointIndices() { indices.reserve(kDefaultReservePointNum); }

	std::vector<int> indices;

	typedef std::shared_ptr<PointIndices> Ptr;
	typedef std::shared_ptr<const PointIndices> ConstPtr;
};


template <typename T>
struct AS_EXPORTS Point2D {
	T x = 0;
	T y = 0;
};

using Point2DF = Point2D<float>;
using Point2DI = Point2D<int>;
using Point2DD = Point2D<double>;


template <typename T>
struct AS_EXPORTS Point3D {
	T x = 0;
	T y = 0;
	T z = 0;
};

using Point3DF = Point3D<float>;
using Point3DI = Point3D<int>;
using Point3DD = Point3D<double>;
}

#endif