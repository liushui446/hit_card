#ifndef _LUMEN_DEF_HPP_
#define _LUMEN_DEF_HPP_

#include "as/core/def.h"

namespace as
{
    struct AS_EXPORTS LumenData
	{
		double blue_avg;
		double green_avg;
		double red_avg;

		double blue_minVal;
		double blue_maxVal;
		double green_minVal;

		double green_maxVal;
		double red_minVal;
		double red_maxVal;

		LumenData() : 
			blue_avg(0),
			green_avg(0),
			red_avg(0),
			blue_minVal(0),
			blue_maxVal(0),
			green_minVal(0),
			green_maxVal(0),
			red_minVal(0),
			red_maxVal(0)
		{};
	};

	struct AS_EXPORTS IlluminateData
	{
		double blue;
		double green;
		double red;
		double white;

		IlluminateData()
			: blue(30)
			, green(30)
			, red(30)
			, white(0)
		{
		};
	};
}

#endif