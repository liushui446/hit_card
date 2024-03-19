#pragma once

#include "as/core/DefectDef.hpp"
#include "as/core/DetectDef.hpp"

namespace as
{   
	/// <summary>
	/// 返回值(元件注册时使用)
	/// </summary>
	struct AS_EXPORTS ReturnValue
	{
		ERROR_LEVEL error_level;
		int error_type;					 	 // 错误值(0/1)
		int return_value;					 // 返回值
		int m_nReturnValueHigh;	 // 设定判断值上限
		int m_nReturnValueLow;		 // 设定判断值下限

		ReturnValue(ERROR_LEVEL l1, int p1, int p2, int p3, int p4)
			: error_level(l1),
			  error_type(p1),
			  return_value(p2),
			  m_nReturnValueHigh(p3),
			  m_nReturnValueLow(p4)
		{
		}

		ReturnValue()
			: error_level(ERROR_LEVEL::OK),
			  error_type(-1),
			  return_value(0),
			  m_nReturnValueHigh(0),
			  m_nReturnValueLow(0)
		{
		}
	};
} // namespace as
