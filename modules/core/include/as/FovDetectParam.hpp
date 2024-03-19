#pragma once

#include"as/PadCore.hpp"

namespace as
{
	// 单个焊盘的检测数据
	struct PadDetectParam
	{
		//size_t iPadID_;
		cv::Mat cvHImg_;
		cv::Mat cvRGBImg_;
		double scalex_;
		double scaley_;
		DetectionPadDataPtr pDetectionPadData_;
	};

	using PadDetectParamPtr = std::shared_ptr<PadDetectParam>;

	// 单个Fov的检测系数管理器
	struct FovDetectParam
	{
		size_t iFovID_;
		cv::Mat cvFovRGBImg_;
		cv::Mat cvFovHImg_;
		std::vector<PadDetectParamPtr> pDetectParam_;
	};

	using FovDetectParamPtr = std::shared_ptr<FovDetectParam>;

}