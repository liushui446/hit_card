#pragma once

#include"as/PadCore.hpp"

namespace as
{
	// �������̵ļ������
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

	// ����Fov�ļ��ϵ��������
	struct FovDetectParam
	{
		size_t iFovID_;
		cv::Mat cvFovRGBImg_;
		cv::Mat cvFovHImg_;
		std::vector<PadDetectParamPtr> pDetectParam_;
	};

	using FovDetectParamPtr = std::shared_ptr<FovDetectParam>;

}