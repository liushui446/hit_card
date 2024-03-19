#include <as/ErrorLevel.hpp>

namespace as
{
	ErrorLevel::ErrorLevel(const int& cLevel, const string& Define)
		:m_clevel(cLevel),
		m_define(Define)
	{
	}

	int ErrorLevel::getLevel() 
	{
		return m_clevel;
	}

	string ErrorLevel::getDefine()
	{
		return m_define;
	}

	string ErrorLevel::getENGDefine()
	{
		return m_engdefine;
	}

	void ErrorLevel::setLevel(const int& cLevel)
	{
		m_clevel = cLevel;
	}

	void ErrorLevel::setDefine(const string& Define)
	{
		m_define = Define;
	}

	void ErrorLevel::setENGDefine(const string& ENGDefine)
	{
		m_engdefine = ENGDefine;
	}
}