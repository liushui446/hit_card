#include "as/PadCore.hpp"

namespace as
{

	DetectionPadData::DetectionPadData()
	{
		m_PadName = 1;
		m_PadArea = 0;
		m_PadThickness = 0;
		m_BodyPosition.x = 0;
		m_BodyPosition.y = 0;
		m_dAngle = 0;
		m_dOutsideDiameter = 0;  //外径
		m_dInsideDiameter = 0;	//内径
		m_ptrSpiAlgorithmParam = std::make_shared<SPIAlgorithmParam>();
	}

	DetectionPadData& DetectionPadData::operator=(DetectionPadData& ref)
	{
		this->m_PadArea = ref.GetPadArea();
		this->m_PadName = ref.GetPadName();
		this->m_padshape_grpname = ref.GetPadShape();
		this->m_nBlockId = ref.GetBlockId();
		this->m_nArrayId = ref.GetArrayId();
		this->m_BodyPosition = ref.GetBodyPosition();
		this->m_RoiPosition = ref.GetPadRoiPos();
		this->m_dBodyWidth = ref.GetBodyWidth();
		this->m_dBodyHeight = ref.GetBodyHeight();
		this->m_dInsideDiameter = ref.GetInDiameter();
		this->m_dOutsideDiameter = ref.GetOutDiameter();
		this->m_dAngle = ref.GetAngle();
		this->m_bSkip = ref.GetSkip();
		this->m_bCompleteDetection = ref.GetCompleteDetection();
		if (ref.GetSpiAlgorithmParam() != nullptr)
		{
			this->m_ptrSpiAlgorithmParam = make_shared<SPIAlgorithmParam>();
			*this->m_ptrSpiAlgorithmParam = *ref.GetSpiAlgorithmParam();
		}
		else
		{
			this->m_ptrSpiAlgorithmParam = nullptr;
		}
		return *this;
	}

	void DetectionPadData::SetPadName(int name)
	{
		m_PadName = name;
	}

	int DetectionPadData::GetPadName()
	{
		return m_PadName;
	}

	double DetectionPadData::GetOutDiameter()
	{
		return m_dOutsideDiameter;
	}

	void DetectionPadData::SetOutDiameter(double val)
	{
		m_dOutsideDiameter = val;
	}

	double DetectionPadData::GetInDiameter()
	{
		return m_dInsideDiameter;
	}

	void DetectionPadData::SetInDiameter(double val)
	{
		m_dInsideDiameter = val;
	}

	PadShape DetectionPadData::GetPadShape()
	{
		return m_padshape_grpname;
	}

	void DetectionPadData::SetPadShape(PadShape shape)
	{
		m_padshape_grpname = shape;
	}

	SPIAlgorithmParamPtr DetectionPadData::GetSpiAlgorithmParam()
	{
		return m_ptrSpiAlgorithmParam;
	}

	void DetectionPadData::SetSpiAlgorithmParam(SPIAlgorithmParamPtr algoparam)
	{
		m_ptrSpiAlgorithmParam = algoparam;
	}

	void DetectionPadData::SetPadArea(double area)
	{
		m_PadArea = area;
	}

	double DetectionPadData::GetPadArea()
	{
		return m_PadArea;
	}

	void DetectionPadData::SetPadThickness(double thickness)
	{
		m_PadThickness = thickness;
	}

	double DetectionPadData::GetPadThickness()
	{
		return m_PadThickness;
	}

	void DetectionPadData::SetPadRoiPos(Point roi_pos)
	{
		m_RoiPosition = roi_pos;
	}

	Point DetectionPadData::GetPadRoiPos()
	{
		return m_RoiPosition;
	}

	PadDataSet::PadDataSet()
	{
		m_pDetectionPadDataSet.clear();
		m_pPadGroupManager = make_shared<PadGroupManager>();
	}

	map<string, map<DWORD, shared_ptr<DetectionPadData>>> PadDataSet::GetAllPadData()
	{
		return m_pDetectionPadDataSet;
	}

	map<DWORD, shared_ptr<DetectionPadData>> PadDataSet::GetLayerPadData(string layername)
	{
		if (FindLayerPadData(layername))
		{
			return m_pDetectionPadDataSet.at(layername);
		}
		return map<DWORD, shared_ptr<DetectionPadData>>();
	}

