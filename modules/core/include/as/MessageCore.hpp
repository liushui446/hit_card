#ifndef AS_MESSAGECORE_HPP
#define AS_MESSAGECORE_HPP

#include "as/CommonCore.hpp"

namespace as
{
	class AS_EXPORTS Message
	{
	public:
		Message() = default;
		Message(const int& CODE, const string& ENG, const string& CHS, const bool& ISUSE);
		~Message() = default;

		const int& getCode() const;
		const string getCodex16() const;
		const string& getEng() const;
		const string& getChs() const;
		const bool& getIsUse() const;
		const string& getSol() const;

		void setCode(const int& code);
		void setEng(const string& eng);
		void setChs(const string& chs);
		void setIsUse(const bool& isuse);
		void setSol(const string& sol);
		void setENGSol(const string& engsol);

	private:
		int m_code;
		string m_eng;
		string m_chs;
		string m_sol;
		string m_engsol;
		bool m_IsUse;
	};


	class AS_EXPORTS ProductData
	{
	public:

		const string& getTime() const;
		const string& getData() const;
		const string& getURL() const;
		void setTime(const string& time);
		void setData(const string& data);
		void setURL(const string& url);
	private:
		string time;
		string data;
		string url;
	};
};
#endif
