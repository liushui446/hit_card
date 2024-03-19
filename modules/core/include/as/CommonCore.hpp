#ifndef AS_COMMONCORE_HPP
#define AS_COMMONCORE_HPP

#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <map>
#include <set>
#include <deque>
#include <algorithm>
#include <functional>
#include <filesystem>
#include <mutex>
#include <fstream>
#include <unordered_map>

#include "as/core/def.h"
#include "as/ErrorCode.hpp"
#include "as/core/Color.hpp"

using std::cout;
using std::endl;
using std::map;
using std::set;
using std::pair;
using std::deque;
using std::vector;
using std::string;
using std::to_string;
using std::shared_ptr;
using std::make_shared;
using std::unique_ptr;
using std::make_unique;
using std::for_each;
using std::mutex;
using std::function;
using std::condition_variable;
using std::ifstream;
using std::ofstream;
using std::thread;
using std::dynamic_pointer_cast;
using std::tuple;

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef double				DOUBLE;
typedef int                 INT;
typedef unsigned int        UINT;

#define	MARK_SUM (40)		// Mark点数

#define PI 3.1415926

namespace as
{
	class Point;
}

namespace boost
{
	namespace serialization
	{
		template <class Archive>
		void serialize(Archive& ar, as::Point& val, const unsigned int version);
	}
}

namespace as
{
	//Ref类型定义
	enum class RefDefType
	{
		R_1 = 0,    //一个字符类型
		CV_1 = 1,	//两个字符类型
		N_1 = 2     //纯数字
	};

	//mark点形状
	enum class LogicType
	{
		LOGIC_WHITE = 0,		// 白色
		LOGIC_BLACK				// 黑色    
	};

	//焊盘形状
	enum class PadShape
	{
		Rect = 1,		//正方形
		Circle = 2,		//圆形
		Oval = 3,	    //椭圆形
		Polygon = 4     //多边形
	};

	//AOI注册元件标准、生产的应用模式(检测模式)
	enum class DefectMode
	{
		SMTMode = 1,        //SMT检测模式
		WaveSolderMode = 2, //波峰焊检测模式
		HGMode = 3,         //红胶检测模式
		HASLMode = 4,       //喷锡板检测模式
		FurnaceFront = 5,   //炉前检测模式
	};

	// 坐标系统方向
	enum class CoordinateType
	{
		RIGHT_DOWN = 0,         // 右下方向
		LEFT_DOWN = 1,			// 左下方向
		RIGHT_UP = 2,			// 右上方向
		LEFT_UP = 3				// 左上方向
	};

	enum class CoordinateSystem
	{
		MechanicalCoorSystem = 0,	//机械坐标系
		PCBCoorSystem,				//标定坐标系
		MountOriginCoorSystem,		//贴装原点坐标
		BlockCoorSystem,			//块坐标系
		ArrayCoorSystem				//拼板坐标系
	};

	//站
	enum class Station
	{
		StationF1 = 0,       // 前轨道站1
		StationF2,
		StationF3,
		size
	};

	//轨道
	enum class Orbit
	{
		Orbit_FRONT = 1,
		Orbit_BEHIND,
	};

	class Point
	{
	public:
		//template <class Archive>
		//friend void boost::serialization::serialize(Archive& ar, Point& val, const unsigned int version);

		Point::Point() {
			x = 0;
			y = 0;
		};

		Point::Point(double _x, double _y) {
			x = _x;
			y = _y;
		};

		Point::Point(const Point& pt)
			: x(pt.x), y(pt.y) {}

		Point& Point::operator = (const Point& pt) {
			this->x = pt.x;
			this->y = pt.y;
			return *this;
		}

		Point Point::operator + (const Point& pt) {
			return Point(this->x + pt.x, this->y + pt.y);
		}

		Point& Point::operator += (const Point& pt) {
			this->x = this->x + pt.x;
			this->y = this->y + pt.y;
			return *this;
		}

		Point Point::operator - (const Point& pt) {
			return Point(this->x - pt.x, this->y - pt.y);
		}

		Point& Point::operator -= (const Point& pt) {
			this->x = this->x - pt.x;
			this->y = this->y - pt.y;
			return *this;
		}

		Point Point::operator * (const int val) {
			return Point(this->x * val, this->y * val);
		}

		Point& Point::operator *= (const int val) {
			this->x *= val;
			this->y *= val;
			return *this;
		}

		Point Point::operator / (const int val) {
			return Point(this->x / val, this->y / val);
		}

		Point& Point::operator /= (const int val) {
			this->x /= val;
			this->y /= val;
			return *this;
		}

		void Point::setPoint(double _x, double _y) {
			x = _x;
			y = _y;
		};

		void Point::setPointX(double _x)
		{
			x = _x;
		}

		void Point::setPointY(double _y)
		{
			y = _y;
		}

		void Point::setPoint(Point pos) {
			x = pos.x;
			y = pos.y;
		};

		bool Point::operator==(const Point p)
		{
			return x == p.x && y == p.y;
		}

		double Point::getPintX()
		{
			return x;
		}

		double Point::getPintY()
		{
			return y;
		}

		double x;
		double y;
	};
}
#endif