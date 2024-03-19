#include "as/ComponentCore.hpp"

namespace as
{
	NoGoodParam::NoGoodParam()
	{
		m_dRoiWidth = 0;
		m_dRoiHight = 0;
		m_dRoiAngle = 0;
		m_eDefectType = AOI_DefectType::Offset;
		m_strNGID = "";
		m_tRegistration = false;
		m_strApplicationType = "";
		m_pAlgorithmParam.clear();
		m_Resolution = 15;
		m_NgImageBase.clear();
		m_strApplicationType = "10000";
	}

	NoGoodParam& NoGoodParam::operator=(NoGoodParam& ref)
	{
		this->m_singleNGMechPos = ref.GetRoiMechPosition();
		this->m_cRoiPos = ref.GetRoiPosition();
		this->m_dRoiWidth = ref.GetRoiWidth();
		this->m_dRoiHight = ref.GetRoiHight();
		this->m_eDefectType = ref.GetDefectType();
		this->m_strNGID = ref.GetNGID();
		this->m_NgImageBase.swap(ref.GetNGImage());
		this->m_tRegistration = ref.GetRegistration();
		this->m_strApplicationType = ref.GetApplicationType();
		this->m_pAlgorithmParam.clear();
		this->m_Resolution = ref.GetResolution();
		map<AOI_Algorithm_Type, shared_ptr<AOIAlgorithmParam>> all_AlgorithmParam = ref.GetAllAlgorithmParam();
		for (auto algorithn_iter = all_AlgorithmParam.begin(); algorithn_iter != all_AlgorithmParam.end(); algorithn_iter++)
		{
			shared_ptr<AOIAlgorithmParam> temp_pAlgorithmParam;
			AOI_Algorithm_Type temp_algorithm_type = algorithn_iter->second->getAlgorithmTypeData();
			switch (temp_algorithm_type)
			{
			case AOI_Algorithm_Type::TOC:
				temp_pAlgorithmParam = make_shared<TOCParam>(*std::dynamic_pointer_cast<TOCParam>(algorithn_iter->second));
				break;
			case AOI_Algorithm_Type::Match:
				temp_pAlgorithmParam = make_shared<MatchParam>(*std::dynamic_pointer_cast<MatchParam>(algorithn_iter->second));
				break;
			case AOI_Algorithm_Type::Histogram:
				temp_pAlgorithmParam = make_shared<HISTOParam>(*std::dynamic_pointer_cast<HISTOParam>(algorithn_iter->second));
				break;
			case AOI_Algorithm_Type::OCV:
				temp_pAlgorithmParam = make_shared<OCVParam>(*std::dynamic_pointer_cast<OCVParam>(algorithn_iter->second));
				break;
			case AOI_Algorithm_Type::Compare:
				temp_pAlgorithmParam = make_shared<CompareParam>(*std::dynamic_pointer_cast<CompareParam>(algorithn_iter->second));
				break;
			case AOI_Algorithm_Type::Distance:
				temp_pAlgorithmParam = make_shared<DistanceParam>(*std::dynamic_pointer_cast<DistanceParam>(algorithn_iter->second));
				break;
			case AOI_Algorithm_Type::Glue:
				temp_pAlgorithmParam = make_shared<GLUEParam>(*std::dynamic_pointer_cast<GLUEParam>(algorithn_iter->second));
				break;
			case AOI_Algorithm_Type::Length:
				temp_pAlgorithmParam = make_shared<LengthParam>(*std::dynamic_pointer_cast<LengthParam>(algorithn_iter->second));
				break;
			case AOI_Algorithm_Type::Padplace:
				temp_pAlgorithmParam = make_shared<PadplaceParam>(*std::dynamic_pointer_cast<PadplaceParam>(algorithn_iter->second));
				break;
			case AOI_Algorithm_Type::PIN:
				temp_pAlgorithmParam = make_shared<PINParam>(*std::dynamic_pointer_cast<PINParam>(algorithn_iter->second));
				break;
			case AOI_Algorithm_Type::Pole:
				temp_pAlgorithmParam = make_shared<PoleParam>(*std::dynamic_pointer_cast<PoleParam>(algorithn_iter->second));
				break;
			case AOI_Algorithm_Type::Short:
				temp_pAlgorithmParam = make_shared<ShortParam>(*std::dynamic_pointer_cast<ShortParam>(algorithn_iter->second));
				break;
			case AOI_Algorithm_Type::Match2:
				temp_pAlgorithmParam = make_shared<Match2Param>(*std::dynamic_pointer_cast<Match2Param>(algorithn_iter->second));
				break;
			case AOI_Algorithm_Type::Other:
				temp_pAlgorithmParam = make_shared<OtherParam>(*std::dynamic_pointer_cast<OtherParam>(algorithn_iter->second));
				break;
			case AOI_Algorithm_Type::ALOffset:
				temp_pAlgorithmParam = make_shared<ALOffsetParam>(*std::dynamic_pointer_cast<ALOffsetParam>(algorithn_iter->second));
				break;
			case AOI_Algorithm_Type::Crest:
				temp_pAlgorithmParam = make_shared<CrestParam>(*std::dynamic_pointer_cast<CrestParam>(algorithn_iter->second));
				break;
			case AOI_Algorithm_Type::Hole:
				temp_pAlgorithmParam = make_shared<HoleParam>(*std::dynamic_pointer_cast<HoleParam>(algorithn_iter->second));
				break;
			case AOI_Algorithm_Type::Barcode:
				temp_pAlgorithmParam = make_shared<BarcodeParam>(*std::dynamic_pointer_cast<BarcodeParam>(algorithn_iter->second));
				break;
			default:
				break;
			}
			*temp_pAlgorithmParam = *algorithn_iter->second;
			this->InsertAlgorithmParam(temp_algorithm_type, temp_pAlgorithmParam);
		}
		return *this;
	}

