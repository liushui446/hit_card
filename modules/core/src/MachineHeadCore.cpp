#include "as/MachineHeadCore.hpp"

namespace as
{
	Camera::Camera()
	{
		m_dScaleX = 0.014117;
		m_dScaleY = 0.014117;
		m_dRotateAngle = 0;
		m_dStepX = 20;
		m_dStepY = 20;
		m_dSearchWidth = 9;
		m_dSearchHeight = 9;
		m_dViewX = 36.13248;
		m_dViewY = 30.199808;
	}

	void Camera::SetScaleX(double scale_x)
	{
		m_dScaleX = scale_x;
	}

	double Camera::GetScaleX()
	{
		return m_dScaleX;
	}

	void Camera::SetScaleY(double scale_y)
	{
		m_dScaleY = scale_y;
	}

	double Camera::GetScaleY()
	{
		return m_dScaleY;
	}

	void Camera::SetRotateAngle(double angle)
	{
		m_dRotateAngle = angle;
	}

	double Camera::GetRotateAngle()
	{
		return m_dRotateAngle;
	}

	void Camera::SetStepX(double step_x)
	{
		m_dStepX = step_x;
	}

	double Camera::GetStepX()
	{
		return m_dStepX;
	}

	void Camera::SetStepY(double step_y)
	{
		m_dStepY = step_y;
	}

	double Camera::GetStepY()
	{
		return m_dStepY;
	}

	void Camera::SetCaliPos(Point pos)
	{
		m_cCaliPos = pos;
	}

	Point Camera::GetCaliPos()
	{
		return m_cCaliPos;
	}

	void Camera::SetSearchWidth(double width)
	{
		m_dSearchWidth = width;
	}

	double Camera::GetSearchWidth()
	{
		return m_dSearchWidth;
	}

	void Camera::SetSearchHeight(double heigth)
	{
		m_dSearchHeight = heigth;
	}

	double Camera::GetSearchHeight()
	{
		return m_dSearchHeight;
	}

	void Camera::SetViewX(double view_x)
	{
		m_dViewX = view_x;
	}

	double Camera::GetViewX() 
	{
		return m_dViewX;
	}

	void Camera::SetViewY(double view_y)
	{
		m_dViewY = view_y;
	}

	double Camera::GetViewY()
	{
		return m_dViewY;
	}

	Camera& MachineHead::GetCamera()
	{
		return m_camera;
	}
}