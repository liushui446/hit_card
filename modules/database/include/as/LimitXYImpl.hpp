#ifndef AS_LIMITXYIMPL_HPP 
#define AS_LIMITXYIMPL_HPP

#include "as/RangeCore.hpp"
#include "score.hpp"

namespace as
{
	class AS_EXPORTS LimitXYImpl
	{
	public:
		map<RangeTab, RangeBase> GetLimit();
		bool UpdateLimitXYRZ(shared_ptr<RangeBase> limitval);
	private:
		static int LimitResult(void* NotUsed, int argc, char** argv, char** azColName);
		static vector<RangeBase> vec_xy;
	};
}

#endif
