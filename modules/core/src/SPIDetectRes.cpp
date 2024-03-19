#include "as/SPIDetectRes.hpp"

namespace as
{
	SPIDetectRes::SPIDetectRes(void)
		: tPadID_(-1)
		, eDetectRes_(ERROR_LEVEL::OK)
		, vDefects_()
		, sVolumeRes_()
		, sPosRes_()
		, sHeightRes_()
		, sShapeRes_()
		, sAreaRes_()
		, sCoplanarityRes_()
	{
		mHeightImage_ = cv::Mat::zeros(cv::Size(1, 1), CV_32FC1);
		mRGBImage_ = cv::Mat::zeros(cv::Size(1, 1), CV_8UC3);
		return;
	}

	SPIDetectRes& SPIDetectRes::operator=(SPIDetectRes& ref)
	{
		this->tPadID_ = ref.tPadID_;
		this->eDetectRes_ = ref.eDetectRes_;
		this->vDefects_ = ref.vDefects_;
		this->sVolumeRes_ = ref.sVolumeRes_;
		this->sPosRes_ = ref.sPosRes_;
		this->sHeightRes_ = ref.sHeightRes_;
		this->sShapeRes_ = ref.sShapeRes_;
		this->sAreaRes_ = ref.sAreaRes_;
		this->sCoplanarityRes_ = ref.sCoplanarityRes_;
		this->mHeightImage_ = ref.mHeightImage_.clone();
		this->mRGBImage_ = ref.mRGBImage_.clone();
		return *this;
	}

	SPIDetectRes::SPIDetectRes(const SPIDetectRes& ref)
	{
		this->tPadID_ = ref.tPadID_;
		this->eDetectRes_ = ref.eDetectRes_;
		this->vDefects_ = ref.vDefects_;
		this->sVolumeRes_ = ref.sVolumeRes_;
		this->sPosRes_ = ref.sPosRes_;
		this->sHeightRes_ = ref.sHeightRes_;
		this->sShapeRes_ = ref.sShapeRes_;
		this->sAreaRes_ = ref.sAreaRes_;
		this->sCoplanarityRes_ = ref.sCoplanarityRes_;
		this->mHeightImage_ = ref.mHeightImage_.clone();
		this->mRGBImage_ = ref.mRGBImage_.clone();
	}
}