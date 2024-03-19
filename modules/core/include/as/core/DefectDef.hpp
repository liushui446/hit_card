#ifndef _DEFECT_DEF_HPP_
#define _DEFECT_DEF_HPP_

#include <string>
#include "as/core/def.h"

namespace as
{
    enum class SPI_Defect
    {
        Normal,             // 正常
        UnNormal,           // 异常问题
        Bridge,             // 连桥
        Insufficient,       // 少锡
        Excessive,          // 多锡
        Shape,              // 形状不良
        Position,           // 位置不良
        GoldTab,            // 金手指
        UpperHeight,        // 超过高度上界
        LowerHeight,        // 低于高度下界
        HighArea,           // 超过面积上界
        LowArea,            // 低于面积下界
        Coplanarity,        // 共面性
        Smear               // 污渍
    };

    std::string AS_EXPORTS SPI_Defect2Name(SPI_Defect _ng);

    enum class AOI_DefectType
    {
        Offset,					// 偏移
		MissingPart,			// 缺件
		WrongPart,				// 错件
		PoorSolder,				// 少锡
		EmptySolder,			// 空焊
		Reverse,				// 反向
		Rotate,					// 旋转
		Contamination,		    // 异物
		Damage,					// 损坏
		ExcessSolder,			// 多锡
		ExtraPart,				// 多件
		FaultySolder,			// 虚焊
		GlueOverflow,			// 溢胶
		LeadFloat,				// 起翘
		SolderBridge,			// 短路
		Tombstone,				// 立碑
		Upturned,				// 反白
		Size
    };

	std::string AS_EXPORTS AOI_Defect2Name(AOI_DefectType _ng);
} // namespace as

#endif