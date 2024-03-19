#include "as/pfm.hpp"

namespace as {
	cv::Mat PFM::read_pfm(const std::string& filename) {

		PFM pfm_r;
		float* pimg = pfm_r.read_pfm<float>(filename);
		if (pimg == nullptr) {
			return cv::Mat();
		}
		int imgH = pfm_r.getHeight();
		int imgW = pfm_r.getWidth();
		cv::Mat temp = cv::Mat(imgH, imgW, CV_32FC1, pimg).clone();
		return temp;
	}

	Eigen::MatrixXd PFM::read_pfm_eigen(const std::string& filename) {

		PFM pfm_r;
		float* pimg = pfm_r.read_pfm<float>(filename);
		if (pimg == nullptr) {
			return Eigen::MatrixXd();
		}
		int imgH = pfm_r.getHeight();
		int imgW = pfm_r.getWidth();
		Eigen::MatrixXd temp;
		temp.resize(imgH, imgW);
		for (int r = 0; r < imgH; r++)
		{
			for (int c = 0; c < imgW; c++)
			{
				temp(r, c) = (double)pimg[r * imgW + c];
			}
		}
		return temp;
	}

	void PFM::write_pfm(const std::string& filename, cv::Mat& img) {
		if (img.type() != CV_32F) {
			return;
		}
		PFM pfm_w;
		pfm_w.setHeight(img.rows);
		pfm_w.setWidth(img.cols);
		float* pimg = img.ptr<float>(0);
		pfm_w.write_pfm<float>(filename, pimg, -1.0f);

	}
}