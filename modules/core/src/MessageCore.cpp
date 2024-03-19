#include "as/MessageCore.hpp"

using std::string;
using std::make_shared;
using std::shared_ptr;

namespace as
{
	string shortTox16(const int& val)
	{
		char buff[10];
		memset(buff, 0, sizeof(buff));
		sprintf_s(buff, "%04X", val);

		return buff;
	}

	int x16ToShort(const string& val)
	{
		return std::stoi(val, 0, 16);
	}

	Message::Message(const int& CODE, const string& ENG, const string& CHS, const bool& ISUSE)
		:m_code(CODE)
		, m_eng(ENG)
		, m_chs(CHS)
		, m_IsUse(ISUSE)
	{
	}

	const int& Message::getCode() const
	{
		return m_code;
	}

	const string Message::getCodex16() const
	{
		return shortTox16(m_code);
	}

	const string& Message::getEng() const
	{
		return m_eng;
	}

	const string& Message::getChs() const
	{
		return m_chs;
	}

	const bool& Message::getIsUse() const
	{
		return m_IsUse;
	}

	const string& Message::getSol() const
	{
		return m_sol;
	}

	void Message::setCode(const int& code)
	{
		m_code = code;
	}

	void Message::setEng(const string& eng)
	{
		m_eng = eng;
	}

	void Message::setChs(const string& chs)
	{
		m_chs = chs;
	}

	void Message::setIsUse(const bool& isuse)
	{
		m_IsUse = isuse;
	}

	void Message::setSol(const string& sol)
	{
		m_sol = sol;
	}

	void Message::setENGSol(const string& engsol)
	{
		m_engsol = engsol;
	}

	const string& ProductData::getTime() const
	{
		return time;
	}

	void ProductData::setTime(const string& code)
	{
		time = code;
	}

	const string& ProductData::getData() const
	{
		return data;
	}

	void ProductData::setData(const string& code)
	{
		data = code;
	}
	const string& ProductData::getURL() const
	{
		return url;
	}

	void ProductData::setURL(const string& code)
	{
		url = code;
	}
}