	//获取单个焊盘数据
	shared_ptr<DetectionPadData> PadDataSet::GetSinglePadData(string layername, DWORD name)
	{
		if (FindLayerPadData(layername))
		{
			if (m_pDetectionPadDataSet.at(layername).find(name) != m_pDetectionPadDataSet.at(layername).end())
			{
				return m_pDetectionPadDataSet.at(layername).at(name);
			}
		}
		return shared_ptr<DetectionPadData>();
	}

	//插入单个焊盘数据
	void PadDataSet::InsertSinglePadData(string layername, DWORD name, shared_ptr<DetectionPadData> data)
	{
		if (FindLayerPadData(layername))
		{
			m_pDetectionPadDataSet.at(layername).insert(pair<DWORD, shared_ptr<DetectionPadData>>(name, data));
		}
		else
		{
			map<DWORD, shared_ptr<DetectionPadData>> temp_ImportPadDatalist;
			temp_ImportPadDatalist.insert(pair<DWORD, shared_ptr<DetectionPadData>>(name, data));
			m_pDetectionPadDataSet.insert(pair<string, map<DWORD, shared_ptr<DetectionPadData>>>(layername, temp_ImportPadDatalist));
		}
	}

	//查找层预处理数据
	bool PadDataSet::FindLayerPadData(string layername)
	{
		if (m_pDetectionPadDataSet.find(layername) != m_pDetectionPadDataSet.end())
		{
			return true;
		}
		return false;
	}

	//删除单个Gerber层焊盘数据
	void PadDataSet::DeleteSingleLayerPadData(string name)
	{
		if (m_pDetectionPadDataSet.find(name) != m_pDetectionPadDataSet.end())
		{
			m_pDetectionPadDataSet.erase(m_pDetectionPadDataSet.find(name));
		}
	}

	//查找单个焊盘数据
	bool PadDataSet::FindSinglePadData(string layername, DWORD padid)
	{
		if (FindLayerPadData(layername))
		{
			if (m_pDetectionPadDataSet.find(layername)->second.find(padid) != m_pDetectionPadDataSet.find(layername)->second.end())
			{
				return true;
			}
		}
		return false;
	}

	//删除单个焊盘数据
	void PadDataSet::DeleteSinglePadData(string layername, DWORD name)
	{
		m_pDetectionPadDataSet.find(layername)->second.erase(m_pDetectionPadDataSet.find(layername)->second.find(name));
	}
	
	//获取焊盘分组管理类指针
	shared_ptr<PadGroupManager> PadDataSet::GetPadGroupManager()
	{
		return m_pPadGroupManager;
	}

	map<string, Aperture> PadDataSet::GetAllApertureData()
	{
		return m_pApertureDefinateSet;
	}

	bool PadDataSet::FindApertureData(string code)
	{
		if (m_pApertureDefinateSet.find(code) != m_pApertureDefinateSet.end())
		{
			return true;
		}
		return false;
	}

	Aperture PadDataSet::GetSingleApertureData(string code)
	{
		if (FindApertureData(code))
		{
			return m_pApertureDefinateSet.at(code);
		}
		return Aperture();
	}

	void PadDataSet::InsertSingleApertureData(string code, Aperture aperture_data)
	{
		if (!FindApertureData(code))
		{
			m_pApertureDefinateSet.insert(pair<string, Aperture>(code, aperture_data));
		}
	}

	PadGroupManager::PadGroupManager()
	{
		m_pPadShapeGroupMger.clear();
		m_pPadCustomizeGroupMger.clear();
		m_pPartNumberGroupMger.clear();
	}

	PadGroupManager& PadGroupManager::operator=(PadGroupManager& ref)
	{
		this->m_pPadCustomizeGroupMger.clear();
		map<string, PadCustomizeGroup> temp_CustomizeGp = ref.GetAllCustomizeGroup();
		for (auto it= temp_CustomizeGp.begin();it != temp_CustomizeGp.end();it++)
		{
			this->m_pPadCustomizeGroupMger.insert(pair<string, PadCustomizeGroup>(it->first,it->second));
		}

		this->m_pPartNumberGroupMger.clear();
		map<string, PartNumberGroup> temp_PartNumGp = ref.GetAllPartNumberGroup();
		for (auto it = temp_PartNumGp.begin(); it != temp_PartNumGp.end(); it++)
		{
			this->m_pPartNumberGroupMger.insert(pair<string, PartNumberGroup>(it->first, it->second));
		}

		this->m_pPadShapeGroupMger.clear();
		map<PadShape, PadShapeGroup> temp_PadShapeGp = ref.GetAllPadShapeGroup();
		for (auto it = temp_PadShapeGp.begin(); it != temp_PadShapeGp.end(); it++)
		{
			this->m_pPadShapeGroupMger.insert(pair<PadShape, PadShapeGroup>(it->first, it->second));
		}
		return *this;
	}

