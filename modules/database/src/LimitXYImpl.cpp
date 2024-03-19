#include "as/LimitXYImpl.hpp"
#include "as/LogManager.hpp"
#include "as/DBUtils.hpp"

namespace as
{
	vector<RangeBase> LimitXYImpl::vec_xy = {};

	map<RangeTab, RangeBase> LimitXYImpl::GetLimit()
	{
		map<RangeTab, RangeBase> xy;
		string sql;
		char* cErrMsg = NULL;
		MechDBUtils::Getinstance().getConnection();
		sql = fmt::format("select * from MECH_XYLIMIT_PARAM;");
		try
		{
			int res = sqlite3_exec(MechDBUtils::Getinstance().getsqlite(), sql.c_str(), LimitResult, 0, NULL);
			if (res != SQLITE_OK) {
				SoftwareLogfunc::GetInstance().DatabaseWarn("ป๚ะต", "XYZR_LIMIT", cErrMsg == NULL ? "NULL" : cErrMsg, __LINE__);
				MechDBUtils::Getinstance().free();
				throw nullptr;
			}
		}
		catch (...)
		{
			MechDBUtils::Getinstance().free();
			throw nullptr;
		}
		for (size_t i = 0; i < vec_xy.size(); i++)
		{
			xy.insert(pair<RangeTab, RangeBase>(RangeTab((int)RangeTab::XY_LIMIT_X + i), vec_xy.at(i)));
		}
		return xy;
	}

	int LimitXYImpl::LimitResult(void* NotUsed, int argc, char** argv, char** azColName)
	{
		map<string, char*> limitmap;
		XYLimitSystem limitSystem;
		for (int i = 0; i < argc; i++) {
			limitmap[azColName[i]] = argv[i];
		}
		limitSystem.setItem(limitmap["Item"]);
		limitSystem.setMinvalue(atof(limitmap["MinValue"]));
		limitSystem.setMaxvalue(atof(limitmap["MaxValue"]));
		limitSystem.setDefaultvalue(atof(limitmap["DefaultValue"]));
		vec_xy.push_back(limitSystem);
		return NULL;
	}
	
	bool LimitXYImpl::UpdateLimitXYRZ(shared_ptr<RangeBase> limitval)
	{
		string sql;
		char* cErrMsg = NULL;
		MechDBUtils::Getinstance().getConnection();
		try
		{
			sql = fmt::format("update MECH_XYLIMIT_PARAM set MinValue = {},MaxValue = {},DefaultValue = {} WHERE Item = '{}';",
				limitval->getMinvalue(),
				limitval->getMaxvalue(),
				limitval->getDefaultvalue(),
				limitval->getItem()
			);
			int res = sqlite3_exec(MechDBUtils::Getinstance().getsqlite(), sql.c_str(), 0, 0, &cErrMsg);
			if (res != SQLITE_OK) {
				SoftwareLogfunc::GetInstance().DatabaseWarn("ป๚ะต", "XYZR_LIMIT", "ERRORINFO", __LINE__);
				MechDBUtils::Getinstance().free();
				return false;
			}
		}
		catch (...)
		{
			MechDBUtils::Getinstance().free();
			throw false;
		}
		MechDBUtils::Getinstance().free();
		return true;
	}
}