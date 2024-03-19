#ifndef AS_MESSAGEIMPL_HPP
#define AS_MESSAGEIMPL_HPP

#include "as/MessageDao.hpp"

using std::string;
using std::shared_ptr;
using std::make_shared;

namespace as
{
	class AS_EXPORTS MessageImpl:virtual public MessageDao

	{
	public:
		MessageImpl();
		virtual ~MessageImpl() = default;

		//增加
		virtual bool Create(const shared_ptr<Message> val) override;
		//查询
		virtual shared_ptr<Message> Get(const int& code) override;
		//查询整个表
		virtual shared_ptr<vector<Message>> GetList() override;
		//更改
		virtual bool Update(const shared_ptr<Message> val) override;
		//删除
		virtual bool Delete(const shared_ptr<Message> val) override;

	private:
		static int GetCallBack(void* NotUsed, int argc, char** argv, char** azColName);
		static int GetCallBackList(void* NotUsed, int argc, char** argv, char** azColName);

		static shared_ptr<Message> get_res;
		static shared_ptr<vector<Message>> get_resList;
	};
}

#endif // !SMARTSM_MESSAGEIMPL_HPP