	map<string, as::PadCustomizeGroup>& PadGroupManager::GetAllCustomizeGroup()
	{
		return m_pPadCustomizeGroupMger;
	}

	map<string, PartNumberGroup>& PadGroupManager::GetAllPartNumberGroup()
	{
		return m_pPartNumberGroupMger;
	}

	map<PadShape, PadShapeGroup>& PadGroupManager::GetAllPadShapeGroup()
	{
		return m_pPadShapeGroupMger;
	}

	//插入一个自定义组
	void PadGroupManager::InsertCustomizeGroup(string groupname, PadCustomizeGroup custgroup)
	{
		m_pPadCustomizeGroupMger.insert(pair<string, PadCustomizeGroup>(groupname, custgroup));
	}

	//自定义分组全部清空
	void PadGroupManager::ClearAllCustomizeGroup()
	{
		m_pPadCustomizeGroupMger.clear();
	}

	//删除单个自定义组
	void PadGroupManager::ClearSingleCustomizeGroup(string groupname)
	{
		if (m_pPadCustomizeGroupMger.find(groupname) != m_pPadCustomizeGroupMger.end())
		{
			m_pPadCustomizeGroupMger.erase(m_pPadCustomizeGroupMger.find(groupname));
		}
	}
	
	void PadGroupManager::InsertPartGroup(string groupname, vector<DWORD> parts)
	{
		if (FindSinglePartGroup(groupname))
		{
			for (int ind = 0; ind < parts.size(); ind++)
			{
				m_pPartNumberGroupMger.find(groupname)->second.m_vPadNameSet.push_back(parts[ind]);
			}
		}
		else
		{
			PartNumberGroup group;
			group.Ref = groupname;
			for (int ind = 0; ind < parts.size(); ind++)
			{
				group.m_vPadNameSet.push_back(parts[ind]);
			}
			m_pPartNumberGroupMger.insert(pair<string, PartNumberGroup>(groupname, group));
		}
		
	}

	bool PadGroupManager::FindSinglePartGroup(string groupname)
	{
		if (m_pPartNumberGroupMger.find(groupname) != m_pPartNumberGroupMger.end())
		{
			return true;
		}
		return false;
	}

	void PadGroupManager::ClearAllPartGroup()
	{
		m_pPartNumberGroupMger.clear();
	}

	void PadGroupManager::ClearSinglePartGroup(string groupname)
	{
		if (m_pPartNumberGroupMger.find(groupname) != m_pPartNumberGroupMger.end())
		{
			m_pPartNumberGroupMger.erase(m_pPartNumberGroupMger.find(groupname));
		}
	}

	PadCustomizeGroup::PadCustomizeGroup()
	{
		m_vPadNameSet.clear();
	}

	PadCustomizeGroup& PadCustomizeGroup::operator=(PadCustomizeGroup& ref)
	{
		this->m_CustomizeGroupName = ref.m_CustomizeGroupName;
		for (int index = 0;index < ref.m_vPadNameSet.size();index++)
		{
			this->m_vPadNameSet.push_back(ref.m_vPadNameSet[index]);
		}
		return *this;
	}

	PadShapeGroup::PadShapeGroup()
	{
		m_padshape = PadShape::Rect;
		m_vPadNameSet.clear();
	}

	PadShapeGroup& PadShapeGroup::operator=(PadShapeGroup& ref)
	{
		this->m_padshape = ref.m_padshape;
		for (int index = 0; index < ref.m_vPadNameSet.size(); index++)
		{
			this->m_vPadNameSet.push_back(ref.m_vPadNameSet[index]);
		}
		return *this;
	}

	PartNumberGroup::PartNumberGroup()
	{
		m_vPadNameSet.clear();
	}

	PartNumberGroup& PartNumberGroup::operator=(PartNumberGroup& ref)
	{
		this->Ref = ref.Ref;
		for (int index = 0; index < ref.m_vPadNameSet.size(); index++)
		{
			this->m_vPadNameSet.push_back(ref.m_vPadNameSet[index]);
		}
		return *this;
	}
}