	Point NoGoodParam::GetRoiPosition()
	{
		return m_cRoiPos;
	}

	void NoGoodParam::SetRoiPosition(Point pos)
	{
		m_cRoiPos = pos;
 	}

	// 存储单个NG的机械坐标
	Point NoGoodParam::GetRoiMechPosition()
	{
		return m_singleNGMechPos;
	}

	void NoGoodParam::SetRoiMechPosition(Point pos)
	{
		m_singleNGMechPos = pos;
	}
	// 存储单个NG的机械坐标

	double NoGoodParam::GetRoiWidth()
	{
		return m_dRoiWidth;
	}

	void NoGoodParam::SetRoiWidth(double width)
	{
		m_dRoiWidth = width;
	}

	double NoGoodParam::GetRoiHight()
	{
		return m_dRoiHight;
	}

	void NoGoodParam::SetRoiHight(double hight)
	{
		m_dRoiHight = hight;
	}

	double NoGoodParam::GetRoiAngle()
	{
		return m_dRoiAngle;
	}

	void NoGoodParam::SetRoiAngle(double angle)
	{
		m_dRoiHight = angle;
	}

	AOI_DefectType NoGoodParam::GetDefectType()
	{
		return m_eDefectType;
	}

	void NoGoodParam::SetDefectType(AOI_DefectType defect_type)
	{
		m_eDefectType = defect_type;
	}

	string NoGoodParam::GetNGID()
	{
		return m_strNGID;
	}

	void NoGoodParam::SetNGID(string ng_id)
	{
		m_strNGID = ng_id;
	}

	bool NoGoodParam::GetRegistration()
	{
		return m_tRegistration;
	}

	void NoGoodParam::SetRegistration(bool registration)
	{
		m_tRegistration = registration;
	}

	string NoGoodParam::GetApplicationType()
	{
		return m_strApplicationType;
	}

	void NoGoodParam::SetApplicationType(string applica_type)
	{
		m_strApplicationType = applica_type;
	}

	map<AOI_Algorithm_Type, shared_ptr<AOIAlgorithmParam>> NoGoodParam::GetAllAlgorithmParam()
	{
		return m_pAlgorithmParam;
	}

	void NoGoodParam::ClearAlgorithmParam()
	{
		m_pAlgorithmParam.clear();
	}

	void NoGoodParam::InsertAlgorithmParam(AOI_Algorithm_Type algorithm_type, shared_ptr<AOIAlgorithmParam> algorithm_param)
	{
		m_pAlgorithmParam.insert(pair<AOI_Algorithm_Type, shared_ptr<AOIAlgorithmParam>>(algorithm_type, algorithm_param));
	}

