#pragma once

#include <opencv2/opencv.hpp>
#include "as/core/DefectDef.hpp"
#include "as/core/DetectDef.hpp"

namespace as
{
    /// <summary>
	/// 体积检测返回结果
	/// </summary>
	struct AS_EXPORTS SPIVolumeRes
	{
		ERROR_LEVEL eInsufficientRes_; // 少锡检测结果
		ERROR_LEVEL eExcessiveRes_; // 多锡检测结果
		double dVolume_; // 锡膏体积（mm^3）
		
		SPIVolumeRes()
			: eInsufficientRes_(ERROR_LEVEL::OK)
			, eExcessiveRes_(ERROR_LEVEL::OK)
			, dVolume_(0.0)
		{
		}

		SPIVolumeRes(const ERROR_LEVEL& _InsufficientRes, const ERROR_LEVEL& _ExcessiveRes, const double& Volume_)
			: eInsufficientRes_(_InsufficientRes)
			, eExcessiveRes_(_ExcessiveRes)
			, dVolume_(Volume_)
		{
		}
	};
	
	/// <summary>
	/// 位置检测返回结果
	/// </summary>
	struct AS_EXPORTS SPIPosRes
	{
		ERROR_LEVEL ePosRes_; // 位置检测结果
		double dOffsetX_; // 锡膏中心在X方向上的偏移
		double dOffsetY_; // 锡膏中心在Y方向上的偏移

		SPIPosRes()
			: ePosRes_(ERROR_LEVEL::OK)
			, dOffsetX_(0.0)
			, dOffsetY_(0.0)
		{
		}

		SPIPosRes(const ERROR_LEVEL& _PosRes, const double& _offsetx, const double& _offsety)
			: ePosRes_(_PosRes)
			, dOffsetX_(_offsetx)
			, dOffsetY_(_offsety)
		{
		}
	};

	/// <summary>
	/// 连桥检测返回结果
	/// </summary>
	struct AS_EXPORTS SPIBridgeRes
	{
		ERROR_LEVEL eBridgeRes_; // 锡膏连桥检测结果
		std::vector<double> vOffsetX_; // 锡膏连桥区域中心X方向偏移量
		std::vector<double> vOffsetY_; // 锡膏连桥区域中心Y方向偏移量
		std::vector<double> vWidth_; // 锡膏连桥区域中心Width值
		std::vector<double> vHeight_; // 锡膏连桥区域中心Height值

		SPIBridgeRes()
			: eBridgeRes_(ERROR_LEVEL::OK)
		{
		}

		SPIBridgeRes(const ERROR_LEVEL& _PosRes, std::vector<double>& _vOffsetX, std::vector<double>& _vOffsetY, std::vector<double>& _vWidth, std::vector<double>& _vHeight)
			: eBridgeRes_(_PosRes)
			, vOffsetX_(_vOffsetX)
			, vOffsetY_(_vOffsetY)
			, vWidth_(_vWidth)
			, vHeight_(_vHeight)
		{
		}
	};

	/// <summary>
	/// 高度检测返回结果
	/// </summary>
	struct AS_EXPORTS SPIHeightRes
	{
		ERROR_LEVEL eUpperHeightRes_; // 高度超过上限检测结果
        ERROR_LEVEL eLowerHeightRes_; // 高度低于下限检测结果
		double dHeight_; // 检测锡膏平均高度值

		SPIHeightRes()
			: eUpperHeightRes_(ERROR_LEVEL::OK)
            , eLowerHeightRes_(ERROR_LEVEL::OK)
			, dHeight_(0.0)
		{
		}

		SPIHeightRes(const ERROR_LEVEL& _UpperHeightRes, const ERROR_LEVEL& _LowerHeightRes, const double& _dHeight)
			: eUpperHeightRes_(_UpperHeightRes)
            , eLowerHeightRes_(_LowerHeightRes)
			, dHeight_(_dHeight)
		{
		}
	};
	
	/// <summary>
	/// 形状检测返回结果
	/// </summary>
	struct AS_EXPORTS SPIShapeRes
	{
		ERROR_LEVEL eShapeRes_; // 锡膏形状检测结果
		double dBalance_; // 锡膏形状检测的容差

		SPIShapeRes()
			: eShapeRes_(ERROR_LEVEL::OK)
			, dBalance_(0.0)
		{
		}

		SPIShapeRes(const ERROR_LEVEL& _ShapeRes, const double& _dBalance)
			: eShapeRes_(_ShapeRes)
			, dBalance_(_dBalance)
		{
		}
	};

	/// <summary>
	/// 面积检测返回结果
	/// </summary>
	struct AS_EXPORTS SPIAreaRes
	{
		ERROR_LEVEL eHighAreaRes_; // 锡膏区域面积超过上限检测结果
        ERROR_LEVEL eLowAreaRes_; // 锡膏区域面积低于下限检测结果
		double dArea_; // 检测得到的锡膏区域面积

		SPIAreaRes()
			: eHighAreaRes_(ERROR_LEVEL::OK)
            , eLowAreaRes_(ERROR_LEVEL::OK)
			, dArea_(0.0)
		{
		}

