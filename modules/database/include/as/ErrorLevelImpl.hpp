#ifndef AS_ERRORLEVELIMPL_HPP
#define AS_ERRORLEVELIMPL_HPP

#include "as/ErrorLevelDao.hpp"

using std::string;
using std::shared_ptr;
using std::make_shared;

namespace as
{
	class AS_EXPORTS ErrorLevelImpl:virtual public ErrorLevelDao
	{
	public:
		ErrorLevelImpl();
		virtual ~ErrorLevelImpl() = default;

		//增加
		virtual bool Create(shared_ptr<ErrorLevel> val) override;
		//查询
		virtual shared_ptr<ErrorLevel> Get(const int& cLevel) override;
		//更改
		virtual bool Update(const shared_ptr<ErrorLevel> val) override;
		//删除
		virtual bool Delete(const shared_ptr<ErrorLevel> val) override;

	private:
		static int GetCallBack(void* NotUsed, int argc, char** argv, char** azColName);

		static shared_ptr<ErrorLevel> get_res;
	};
}

#endif // !SMARTSM_ERRORLEVELIMPL_HPP
