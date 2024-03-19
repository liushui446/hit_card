#ifndef AS_RANGECORE_HPP 
#define AS_RANGECORE_HPP

#include "as/CommonCore.hpp"

namespace as
{
	enum class RangeTab
	{
		XY_LIMIT_X = 0x3700,
		XY_LIMIT_Y,

		ACCEPT_MARK_X_RNG = 0x0000,
		ACCEPT_MARK_Y_RNG,

		ARRAY_PCB_NUMX_RNG = 0x0200,
		ARRAY_PCB_NUMY_RNG,
		ARRAY_PCB_OFFSETX_RNG,
		ARRAY_PCB_OFFSETY_RNG,
		ARRAY_PCB_SKIP_NUM,
		ARRAY_PCB_ADD_X,
		ARRAY_PCB_ADD_Y,
		ARRAY_PCB_ADD_R,

		BAD_MARK_OFFSETX_RNG = 0x0300,
		BAD_MARK_OFFSETY_RNG,
		BAD_MARK_LIGHT,
		BAD_MARK_CONTRAST,

		BLOCK_PCB_NUMX_RNG = 0x0400,
		BLOCK_PCB_NUMY_RNG,
		BLOCK_PCB_OFFSETX_RNG,
		BLOCK_PCB_OFFSETY_RNG,

		BORAD_SIZE_PCB_LONG = 0x0500,
		BORAD_SIZE_PCB_WIDE,
		BORAD_SIZE_ORIGINX,
		BORAD_SIZE_ORIGINY,

		FIDUCIAL_VISION_ARM_RNG = 0x1500,
		FIDUCIAL_VISION_GAP_RNG,
		FIDUCIAL_VISION_SCORE_RNG,
		FIDUCIAL_VISION_SEARCHWIDTHX_RNG,
		FIDUCIAL_VISION_SEARCHWIDTHY_RNG,
		FIDUCIAL_VISION_SEARCHX_RNG,
		FIDUCIAL_VISION_SEARCHY_RNG,
		FIDUCIAL_VISION_SIZEX_RNG,
		FIDUCIAL_VISION_SIZEY_RNG,
		FIDUCIAL_VISION_THICKNESS_RNG,
	};

	class AS_EXPORTS RangeBase
	{
	public:
		RangeBase() = default;
		RangeBase(string item, int define, double minvalue, double maxvalue, double defaultvalue, string eng);
		virtual ~RangeBase();

		inline const string& getItem() const;
		inline void setItem(const string & val);
		inline const int getDefine() const;
		inline void setDefine(const int val);
		inline const double getMinvalue() const;
		inline void setMinvalue(const double val);
		inline const double getMaxvalue() const;
		inline void setMaxvalue(const double val);
		inline const double getDefaultvalue() const;
		inline void setDefaultvalue(const double val);
		inline const string& getEng() const;
		inline void setEng(const string& val);
	private:
		string m_item;
		int m_define;
		double m_minvalue;
		double m_maxvalue;
		double m_defaultvalue;
		string m_eng;
	};

	class AS_EXPORTS RangeData
	{
	public:
		const map<RangeTab, RangeBase>& getRangeData() const;
		const RangeBase& getRangeBase(RangeTab tab) const;
		void setRangeData(const map<RangeTab, RangeBase>& temp);
		void setRangeData(const RangeTab& tab, const RangeBase& temp);
		static RangeData& GetInstance();
	private:
		map<RangeTab, RangeBase> rangedata;
	};

	class AS_EXPORTS XYLimitSystem : public RangeBase
	{
	public:
		XYLimitSystem::XYLimitSystem();
		XYLimitSystem(string item, int define, double minvalue, double maxvalue, double defaultvalue, string eng);
		virtual ~XYLimitSystem() = default;
	private:
	};

	class AS_EXPORTS RangeAcceptMark : public RangeBase
	{
	public:
		RangeAcceptMark() = default;
		RangeAcceptMark(string item, int define, double minvalue, double maxvalue, double defaultvalue, string eng);
		virtual ~RangeAcceptMark() = default;
	};

	class AS_EXPORTS RangeArrayPcb : public RangeBase
	{
	public:
		RangeArrayPcb() = default;
		RangeArrayPcb(string item, int define, double minvalue, double maxvalue, double defaultvalue, string eng);
		virtual ~RangeArrayPcb() = default;
	};

	class AS_EXPORTS RangeBlockPcb : public RangeBase
	{
	public:
		RangeBlockPcb() = default;
		RangeBlockPcb(string item, int define, double minvalue, double maxvalue, double defaultvalue, string eng);
		virtual ~RangeBlockPcb() = default;
	};

	class AS_EXPORTS RangeBadMark : public RangeBase
	{
	public:
		RangeBadMark() = default;
		RangeBadMark(string item, int define, double minvalue, double maxvalue, double defaultvalue, string eng);
		virtual ~RangeBadMark() = default;
	};

	class AS_EXPORTS RangeBoradSize : public RangeBase
	{
	public:
		RangeBoradSize() = default;
		RangeBoradSize(string item, int define, double minvalue, double maxvalue, double defaultvalue, string eng);
		virtual ~RangeBoradSize() = default;
	};

	class AS_EXPORTS RangeFiducialVision : public RangeBase
	{
	public:
		RangeFiducialVision() = default;
		RangeFiducialVision(string item, int define, double minvalue, double maxvalue, double defaultvalue, string eng);
		virtual ~RangeFiducialVision() = default;
	};
}
#endif
