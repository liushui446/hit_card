#include <filesystem>
#include <iostream>

#include "yaml-cpp/yaml.h"
#include "as/CalibrationData.hpp"

namespace as
{
    ProCalibrationData::ProCalibrationData() 
		: initialized_(false),
		proj_Ks(),
		proj_kcs(),
		proj_Rs(),
		proj_Ts(),
		proj_Es(),
		Rs(),
		Ts(),
		file_path_("") {

	}

	ProCalibrationData::ProCalibrationData(const std::string& calibration_file)
		: initialized_(false),
		proj_Ks(),
		proj_kcs(),
		proj_Rs(),
		proj_Ts(),
		proj_Es(),
		Rs(),
		Ts() {
		file_path_ = calibration_file;
		//read(calibration_file);
	}
	
	ProCalibrationData::~ProCalibrationData() {

	}

	bool ProCalibrationData::is_valid() const {
		return (((cam_K.size() > 0 && cam_kc.size() > 0) || cam_M.size() > 0) && proj_Ks.size() && proj_kcs.size() && proj_kcs.size()
			&& ((((cam_R.size() > 0 && cam_T.size() > 0) || cam_M.size() > 0) && proj_Rs.size() && proj_Ts.size()) || (Rs.size() && Ts.size())));
	}

	bool ProCalibrationData::write(const std::string& calibration_file) {

		if (save_calibration_yml(calibration_file))
		{
			std::cout << "calibration yaml file save success" << std::endl;
			return true;
		}
		else
		{
			std::cout << "calibration yaml file save failed" << std::endl;
			return false;
		}
	}

	bool ProCalibrationData::read(const std::string& calibration_file) {
		std::error_code error;
		auto file_status = std::filesystem::status(calibration_file, error);
		if (error) {
			return false;
		}
		if (!std::filesystem::exists(file_status)) {
			return false;
		}

		std::filesystem::path info(calibration_file);
		if (info.extension().string() == ".yml") {
			load_calibration_yml(calibration_file);
		}
		
		initialized_ = true;
		return true;
	}


