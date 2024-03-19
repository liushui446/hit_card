#ifndef AS_MARKCORE_HPP
#define AS_MARKCORE_HPP

#include "as/core/def.h"
#include "as/CommonCore.hpp"
#include "as/ErrorCode.hpp"


namespace as
{
	class Mark;
	class MarkCom;
	class MarkData;
}
namespace boost
{
	namespace serialization
	{
		/*template <class Archive>
		extern void serialize(Archive& ar, as::FiducialMark& val, const unsigned int version);

		template <class Archive>
		extern void serialize(Archive& ar, as::Mark& val, const unsigned int version);

		template <class Archive>
		extern void serialize(Archive& ar, as::MarkData& val, const unsigned int version);

		template <class Archive>
		extern void serialize(Archive& ar, as::AcceptMark& val, const unsigned int version);

		template <class Archive>
		extern void serialize(Archive& ar, as::BadMark& val, const unsigned int version);*/
	}
}

namespace as {

	struct MarkPosList
	{
		int no;
		double x;
		double y;
		int id;
	};

	typedef struct
	{
		INT Inner;
		INT Outer;

	}MarkLightPara;
	
	enum class AS_EXPORTS MarkType {
		MARK_NONE = -1,		// 初始化参数
		MARK_CIRCLE = 0,        // 圆形
		MARK_DIAMOND,			// 钻石型
		MARK_RECTANGLE,			// 长方形
		MARK_RECTANGLE2,		// 长方形2
		MARK_TRIANGLE,			// 三角形
		MARK_CROSS,				// “+”字光标
		MARK_BUTTERFLY,			// 蝴蝶形
		MARK_SHARP,				// “#”字形
		MARK_ELLIPSE			// 椭圆
	};

	class AS_EXPORTS MarkData
	{
		//markcom
		/*template <class Archive>
		friend void boost::serialization::serialize(Archive& ar, as::MarkData& val, const unsigned int version);*/
	public:
		int m_id;
		MarkType m_shape;

		struct FormData
		{
			DOUBLE Width;					// 形状宽度
			DOUBLE Height;					// 形状高度
			DOUBLE Arm;						// Arm 十字形基准标记的横竖条的宽度
			LogicType Polarity;				// 偏光性 基准点标记的颜色
			DOUBLE Thickness;				// 形状厚度
			DOUBLE Theta;					// 旋转角度
		};

		struct SearchArea
		{
			DOUBLE SX;						// 设定在X轴的方向检查基准点标记的开始位置
			DOUBLE SY;						// 设定在Y轴的方向检查基准点标记的开始位置
			DOUBLE Width;					// 设定在X轴的方向的检查范围
			DOUBLE Height;					// 设定在Y轴的方向的检查范围
		};

		WORD m_score;
		WORD m_binary;						// 二值化阈值
		MarkLightPara m_MarkLightPara;		// 光源参数
		//CameraID m_CurrentCamera;			// 相机ID
		FormData m_form_data;				// 形状数据
		SearchArea m_search_area;			// 搜索范围
		Point m_mark_pos;                     // 位置

	public:
		MarkData();
		MarkData& operator=(MarkData& ref);
		MarkData& operator=(const MarkData& ref);
		int GetMarkID();
		void SetMarkID(int mark_id);

		MarkLightPara GetMarkLightLevel();
		void SetMarkLightLevel(int InnerLevel, int OuterLevel);
		void SetMarkLightInnerLevel(int level_);
		void SetMarkLightOuterLevel(int level_);
		MarkType GetMarkShape();
		void SetMarkShape(MarkType mark_type);

		DOUBLE GetFormTheta();
		DOUBLE GetFormThick();
		LogicType GetFormPolarity();
		DOUBLE GetFormArm();
		DOUBLE GetFormHeight();
		DOUBLE GetFormWidth();
		void SetFormData( DOUBLE width, DOUBLE height, DOUBLE arm, LogicType type, DOUBLE thick, DOUBLE theta);
		void SetFormWidth( DOUBLE width);
		void SetFormHeight( DOUBLE height);
		void SetFormArm( DOUBLE arm);
		void SetFormPolarity( LogicType type);
		void SetFormThick( DOUBLE thick);
		void SetFormTheta( DOUBLE theta);

		Point GetSearchInitPos();
		DOUBLE GetSearchWidth();
		DOUBLE GetSearchHeight();
		void SetSearchArea( DOUBLE search_x, DOUBLE search_y, DOUBLE search_w, DOUBLE search_h);
		void SetSearchInitPos( DOUBLE search_x, DOUBLE search_y);
		void SetSearchWidth( DOUBLE search_w);
		void SetSearchHeight( DOUBLE search_h);

		WORD GetScore();
		void SetScore( WORD score);
		WORD GetBinary();
		void SetBinary( WORD binary);

		Point GetMarkPos();
		void SetMarkPos(Point pos);
	};

}
#endif
