#ifndef _COLOR_HPP_
#define _COLOR_HPP_

#include "as/core/def.h"

namespace as
{
    /// <summary>
    /// 选择彩色的通道
    /// </summary>
    enum class ColorChannel
    {
        R = 1,
        G = 2,
        B = 4,
        RG = R | G,
        RB = R | B,
        GB = G | B,
        RGB = R | B | G,
    };

    /// <summary>
    /// 彩色转灰度的几种方法
    /// </summary>
    enum class ColorMethod
    {
        color = 1,   // 彩色
        average = 2, // 平均
        max = 3,     // 最大
    };

    /// <summary>
    /// 颜色标准值
    /// </summary>
    struct ColorStandard
    {
        // 红色范围
        int m_nRedHigh = 0;
        int m_nRedLow = 0;

        // 绿色范围
        int m_nGreenHigh = 0;
        int m_nGreenLow = 0;

        // 蓝色范围
        int m_nBlueHigh = 0;
        int m_nBlueLow = 0;

        // 亮度范围
        int m_nGrayHigh = 0;
        int m_nGrayLow = 0;

        ColorStandard(int rHigh, int rLow, int gHigh, int gLow, int bHigh, int bLow, int iHigh, int iLow)
            : m_nRedHigh(rHigh),
              m_nRedLow(rLow),
              m_nGreenHigh(gHigh),
              m_nGreenLow(gLow),
              m_nBlueHigh(bHigh),
              m_nBlueLow(bLow),
              m_nGrayHigh(iHigh),
              m_nGrayLow(iLow)
        {
        }
        ColorStandard() = default;

        ColorStandard& operator=(ColorStandard& ref)
		{
			this->m_nRedHigh = ref.m_nRedHigh;
			this->m_nRedLow = ref.m_nRedLow;
			this->m_nGreenHigh = ref.m_nGreenHigh;
			this->m_nGreenLow = ref.m_nGreenLow;
			this->m_nBlueHigh = ref.m_nBlueHigh;
			this->m_nBlueLow = ref.m_nBlueLow;
			this->m_nGrayHigh = ref.m_nGrayHigh;
			this->m_nGrayLow = ref.m_nGrayLow;
			return *this;
		}
    };
}

#endif