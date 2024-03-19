#include "as/MessageImpl.hpp"
#include "as/LogManager.hpp"
#include "as/sqlite3.hpp"
#include <Windows.h>
#include "as/MessageCore.hpp"

using namespace std;

namespace as
{
	shared_ptr<Message> MessageImpl::get_res = nullptr;
	shared_ptr<vector<Message>> MessageImpl::get_resList = nullptr;

	/*extern string shortTox16(const int& val);*/
	extern std::string Dataunitoutf8(string data);
	extern std::string Datautftoun(string data);

	MessageImpl::MessageImpl()
	{
	}

	bool MessageImpl::Create(const shared_ptr<Message> val)
	{
		char* cErrMsg = NULL;
		string sql;
		MessageDBUtils::Getinstance().getConnection();
		sql = fmt::format("insert into Message(CODE, ENG, CHS, IsCheck) values('{}', '{}', '{}','{}');"
			, val->getCodex16()
			, val->getEng()
			, Dataunitoutf8(val->getChs())
			, val->getIsUse()
		);
		int res = sqlite3_exec(MessageDBUtils::Getinstance().getsqlite(), sql.c_str(), 0, 0, &cErrMsg);
		if (res != SQLITE_OK)
		{
			MessageDBUtils::Getinstance().free();
			return false;
		}
		MessageDBUtils::Getinstance().free();
		return true;
	}

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

	shared_ptr<Message> MessageImpl::Get(const int& code)
	{
		get_res = make_shared<Message>();

		char* cErrMsg = NULL;
		string sql;
		MessageDBUtils::Getinstance().getConnection();
		sql = fmt::format("select * from Message where CODE = '{}';", shortTox16(code));
		try
		{
			int res = sqlite3_exec(MessageDBUtils::Getinstance().getsqlite(), sql.c_str(), GetCallBack, 0, &cErrMsg);
			if (res != SQLITE_OK)
			{
				MessageDBUtils::Getinstance().free();
				return nullptr;
			}
		}
		catch (...)
		{
			MessageDBUtils::Getinstance().free();
			return nullptr;
		}
		MessageDBUtils::Getinstance().free();
		return get_res;
	}

	//查询整个表
	shared_ptr<vector<Message>> MessageImpl::GetList()
	{
		get_resList = make_shared<vector<Message>>();

		char* cErrMsg = NULL;
		string sql;
		sql = fmt::format("select * from Message");
		MessageDBUtils::Getinstance().getConnection();
		try
		{
			int res = sqlite3_exec(MessageDBUtils::Getinstance().getsqlite(), sql.c_str(), GetCallBackList, 0, &cErrMsg);
			if (res != SQLITE_OK)
			{
				MessageDBUtils::Getinstance().free();
				return nullptr;
			}
		}
		catch (...)
		{
			MessageDBUtils::Getinstance().free();
			return nullptr;
		}
		MessageDBUtils::Getinstance().free();
		return get_resList;
	}

	bool MessageImpl::Update(const shared_ptr<Message> val)
	{
		char* cErrMsg = NULL;
		string sql;
		MessageDBUtils::Getinstance().getConnection();
		sql = fmt::format("update Message set ENG = '{}', CHS = '{}', IsCheck = '{}' where CODE = '{}';"
			, val->getEng()
			, Dataunitoutf8(val->getChs())
			, static_cast<int>(val->getIsUse())
			, val->getCodex16()
		);

		int res = sqlite3_exec(MessageDBUtils::Getinstance().getsqlite(), sql.c_str(), 0, 0, &cErrMsg);
		if (res != SQLITE_OK)
		{
			MessageDBUtils::Getinstance().free();
			return false;
		}
		MessageDBUtils::Getinstance().free();
		return true;
	}