		SPIAreaRes(const ERROR_LEVEL& _HighAreaRes, const ERROR_LEVEL& _LowAreaRes,const double& _dArea)
			: eHighAreaRes_(_HighAreaRes)
            , eLowAreaRes_(_LowAreaRes)
			, dArea_(_dArea)
		{
		}

	};

	/// <summary>
	/// 形状检测返回结果
	/// </summary>
	struct AS_EXPORTS SPICoplanarityRes
	{
		ERROR_LEVEL eVolumeRes_; // 锡膏共面性的体积检测结果
        ERROR_LEVEL ePosionRes_; // 锡膏共面性的位置检测结果
		double dVolumeRate_; // 锡膏体积超过阈值极限值
        double dOffsetX_; // 锡膏位置偏移
        double dOffsetY_; // 锡膏位置偏移

		SPICoplanarityRes()
			: eVolumeRes_(ERROR_LEVEL::OK)
            , ePosionRes_(ERROR_LEVEL::OK)
			, dVolumeRate_(0.0)
            , dOffsetX_(0.0)
            , dOffsetY_(0.0)
		{
		}

		SPICoplanarityRes(const ERROR_LEVEL& _VolumeRes, const ERROR_LEVEL& _PosionRes,const double& _dVolumeRate, const double& _dOffsetX, const double& _dOffsetY)
			: eVolumeRes_(_VolumeRes)
            , ePosionRes_(_PosionRes)
			, dVolumeRate_(_dVolumeRate)
            , dOffsetX_(_dOffsetX)
            , dOffsetY_(_dOffsetY)
		{
		}

	};
    
	// 检测结果返回
	class AS_EXPORTS SPIDetectRes
	{
	public:
		SPIDetectRes(void);
		~SPIDetectRes(void) {};

		SPIDetectRes& operator=(SPIDetectRes& ref);
		SPIDetectRes(const SPIDetectRes& ref);//定义了复制构造函数

		inline const size_t& GetPadID() { return tPadID_; }
		inline void SetPadID(const size_t& id) { tPadID_ = id; }

		inline const ERROR_LEVEL& GetErrorLevel() { return eDetectRes_; }
		inline void SetErrorLevel(const ERROR_LEVEL& _eDetectRes) { eDetectRes_ = _eDetectRes; }

		inline const std::vector<SPI_Defect>& GetDetects() { return vDefects_; }
		inline void SetDetects(const std::vector<SPI_Defect>& _vDetects) { vDefects_ = _vDetects; }
		inline void PushDetects(const SPI_Defect& _detect) { vDefects_.push_back(_detect); }

		inline const SPIVolumeRes& GetVolumeRes() { return sVolumeRes_; }
		inline void SetVolumeRes(const SPIVolumeRes& _sVolumeRes) { sVolumeRes_ = _sVolumeRes; }

		inline const SPIPosRes& GetPosRes() { return sPosRes_; }
		inline void SetPosRes(const SPIPosRes& _sPosRes) { sPosRes_ = _sPosRes; }

		inline const SPIHeightRes& GetHeightRes() { return sHeightRes_; }
		inline void SetHeightRes(const SPIHeightRes& _sHeightRes) { sHeightRes_ = _sHeightRes; }

		inline const SPIShapeRes& GetShapeRes() { return sShapeRes_; }
		inline void SetShapeRes(const SPIShapeRes& _sShapeRes) { sShapeRes_ = _sShapeRes; }

		inline const SPIAreaRes& GetAreaRes() { return sAreaRes_; }
		inline void SetAreaRes(const SPIAreaRes& _sAreaRes) { sAreaRes_ = _sAreaRes; }

		inline const SPICoplanarityRes& GetCoplanarityRes() { return sCoplanarityRes_; }
		inline void SetCoplanarityRes(const SPICoplanarityRes& _sCoplanarityRes) { sCoplanarityRes_ = _sCoplanarityRes; }

		inline const std::string& GetErrorMsg(){ return sErrorExplanation_; }
		inline void SetErrorMsg(const std::string& _msg) { sErrorExplanation_ = _msg; }

		inline const cv::Mat& GetHeightImage() { return mHeightImage_; }
		inline void SetHeightImage(const cv::Mat& _HeightImage) { mHeightImage_ = _HeightImage.clone(); }

		inline const cv::Mat& GetRGBImage() { return mRGBImage_; }
		inline void SetRGBImage(const cv::Mat& _RGBImage) { mRGBImage_ = _RGBImage; }

	private:
		unsigned long long tPadID_;
		ERROR_LEVEL  eDetectRes_;
        std::vector<SPI_Defect> vDefects_;      
		SPIVolumeRes sVolumeRes_;
		SPIPosRes sPosRes_;
		SPIHeightRes sHeightRes_;
		SPIShapeRes sShapeRes_;
		SPIAreaRes sAreaRes_;
		SPICoplanarityRes sCoplanarityRes_;
		std::string sErrorExplanation_;
		cv::Mat mHeightImage_; // 错误时，保存原始图片
		cv::Mat mRGBImage_; // 错误时，保存原始图片
	};

	using SPIDetectResPtr = std::shared_ptr<SPIDetectRes>;
}