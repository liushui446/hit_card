#pragma once

#include <string>
#include "as/core/def.h"
#include "as/MarkCore.hpp"

namespace as
{
    class AS_EXPORTS MarkResult_Offset
    {
    public:
        MarkResult_Offset(): offset_X(0), offset_Y(0) , offset_R(0) {};
        double offset_X; ///<  The distance between the center of the Mark and the center of the image in the X direction
        double offset_Y; ///<  The distance between the center of the Mark and the center of the image in the Y direction
        double offset_R; ///<  The angle between the Mark and the image coordinate system
    };

    class AS_EXPORTS MarkResult_TimSco
    {
    public:
        double time = 0;  ///<  Time required for component inspection
        double score = 0; ///<  Component inspection score
    };

    class AS_EXPORTS MarkResult{
    public: 
        APIErrCode errorcode;
        MarkResult_Offset offset;
        std::string ErrorExp;
        MarkResult(): errorcode(APIErrCode::FAIL), ErrorExp(""){}
    };

    class AS_EXPORTS MarkTeachResult :public MarkResult
    {
    public:
        MarkData mark;
        MarkTeachResult() = default;
    };

    class AS_EXPORTS MarkTestResult :public MarkResult
    {
    public:
        MarkResult_TimSco timsco;
        int ChkResult = 0;
        string errorImgDir;

        MarkTestResult()= default;
    };


}// as