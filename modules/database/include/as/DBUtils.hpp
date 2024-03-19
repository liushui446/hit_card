#ifndef AS_COMDBUTILS_HPP
#define AS_COMDBUTILS_HPP
#include "as/sqlite3.hpp"
#include <iostream>
#include <string>
#include <direct.h>
#include "as/core/def.h"
#include <memory>

using std::shared_ptr;
using std::string;

namespace as
{
	//数据库路径类
	class AS_EXPORTS DataBasePath
	{
	public:
		static void GetDataBasePath();
		static std::string CompoPath;
		static std::string MechPath;
		static std::string AuthorityPath;
		static std::string MessagePath;
		static std::string RangePath;
	};

	//声明元件模板数据库功能类
	class AS_EXPORTS CompoDBUtils
	{
	public:
		bool getConnection();
		void free();
		sqlite3* getsqlite();
		sqlite3_stmt* getsqlite_stmt();
		static CompoDBUtils& Getinstance();
	private:
		sqlite3* pDB1 = NULL;//声明一个数据库
		sqlite3_stmt* stmt = NULL;
	};

	//权限数据库
	class AS_EXPORTS AuthorityDBUtils
	{
	public:
		bool getConnection();
		void free();
		sqlite3* getsqlite();
		static AuthorityDBUtils& Getinstance();
	private:
		sqlite3* pDB1 = NULL;//声明一个数据库
	};

	//消息数据库
	class AS_EXPORTS MessageDBUtils
	{
	public:
		bool getConnection();
		void free();
		sqlite3* getsqlite();
		static MessageDBUtils& Getinstance();
	private:
		sqlite3* pDB1 = NULL;//声明一个数据库
	};

	//机械数据库
	class AS_EXPORTS MechDBUtils
	{
	public:
		bool getConnection();
		void free();
		sqlite3* getsqlite();
		static MechDBUtils& Getinstance();
	private:
		sqlite3* pDB1 = NULL;//声明一个数据库
	};

	//Range数据库
	class AS_EXPORTS RangeDBUtils
	{
	public:
		bool getConnection();
		void free();
		sqlite3* getsqlite();
		static RangeDBUtils& Getinstance();
	private:
		sqlite3* pDB1 = NULL;//声明一个数据库
	};
}

#endif