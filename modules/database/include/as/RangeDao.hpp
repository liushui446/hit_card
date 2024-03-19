#ifndef AS_RANGEDAO_HPP
#define AS_RANGEDAO_HPP

#include <as/RangeCore.hpp>
using std::shared_ptr;
using std::string;
using std::make_shared;

namespace as
{
	class AS_EXPORTS RangeBaseDao
	{
	public:
		RangeBaseDao() = default;
		virtual ~RangeBaseDao() = default;

		//增加
		virtual bool Create(const shared_ptr<RangeBase> val) = 0;
		//更改
		virtual bool Update(const shared_ptr<RangeBase> val) = 0;
		//删除
		virtual bool Delete(const shared_ptr<RangeBase> val) = 0;

	protected:
		//查询
		virtual shared_ptr<RangeBase> Get(const string& item) = 0;
		virtual shared_ptr<RangeData> Getall() = 0;
	};

	class AS_EXPORTS RangeAcceptMarkDao
		: virtual public RangeBaseDao
	{
	public:
		virtual ~RangeAcceptMarkDao() = default;

		virtual shared_ptr<RangeAcceptMark> GetItem(const string& item) = 0;
		virtual shared_ptr<RangeData> Getall() = 0;
	};

	class AS_EXPORTS XYLimitSystemDao
		: virtual public RangeBaseDao
	{
	public:
		virtual ~XYLimitSystemDao() = default;

		virtual shared_ptr<XYLimitSystem> GetItem(const string& item) = 0;
		virtual shared_ptr<RangeData> Getall() = 0;
	};

	class AS_EXPORTS RangeArrayPcbDao
		: virtual public RangeBaseDao
	{
	public:
		virtual ~RangeArrayPcbDao() = default;

		virtual shared_ptr<RangeArrayPcb> GetItem(const string& item) = 0;
		virtual shared_ptr<RangeData> Getall() = 0;
	};

	class AS_EXPORTS RangeBadMarkDao
		: virtual public RangeBaseDao
	{
	public:
		virtual ~RangeBadMarkDao() = default;

		virtual shared_ptr<RangeBadMark> GetItem(const string& item) = 0;
		virtual shared_ptr<RangeData> Getall() = 0;
	};

	class AS_EXPORTS RangeBoradSizeDao
		: virtual public RangeBaseDao
	{
	public:
		virtual ~RangeBoradSizeDao() = default;

		virtual shared_ptr<RangeBoradSize> GetItem(const string& item) = 0;
		virtual shared_ptr<RangeData> Getall() = 0;
	};

	class AS_EXPORTS RangeBlockPcbDao
		: virtual public RangeBaseDao
	{
	public:
		virtual ~RangeBlockPcbDao() = default;

		virtual shared_ptr<RangeBlockPcb> GetItem(const string& item) = 0;
		virtual shared_ptr<RangeData> Getall() = 0;
	};
}
#endif