	bool MessageImpl::Delete(const shared_ptr<Message> val)
	{
		char* cErrMsg = NULL;
		string sql;
		MessageDBUtils::Getinstance().getConnection();
		sql = fmt::format("delete from Message where CODE = '{}';", val->getCodex16());
		int res = sqlite3_exec(MessageDBUtils::Getinstance().getsqlite(), sql.c_str(), 0, 0, &cErrMsg);
		if (res != SQLITE_OK)
		{
			MessageDBUtils::Getinstance().free();
			return false;
		}
		MessageDBUtils::Getinstance().free();
		return true;
	}

	int MessageImpl::GetCallBack(void* NotUsed, int argc, char** argv, char** azColName)
	{
		map<string, string> callback_res;
		for (size_t i = 0; i < argc; i++)
		{
			if (argv[i] == NULL)
				callback_res[azColName[i]] = "";
			else
				callback_res[azColName[i]] = argv[i];
		}

		get_res->setCode(std::stoi(callback_res["CODE"], 0, 16));	//16进制
		get_res->setEng(callback_res["ENG"]);
		string test = Datautftoun(callback_res["CHS"]);
		get_res->setChs(test);
		get_res->setIsUse(stoi(callback_res["IsCheck"]));
		string sol = Datautftoun(callback_res["Solution"]);
		get_res->setSol(sol);
		string Engsol = Datautftoun(callback_res["ENGSolution"]);
		get_res->setENGSol(Engsol);
		return 0;
	}

	int MessageImpl::GetCallBackList(void* NotUsed, int argc, char** argv, char** azColName)
	{
		map<string, string> callback_res;
		for (size_t i = 0; i < argc; i++)
		{
			if (argv[i] == NULL)
				callback_res[azColName[i]] = "";
			else
				callback_res[azColName[i]] = argv[i];
		}
		Message temp;
		temp.setCode(std::stoi(callback_res["CODE"], 0, 16));	//16进制
		temp.setEng(callback_res["ENG"]);
		string test = Datautftoun(callback_res["CHS"]);
		temp.setChs(test);
		temp.setIsUse(std::stoi(callback_res["IsCheck"]));
		get_resList->push_back(temp);

		return 0;
	}

	string ws2s(wstring& ws)
	{
		std::string curLocale = setlocale(LC_ALL, NULL);
		setlocale(LC_ALL, "chs");
		const wchar_t* _Source = ws.c_str();
		size_t  _Dsize = 2 * ws.size() + 1;
		char* _Dest = new char[_Dsize];
		memset(_Dest, 0, _Dsize);
		wcstombs(_Dest, _Source, _Dsize);

		string result = _Dest;
		delete[]_Dest;
		setlocale(LC_ALL, curLocale.c_str());
		return result;
	}

	std::wstring s2ws(const std::string& s)
	{
		setlocale(LC_ALL, "chs");
		const char* _Source = s.c_str();
		size_t _Dsize = s.size() + 1;
		wchar_t* _Dest = new wchar_t[_Dsize];
		wmemset(_Dest, 0, _Dsize);
		mbstowcs(_Dest, _Source, _Dsize);
		std::wstring result = _Dest;
		delete[]_Dest;
		setlocale(LC_ALL, "C");
		return result;
	}

	size_t Utf8ToUnicodeLength(const string& utf8)
	{
		size_t wchars = 0;

		size_t utf8Len = utf8.length();
		size_t utf8Pos = 0;
		while (utf8Pos < utf8Len)
		{
			unsigned char utf8Ch = utf8[utf8Pos];

			// 1111 110X, 10XX XXXX, 10XX XXXX, 10XX XXXX, 10XX XXXX, 10XX XXXX
			// 1111 10XX, 10XX XXXX, 10XX XXXX, 10XX XXXX, 10XX XXXX
			// 1111 0XXX, 10XX XXXX, 10XX XXXX, 10XX XXXX 
			if (0xF0 <= utf8Ch)
			{
				return 0; // 需要UCS-4，未处理
			}
			// 1110 XXXX, 10XX XXXX, 10XX XXXX
			else if (0xE0 <= utf8Ch && utf8Ch < 0xF0)
			{
				utf8Pos += 3;
				wchars += 1;
			}
			// 110X XXXX, 10XX XXXX
			else if (0xC0 <= utf8Ch && utf8Ch < 0xE0)
			{
				utf8Pos += 2;
				wchars += 1;
			}
			// 10XX XXXX 
			else if (0x80 <= utf8Ch && utf8Ch < 0xC0)
			{
				return 0; // 非法情况，Utf8首字节不存在该种编码
			}
			// 0XXX XXXX
			else
			{
				utf8Pos += 1;
				wchars += 1;
			}
		}

		return wchars;
	}

