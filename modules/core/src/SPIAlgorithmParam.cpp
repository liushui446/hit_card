#include "as/SPIAlgorithmParam.hpp"

namespace as
{
    SPIAlgorithmParam::SPIAlgorithmParam()
        : m_PadID(0)
        , m_color_channel()
        , m_color_method()
        , m_search_scope()
        , m_seg_color()
        , m_voluem_param()
        , m_position_param()
		, m_bridge_param()
        , m_height_param()
        , m_shape_param()
        , m_area_param()
        , m_coplanarity_param()
    {   
        return;
    }

    SPIAlgorithmParam& SPIAlgorithmParam::operator=(SPIAlgorithmParam& ref)
    {
        this->m_PadID = ref.m_PadID;
        this->m_color_channel = ref.m_color_channel;
        this->m_color_method = ref.m_color_method;
        this->m_search_scope = ref.m_search_scope;
        this->m_seg_color = ref.m_seg_color;
        this->m_voluem_param = ref.m_voluem_param;
        this->m_position_param = ref.m_position_param;
        this->m_bridge_param = ref.m_bridge_param;
        this->m_height_param = ref.m_height_param;
        this->m_shape_param = ref.m_shape_param;
        this->m_area_param = ref.m_area_param;
        this->m_coplanarity_param = ref.m_coplanarity_param;
        return *this;
    }
}