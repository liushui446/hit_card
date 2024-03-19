#include "as/ImportPadData.hpp"

namespace as
{

	ImportPadData::ImportPadData()
	{
		m_PadId = 0;
		m_pos.x = 0.0;
		m_pos.y = 0.0;
		m_angle = 0.0;
		m_dlength = 0.0;
		m_dwidth = 0.0;
		m_shape = PadShape::Rect;
		m_apertureCode = "";
		m_dOutsideDiameter = 0.0;
		m_dInsideDiameter = 0.0;
	}

	ImportPadData& ImportPadData::operator=(ImportPadData& ref)
	{
		this->m_PadId = ref.GetPadId();
		this->m_pos.x = ref.GetPadPos().getPintX();
		this->m_pos.y = ref.GetPadPos().getPintY();
		this->m_shape = ref.GetPadShape();
		this->m_apertureCode = ref.GetPadAperture();
		this->m_dlength = ref.GetLength();
		this->m_dwidth = ref.GetWidth();
		this->m_dOutsideDiameter = ref.GetOutDiameter();
		this->m_dInsideDiameter = ref.GetInDiameter();
		return *this;
	}

	void ImportPadData::SetPadId(DWORD val)
	{
		m_PadId = val;
	}

	DWORD ImportPadData::GetPadId()
	{
		return m_PadId;
	}

	void ImportPadData::SetPadPos(Point val)
	{
		m_pos = val;
	}

	Point& ImportPadData::GetPadPos()
	{
		return m_pos;
	}

	void ImportPadData::SetPadAperture(string val)
	{
		m_apertureCode = val;
	}

	string ImportPadData::GetPadAperture()
	{
		return m_apertureCode;
	}

	void ImportPadData::SetPadShape(PadShape val)
	{
		m_shape = val;
	}

	PadShape ImportPadData::GetPadShape()
	{
		return m_shape;
	}

	void ImportPadData::SetPadAngle(double angle)
	{
		m_angle = angle;
	}

	double ImportPadData::GetPadAngle()
	{
		return m_angle;
	}

	double ImportPadData::GetLength()
	{
		return m_dlength;
	}

	void ImportPadData::SetLength(double val)
	{
		m_dlength = val;
	}

	double ImportPadData::GetWidth()
	{
		return m_dwidth;
	}

	void ImportPadData::SetWidth(double val)
	{
		m_dwidth = val;
	}

	double ImportPadData::GetOutDiameter()
	{
		return m_dOutsideDiameter;
	}

	void ImportPadData::SetOutDiameter(double val)
	{
		m_dOutsideDiameter = val;
	}

	double ImportPadData::GetInDiameter()
	{
		return m_dInsideDiameter;
	}

	void ImportPadData::SetInDiameter(double val)
	{
		m_dInsideDiameter = val;
	}

	

	ImportPadDataSet::ImportPadDataSet()
	{
		m_pImportPadDataSet.clear();
	}

	//��ȡ����Ԥ����������
	map<string, map<DWORD, shared_ptr<ImportPadData>>> ImportPadDataSet::GetAllImportPadData()
	{
		return m_pImportPadDataSet;
	}

	//��ȡ��Ԥ����������
	map<DWORD, shared_ptr<ImportPadData>> ImportPadDataSet::GetLayerImportPadData(string layername)
	{
		if (FindLayerImportPadData(layername))
		{
			return m_pImportPadDataSet.at(layername);
		}
		return map<DWORD, shared_ptr<ImportPadData>>();
	}

	//��ȡ����Ԥ����������
	shared_ptr<ImportPadData> ImportPadDataSet::GetSingleImportPadData(string layername, DWORD name)
	{
		if (FindSingleImportPadData(layername, name))
		{
			return m_pImportPadDataSet.at(layername).at(name);
		}
		return shared_ptr<ImportPadData>();
	}

	//���뵥��Ԥ����������
	void ImportPadDataSet::InsertSingleImportPadData(string layername, DWORD name, shared_ptr<ImportPadData> data)
	{
		if (FindLayerImportPadData(layername))
		{
			m_pImportPadDataSet.at(layername).insert(pair<DWORD, shared_ptr<ImportPadData>>(name, data));
		}
		else
		{
			map<DWORD, shared_ptr<ImportPadData>> temp_ImportPadDatalist;
			temp_ImportPadDatalist.insert(pair<DWORD, shared_ptr<ImportPadData>>(name, data));
			m_pImportPadDataSet.insert(pair<string, map<DWORD, shared_ptr<ImportPadData>>>(layername, temp_ImportPadDatalist));
		}
	}

