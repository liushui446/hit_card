#include "as/edit/BenchmarkProcess.hpp"

namespace as
{
	BenchMarkProcess::BenchMarkProcess()
	{
		m_pBaseboard_data = *ASContext::GetInstance().GetBaseBoard();
	}

	//更新mark点数据
	void BenchMarkProcess::Update()
	{
		m_pBaseboard_data.UpdateMarkCalFlag();
		*ASContext::GetInstance().GetBaseBoard() = m_pBaseboard_data;
	}
}