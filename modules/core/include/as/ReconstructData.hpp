#ifndef _RECONSTRUCT_DATA_HPP_
#define _RECONSTRUCT_DATA_HPP_

#include "as/core/def.h"
#include "as/core/imgproc/ASRect.hpp"

namespace as
{
    struct AS_EXPORTS ReconstructParam
    {
        RectI roi_region;
        int pattern_count;
        int projector_list_enable;
        double scale;

        ReconstructParam()
        {
            roi_region.x = 0;
            roi_region.y = 0;
            roi_region.width = 3840;
            roi_region.height = 3000;
            pattern_count = 18;
            projector_list_enable = 15;
            scale = 1.0;
        }
    };
}

#endif