	void Utf8ToUnicode(wstring& unicode, const string& utf8)
	{
		size_t wcLen = Utf8ToUnicodeLength(utf8) + 1;
		if (1 < wcLen)
		{
			unicode.resize(wcLen);

			size_t utf8Pos = 0;
			size_t unicodePos = 0;

			size_t utf8Len = utf8.length();
			while (utf8Pos < utf8Len)
			{
				unsigned short utfCh0 = utf8[utf8Pos + 0] & 0xFF;

				// 1111 110X, 10XX XXXX, 10XX XXXX, 10XX XXXX, 10XX XXXX, 10XX XXXX
				// 1111 10XX, 10XX XXXX, 10XX XXXX, 10XX XXXX, 10XX XXXX
				// 1111 0XXX, 10XX XXXX, 10XX XXXX, 10XX XXXX 
				if (0xF0 <= utfCh0)
				{
					break; // 需要UCS-4，未处理
				}
				// 1110 XXXX, 10XX XXXX, 10XX XXXX
				else if (0xE0 <= utfCh0 && utfCh0 < 0xF0)
				{
					unsigned short utfCh1 = utf8[utf8Pos + 1] & 0xFF;
					unsigned short utfCh2 = utf8[utf8Pos + 2] & 0xFF;
					unicode[unicodePos] = ((((utfCh0 << 4) & 0xF0) + ((utfCh1 >> 2) & 0x0F)) << 8) + (((utfCh1 << 6) & 0xC0) + (utfCh2 & 0x3F));

					utf8Pos += 3;
					unicodePos += 1;
				}
				// 110X XXXX, 10XX XXXX
				else if (0xC0 <= utfCh0 && utfCh0 < 0xE0)
				{
					unsigned short utfCh1 = utf8[utf8Pos + 1] & 0xFF;
					unicode[unicodePos] = (((utfCh0 >> 2) & 0x07) << 8) + ((utfCh0 << 6) & 0xC0 + utfCh1 & 0x3F);

					utf8Pos += 2;
					unicodePos += 1;
				}
				// 10XX XXXX 
				else if (0x80 <= utfCh0 && utfCh0 < 0xC0)
				{
					break; // 非法情况，Utf8首字节不存在该种编码
				}
				// 0XXX XXXX
				else
				{
					unicode[unicodePos] = utfCh0;

					utf8Pos += 1;
					unicodePos += 1;
				}
			}

			unicode[unicodePos] = 0;
		}
	}

	std::string Unicode2Utf8(std::wstring& widestring)
	{
		using namespace std;
		int utf8size = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, NULL, 0, NULL, NULL);
		if (utf8size == 0)
		{
			throw std::exception("Error in conversion.");
		}
		std::vector<char> resultstring(utf8size);
		int convresult = ::WideCharToMultiByte(CP_UTF8, 0, widestring.c_str(), -1, &resultstring[0], utf8size, NULL, NULL);
		if (convresult != utf8size)
		{
			throw std::exception("La falla!");
		}
		return std::string(&resultstring[0]);
	}

	std::string Datautftoun(string data)
	{
		wstring wstr2;
		Utf8ToUnicode(wstr2, data);
		string str3;
		str3 = ws2s(wstr2);
		return str3;
	}

	std::string Dataunitoutf8(string data)
	{
		wstring wstr2 = s2ws(data);

		string str3 = Unicode2Utf8(wstr2);

		return str3;
	}
}