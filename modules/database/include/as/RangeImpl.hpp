#ifndef AOI_RANGEIMPL_HPP
#define AOI_RANGEIMPL_HPP

#include <aoi/RangeDao.hpp>
#include "score.hpp"
using std::string;
using std::shared_ptr;
using std::make_shared;

namespace aoi
{
	const string XYLimit_tabname = "XYZR_LIMIT";
	const string accept_mark_tabname = "ACCEPT_MARK";
	const string array_pcb_tabname = "ARRAY_PCB";
	const string bad_mark_tabname = "BAD_MARK";
	const string block_pcb_tabname = "BLOCK_PCB";
	const string borad_size_tabname = "BORAD_SIZE";


	class AOI_EXPORTS RangeBaseImpl
		:virtual public RangeBaseDao
	{
	public:
		RangeBaseImpl(const string& tablename, const aoi::RangeTab& tab);
		virtual ~RangeBaseImpl() = default;

		//增加
		virtual bool Create(const shared_ptr<aoi::RangeBase> val) override;
		//查询
		virtual shared_ptr<aoi::RangeBase> Get(const string& item) override;
		virtual shared_ptr<aoi::RangeData> Getall() override;
		//更改
		virtual bool Update(const shared_ptr<aoi::RangeBase> val) override;
		//删除
		virtual bool Delete(const shared_ptr<aoi::RangeBase> val) override;

	private:
		static int GetCallBack(void* NotUsed, int argc, char** argv, char** azColName);
		static int allBack(void* NotUsed, int argc, char** argv, char** azColName);

		static shared_ptr<aoi::RangeBase> get_res;
		static shared_ptr<aoi::RangeData> alldata;
		static vector<aoi::RangeBase> range_temp;

		string m_tablename;
		aoi::RangeTab m_tab;
	};

	class AOI_EXPORTS RangeAcceptMarkImpl
		: virtual public RangeAcceptMarkDao
		, virtual public RangeBaseImpl
	{
	public:
		RangeAcceptMarkImpl();
		virtual ~RangeAcceptMarkImpl() = default;

		virtual shared_ptr<aoi::RangeAcceptMark> GetItem(const string& item) override;
		virtual shared_ptr<aoi::RangeData> Getall() override;
	};

	class AOI_EXPORTS RangeArrayPcbImpl
		: virtual public RangeArrayPcbDao
		, virtual public RangeBaseImpl
	{
	public:
		RangeArrayPcbImpl();
		virtual ~RangeArrayPcbImpl() = default;

		virtual shared_ptr<RangeArrayPcb> GetItem(const string& item) override;
		virtual shared_ptr<aoi::RangeData> Getall() override;
	};

	class AOI_EXPORTS XYLimitSystemImpl
		: virtual public XYLimitSystemDao
		, virtual public RangeBaseImpl
	{
	public:
		XYLimitSystemImpl();
		virtual ~XYLimitSystemImpl() = default;

		virtual shared_ptr<XYLimitSystem> GetItem(const string& item) override;
		virtual shared_ptr<aoi::RangeData> Getall() override;
	};

	class AOI_EXPORTS RangeBadMarkImpl
		: virtual public RangeBadMarkDao
		, virtual public RangeBaseImpl
	{
	public:
		RangeBadMarkImpl();
		virtual ~RangeBadMarkImpl() = default;

		virtual shared_ptr<RangeBadMark> GetItem(const string& item) override;
		virtual shared_ptr<RangeData> Getall() override;
	};

	class AOI_EXPORTS RangeBoradSizeImpl
		: virtual public RangeBoradSizeDao
		, virtual public RangeBaseImpl
	{
	public:
		RangeBoradSizeImpl();
		virtual ~RangeBoradSizeImpl() = default;

		virtual shared_ptr<RangeBoradSize> GetItem(const string& item) override;
		virtual shared_ptr<RangeData> Getall() override;
	};

	class AOI_EXPORTS RangeBlockPcbImpl
		: virtual public RangeBlockPcbDao
		, virtual public RangeBaseImpl
	{
	public:
		RangeBlockPcbImpl();
		virtual ~RangeBlockPcbImpl() = default;

		virtual shared_ptr<RangeBlockPcb> GetItem(const string& item) override;
		virtual shared_ptr<RangeData> Getall() override;
	};
}
#endif