	void NoGoodParam::DeleteAlgorithmParam(AOI_Algorithm_Type algorithm_type)
	{
		if (m_pAlgorithmParam.find(algorithm_type) != m_pAlgorithmParam.end())
		{
			m_pAlgorithmParam.erase(m_pAlgorithmParam.find(algorithm_type));
		}
	}

	bool NoGoodParam::FindAlgorithm(AOI_Algorithm_Type algorithm_type)
	{
		if (m_pAlgorithmParam.find(algorithm_type) == m_pAlgorithmParam.end())
		{
			return false;
		}
		return true;
	}

	shared_ptr<AOIAlgorithmParam> NoGoodParam::GetAlgorithmParam(AOI_Algorithm_Type algorithm_type)
	{
		shared_ptr<AOIAlgorithmParam> algor_param;
		if (m_pAlgorithmParam.find(algorithm_type) != m_pAlgorithmParam.end())
		{
			algor_param = m_pAlgorithmParam.find(algorithm_type)->second;
		}
		return algor_param;
	}

	shared_ptr<AOIAlgorithmParam> NoGoodParam::GetUseAlgorithmParam()
	{
		for (auto iter = m_pAlgorithmParam.begin(); iter != m_pAlgorithmParam.end(); iter++)
		{
			if (iter->second->getAlgorithmUseFlag())
			{
				return iter->second;
			}
		}
		return nullptr;
	}

	void  NoGoodParam::SetUseAlgorithmParam(AOI_Algorithm_Type algorithm_type)
	{
		for (auto algorithm_iter = m_pAlgorithmParam.begin(); algorithm_iter != m_pAlgorithmParam.end(); algorithm_iter++)
		{
			if (algorithm_iter->first == algorithm_type)
			{
				algorithm_iter->second->SetlgorithmUseFlag(true);
			}
			else
			{
				algorithm_iter->second->SetlgorithmUseFlag(false);
			}
		}
	}

	Component::Component()
	{
		m_strPackageType = "";
		m_strCompName = "";
		m_vpNGParam.clear();
		m_ePackageType = PackageType::CHIP_R;	
		m_vImageData.clear();
		m_dCompWidth = 0;
		m_dCompHeight = 0;
		m_bIsExistInDB = false;
	}

	Component& Component::operator=(Component& ref)
	{
		this->m_ePackageType = ref.GetPackageType();
		this->m_strPackageType = ref.GetPackageTypeName();
		this->m_strCompName = ref.GetCompName();
		this->m_bIsExistInDB = ref.GetIsExistInDB();
		this->m_vImageData.swap(ref.GetImageData());
		this->m_vpNGParam.clear();
		NoGoodParam temp_ng_param;
		map<string, NoGoodParam> temp_allngparam = ref.GetAllNoGoodParam();
		for (auto ng_param_iter = temp_allngparam.begin(); ng_param_iter != temp_allngparam.end(); ng_param_iter++)
		{
			temp_ng_param = ng_param_iter->second;
			this->m_vpNGParam.insert(pair<string, NoGoodParam>(ng_param_iter->first, temp_ng_param));
		}
		return *this;
	}

	PackageType Component::GetPackageType()
	{
		return m_ePackageType;
	}

	void Component::SetPackageType(PackageType package_type)
	{
		m_ePackageType = package_type;
	}

	string Component::GetPackageTypeName()
	{
		return m_strPackageType;
	}

	void Component::SetPackageTypeName(string package_type)
	{
		m_strPackageType = package_type;
	}

	string Component::GetCompName()
	{
		return m_strCompName;
	}

	void Component::SetCompName(string name)
	{
		m_strCompName = name;
	}

	map<string, NoGoodParam> Component::GetAllNoGoodParam()
	{
		return m_vpNGParam;
	}

	void Component::InsertNoGoodParam(string ng_id, NoGoodParam ng_param)
	{
		m_vpNGParam.insert(pair<string, NoGoodParam>(ng_id, ng_param));
	}

	void Component::DeleteNoGoodParam(string ng_id)
	{
		if (m_vpNGParam.find(ng_id) != m_vpNGParam.end())
		{
			m_vpNGParam.erase(m_vpNGParam.find(ng_id));
		}
	}

	inline bool Component::FindNoGoodParam(string ng_id)
	{
		if (m_vpNGParam.find(ng_id) == m_vpNGParam.end())
		{
			return false;
		}
		return true;
	}

