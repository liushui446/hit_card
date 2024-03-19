#ifndef AS_APERTUREDEFINATE_HPP
#define AS_APERTUREDEFINATE_HPP
#include "as/CommonCore.hpp"

namespace as
{
	/* 类名：Aperture
* 创建日期： 2023/10/24
* By ypk
*	@file	GerberParser.hpp
*	@brief	光圈定义类
*	@version 1.0
*/
	class AS_EXPORTS Aperture
	{
	public:
		Aperture();
		Aperture& operator= (Aperture& ref);
		string GetApertureCode();
		void SetApertureCode(string val);

		as::PadShape GetApertureShape();
		void SetApertureShape(as::PadShape val);

		double GetLength();
		void SetLength(double val);

		double GetWidth();
		void SetWidth(double val);

		double GetOutDiameter();
		void SetOutDiameter(double val);

		double GetInDiameter();
		void SetInDiameter(double val);
	private:
		string m_ApertureCode;				//光圈描述码
		as::PadShape m_shape;				//光圈类型
		double m_Aperture_Length;			//光圈长度
		double m_Aperture_Width;			//光圈宽度
		double m_Aperture_OutsideDiameter;  //光圈外径（直径）
		double m_Aperture_InsideDiameter;   //光圈内径（直径）
	};
}

#endif