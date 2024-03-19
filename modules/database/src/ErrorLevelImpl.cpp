#include "as/ErrorLevelImpl.hpp"

namespace as
{
	shared_ptr<ErrorLevel> ErrorLevelImpl::get_res = nullptr;

	extern std::string Dataunitoutf8(string data);
	extern std::string Datautftoun(string data);

	ErrorLevelImpl::ErrorLevelImpl()
	{
	}

	bool ErrorLevelImpl::Create(shared_ptr<ErrorLevel> val)
	{
		char* cErrMsg = NULL;
		string sql;
		MessageDBUtils::Getinstance().getConnection();
		sql = fmt::format("insert into ErrorLevel(cLevel, Define) values('{}', '{}');", Dataunitoutf8(val->getDefine()), val->getLevel());
		int res = sqlite3_exec(MessageDBUtils::Getinstance().getsqlite(), sql.c_str(), 0, 0, &cErrMsg);
		if (res != SQLITE_OK)
		{
			MessageDBUtils::Getinstance().free();
			return false;
		}
		MessageDBUtils::Getinstance().free();
		return true;
	}

	shared_ptr<ErrorLevel> ErrorLevelImpl::Get(const int& cLevel)
	{
		get_res = make_shared<ErrorLevel>();

		char* cErrMsg = NULL;
		string sql;
		MessageDBUtils::Getinstance().getConnection();
		sql = fmt::format("select * from ErrorLevel where cLevel = '{}';", std::to_string(cLevel));
		try
		{
			int res = sqlite3_exec(MessageDBUtils::Getinstance().getsqlite(), sql.c_str(), GetCallBack, 0, &cErrMsg);
			if (res != SQLITE_OK)
			{
				MessageDBUtils::Getinstance().free();
				throw nullptr;
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

	bool ErrorLevelImpl::Update(const shared_ptr<ErrorLevel> val)
	{
		char* cErrMsg = NULL;
		string sql;
		MessageDBUtils::Getinstance().getConnection();
		sql = fmt::format("update ErrorLevel set Define = '{}' where cLevel = '{}';", Dataunitoutf8(val->getDefine()), val->getLevel());

		int res = sqlite3_exec(MessageDBUtils::Getinstance().getsqlite(), sql.c_str(), 0, 0, &cErrMsg);
		if (res != SQLITE_OK)
		{
			MessageDBUtils::Getinstance().free();
			return false;
		}
		MessageDBUtils::Getinstance().free();
		return true;
	}

	bool ErrorLevelImpl::Delete(const shared_ptr<ErrorLevel> val)
	{
		char* cErrMsg = NULL;
		string sql;
		MessageDBUtils::Getinstance().getConnection();
		sql = fmt::format("delete from ErrorLevel where cLevel = '{}';", val->getLevel());

		int res = sqlite3_exec(MessageDBUtils::Getinstance().getsqlite(), sql.c_str(), 0, 0, &cErrMsg);
		if (res != SQLITE_OK)
		{
			MessageDBUtils::Getinstance().free();
			return false;
		}
		MessageDBUtils::Getinstance().free();
		return true;
	}

	int ErrorLevelImpl::GetCallBack(void* NotUsed, int argc, char** argv, char** azColName)
	{
		map<string, string> callback_res;
		for (size_t i = 0; i < argc; i++)
		{
			callback_res[azColName[i]] = argv[i];
		}

		get_res->setLevel(std::stoi(callback_res["cLevel"]));
		get_res->setDefine(Datautftoun(callback_res["Define"]));
		get_res->setENGDefine(Datautftoun(callback_res["ENGDefine"]));
		return 0;
	}

}