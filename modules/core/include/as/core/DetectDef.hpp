#ifndef _DETECT_DEF_HPP_
#define _DETECT_DEF_HPP_

#include "as/core/def.h"
#include "as/CommonCore.hpp"

namespace as
{
	/*********************************************
	 * 公用参数
	 *
	 */

	enum class AS_EXPORTS ERROR_LEVEL
	{
		NG,
		OK,
		WARNING
	};

	std::string AS_EXPORTS ErrorLevel2Name(ERROR_LEVEL _level);


	enum AS_EXPORTS DetectFlag
	{
		NotCollect = 0,		//未采集
		NotDetect = 1,		//未检测
		Detecting = 2,		//检测中
		DetectSucess = 3,	//检测成功
		DetectFail = 4		//检测失败
	};

	/// <summary>
	/// 搜索范围
	/// </summary>
	struct AS_EXPORTS SearchScope
	{
		double dX = 0;
		double dY = 0;
		double dAngle = 0;
	};

	/// <summary>
	/// 允许偏移
	/// </summary>
	struct AS_EXPORTS AllowOffset
	{
		double dOffsetX = 0;
		double dOffsetY = 0;
		double dAngle = 0;
	};

	// Up and down, left and right, east and west, north and south
	enum class AS_EXPORTS DIR
	{
		Up,
		Down,
		Left,
		Right,
		East = Right,
		West = Left,
		North = Up,
		South = Down
	};

	/*********************************************
	 * SPI检测参数
	 *
	 */

	enum class AS_EXPORTS SPI_Detect_Type
	{
		Volume,		// 体积
		Position,		// 位置
		Bridge,			// 连桥
		Height,			// 高度
		Shape,			// 形状
		Area,			// 面积
		Coplanarity // 共面性
	};

	// 检测项：体积；参数单位：百分比
	struct AS_EXPORTS SPI_VOLUME_PARAM
	{
		double ErrInstPct;	// 少锡错误阈值
		double WarnInstPct; // 少锡警告阈值,使用呢时应注意，Warning参数为相对Err参数的基础上进行加减得到,实际为ErrInst到ErrInst+WarnInst
		double ErrExcvPct;	// 多锡错误阈值
		double WarnExcvPct; // 多锡警告阈值,使用呢时应注意，Warning参数为相对Err参数的基础上进行加减得到,实际为ErrExcv到ErrExcv-WarnExcv
		bool Detect;		// 是否进行检测
		const SPI_Detect_Type Type;

		SPI_VOLUME_PARAM()
			: Type(SPI_Detect_Type::Volume)
		{
			ErrInstPct = 0.5;
			WarnInstPct = 0.2;
			ErrExcvPct = 1.7;
			WarnExcvPct = 0.2;
			Detect = false;
		}

		SPI_VOLUME_PARAM& operator=(SPI_VOLUME_PARAM& ref)
		{
			this->ErrInstPct = ref.ErrInstPct;
			this->WarnInstPct = ref.WarnInstPct;
			this->ErrExcvPct = ref.ErrExcvPct;
			this->WarnExcvPct = ref.WarnExcvPct;
			this->Detect = ref.Detect;
			return *this;
		}
	};

	// 检测项：位置偏移；参数单位：mm
	struct AS_EXPORTS SPI_POSITION_PARAM
	{
		double ErrX; // X方向偏移错误阈值
		double ErrY; // Y方向偏移错误阈值
		double Warn; // 预警量
		bool Detect; // 是否进行检测
		const SPI_Detect_Type Type;

		SPI_POSITION_PARAM()
			: Type(SPI_Detect_Type::Position)
		{
			ErrX = 0.5;
			ErrY = 0.5;
			Warn = 0.01;
			Detect = false;
		}

		SPI_POSITION_PARAM& operator=(SPI_POSITION_PARAM& ref)
		{
			this->ErrX = ref.ErrX;
			this->ErrY = ref.ErrY;
			this->Warn = ref.Warn;
			this->Detect = ref.Detect;
			return *this;
		}
	};

	// 检测项：连桥；参数单位：um
	struct AS_EXPORTS SPI_BRIDGE_PARAM
	{
		double ErrHeight;	// 高度错误阈值
		double ErrDist; // 距离错误阈值
		bool UpDetect;	// 上部检测
		bool DownDetect;// 下部检测
		bool LeftDetect;// 左侧检测
		bool RightDetect;// 右侧检测
		bool Detect;	// 是否进行检测
		const SPI_Detect_Type Type;

		SPI_BRIDGE_PARAM()
			: Type(SPI_Detect_Type::Bridge)
		{
			ErrHeight = 80;
			ErrDist = 300;
			UpDetect = true;
			DownDetect = true;
			LeftDetect = true;
			RightDetect = true;
			Detect = false;
		}

