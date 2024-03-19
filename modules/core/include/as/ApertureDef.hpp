#ifndef AS_APERTUREDEFINATE_HPP
#define AS_APERTUREDEFINATE_HPP
#include "as/CommonCore.hpp"

namespace as
{
	/* ������Aperture
* �������ڣ� 2023/10/24
* By ypk
*	@file	GerberParser.hpp
*	@brief	��Ȧ������
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
		string m_ApertureCode;				//��Ȧ������
		as::PadShape m_shape;				//��Ȧ����
		double m_Aperture_Length;			//��Ȧ����
		double m_Aperture_Width;			//��Ȧ���
		double m_Aperture_OutsideDiameter;  //��Ȧ�⾶��ֱ����
		double m_Aperture_InsideDiameter;   //��Ȧ�ھ���ֱ����
	};
}

#endif