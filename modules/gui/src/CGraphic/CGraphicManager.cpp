#include "as/CGraphic/CGraphicManager.h"

namespace as
{
	CGraphicManager::CGraphicManager()
	{
	}

	CGraphicManager::~CGraphicManager()
	{
		for (int i = 0; i < m_Pad_AllItems.size(); i++)
		{
			delete m_Pad_AllItems[i];
		}
	}

	CGraphicManager::PadCGraphic::~PadCGraphic()
	{
	}

	CGraphicManager::CADCGraphic::~CADCGraphic()
	{
	}

	//��Ӻ���
	void CGraphicManager::AddPad(shared_ptr<as::ImportPadData> padData, long padID)
	{
		//��padData �л�ȡ��������ݣ�������״���Ƕȡ�λ�á�������
		as::PadShape shape = padData->GetPadShape();
		as::Point padpos(padData->GetPadPos().x / 0.1, padData->GetPadPos().y / 0.1);
		double angle = padData->GetPadAngle();
		double width = padData->GetLength() / 0.1;
		double height = padData->GetWidth() / 0.1;
		double indiameter = padData->GetInDiameter() / 0.1;
		double outdiameter = padData->GetOutDiameter() / 0.1;

		CGraphic* obj1 = NULL;
		PadCGraphic* my_items = NULL;

		if (shape == as::PadShape::Circle)
		{
			obj1 = new as::CGraphicCircle(QRectF(padpos.x, -padpos.y, indiameter, outdiameter));
			obj1->SetParameters(padpos.x, -padpos.y, indiameter, outdiameter);
		}
		else if (shape == as::PadShape::Rect)
		{
			obj1 = new as::CGraphicRect(QRectF(padpos.x - width / 2, -(padpos.y + height / 2), width, height));
			obj1->SetParameters(padpos.x - width / 2, -(padpos.y + height / 2), width, height);
		}
		else if (shape == as::PadShape::Oval)
		{
			obj1 = new as::CGraphicOval(QRectF(padpos.x, -padpos.y, width, height));
			obj1->SetParameters(padpos.x, -padpos.y, width, height);
		}
		else if (shape == as::PadShape::Polygon)
		{
			obj1 = new as::CGraphicPolygon(QRectF(padpos.x, -(padpos.y + height / 2), width, height));
			obj1->SetParameters(padpos.x, -(padpos.y + height / 2), width, height);
		}
		obj1->SetAngle(angle);
		my_items = new PadCGraphic(padID, obj1);
		m_Pad_AllItems.push_back(my_items);

		return;
	}

	//��ȡ���к���Item
	vector<as::CGraphicManager::PadCGraphic*> CGraphicManager::GetPadAllItems()
	{
		return m_Pad_AllItems;
	}

	//��ȡ��������Item
	CGraphic* CGraphicManager::GetPadItem(int id)
	{
		for (size_t i = 0; i < m_Pad_AllItems.size(); i++)
		{
			if (m_Pad_AllItems[i]->m_Pad_id == id)
			{
				return m_Pad_AllItems[i]->m_PadObject;
			}
		}
		return nullptr;
	}

	//ɾ��ĳ��Ԫ��GraphicObject, ��Ҫ��|��|Ԫ������
	void CGraphicManager::DeletePad(int id)
	{
		int DeleteIndex = -1;
		for (size_t i = 0; i < m_Pad_AllItems.size(); i++)
		{
			if (m_Pad_AllItems[i]->m_Pad_id == id)
			{
				// ���ݿ�|ƴ|Ԫ��������������ǰ��ɾ��Ԫ����Vec����
				DeleteIndex = i;

				delete m_Pad_AllItems[i]->m_PadObject;
				delete m_Pad_AllItems[i];
			}
		}
		if (DeleteIndex == -1)return;
		// ������ִ��ɾ������
		auto iterBegin = m_Pad_AllItems.begin();
		m_Pad_AllItems.erase(iterBegin + DeleteIndex);
	}

	//���CADλ��
	void CGraphicManager::AddCAD(as::Point CADPos, int block_id, int array_id, int compo_id)
	{
		CGraphic* obj1 = NULL;
		CADCGraphic* cadItem = NULL;
		obj1 = new as::CGraphicLine(QRectF(CADPos.x / 0.1, -CADPos.y / 0.1, 1, 1));
		obj1->SetParameters(CADPos.x / 0.1, -CADPos.y / 0.1, 1, 1);
		cadItem =new CADCGraphic(block_id, array_id, compo_id, obj1);
		m_CAD_AllItems.push_back(cadItem);
	}

	//ɾ��ĳ��CAD��Graphic, ��Ҫ��|��|Ԫ������
	void CGraphicManager::DeleteCAD(int block_id, int array_id, int compo_id)
	{
		int DeleteIndex = -1;
		for (size_t i = 0; i < m_CAD_AllItems.size(); i++)
		{
			if (m_CAD_AllItems[i]->m_block_id == block_id && m_CAD_AllItems[i]->m_array_id == array_id && m_CAD_AllItems[i]->m_compo_id == compo_id)
			{
				// ���ݿ�|ƴ|Ԫ��������������ǰ��ɾ��Ԫ����Vec����
				DeleteIndex = i;

				delete m_CAD_AllItems[i]->m_CADObject;
				delete m_CAD_AllItems[i];
			}
		}
		if (DeleteIndex == -1)return;
		// ������ִ��ɾ������
		auto iterBegin = m_CAD_AllItems.begin();
		m_CAD_AllItems.erase(iterBegin + DeleteIndex);
	}

	//�ⲿ����:ͨ���顢ƴ��Ԫ����������Ԫ��ͼԪ
	CGraphic* CGraphicManager::GetCADitem(int block_id, int array_id, int compo_id)
	{
		for (size_t i = 0; i < m_CAD_AllItems.size(); i++)
		{
			if (m_CAD_AllItems[i]->m_block_id == block_id && m_CAD_AllItems[i]->m_array_id == array_id && m_CAD_AllItems[i]->m_compo_id == compo_id)
			{
				return m_CAD_AllItems[i]->m_CADObject;
			}
		}
		return nullptr;
	}

	// ��ȡ��ǰ��ͼ����CAD����
	vector<CGraphicManager::CADCGraphic*> CGraphicManager::GetAllCADItems() const
	{
		return m_CAD_AllItems;
	}

	// ��ȡ��ǰ��ͼ����CAD��Items
	vector<CGraphic*> CGraphicManager::GetAllCADCGraphic() const
	{
		vector<CGraphic*> partsVec;
		// ��ȡ��ǰ��ͼ����CAD Mark������
		vector<CADCGraphic*> partsCADVec = GetAllCADItems();
		for (size_t i = 0; i < partsCADVec.size(); i++)
		{
			CGraphic* singlePartCgraphic = partsCADVec[i]->m_CADObject;
			partsVec.push_back(singlePartCgraphic);
		}
		return partsVec;
	}

}