	bool ProCalibrationData::load_calibration_yml(std::string const& filename) {
		YAML::Node node = YAML::LoadFile(filename);
		if (node.IsNull()) {
			return false;
		}
		
		proj_Ks[PROJECTORID::PROJECTOR_ID_UP].resize(3, 3);
		proj_Ks[PROJECTORID::PROJECTOR_ID_DOWN].resize(3, 3);
		proj_Ks[PROJECTORID::PROJECTOR_ID_LEFT].resize(3, 3);
		proj_Ks[PROJECTORID::PROJECTOR_ID_RIGHT].resize(3, 3);
		proj_Rs[PROJECTORID::PROJECTOR_ID_UP].resize(3, 3);
		proj_Rs[PROJECTORID::PROJECTOR_ID_DOWN].resize(3, 3);
		proj_Rs[PROJECTORID::PROJECTOR_ID_LEFT].resize(3, 3);
		proj_Rs[PROJECTORID::PROJECTOR_ID_RIGHT].resize(3, 3);
		Rs[PROJECTORID::PROJECTOR_ID_UP].resize(3, 3);
		Rs[PROJECTORID::PROJECTOR_ID_DOWN].resize(3, 3);
		Rs[PROJECTORID::PROJECTOR_ID_LEFT].resize(3, 3);
		Rs[PROJECTORID::PROJECTOR_ID_RIGHT].resize(3, 3);
		proj_Ts[PROJECTORID::PROJECTOR_ID_UP].resize(3);
		proj_Ts[PROJECTORID::PROJECTOR_ID_DOWN].resize(3);
		proj_Ts[PROJECTORID::PROJECTOR_ID_LEFT].resize(3);
		proj_Ts[PROJECTORID::PROJECTOR_ID_RIGHT].resize(3);
		cam_K.resize(3, 3);
		cam_R.resize(3, 3);
        
		for (int r = 0; r < 3; ++r) {
			proj_Ts[PROJECTORID::PROJECTOR_ID_UP](r) = node["projU_T"]["data"][r].as<double>();
			proj_Ts[PROJECTORID::PROJECTOR_ID_DOWN](r) = node["projD_T"]["data"][r].as<double>();
			proj_Ts[PROJECTORID::PROJECTOR_ID_LEFT](r) = node["projL_T"]["data"][r].as<double>();
			proj_Ts[PROJECTORID::PROJECTOR_ID_RIGHT](r) = node["projR_T"]["data"][r].as<double>();
			for (int c = 0; c < 3; ++c) {
				cam_K(r, c) = node["cam_K"]["data"][c + 3 * r].as<double>();
				cam_R(r, c) = node["cam_R"]["data"][c + 3 * r].as<double>();
				
				proj_Ks[PROJECTORID::PROJECTOR_ID_UP](r,c) = node["projU_K"]["data"][c + 3 * r].as<double>();
				proj_Ks[PROJECTORID::PROJECTOR_ID_DOWN](r,c) = node["projD_K"]["data"][c + 3 * r].as<double>();
				proj_Ks[PROJECTORID::PROJECTOR_ID_LEFT](r,c) = node["projL_K"]["data"][c + 3 * r].as<double>();
				proj_Ks[PROJECTORID::PROJECTOR_ID_RIGHT](r,c) = node["projR_K"]["data"][c + 3 * r].as<double>();

				proj_Rs[PROJECTORID::PROJECTOR_ID_UP](r, c) = node["projU_R"]["data"][c + 3 * r].as<double>();
				proj_Rs[PROJECTORID::PROJECTOR_ID_DOWN](r, c) = node["projD_R"]["data"][c + 3 * r].as<double>();
				proj_Rs[PROJECTORID::PROJECTOR_ID_LEFT](r, c) = node["projL_R"]["data"][c + 3 * r].as<double>();
				proj_Rs[PROJECTORID::PROJECTOR_ID_RIGHT](r, c) = node["projR_R"]["data"][c + 3 * r].as<double>();

				Rs[PROJECTORID::PROJECTOR_ID_UP](r, c) = node["Ru"]["data"][c + 3 * r].as<double>();
				Rs[PROJECTORID::PROJECTOR_ID_DOWN](r, c) = node["Rd"]["data"][c + 3 * r].as<double>();
				Rs[PROJECTORID::PROJECTOR_ID_LEFT](r, c) = node["Rl"]["data"][c + 3 * r].as<double>();
				Rs[PROJECTORID::PROJECTOR_ID_RIGHT](r, c) = node["Rr"]["data"][c + 3 * r].as<double>();
			}
		}
		
		cam_M.resize(3, 4);
		for (int r = 0; r < 3; ++r) {
			for (int c = 0; c < 4; ++c) {
				cam_M(r, c) = node["cam_M"]["data"][c + 4 * r].as<double>();
			}
		}

		proj_kcs[PROJECTORID::PROJECTOR_ID_UP].resize(14);
		proj_kcs[PROJECTORID::PROJECTOR_ID_DOWN].resize(14);
		proj_kcs[PROJECTORID::PROJECTOR_ID_LEFT].resize(14);
		proj_kcs[PROJECTORID::PROJECTOR_ID_RIGHT].resize(14);
		for (int r = 0; r < 14; ++r) {
			proj_kcs[PROJECTORID::PROJECTOR_ID_UP](r) = node["projU_kc"]["data"][r].as<double>();
			proj_kcs[PROJECTORID::PROJECTOR_ID_DOWN](r) = node["projD_kc"]["data"][r].as<double>();
			proj_kcs[PROJECTORID::PROJECTOR_ID_LEFT](r) = node["projL_kc"]["data"][r].as<double>();
			proj_kcs[PROJECTORID::PROJECTOR_ID_RIGHT](r) = node["projR_kc"]["data"][r].as<double>();
		}
		
		Ts[PROJECTORID::PROJECTOR_ID_UP].resize(2);
		Ts[PROJECTORID::PROJECTOR_ID_DOWN].resize(2);
		Ts[PROJECTORID::PROJECTOR_ID_LEFT].resize(2);
		Ts[PROJECTORID::PROJECTOR_ID_RIGHT].resize(2);

		for (int r = 0; r < 2; ++r) {
			Ts[PROJECTORID::PROJECTOR_ID_UP](r) = node["Tu"]["data"][r].as<double>();
			Ts[PROJECTORID::PROJECTOR_ID_DOWN](r) = node["Td"]["data"][r].as<double>();
			Ts[PROJECTORID::PROJECTOR_ID_LEFT](r) = node["Tl"]["data"][r].as<double>();
			Ts[PROJECTORID::PROJECTOR_ID_RIGHT](r) = node["Tr"]["data"][r].as<double>();
		}

		//delta_phi_local_coeffs.ppm
		phase_height_map_coeffs[PROJECTORID::PROJECTOR_ID_UP].resize(27);
		phase_height_map_coeffs[PROJECTORID::PROJECTOR_ID_DOWN].resize(27);
		phase_height_map_coeffs[PROJECTORID::PROJECTOR_ID_LEFT].resize(27);
		phase_height_map_coeffs[PROJECTORID::PROJECTOR_ID_RIGHT].resize(27);
		for (int r = 0; r < 27; ++r) {
			phase_height_map_coeffs[PROJECTORID::PROJECTOR_ID_UP](r) = node["PHMapU"]["data"][r].as<double>();
			phase_height_map_coeffs[PROJECTORID::PROJECTOR_ID_DOWN](r) = node["PHMapD"]["data"][r].as<double>();
			phase_height_map_coeffs[PROJECTORID::PROJECTOR_ID_LEFT](r) = node["PHMapL"]["data"][r].as<double>();
			phase_height_map_coeffs[PROJECTORID::PROJECTOR_ID_RIGHT](r) = node["PHMapR"]["data"][r].as<double>();
		}

		return true;
	}

