#ifndef AS_MESSAGEDAO_HPP
#define AS_MESSAGEDAO_HPP

#include "as/MessageCore.hpp"
#include "as/DBUtils.hpp"
#include "as/score.hpp"

namespace as
{
	class AS_EXPORTS MessageDao
	{
	public:
		MessageDao() = default;
		virtual ~MessageDao() = default;

		//增加
		virtual bool Create(const shared_ptr<Message> val) = 0;
		//查询
		virtual shared_ptr<Message> Get(const int& cLevel) = 0;
		//查询
		virtual shared_ptr<vector<Message>> GetList() = 0;
		//更改
		virtual bool Update(const shared_ptr<Message> val) = 0;
		//删除
		virtual bool Delete(const shared_ptr<Message> val) = 0;

	protected:
		as::MechDBUtils* db;
	};

};

#endif // !SMARTSM_MESSAGEDAO_HPP
