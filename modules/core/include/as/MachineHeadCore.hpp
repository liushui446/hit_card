#ifndef AS_MACHINEHEADCORE_HPP
#define AS_MACHINEHEADCORE_HPP

#include "as/CommonCore.hpp"

namespace as
{
	//���
	class AS_EXPORTS Camera
	{
	public:
		Camera();
		void SetScaleX(double scale_x);
		double GetScaleX();
		void SetScaleY(double scale_y);
		double GetScaleY();
		void SetRotateAngle(double angle);
		double GetRotateAngle();
		void SetStepX(double step_x);
		double GetStepX();
		void SetStepY(double step_y);
		double GetStepY();
		void SetCaliPos(Point pos);
		Point GetCaliPos();
		void SetSearchWidth(double width);
		double GetSearchWidth();
		void SetSearchHeight(double heigth);
		double GetSearchHeight();
		void SetViewX(double view_x);
		double GetViewX();
		void SetViewY(double view_y);
		double GetViewY();
	private:
		double m_dScaleX;//�̶�X
		double m_dScaleY;//�̶�Y
		double m_dRotateAngle;//��ת�Ƕ�
		double m_dStepX;//����X
		double m_dStepY;//����Y
		Point m_cCaliPos;//У��λ��
		double m_dSearchWidth;//������
		double m_dSearchHeight;//������
		double m_dViewX;//��Ұx��С
		double m_dViewY;//��ҰY��С
	};

	//��ͷ
	class AS_EXPORTS MachineHead
	{
	public:
		Camera& GetCamera();
	private:
		//���
		Camera m_camera;
	};
}
#endif
