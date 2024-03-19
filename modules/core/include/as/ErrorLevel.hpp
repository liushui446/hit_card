#ifndef AS_ERRORLEVEL_HPP
#define AS_ERRORLEVEL_HPP

#include "as/CommonCore.hpp"

namespace as
{
	class AS_EXPORTS ErrorLevel
	{
	public:
		ErrorLevel() = default;
		ErrorLevel(const int& cLevel, const string& Define);

		~ErrorLevel() = default;

		int getLevel();
		string getDefine();
		string getENGDefine();

		void setLevel(const int& cLevel);
		void setDefine(const string& Define);
		void setENGDefine(const string& ENGDefine);
	private:
		int m_clevel;
		string m_define;
		string m_engdefine;
	};
}

#endif // !SMARTSM_ERRORLEVELCORE_HPP
