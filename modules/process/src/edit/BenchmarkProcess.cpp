#include "as/edit/BenchmarkProcess.hpp"

namespace as
{
	BenchMarkProcess::BenchMarkProcess()
	{
		m_pBaseboard_data = *ASContext::GetInstance().GetBaseBoard();
	}

	//����mark������
	void BenchMarkProcess::Update()
	{
		m_pBaseboard_data.UpdateMarkCalFlag();
		*ASContext::GetInstance().GetBaseBoard() = m_pBaseboard_data;
	}
}