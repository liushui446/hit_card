#include <as/Rangelmpl.hpp>
#include <as/sqlite3.hpp>
#include <as/DBUtils.hpp>
#include <Windows.h>
using namespace std;

namespace as
{
	shared_ptr<RangeBase> RangeBaseImpl::get_res = nullptr;

	shared_ptr<RangeData> RangeBaseImpl::alldata = make_shared<RangeData>();
	vector<RangeBase> RangeBaseImpl::range_temp;

	RangeBaseImpl::RangeBaseImpl(const string& tablename, const RangeTab& tab)
		: m_tablename(tablename)
		, m_tab(tab)
	{
	}

	bool RangeBaseImpl::Create(const shared_ptr<RangeBase> val)
	{
		char* cErrMsg;
		string sql;

		sql = fmt::format("insert into {} values('{}', {}, {}, {}, {}, '{}');"
			, m_tablename
			, val->getItem()
			, val->getDefine()
			, val->getMinvalue()
			, val->getMaxvalue()
			, val->getDefaultvalue()
			, val->getEng()
		);

		int res = sqlite3_exec(as::RangeDBUtils::Getinstance().getsqlite(), sql.c_str(), 0, 0, &cErrMsg);
		if (res != SQLITE_OK)
		{
			cout << "insert fail" << cErrMsg << endl;
			return false;
		}

		return true;
	}

	shared_ptr<RangeBase> RangeBaseImpl::Get(const string& item)
	{
		get_res = make_shared<RangeBase>();
		char* cErrMsg;
		string sql;

		sql = fmt::format("select * from {} where Item = '{}';", m_tablename, item);

		int res = sqlite3_exec(as::RangeDBUtils::Getinstance().getsqlite(), sql.c_str(), GetCallBack, 0, &cErrMsg);
		if (res != SQLITE_OK)
		{
			cout << "select fail" << cErrMsg << endl;
			return nullptr;
		}
		return get_res;
	}

	shared_ptr<RangeData> RangeBaseImpl::Getall()
	{
		get_res = make_shared<RangeBase>();
		range_temp.clear();

		char* cErrMsg;
		string sql;
		as::RangeDBUtils::Getinstance().getConnection();
		sql = fmt::format("select * from {};", m_tablename);
		try
		{
			int res = sqlite3_exec(as::RangeDBUtils::Getinstance().getsqlite(), sql.c_str(), allBack, 0, &cErrMsg);
			if (res != SQLITE_OK)
			{
				cout << "select fail" << cErrMsg << endl;
				throw nullptr;
			}
		}
		catch (...)
		{
			throw false;
		}

		for (size_t i = 0; i < range_temp.size(); i++)
		{
			alldata->setRangeData(static_cast<RangeTab>(static_cast<int>(m_tab) + i), range_temp.at(i));
		}

		return alldata;
	}

	bool RangeBaseImpl::Update(const shared_ptr<RangeBase> val)
	{
		char* cErrMsg;
		string sql;

		sql = fmt::format("update {} set Define = {},MinValue = {},MaxValue = {},DefaultValue = {},ENG = '{}' WHERE Item = '{}';"
			, m_tablename
			, val->getDefine()
			, val->getMinvalue()
			, val->getMaxvalue()
			, val->getDefaultvalue()
			, val->getEng()
			, val->getItem()
		);

		int res = sqlite3_exec(as::RangeDBUtils::Getinstance().getsqlite(), sql.c_str(), 0, 0, &cErrMsg);
		if (res != SQLITE_OK)
		{
			cout << "update fail" << cErrMsg << endl;
			return false;
		}

		return true;
	}

	bool RangeBaseImpl::Delete(const shared_ptr<RangeBase> val)
	{
		char* cErrMsg;
		string sql;

		sql = fmt::format("delete from {} where Item  = '{}';", m_tablename, val->getItem());

		int res = sqlite3_exec(as::RangeDBUtils::Getinstance().getsqlite(), sql.c_str(), 0, 0, &cErrMsg);
		if (res != SQLITE_OK)
		{
			cout << "delete fail" << cErrMsg << endl;
			return false;
		}

		return true;
	}

