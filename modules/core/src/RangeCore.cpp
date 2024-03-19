#include "as/RangeCore.hpp"

namespace as
{
	RangeBase::RangeBase(string item, int define, double minvalue, double maxvalue, double defaultvalue, string eng)
		:m_item(item)
		, m_define(define)
		, m_minvalue(minvalue)
		, m_maxvalue(maxvalue)
		, m_defaultvalue(defaultvalue)
		, m_eng(eng)
	{
		
	}

	RangeBase::~RangeBase()
	{
	}

	XYLimitSystem::XYLimitSystem()
	{

	}

	const string& RangeBase::getItem() const
	{
		return m_item;
	}

	void RangeBase::setItem(const string& val)
	{
		m_item = val;
	}

	const int RangeBase::getDefine() const
	{
		return m_define;
	}

	void RangeBase::setDefine(const int val)
	{
		m_define = val;
	}

	const double RangeBase::getMinvalue() const
	{
		return m_minvalue;
	}

	void RangeBase::setMinvalue(const double val)
	{
		m_minvalue = val;
	}

	const double RangeBase::getMaxvalue() const
	{
		return m_maxvalue;
	}

	void RangeBase::setMaxvalue(const double val)
	{
		m_maxvalue = val;
	}

	const double RangeBase::getDefaultvalue() const
	{
		return m_defaultvalue;
	}

	void RangeBase::setDefaultvalue(const double val)
	{
		m_defaultvalue = val;
	}
	
	const string& RangeBase::getEng() const
	{
		return m_eng;
	}
	
	void RangeBase::setEng(const string& val)
	{
		m_eng = val;
	}

	const map<RangeTab, RangeBase>& RangeData::getRangeData() const
	{
		return rangedata;
	}

	const RangeBase& RangeData::getRangeBase(RangeTab tab) const
	{
		return rangedata.find(tab)->second;
	}

	void RangeData::setRangeData(const map<RangeTab, RangeBase>& temp)
	{
		rangedata = temp;
	}

	void RangeData::setRangeData(const RangeTab& tab, const RangeBase& temp)
	{
		if (rangedata.find(tab) == rangedata.end())
		{
			rangedata.insert(pair<RangeTab, RangeBase>(tab, temp));
		}
		else 
		{
			rangedata[tab] = temp;
		}

	}

	RangeData& RangeData::GetInstance()
	{
		static RangeData Rangedata_;
		return Rangedata_;
	}

	RangeAcceptMark::RangeAcceptMark(string item, int define, double minvalue, double maxvalue, double defaultvalue, string eng)
		:RangeBase(item, define, minvalue, maxvalue, defaultvalue, eng)
	{

	}

	XYLimitSystem::XYLimitSystem(string item, int define, double minvalue, double maxvalue, double defaultvalue, string eng)
		: RangeBase(item, define, minvalue, maxvalue, defaultvalue, eng)
	{

	}

	RangeArrayPcb::RangeArrayPcb(string item, int define, double minvalue, double maxvalue, double defaultvalue, string eng)
		: RangeBase(item, define, minvalue, maxvalue, defaultvalue, eng)
	{

	}

	RangeBlockPcb::RangeBlockPcb(string item, int define, double minvalue, double maxvalue, double defaultvalue, string eng)
		: RangeBase(item, define, minvalue, maxvalue, defaultvalue, eng)
	{

	}

	RangeBadMark::RangeBadMark(string item, int define, double minvalue, double maxvalue, double defaultvalue, string eng)
		: RangeBase(item, define, minvalue, maxvalue, defaultvalue, eng)
	{

	}

	RangeBoradSize::RangeBoradSize(string item, int define, double minvalue, double maxvalue, double defaultvalue, string eng)
		: RangeBase(item, define, minvalue, maxvalue, defaultvalue, eng)
	{

	}

	RangeFiducialVision::RangeFiducialVision(string item, int define, double minvalue, double maxvalue, double defaultvalue, string eng)
		: RangeBase(item, define, minvalue, maxvalue, defaultvalue, eng)
	{

	}
}