		SPI_BRIDGE_PARAM& operator=(SPI_BRIDGE_PARAM& ref)
		{
			this->ErrHeight = ref.ErrHeight;
			this->ErrDist = ref.ErrDist;
			this->UpDetect = ref.UpDetect;
			this->DownDetect = ref.DownDetect;
			this->LeftDetect = ref.LeftDetect;
			this->RightDetect = ref.RightDetect;
			this->Detect = ref.Detect;
			return *this;
		}
	};

	// 检测项：高度；参数单位：um
	struct AS_EXPORTS SPI_HEIGHT_PARAM
	{
		double ErrLowerH; // 高度下限错误阈值
		double ErrUpperH; // 高度上限错误阈值
		double WarnH;	  // 预警量
		bool Detect;	  // 是否进行检测
		const SPI_Detect_Type Type;

		SPI_HEIGHT_PARAM()
			: Type(SPI_Detect_Type::Height)
		{
			ErrLowerH = 50;
			ErrUpperH = 250;
			WarnH = 20;
			Detect = false;
		}

		SPI_HEIGHT_PARAM& operator=(SPI_HEIGHT_PARAM& ref)
		{
			this->ErrLowerH = ref.ErrLowerH;
			this->ErrUpperH = ref.ErrUpperH;
			this->WarnH = ref.WarnH;
			this->Detect = ref.Detect;
			return *this;
		}
	};

	// 检测项：形状；参数单位：um
	struct AS_EXPORTS SPI_SHAPE_PARAM
	{
		double Balance; // 容差阈值
		bool Detect;	// 是否进行检测
		const SPI_Detect_Type Type;

		SPI_SHAPE_PARAM()
			: Type(SPI_Detect_Type::Shape)
		{
			Balance = 180;
			Detect = false;
		}

		SPI_SHAPE_PARAM& operator=(SPI_SHAPE_PARAM& ref)
		{
			this->Balance = ref.Balance;
			this->Detect = ref.Detect;
			return *this;
		}
	};

	// 检测项：面积；参数单位：百分比
	struct AS_EXPORTS SPI_AREA_PARAM
	{
		double ErrMinAreaPct; // 最小面积百分比
		double ErrMaxAreaPct; // 最大面积百分比
		bool Detect;		  // 是否进行检测
		const SPI_Detect_Type Type;

		SPI_AREA_PARAM()
			: Type(SPI_Detect_Type::Area)
		{
			ErrMinAreaPct = 0.5;
			ErrMaxAreaPct = 2.0;
			Detect = false;
		}

		SPI_AREA_PARAM& operator=(SPI_AREA_PARAM& ref)
		{
			this->ErrMinAreaPct = ref.ErrMinAreaPct;
			this->ErrMaxAreaPct = ref.ErrMaxAreaPct;
			this->Detect = ref.Detect;
			return *this;
		}
	};

	// 检测项：共面性；参数单位：百分比
	struct AS_EXPORTS SPI_COPLANARITY_PARAM
	{
		double ErrVoluePct;
		double WarnVoluePct;
		double ErrOffsetNum;
		double WarnOffsetNum;
		double TopAreaPct;
		bool VolumeDetect;
		bool OffsetDetect;
		bool Detect;
		const SPI_Detect_Type Type;

		SPI_COPLANARITY_PARAM()
			: Type(SPI_Detect_Type::Coplanarity)
		{
			ErrVoluePct = 0.2;
			WarnVoluePct = 0.04;
			ErrOffsetNum = 10;
			WarnOffsetNum = 2;
			TopAreaPct = 0;
			VolumeDetect = true;
			OffsetDetect = true;
			Detect = false;
		}

		SPI_COPLANARITY_PARAM& operator=(SPI_COPLANARITY_PARAM& ref)
		{
			this->ErrVoluePct = ref.ErrVoluePct;
			this->WarnVoluePct = ref.WarnVoluePct;
			this->ErrOffsetNum = ref.ErrOffsetNum;
			this->WarnOffsetNum = ref.WarnOffsetNum;
			this->TopAreaPct = ref.TopAreaPct;
			this->VolumeDetect = ref.VolumeDetect;
			this->OffsetDetect = ref.OffsetDetect;
			this->Detect = ref.Detect;
			return *this;
		}
	};

	/*********************************************
	 * AOI检测参数
	 *
	 */

	/// <summary>
	/// 检测类型
	/// </summary>
	enum class AS_EXPORTS AOI_Detection_Type
	{
		BodyDot,
		Pad,
		PadDot,
		FreeDot,
		ReferDot,
	};

	/// <summary>
	/// 算法类型
	/// </summary>
	enum class AS_EXPORTS AOI_Algorithm_Type
	{
		TOC,
		Match,
		Histogram,
		OCV,
		Compare,
		Distance,
		Glue,
		Length,
		Padplace,
		PIN,
		Pole,
		Short,
		Match2,
		Other,
		ALOffset,
		Crest,
		Hole,
		Barcode,
	};

} // namespace as

#endif // _AS_CORE_DETECT_DEF_HPP_