	int RangeBaseImpl::GetCallBack(void* NotUsed, int argc, char** argv, char** azColName)
	{
		map<string, string> callback_res;
		for (size_t i = 0; i < argc; i++)
		{
			callback_res[azColName[i]] = argv[i];
		}

		get_res->setItem(callback_res["Item"]);
		get_res->setDefine(std::stoi(callback_res["Define"]));
		get_res->setMinvalue(stod(callback_res["MinValue"]));
		get_res->setMaxvalue(stod(callback_res["MaxValue"]));
		get_res->setDefaultvalue(stod(callback_res["DefaultValue"]));
		get_res->setEng(callback_res["ENG"]);

		return 0;
	}

	int RangeBaseImpl::allBack(void* NotUsed, int argc, char** argv, char** azColName)
	{
		map<string, string> callback_res;
		for (size_t i = 0; i < argc; i++)
		{
			callback_res[azColName[i]] = argv[i];
		}

		get_res->setItem(callback_res["Item"]);
		get_res->setDefine(std::stoi(callback_res["Define"]));
		get_res->setMinvalue(stod(callback_res["MinValue"]));
		get_res->setMaxvalue(stod(callback_res["MaxValue"]));
		get_res->setDefaultvalue(stod(callback_res["DefaultValue"]));
		get_res->setEng(callback_res["ENG"]);

		range_temp.push_back(*get_res);

		return 0;
	}

	RangeAcceptMarkImpl::RangeAcceptMarkImpl()
		:RangeBaseImpl(accept_mark_tabname, RangeTab::ACCEPT_MARK_X_RNG)
	{
	}

	shared_ptr<as::RangeAcceptMark> RangeAcceptMarkImpl::GetItem(const string& item)
	{
		return std::static_pointer_cast<RangeAcceptMark>(this->RangeBaseImpl::Get(item));
	}

	shared_ptr<as::RangeData> RangeAcceptMarkImpl::Getall()
	{
		return this->RangeBaseImpl::Getall();
	}

	RangeArrayPcbImpl::RangeArrayPcbImpl()
		: RangeBaseImpl(array_pcb_tabname, RangeTab::ARRAY_PCB_NUMX_RNG)
	{
	}

	shared_ptr<RangeArrayPcb> RangeArrayPcbImpl::GetItem(const string& item)
	{
		return std::static_pointer_cast<RangeArrayPcb>(this->RangeBaseImpl::Get(item));
	}

	shared_ptr<RangeData> RangeArrayPcbImpl::Getall()
	{
		return this->RangeBaseImpl::Getall();
	}

	RangeBadMarkImpl::RangeBadMarkImpl()
		: RangeBaseImpl(bad_mark_tabname, RangeTab::BAD_MARK_OFFSETX_RNG)
	{
	}

	shared_ptr<RangeBadMark> RangeBadMarkImpl::GetItem(const string& item)
	{
		return std::static_pointer_cast<RangeBadMark>(this->RangeBaseImpl::Get(item));
	}

	shared_ptr<RangeData> RangeBadMarkImpl::Getall()
	{
		return this->RangeBaseImpl::Getall();
	}

	RangeBoradSizeImpl::RangeBoradSizeImpl()
		: RangeBaseImpl(borad_size_tabname, RangeTab::BORAD_SIZE_PCB_LONG)
	{
	}

	XYLimitSystemImpl::XYLimitSystemImpl()
		: RangeBaseImpl(XYLimit_tabname, RangeTab::XY_LIMIT_X)
	{
	}

	shared_ptr<XYLimitSystem> XYLimitSystemImpl::GetItem(const string& item)
	{
		return std::static_pointer_cast<XYLimitSystem>(this->RangeBaseImpl::Get(item));
	}

	shared_ptr<RangeData> XYLimitSystemImpl::Getall()
	{
		return this->RangeBaseImpl::Getall();
	}

	shared_ptr<RangeBoradSize> RangeBoradSizeImpl::GetItem(const string& item)
	{
		return std::static_pointer_cast<RangeBoradSize>(this->RangeBaseImpl::Get(item));
	}

	shared_ptr<RangeData> RangeBoradSizeImpl::Getall()
	{
		return this->RangeBaseImpl::Getall();
	}

	RangeBlockPcbImpl::RangeBlockPcbImpl()
		: RangeBaseImpl(block_pcb_tabname, RangeTab::BLOCK_PCB_NUMX_RNG)
	{
	}

	shared_ptr<RangeBlockPcb> RangeBlockPcbImpl::GetItem(const string& item)
	{
		return std::static_pointer_cast<RangeBlockPcb>(this->RangeBaseImpl::Get(item));
	}

	shared_ptr<RangeData> RangeBlockPcbImpl::Getall()
	{
		return this->RangeBaseImpl::Getall();
	}
}