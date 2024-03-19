#include "as/MarkCore.hpp"
#include "as/ConveyorParaCore.hpp"
#include "as/CoorTrans.hpp"
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace as {


	MarkData::MarkData()
	{
		m_id = 1;
		m_shape = MarkType::MARK_CIRCLE;
		m_binary = 128;
		m_score = 1;
		m_form_data.Width = 0;
		m_form_data.Height = 0;
		m_form_data.Theta = 1;
		m_form_data.Arm = 1;
		m_form_data.Polarity = LogicType::LOGIC_WHITE;
		m_form_data.Thickness = 0;
		m_search_area.SX = 1;
		m_search_area.SY = 1;
		m_search_area.Width = 4;
		m_search_area.Height = 4;
		m_MarkLightPara.Outer = 15;
		m_MarkLightPara.Inner = 15;
	}

	MarkData& MarkData::operator=(MarkData& ref)
	{
		this->m_id = ref.GetMarkID();
		this->m_mark_pos = ref.GetMarkPos();
		this->m_binary = ref.GetBinary();
		this->m_form_data.Width = ref.GetFormWidth();
		this->m_form_data.Height = ref.GetFormHeight();
		this->m_form_data.Theta = ref.GetFormTheta();
		this->m_form_data.Arm = ref.GetFormArm();
		this->m_form_data.Polarity = ref.GetFormPolarity();
		this->m_form_data.Thickness = ref.GetFormThick();
		this->m_search_area.SX = ref.GetSearchInitPos().x;
		this->m_search_area.SY = ref.GetSearchInitPos().y;
		this->m_search_area.Width = ref.GetSearchWidth();
		this->m_search_area.Height = ref.GetSearchHeight();
		this->m_MarkLightPara.Outer = ref.GetMarkLightLevel().Outer;
		this->m_MarkLightPara.Inner = ref.GetMarkLightLevel().Inner;
		this->m_shape = ref.GetMarkShape();
		this->m_score = ref.GetScore();
		return *this;
	}

	MarkData& MarkData::operator=(const MarkData& ref)
	{
		this->m_id = ref.m_id;
		this->m_binary = ref.m_binary;
		this->m_form_data.Width = ref.m_form_data.Width;
		this->m_form_data.Height = ref.m_form_data.Height;
		this->m_form_data.Theta = ref.m_form_data.Theta;
		this->m_form_data.Arm = ref.m_form_data.Arm;
		this->m_form_data.Polarity = ref.m_form_data.Polarity;
		this->m_form_data.Thickness = ref.m_form_data.Thickness;
		this->m_search_area.SX = ref.m_search_area.SX;
		this->m_search_area.SY = ref.m_search_area.SY;
		this->m_search_area.Width = ref.m_search_area.Width;
		this->m_search_area.Height = ref.m_search_area.Height;
		this->m_MarkLightPara.Outer = ref.m_MarkLightPara.Outer;
		this->m_MarkLightPara.Inner = ref.m_MarkLightPara.Inner;
		this->m_shape = ref.m_shape;
		this->m_score = ref.m_score;
		return *this;
	}

	int MarkData::GetMarkID()
	{
		return m_id;
	}
	void MarkData::SetMarkID(int mark_id)
	{
		m_id = mark_id;
		return;
	}
	MarkLightPara MarkData::GetMarkLightLevel()
	{
		return m_MarkLightPara;
	}
	void MarkData::SetMarkLightLevel(int InnerLevel, int OuterLevel)
	{
		m_MarkLightPara.Inner = InnerLevel;
		m_MarkLightPara.Outer = OuterLevel;
		return;
	}
	void MarkData::SetMarkLightInnerLevel(int level_)
	{
		m_MarkLightPara.Inner = level_;
	}
	void MarkData::SetMarkLightOuterLevel(int level_)
	{
		m_MarkLightPara.Outer = level_;
	}
	MarkType MarkData::GetMarkShape()
	{
		return m_shape;
	}
	void MarkData::SetMarkShape(MarkType mark_type)
	{
		m_shape = mark_type;
		return;
	}
	DOUBLE MarkData::GetFormTheta()
	{
		return m_form_data.Theta;
	}
	DOUBLE MarkData::GetFormThick()
	{
		return m_form_data.Thickness;
	}
	LogicType MarkData::GetFormPolarity()
	{
		return m_form_data.Polarity;
	}
	DOUBLE MarkData::GetFormArm()
	{
		return m_form_data.Arm;
	}
	DOUBLE MarkData::GetFormHeight()
	{
		return m_form_data.Height;
	}
	DOUBLE MarkData::GetFormWidth()
	{
		return m_form_data.Width;
	}

	void MarkData::SetFormData(DOUBLE width, DOUBLE height, DOUBLE arm, LogicType type, DOUBLE thick, DOUBLE theta)
	{
		m_form_data.Arm = arm;
		m_form_data.Width = width;
		m_form_data.Height = height;
		m_form_data.Polarity = type;
		m_form_data.Theta = theta;
		m_form_data.Thickness = thick;
		return;
	}
	void MarkData::SetFormWidth(DOUBLE width)
	{
		m_form_data.Width = width;
		return;
	}
	void MarkData::SetFormHeight(DOUBLE height)
	{
		m_form_data.Height = height;
		return;
	}
	void MarkData::SetFormArm(DOUBLE arm)
	{
		m_form_data.Arm = arm;
		return;
	}
	void MarkData::SetFormPolarity(LogicType type)
	{
		m_form_data.Polarity = type;
		return;
	}
	void MarkData::SetFormThick(DOUBLE thick)
	{
		m_form_data.Thickness = thick;
		return;
	}
	void MarkData::SetFormTheta(DOUBLE theta)
	{
		m_form_data.Theta = theta;
		return;
	}

	Point MarkData::GetSearchInitPos()
	{
		Point pos;
		pos.x = m_search_area.SX;
		pos.y = m_search_area.SY;
		return pos;
	}
	DOUBLE MarkData::GetSearchWidth()
	{
		return  m_search_area.Width;
	}
	DOUBLE MarkData::GetSearchHeight()
	{
		return  m_search_area.Height;
	}
	void MarkData::SetSearchArea(DOUBLE search_x, DOUBLE search_y, DOUBLE search_w, DOUBLE search_h)
	{
		m_search_area.Height = search_h;
		m_search_area.Width = search_w;
		m_search_area.SX = search_x;
		m_search_area.SY = search_y;
		return;
	}
	void MarkData::SetSearchInitPos(DOUBLE search_x, DOUBLE search_y)
	{
		m_search_area.SX = search_x;
		m_search_area.SY = search_y;
		return;
	}
	void MarkData::SetSearchWidth(DOUBLE search_w)
	{
		m_search_area.Width = search_w;
		return;
	}
	void MarkData::SetSearchHeight(DOUBLE search_h)
	{
		m_search_area.Height = search_h;
		return;
	}
	WORD MarkData::GetScore()
	{
		return m_score;
	}
	void MarkData::SetScore(WORD score)
	{
		m_score = score;
	}
	WORD MarkData::GetBinary()
	{
		return m_binary;
	}
	void MarkData::SetBinary(WORD binary)
	{
		m_binary = binary;
		return;
	}

	Point MarkData::GetMarkPos()
	{
		return m_mark_pos;
	}

	void MarkData::SetMarkPos(Point pos)
	{
		m_mark_pos = pos;
	}

}
