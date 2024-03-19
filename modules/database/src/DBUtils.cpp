#include"as/DBUtils.hpp"
#include <fstream>
#include <mutex>
#include <deque>
#include <map>
#include <vector>
#include <chrono>
#include <thread>

namespace as
{
	std::string DataBasePath::CompoPath = "";
	std::string DataBasePath::MechPath = "";
	std::string DataBasePath::AuthorityPath = "";
	std::string DataBasePath::MessagePath = "";
	std::string DataBasePath::RangePath = "";

	//不同数据库路径的获取
	void DataBasePath::GetDataBasePath()
	{
		std::string path;

		if ((path = getcwd(NULL, 0)) == "")
			path = "..//...//";
		else
		{
			int slow_ptr = 0, fast_ptr = path.find("\\");
			while (fast_ptr < path.size())
			{
				slow_ptr = fast_ptr;
				while (fast_ptr < path.size() && path[fast_ptr++] != '\\');

				std::string sub = path.substr(slow_ptr, fast_ptr - slow_ptr - 1);
				if (sub == "build")
					break;
			}
			path = path.substr(0, slow_ptr - 1);
		}
		//CompoPath = path + "\\modules\\database\\src\\db\\ComponentDB.db";
		CompoPath = path + "\\modules\\database\\src\\db\\component_test.db";
		MechPath = path + "\\modules\\database\\src\\db\\MechDB.db";
		AuthorityPath = path + "\\modules\\database\\src\\db\\Authority.db";
		MessagePath = path + "\\modules\\database\\src\\db\\MessageDB.db";
		RangePath = path + "\\modules\\database\\src\\db\\RangeDB.db";
	}

	//连接数据库并打开
	bool CompoDBUtils::getConnection()
	{
		int nRes = sqlite3_open(DataBasePath::CompoPath.c_str(), &pDB1);
		if (nRes != SQLITE_OK) {
			std::cout << "open databases fail";
			return false;
		}
		return true;
	}

	//关闭数据库
	void CompoDBUtils::free() {
		if (pDB1 != NULL) {
			sqlite3_close(pDB1);
		}
	}
	
	sqlite3* as::CompoDBUtils::getsqlite() {
		return pDB1;
	}

	sqlite3_stmt* as::CompoDBUtils::getsqlite_stmt() {
		return stmt;
	}
	
	//数据库连接通信单例
	CompoDBUtils& CompoDBUtils::Getinstance()
	{
		static CompoDBUtils m_cCompoDBUtils;
		return m_cCompoDBUtils;
	}

	bool AuthorityDBUtils::getConnection()
	{
		int nRes = sqlite3_open(DataBasePath::AuthorityPath.c_str(), &pDB1);
		if (nRes != SQLITE_OK) {
			std::cout << "open databases fail";
			return false;
		}
		return true;
	}

	void AuthorityDBUtils::free()
	{
		if (pDB1 != NULL) {
			sqlite3_close(pDB1);
		}
	}

	sqlite3* AuthorityDBUtils::getsqlite()
	{
		return pDB1;
	}

	AuthorityDBUtils& AuthorityDBUtils::Getinstance()
	{
		static AuthorityDBUtils m_cAuthorityDBUtils;
		return m_cAuthorityDBUtils;
	}

	bool MessageDBUtils::getConnection()
	{
		int nRes = sqlite3_open(DataBasePath::MessagePath.c_str(), &pDB1);
		if (nRes != SQLITE_OK) {
			std::cout << "open databases fail";
			return false;
		}
		return true;
	}

	void MessageDBUtils::free()
	{
		if (pDB1 != NULL) {
			sqlite3_close(pDB1);
		}
	}

	sqlite3* MessageDBUtils::getsqlite()
	{
		return pDB1;
	}

	MessageDBUtils& MessageDBUtils::Getinstance()
	{
		static MessageDBUtils m_cMessageDBUtils;
		return m_cMessageDBUtils;
	}

	bool MechDBUtils::getConnection()
	{
		int nRes = sqlite3_open(DataBasePath::MechPath.c_str(), &pDB1);
		if (nRes != SQLITE_OK) {
			std::cout << "open databases fail";
			return false;
		}
		return true;
	}

	void MechDBUtils::free()
	{
		if (pDB1 != NULL) {
			sqlite3_close(pDB1);
		}
	}

	sqlite3* MechDBUtils::getsqlite()
	{
		return pDB1;
	}

	MechDBUtils& MechDBUtils::Getinstance()
	{
		static MechDBUtils m_cMechDBUtils;
		return m_cMechDBUtils;
	}

	bool RangeDBUtils::getConnection()
	{
		int nRes = sqlite3_open(DataBasePath::RangePath.c_str(), &pDB1);
		if (nRes != SQLITE_OK) {
			std::cout << "open databases fail";
			return false;
		}
		return true;
	}

	void RangeDBUtils::free()
	{
		if (pDB1 != NULL) {
			sqlite3_close(pDB1);
		}
	}

	sqlite3* RangeDBUtils::getsqlite()
	{
		return pDB1;
	}

	RangeDBUtils& RangeDBUtils::Getinstance()
	{
		static RangeDBUtils m_cMechDBUtils;
		return m_cMechDBUtils;
	}
}