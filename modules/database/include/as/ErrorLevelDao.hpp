#ifndef AS_ERRORLEVELDAO_HPP
#define AS_ERRORLEVELDAO_HPP

#include "as/DBUtils.hpp"
#include "as/ErrorLevel.hpp"
#include "score.hpp"

namespace as
{
	class AS_EXPORTS ErrorLevelDao
	{
	public:
		ErrorLevelDao() = default;
		virtual ~ErrorLevelDao() = default;

		//增加
		virtual bool Create(shared_ptr<ErrorLevel> val) = 0;
		//查询
		virtual shared_ptr<ErrorLevel> Get(const int& cLevel) = 0;
		//更改
		virtual bool Update(const shared_ptr<ErrorLevel> val) = 0;
		//删除
		virtual bool Delete(const shared_ptr<ErrorLevel> val) = 0;

	protected:
		as::AuthorityDBUtils* db;
	};
};

#endif // !SMARTSM_ERRORLEVELDAO_HPP
