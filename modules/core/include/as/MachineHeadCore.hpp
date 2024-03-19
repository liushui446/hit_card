#ifndef AS_MACHINEHEADCORE_HPP
#define AS_MACHINEHEADCORE_HPP

#include "as/CommonCore.hpp"

namespace as
{
	//相机
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
		double m_dScaleX;//刻度X
		double m_dScaleY;//刻度Y
		double m_dRotateAngle;//旋转角度
		double m_dStepX;//步距X
		double m_dStepY;//步距Y
		Point m_cCaliPos;//校正位置
		double m_dSearchWidth;//搜索宽
		double m_dSearchHeight;//搜索高
		double m_dViewX;//视野x大小
		double m_dViewY;//视野Y大小
	};

	//机头
	class AS_EXPORTS MachineHead
	{
	public:
		Camera& GetCamera();
	private:
		//相机
		Camera m_camera;
	};
}
#endif