	NoGoodParam& Component::GetNoGoodParam(string ng_id)
	{
		if (m_vpNGParam.find(ng_id) != m_vpNGParam.end())
		{
			return m_vpNGParam.find(ng_id)->second;
		}
		NoGoodParam ng_param;
		return ng_param;
	}

	void Component::UpdateNoGoodParam(string ng_id, NoGoodParam ng_param)
	{
		if (m_vpNGParam.find(ng_id) != m_vpNGParam.end())
		{
			m_vpNGParam.find(ng_id)->second = ng_param;
		}
	}

	vector<unsigned char> Component::GetImageData()
	{
		return m_vImageData;
	}

	void Component::SetImageData(vector<unsigned char> image_data)
	{
		m_vImageData.clear();
		m_vImageData = image_data;
	}

	void Component::SetIsExistInDB(bool flag)
	{
		m_bIsExistInDB = flag;
	}

	bool Component::GetIsExistInDB()
	{
		return m_bIsExistInDB;
	}

	double Component::ComputeCompoentWidth()
	{
		//遍历NG找到距离中心的最远的2个点位置
		double left_max_x = m_vpNGParam.begin()->second.GetRoiPosition().x;
		double right_max_x = m_vpNGParam.begin()->second.GetRoiPosition().x + m_vpNGParam.begin()->second.GetRoiWidth();
		for (auto ng_iter = m_vpNGParam.begin(); ng_iter != m_vpNGParam.end(); ng_iter++)
		{
			if (ng_iter == m_vpNGParam.begin())
			{
				continue;
			}

			Point roi_pos = ng_iter->second.GetRoiPosition();
			double aoi_width = ng_iter->second.GetRoiWidth();

			if (left_max_x - roi_pos.x > 1e-3)
			{
				left_max_x = roi_pos.x;
			}

			if (roi_pos.x + aoi_width - right_max_x > 1e-3)
			{
				right_max_x = roi_pos.x + aoi_width;
			}
		}
		//计算元件大小
		return right_max_x - left_max_x + 0.95;
	}

	double Component::ComputeCompoentHeight()
	{
		//遍历NG找到距离中心的最远的2个点位置
		double top_max_y = m_vpNGParam.begin()->second.GetRoiPosition().y + m_vpNGParam.begin()->second.GetRoiHight();
		double down_max_y = m_vpNGParam.begin()->second.GetRoiPosition().y;
		for (auto ng_iter = m_vpNGParam.begin(); ng_iter != m_vpNGParam.end(); ng_iter++)
		{
			if (ng_iter == m_vpNGParam.begin())
			{
				continue;
			}
			Point roi_pos = ng_iter->second.GetRoiPosition();
			double aoi_height = ng_iter->second.GetRoiHight();

			if (down_max_y - roi_pos.y > 1e-3)
			{
				down_max_y = roi_pos.y;
			}

			if (roi_pos.y + aoi_height - top_max_y > 1e-3)
			{
				top_max_y = roi_pos.y + aoi_height;
			}
		}
		//计算元件大小
		return top_max_y - down_max_y + 0.95;
	}

	ComponentData::ComponentData()
	{
		m_mCompList.clear();
	}

	map<string, shared_ptr<Component>> ComponentData::GetAllComponent()
	{
		return m_mCompList;
	}

	void ComponentData::InsertComponent(string package_name, shared_ptr<Component> component)
	{
		m_mCompList.insert(pair<string, shared_ptr<Component>>(package_name, component));
	}

	void ComponentData::DeleteComponent(string package_name)
	{
		if (FindComponent(package_name))
		{
			auto comp_iter = m_mCompList.find(package_name);
			m_mCompList.erase(comp_iter);
		}
	}

	bool ComponentData::FindComponent(string package_name)
	{
		if (m_mCompList.find(package_name) == m_mCompList.end())
		{
			return false;
		}
		return true;
	}

	//bool ComponentData::FindStrComponent(string package_name)
	//{
	//	/*if (m_mCompList.find(package_name) == m_mCompList.end())
	//	{
	//		return false;
	//	}*/
	//	return true;
	//}

	shared_ptr<Component> ComponentData::GetComponent(string package_name)
	{
		if (FindComponent(package_name))
		{
			return m_mCompList.find(package_name)->second;
		}
		return nullptr;
	}
}