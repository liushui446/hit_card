#ifndef _CALIBRATION_DEF_HPP_
#define _CALIBRATION_DEF_HPP_

#include <string>
#include <map>
#include <Eigen/Core>
#include "as/core/def.h"
#include "as/ProjectorDef.hpp"
#include "as/LumenDef.hpp"
#include "as/ErrorCode.hpp"
#include "as/pfm.hpp"

namespace as
{
	//Phase Distortion Compensation LUT
	class PhaseDistCompLUT {
	public:
		PhaseDistCompLUT() :order(0) {
		}

		double* at(int index) {
			return coeffs.row(index).data();
		}

		const double* at(int index) const {
			return coeffs.row(index).data();
		}

		inline Eigen::MatrixXd& getCoeffs() {
			return coeffs;
		}

		inline const Eigen::MatrixXd& getCoeffs() const {
			return coeffs;
		}

		inline void setOrder(int order_) {
			order = order_;
		}

		inline int getOrder() const {
			return order;
		}

		inline void setScale(double scale_) {
			norm_scale = scale_;
		}

		inline double getScale() const {
			return norm_scale;
		}

		inline void setRoot(std::string root_) {
			save_root = root_;
		}

		inline std::string getRoot() const {
			return save_root;
		}

	private:
		Eigen::MatrixXd coeffs; //[rows*cols, order + 1]
		double norm_scale;
		int order;
		std::string save_root;
	};
	
	class AS_EXPORTS ProCalibrationData {
	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW
	public:
		ProCalibrationData();
		~ProCalibrationData();
		explicit ProCalibrationData(const std::string& calibration_file);

		bool is_valid() const;

		bool write(const std::string& calibration_file);
		bool read(const std::string& calibration_file);
	public:

		Eigen::MatrixXd cam_K;
		Eigen::VectorXd cam_kc;
		Eigen::MatrixXd cam_R;
		Eigen::VectorXd cam_T;
		Eigen::MatrixXd cam_M;

		std::map<PROJECTORID, Eigen::MatrixXd> proj_Ks; //Intrinsic 3x3
		std::map<PROJECTORID, Eigen::VectorXd> proj_kcs; //Distort Vector 14x1
		std::map<PROJECTORID, Eigen::MatrixXd> proj_Rs; //Projector <- World Coord
		std::map<PROJECTORID, Eigen::VectorXd> proj_Ts; //Projector <- World Coord
		std::map<PROJECTORID, Eigen::MatrixXd> proj_Es; //Projector -> Camera Essential Matrix

		std::map<PROJECTORID, Eigen::MatrixXd> Rs; //Projector -> Camera
		std::map<PROJECTORID, Eigen::VectorXd> Ts; //Projector -> Camera

		std::map<PROJECTORID, PhaseDistCompLUT> delta_phi_local_coeffs; //(rows*cols, order + 1)
		std::map<PROJECTORID, Eigen::VectorXd> phase_height_map_coeffs; // phase->height map coeffs

	private:
		bool load_calibration_yml(std::string const& filename);
		bool load_calibration_yml2(std::string const& filename);
		bool save_calibration_yml(std::string const& filename);

	private:
		bool initialized_;
		std::string file_path_;
	};

	typedef std::shared_ptr<ProCalibrationData> ProCalibrationDataPtr;
	typedef const std::shared_ptr<ProCalibrationData> ProCalibrationDataConstPtr;
	
	class AS_EXPORTS LumenCalibrationData{
	public:
		LumenCalibrationData() = default;
		~LumenCalibrationData() = default;
		LumenCalibrationData(const LumenCalibrationData& rhs);

	public:
		LumenData m_lumenData;
		bool m_getData;
		APIErrCode m_errorCode;
	};
}

#endif