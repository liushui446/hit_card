#ifndef AS_BENCHMARKPROCESS_HPP
#define AS_BENCHMARKPROCESS_HPP

#include "as/CommonCore.hpp"
#include "as/Common/UiCallback.h"
#include "as/ASContext.hpp"
#include "as/MarkCore.hpp"

namespace as
{
	struct BenchMarkData
	{
		WORD m_score;							// 分数
		WORD m_binary;							// 二值化阈值
		MarkLightPara m_MarkLightPara;			// 光源参数
		MarkData::FormData m_form_data;			// 形状数据
		MarkData::SearchArea m_search_area;		// 搜索范围
	};

	class AS_EXPORTS BenchMarkProcess
	{
	public:
		BenchMarkProcess::BenchMarkProcess();
		//更新mark点数据
		void Update();
		
	private:
		BaseBoard m_pBaseboard_data;
		MarkData m_pMarkData;
	};

}
#endif