	//���Ҳ�Ԥ��������
	bool ImportPadDataSet::FindLayerImportPadData(string layername)
	{
		if (m_pImportPadDataSet.find(layername) != m_pImportPadDataSet.end())
		{
			return true;
		}
		return false;
	}

	//���ҵ���Ԥ����������
	bool ImportPadDataSet::FindSingleImportPadData(string layername, DWORD padid)
	{
		if (FindLayerImportPadData(layername))
		{
			if (m_pImportPadDataSet.find(layername)->second.find(padid) != m_pImportPadDataSet.find(layername)->second.end())
			{
				return true;
			}
		}
		return false;
	}

	//ɾ��������������
	void ImportPadDataSet::DeleteSingleImportPadData(string layername, DWORD name)
	{
		m_pImportPadDataSet.find(layername)->second.erase(m_pImportPadDataSet.find(layername)->second.find(name));
	}

	//ɾ������Gerber�㺸������
	void ImportPadDataSet::DeleteGerberImportpadData(string layername)
	{
		m_pImportPadDataSet.erase(m_pImportPadDataSet.find(layername));
	}

	//��ȡ����Ԥ�����Ȧ����
	map<string, map<string, Aperture>> ImportPadDataSet::GetAllImportApertureData()
	{
		return m_pApertureDataSet;
	}

	//��ȡ��Ԥ�����Ȧ����
	map<string, Aperture> ImportPadDataSet::GetLayerImportApertureData(string layername)
	{
		if (FindLayerImportApertureData(layername))
		{
			return m_pApertureDataSet.at(layername);
		}
		return map<string, Aperture>();
	}

	//��ȡ����Ԥ�����Ȧ����
	Aperture ImportPadDataSet::GetSingleImportApertureData(string layername, string code)
	{
		if (FindSingleImportApertureData(layername, code))
		{
			return m_pApertureDataSet.find(layername)->second.at(code);
		}
		return Aperture();
	}

	//���뵥��Ԥ�����Ȧ����
	void ImportPadDataSet::InsertSingleApertureData(string layername, string code, Aperture aperture_data)
	{
		if (FindLayerImportApertureData(layername))
		{
			m_pApertureDataSet.at(layername).insert(pair<string, Aperture>(code, aperture_data));
		}
		else
		{
			map<string, Aperture> temp_ImportAperturelist;
			temp_ImportAperturelist.insert(pair<string, Aperture>(code, aperture_data));
			m_pApertureDataSet.insert(pair<string, map<string, Aperture>>(layername, temp_ImportAperturelist));
		}
	}

	//���Ҳ�Ԥ�����Ȧ����
	bool ImportPadDataSet::FindLayerImportApertureData(string layername)
	{
		if (m_pApertureDataSet.find(layername) != m_pApertureDataSet.end())
		{
			return true;
		}
		return false;
	}

	//ɾ��������Ȧ����
	bool ImportPadDataSet::FindSingleImportApertureData(string layername, string code)
	{

		if (FindLayerImportApertureData(layername))
		{
			if (m_pApertureDataSet.find(layername)->second.find(code) != m_pApertureDataSet.find(layername)->second.end())
			{
				return true;
			}
		}
		return false;
	}

	//ɾ��������Ȧ����
	void ImportPadDataSet::DeleteSingleImportApertureData(string layername, string code)
	{
		m_pApertureDataSet.find(layername)->second.erase(m_pApertureDataSet.find(layername)->second.find(code));
	}

	//ɾ������Gerber���Ȧ����
	void ImportPadDataSet::DeleteGerberImportApertureData(string layername)
	{
		m_pApertureDataSet.erase(m_pApertureDataSet.find(layername));
	}

	ImportPadContext::ImportPadContext()
	{
		m_ptrImportPadDataSet = make_shared<ImportPadDataSet>();
	}

	ImportPadContext& ImportPadContext::GetInstance()
	{
		static ImportPadContext importpad_context;
		return importpad_context;
	}

	shared_ptr<ImportPadDataSet> ImportPadContext::GetImportPadDataSet()
	{
		return m_ptrImportPadDataSet;
	}
}

