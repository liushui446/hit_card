#pragma once
#include "opencv2/opencv.hpp"

#include "as/core/DetectDef.hpp"
#include "as/core/DefectDef.hpp"
#include "as/core/Color.hpp"
#include "as/core/def.h"

namespace as
{
	class AS_EXPORTS SPIAlgorithmParam
	{
	public:
		SPIAlgorithmParam(void);
		virtual ~SPIAlgorithmParam(void) {};

		SPIAlgorithmParam& operator=(SPIAlgorithmParam& ref);

		inline const size_t& GetPadID() { return m_PadID; }
		inline void SetPadID(const size_t& id) { m_PadID = id; }

		inline const ColorChannel& GetColorChannel() { return m_color_channel; }
		inline void SetColorChannel(ColorChannel& _color_channel) { m_color_channel = _color_channel; }

		inline const ColorMethod& GetColorMethod() { return m_color_method; }
		inline void SetColorChannel(ColorMethod& _color_method) { m_color_method = _color_method; }

		inline const SearchScope& GetSearchScope() { return m_search_scope; }
		inline void SetSearchScope(SearchScope& _search_scope) { m_search_scope = _search_scope; }

		inline const ColorStandard& GetColorStandard() { return m_seg_color; }
		inline void SetColorStandard(ColorStandard& _seg_color) { m_seg_color = _seg_color; }

		inline const SPI_VOLUME_PARAM& GetVolumeParam() { return m_voluem_param; }
		inline void SetVolumeParam(SPI_VOLUME_PARAM& _voluem_param) { m_voluem_param = _voluem_param; }

		inline const SPI_POSITION_PARAM& GetPositionParam() { return m_position_param; }
		inline void SetPositionParam(SPI_POSITION_PARAM& _position_param) { m_position_param = _position_param; }

		inline const SPI_BRIDGE_PARAM& GetBridgeParam() { return m_bridge_param; }
		inline void SetBridgeParam(SPI_BRIDGE_PARAM& _bridge_param) { m_bridge_param = _bridge_param; }

		inline const SPI_HEIGHT_PARAM& GetHeightParam() { return m_height_param; }
		inline void SetHeightParam(SPI_HEIGHT_PARAM& _height_param) { m_height_param = _height_param; }

		inline const SPI_SHAPE_PARAM& GetShapeParam() { return m_shape_param; }
		inline void SetShapeParam(SPI_SHAPE_PARAM& _shape_param) { m_shape_param = _shape_param; }

		inline const SPI_AREA_PARAM& GetAreaParam() { return m_area_param; }
		inline void SetAreaParam(SPI_AREA_PARAM& _area_param) { m_area_param = _area_param; }

		inline const SPI_COPLANARITY_PARAM& GetCoplanarityParam() { return m_coplanarity_param; }
		inline void SetCoplanarityParam(SPI_COPLANARITY_PARAM& _coplanarity_param) { m_coplanarity_param = _coplanarity_param; }

	private:
		size_t m_PadID;
		ColorChannel m_color_channel;               // 分割图片颜色
		ColorMethod m_color_method;                 // 彩色图片转灰度方法
		SearchScope m_search_scope;                 // roi大小，旋转角度以焊盘坐标系（PCB坐标系）为准
		ColorStandard m_seg_color;                  // 锡膏区域分割颜色取值范围
		SPI_VOLUME_PARAM m_voluem_param;            // 体积检测参数
		SPI_POSITION_PARAM m_position_param;        // 位置检测参数
		SPI_BRIDGE_PARAM m_bridge_param;            // 连桥检测参数
		SPI_HEIGHT_PARAM m_height_param;            // 高度检测参数
		SPI_SHAPE_PARAM m_shape_param;              // 形状检测参数
		SPI_AREA_PARAM m_area_param;                // 面积检测参数
		SPI_COPLANARITY_PARAM m_coplanarity_param;  // 共面性检测参数
	};

	using SPIAlgorithmParamPtr = std::shared_ptr<SPIAlgorithmParam>;

}