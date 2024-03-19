#include "as/ApertureDef.hpp"
namespace as
{
	Aperture::Aperture()
	{
		m_ApertureCode = "";
		m_shape = as::PadShape::Rect;
		m_Aperture_Length = 0;			//光圈长度
		m_Aperture_Width = 0;			//光圈宽度
		m_Aperture_OutsideDiameter = 0;  //光圈外径（直径）
		m_Aperture_InsideDiameter = 0;   //光圈内径（直径）
	}

	Aperture& Aperture::operator=(Aperture& ref)
	{
		this->m_ApertureCode = ref.GetApertureCode();
		this->m_shape = ref.GetApertureShape();
		this->m_Aperture_OutsideDiameter = ref.GetOutDiameter();
		this->m_Aperture_InsideDiameter = ref.GetInDiameter();
		this->m_Aperture_Length = ref.GetLength();
		this->m_Aperture_Width = ref.GetWidth();
		return *this;
	}

	string Aperture::GetApertureCode()
	{
		return m_ApertureCode;
	}

	void Aperture::SetApertureCode(string val)
	{
		m_ApertureCode = val;
	}

	as::PadShape Aperture::GetApertureShape()
	{
		return m_shape;
	}

	void Aperture::SetApertureShape(as::PadShape val)
	{
		m_shape = val;
	}

	double Aperture::GetLength()
	{
		return m_Aperture_Length;
	}

	void Aperture::SetLength(double val)
	{
		m_Aperture_Length = val;
	}

	double Aperture::GetWidth()
	{
		return m_Aperture_Width;
	}

	void Aperture::SetWidth(double val)
	{
		m_Aperture_Width = val;
	}

	double Aperture::GetOutDiameter()
	{
		return m_Aperture_OutsideDiameter;
	}

	void Aperture::SetOutDiameter(double val)
	{
		m_Aperture_OutsideDiameter = val;
	}

	double Aperture::GetInDiameter()
	{
		return m_Aperture_InsideDiameter;
	}

	void Aperture::SetInDiameter(double val)
	{
		m_Aperture_InsideDiameter = val;
	}
}