	bool ProCalibrationData::load_calibration_yml2(std::string const& filename)
	{
		YAML::Node node = YAML::LoadFile(filename);
		if (node.IsNull()) {
			return false;
		}

		int proj_num = node["proj_num"].as<int>();
		std::vector<PROJECTORID>proj_idx;
		std::string select = "1234";
		std::string name = "Projector";
		for (int i = 0; i < proj_num; i++)
		{
			std::string proj_name = name + select[i];
			proj_idx.push_back((PROJECTORID)node["proj_idx"][proj_name].as<int>());
		}

		std::map<PROJECTORID, std::string>positions;
		positions[PROJECTORID::PROJECTOR_ID_UP] = "U";
		positions[PROJECTORID::PROJECTOR_ID_DOWN] = "D";
		positions[PROJECTORID::PROJECTOR_ID_LEFT] = "L";
		positions[PROJECTORID::PROJECTOR_ID_RIGHT] = "R";

		for (int num = 0; num < proj_num; num++)
		{
			proj_Ks[proj_idx[num]].resize(3, 3);
			proj_Rs[proj_idx[num]].resize(3, 3);
			Rs[proj_idx[num]].resize(3, 3);
			proj_Ts[proj_idx[num]].resize(3);
			proj_kcs[proj_idx[num]].resize(14);
			Ts[proj_idx[num]].resize(2);
			std::string proj_Ts_name = "proj" + positions[proj_idx[num]] + "_T";
			std::string proj_Ks_name = "proj" + positions[proj_idx[num]] + "_K";
			std::string proj_Rs_name = "proj" + positions[proj_idx[num]] + "_R";
			std::string Rs_name = "R" + positions[proj_idx[num]];
			std::string proj_kcs_name = "proj" + positions[proj_idx[num]] + "_kc";
			std::string Ts_name = "T" + positions[proj_idx[num]];
			for (int i = 0; i < 3; i++)
			{
				proj_Ts[proj_idx[num]](i) = node[proj_Ts_name]["data"][i].as<double>();
				for (int j = 0; j < 3; j++)
				{
					proj_Ks[proj_idx[num]](i, j) = node[proj_Ks_name]["data"][3 * i + j].as<double>();
					proj_Rs[proj_idx[num]](i, j) = node[proj_Rs_name]["data"][3 * i + j].as<double>();
					Rs[proj_idx[num]](i, j) = node[Rs_name]["data"][3 * i + j].as<double>();
				}
			}

			for (int r = 0; r < 14; r++)
			{
				proj_kcs[proj_idx[num]](r) = node[proj_kcs_name]["data"][r].as<double>();
			}
			for (int r = 0; r < 2; r++)
			{
				Ts[proj_idx[num]](r) = node[Ts_name]["data"][r].as<double>();
			}
		}
		cam_K.resize(3, 3);
		cam_R.resize(3, 3);
		cam_M.resize(3, 4);
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				cam_K(i, j) = node["cam_K"]["data"][j + 3 * i].as<double>();
				cam_R(i, j) = node["cam_R"]["data"][j + 3 * i].as<double>();
			}
			for (int k = 0; k < 4; k++)
			{
				cam_M(i, k) = node["cam_M"]["data"][k + 4 * i].as<double>();
			}
		}
		std::string PHMap_name = "PHMaps" + positions[proj_idx[0]];
		if (node[PHMap_name]["rows"].as<std::string>() != "null")
		{
			for (int i = 0; i < proj_num; i++)
			{
				std::string PHMaps_name = "PHMaps" + positions[proj_idx[i]];
				phase_height_map_coeffs[proj_idx[i]].resize(27);
				for (int r = 0; r < 27; r++)
				{
					phase_height_map_coeffs[proj_idx[i]](r) = node[PHMaps_name]["data"][r].as<double>();
				}
			}
		}

		//读取pfm文件获得delta_phi_local_coeffs
		for (int i = 0; i < proj_num; i++)
		{
			std::string delta_coeffs_name = "delta_phi_local_coeffs_" + positions[proj_idx[i]];
			std::string save_root = node[delta_coeffs_name]["root"].as<std::string>();
			Eigen::MatrixXd& ply_coeffs = delta_phi_local_coeffs[proj_idx[i]].getCoeffs();
			ply_coeffs = PFM::read_pfm_eigen(save_root);
			int order = node[delta_coeffs_name]["Order"].as<int>();
			double scale = node[delta_coeffs_name]["Scale"].as<double>();
			delta_phi_local_coeffs[proj_idx[i]].setOrder(order);
			delta_phi_local_coeffs[proj_idx[i]].setScale(scale);
		}

	}

	bool ProCalibrationData::save_calibration_yml(std::string const& filename)
	{
		//将光机数量及对应id属性存入yml文件
		YAML::Node node;

		std::vector<PROJECTORID>proj_idx;
		for (std::map<PROJECTORID, Eigen::MatrixXd>::iterator it = proj_Ks.begin(); it != proj_Ks.end(); it++)
		{
			proj_idx.push_back(it->first);
		}
		int proj_num = proj_idx.size();
		node["proj_num"] = proj_num;
		std::string select = "1234";
		std::string name = "Projector";
		for (int i = 0; i < proj_num; i++)
		{
			std::string proj_name = name + select[i];
			int id = (int)proj_idx[i];
			node["proj_idx"][proj_name] = id;
		}

		//存放矩阵值
		std::vector<double>vcam_K, vcam_kc, vcam_R, vcam_T, vcam_M;
		std::vector<std::vector<double>>vproj_Ks(proj_num), vproj_kcs(proj_num), vproj_Rs(proj_num),
			vproj_Ts(proj_num), vproj_Es(proj_num), vRs(proj_num), vTs(proj_num), vphMaps(proj_num);

		std::map<PROJECTORID, std::string>positions;
		positions[PROJECTORID::PROJECTOR_ID_UP] = "U";
		positions[PROJECTORID::PROJECTOR_ID_DOWN] = "D";
		positions[PROJECTORID::PROJECTOR_ID_LEFT] = "L";
		positions[PROJECTORID::PROJECTOR_ID_RIGHT] = "R";

		//将Eigen值存入vector
		//1、光机
		for (int num = 0; num < proj_num; num++)
		{
			for (int i = 0; i < 3; i++)
			{
				vproj_Ts[num].push_back(proj_Ts[proj_idx[num]](i));

				for (int j = 0; j < 3; j++)
				{
					vproj_Ks[num].push_back(proj_Ks[proj_idx[num]](i, j));
					vproj_Rs[num].push_back(proj_Rs[proj_idx[num]](i, j));
					vRs[num].push_back(Rs[proj_idx[num]](i, j));
				}
			}
			for (int r = 0; r < 14; r++)
			{
				vproj_kcs[num].push_back(proj_kcs[proj_idx[num]](r));
			}
			for (int r = 0; r < 2; r++)
			{
				vTs[num].push_back(Ts[proj_idx[num]](r));
			}
			//Es可能为空，加判断
			if (proj_Es.size() != 0)
			{
				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						vproj_Es[num].push_back(proj_Es[proj_idx[num]](i, j));
					}
				}
			}
			//phMaps可能为空，加判断
			if (phase_height_map_coeffs.size() != 0)
			{
				for (int r = 0; r < 27; r++)
				{
					vphMaps[num].push_back(phase_height_map_coeffs[proj_idx[num]](r));
				}
			}
		}

		//2、相机
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				vcam_M.push_back(cam_M(i, j));
			}
			for (int k = 0; k < 3; k++)
			{
				vcam_K.push_back(cam_K(i, k));
				vcam_R.push_back(cam_R(i, k));
			}
		}
		for (int r = 0; r < 4; r++)
		{
			vcam_kc.push_back(cam_kc(r));
		}
		for (int r = 0; r < 2; r++)
		{
			vcam_T.push_back(cam_T(r));
		}

		//写入标定文件
		node["cam_K"]["rows"] = cam_K.rows();
		node["cam_K"]["cols"] = cam_K.cols();
		node["cam_K"]["data"] = vcam_K;

		node["cam_kc"]["rows"] = cam_kc.size();
		node["cam_kc"]["cols"] = 1;
		node["cam_kc"]["data"] = vcam_kc;

		node["cam_R"]["rows"] = cam_R.rows();
		node["cam_R"]["cols"] = cam_R.cols();
		node["cam_R"]["data"] = vcam_R;

		node["cam_T"]["rows"] = cam_T.size();
		node["cam_T"]["cols"] = 1;
		node["cam_T"]["data"] = vcam_T;

		node["cam_M"]["rows"] = cam_M.rows();
		node["cam_M"]["cols"] = cam_M.cols();
		node["cam_M"]["data"] = vcam_M;

		for (int i = 0; i < proj_num; i++)
		{
			std::string proj_Ks_name = "proj" + positions[proj_idx[i]] + "_K";
			node[proj_Ks_name]["rows"] = proj_Ks[proj_idx[i]].rows();
			node[proj_Ks_name]["cols"] = proj_Ks[proj_idx[i]].cols();
			node[proj_Ks_name]["data"] = vproj_Ks[i];
		}
		for (int i = 0; i < proj_num; i++)
		{
			std::string proj_kcs_name = "proj" + positions[proj_idx[i]] + "_kc";
			node[proj_kcs_name]["rows"] = 1;
			node[proj_kcs_name]["cols"] = proj_kcs[proj_idx[i]].size();
			node[proj_kcs_name]["data"] = vproj_kcs[i];
		}
		for (int i = 0; i < proj_num; i++)
		{
			std::string proj_Rs_name = "proj" + positions[proj_idx[i]] + "_R";
			node[proj_Rs_name]["rows"] = proj_Rs[proj_idx[i]].rows();
			node[proj_Rs_name]["cols"] = proj_Rs[proj_idx[i]].cols();
			node[proj_Rs_name]["data"] = vproj_Rs[i];
		}
		for (int i = 0; i < proj_num; i++)
		{
			std::string proj_Ts_name = "proj" + positions[proj_idx[i]] + "_T";
			node[proj_Ts_name]["rows"] = proj_Ts[proj_idx[i]].size();
			node[proj_Ts_name]["cols"] = 1;
			node[proj_Ts_name]["data"] = vproj_Ts[i];
		}
		//若Es为空，写入null
		if (proj_Es.size() == 0)
		{
			for (int i = 0; i < proj_num; i++)
			{
				std::string proj_Es_name = "proj" + positions[proj_idx[i]] + "_E";
				node[proj_Es_name]["rows"] = "null";
				node[proj_Es_name]["cols"] = "null";
				node[proj_Es_name]["data"] = "null";
			}
		}
		else
		{
			for (int i = 0; i < proj_num; i++)
			{
				std::string proj_Es_name = "proj" + positions[proj_idx[i]] + "_E";
				node[proj_Es_name]["rows"] = proj_Es[proj_idx[i]].rows();
				node[proj_Es_name]["cols"] = proj_Es[proj_idx[i]].cols();
				node[proj_Es_name]["data"] = vproj_Es[i];
			}
		}
		for (int i = 0; i < proj_num; i++)
		{
			std::string Rs_name = "R" + positions[proj_idx[i]];
			node[Rs_name]["rows"] = Rs[proj_idx[i]].rows();
			node[Rs_name]["cols"] = Rs[proj_idx[i]].cols();
			node[Rs_name]["data"] = vRs[i];
		}
		for (int i = 0; i < proj_num; i++)
		{
			std::string Ts_name = "T" + positions[proj_idx[i]];
			node[Ts_name]["rows"] = Ts[proj_idx[i]].size();
			node[Ts_name]["cols"] = 1;
			node[Ts_name]["data"] = vTs[i];
		}
		//若phMaps为空，写入null
		if (phase_height_map_coeffs.size() == 0)
		{
			for (int i = 0; i < proj_num; i++)
			{
				std::string PHMaps_name = "PHMaps" + positions[proj_idx[i]];
				node[PHMaps_name]["rows"] = "null";
				node[PHMaps_name]["cols"] = "null";
				node[PHMaps_name]["data"] = "null";
			}
		}
		else
		{
			for (int i = 0; i < proj_num; i++)
			{
				std::string PHMaps_name = "PHMaps" + positions[proj_idx[i]];
				node[PHMaps_name]["rows"] = phase_height_map_coeffs[proj_idx[i]].size();
				node[PHMaps_name]["cols"] = 1;
				node[PHMaps_name]["data"] = vphMaps[i];
			}
		}
		//保存delta_phi_local_coeffs.pfm文件路径 order scale
		for (int i = 0; i < proj_num; i++)
		{
			std::string delta_coeffs_name = "delta_phi_local_coeffs_" + positions[proj_idx[i]];
			node[delta_coeffs_name]["root"] = delta_phi_local_coeffs[proj_idx[i]].getRoot();
			node[delta_coeffs_name]["Order"] = delta_phi_local_coeffs[proj_idx[i]].getOrder();
			node[delta_coeffs_name]["Scale"] = delta_phi_local_coeffs[proj_idx[i]].getScale();
		}

		std::ofstream fout;
		fout.open(filename, std::ios::out);
		fout << node;
		return true;
	}

	LumenCalibrationData::LumenCalibrationData(const LumenCalibrationData& rhs){
		this->m_errorCode = rhs.m_errorCode;
		this->m_getData = rhs.m_getData;
		this->m_lumenData = rhs.m_lumenData;
	}
}