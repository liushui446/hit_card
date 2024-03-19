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
		WORD m_score;							// ����
		WORD m_binary;							// ��ֵ����ֵ
		MarkLightPara m_MarkLightPara;			// ��Դ����
		MarkData::FormData m_form_data;			// ��״����
		MarkData::SearchArea m_search_area;		// ������Χ
	};

	class AS_EXPORTS BenchMarkProcess
	{
	public:
		BenchMarkProcess::BenchMarkProcess();
		//����mark������
		void Update();
		
	private:
		BaseBoard m_pBaseboard_data;
		MarkData m_pMarkData;
	};

}
#endif