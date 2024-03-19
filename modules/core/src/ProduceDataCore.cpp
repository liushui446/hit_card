#include "as/ProduceDataCore.hpp"

namespace as {

	ProduceMechData::ProduceMechData()
	{
	}

	ProduceMechData::~ProduceMechData()
	{
	}

	/**
	 * @brief 获取传送带参数信息
	 * @return 返回ConveyorPara对象
	*/
	ConveyorPara ProduceMechData::GetConveyorPara()
	{
		return m_cConveyorPara;
	}

	void ProduceMechData::SetConveyorPara(ConveyorPara conveyor_para)
	{
		m_cConveyorPara = conveyor_para;
	}

	MachineHead ProduceMechData::GetMachineHead()
	{
		return m_cMachineHead;
	}

	void ProduceMechData::SetMachineHead(MachineHead machine_head)
	{
		m_cMachineHead = machine_head;
	}

	/**
	 * @brief ProduceMountList类构造函数
	*/
	ProduceCommonData::ProduceCommonData()
	{
		m_BaseBoardData = make_shared<BaseBoard>();
		m_ProduceMechData = make_shared<ProduceMechData>();
	}

	/**
	 * @brief ProduceMountList类析构函数
	*/
	ProduceCommonData::~ProduceCommonData()
	{
	}

	/**
	 * @brief 获取基板信息
	 * @return 基板信息
	*/
	shared_ptr<BaseBoard> ProduceCommonData::GetBaseBoardData()
	{
		return m_BaseBoardData;
	}

	void ProduceCommonData::InsertBaseBoardData(shared_ptr<BaseBoard> base_board)
	{
		*m_BaseBoardData = *base_board;
	}

	shared_ptr<ProduceMechData> ProduceCommonData::GetProduceMechData()
	{
		return m_ProduceMechData;
	}

	AOI_ProduceDetectionData::AOI_ProduceDetectionData()
	{
		m_nBlock = 1;
		m_nArray = 1;
		m_vDetectionDataList.clear();
	}

	Point AOI_ProduceDetectionData::GetCenterPos()
	{
		return m_cVisionCenterPos;
	}

	void AOI_ProduceDetectionData::SetCenterPos(Point pos)
	{
		m_cVisionCenterPos = pos;
	}

	int AOI_ProduceDetectionData::GetBlock()
	{
		return m_nBlock;
	}

	void AOI_ProduceDetectionData::SetBlock(int block)
	{
		m_nBlock = block;
	}

	int AOI_ProduceDetectionData::GetArray()
	{
		return m_nArray;
	}

	void AOI_ProduceDetectionData::SetArray(int array)
	{
		m_nArray = array;
	}

	vector<DetectionPointData>& AOI_ProduceDetectionData::GetDetectionDataList()
	{
		return m_vDetectionDataList;
	}

	void AOI_ProduceDetectionData::SetDetectionDataList(vector<DetectionPointData> detect_datalist)
	{
		m_vDetectionDataList = detect_datalist;
	}

	void AOI_ProduceDetectionData::ClearDetectedData()
	{
		for (auto detectiter = m_vDetectionDataList.begin(); detectiter != m_vDetectionDataList.end();)
		{
			//处理数据
			if (detectiter->GetCompleteDetection())
			{
				detectiter = m_vDetectionDataList.erase(detectiter);
			}
			else
			{
				detectiter++;
			}
		}
	}

	void AOI_ProduceDetectionData::ClearCompDetectionFlag()
	{
		for (auto detectiter = m_vDetectionDataList.begin(); detectiter != m_vDetectionDataList.end(); detectiter++)
		{
			detectiter->SetCompleteDetection(false);
		}
	}

	SPI_ProduceDetectionData::SPI_ProduceDetectionData()
	{
		m_nBlock = 1;
		m_nArray = 1;
		m_vDetectionDataList.clear();
	}

	Point SPI_ProduceDetectionData::GetCenterPos()
	{
		return m_cVisionCenterPos;
	}

	void SPI_ProduceDetectionData::SetCenterPos(Point pos)
	{
		m_cVisionCenterPos = pos;
	}
	int SPI_ProduceDetectionData::GetBlock()
	{
		return m_nBlock;
	}
	void SPI_ProduceDetectionData::SetBlock(int block)
	{
		m_nBlock = block;
	}

	int SPI_ProduceDetectionData::GetArray()
	{
		return m_nArray;
	}

	void SPI_ProduceDetectionData::SetArray(int array)
	{
		m_nArray = array;
	}

	vector<DetectionPadData>& SPI_ProduceDetectionData::GetDetectionDataList()
	{
		return m_vDetectionDataList;
	}

	void SPI_ProduceDetectionData::SetDetectionDataList(vector<DetectionPadData> detect_datalist)
	{
		m_vDetectionDataList = detect_datalist;
	}

	void SPI_ProduceDetectionData::ClearDetectedData()
	{
		for (auto detectiter = m_vDetectionDataList.begin(); detectiter != m_vDetectionDataList.end();)
		{
			//处理数据
			if (detectiter->GetCompleteDetection())
			{
				detectiter = m_vDetectionDataList.erase(detectiter);
			}
			else
			{
				detectiter++;
			}
		}
	}

	void SPI_ProduceDetectionData::ClearCompDetectionFlag()
	{
		for (auto detectiter = m_vDetectionDataList.begin(); detectiter != m_vDetectionDataList.end(); detectiter++)
		{
			detectiter->SetCompleteDetection(false);
		}
	}

	/**
	 * @brief ProduceData类构造函数
	*/
	ProduceData::ProduceData()
	{
	}

	/**
	 * @brief ProduceData类析构函数
	*/
	ProduceData::~ProduceData()
	{
	}

	/**
	 * @brief 获取生产条件
	 * @return 生产条件
	*/
	ProduceCondition& ProduceData::GetProduceCondition()
	{
		return m_ProduceCondition;
	}

	/**
	 * @brief 设置生产条件
	*/
	void ProduceData::SetProduceCondition(ProduceCondition& conditiondata)
	{
		m_ProduceCondition = conditiondata;
	}

	/**
	 * @brief 获取生产数据贴装信息
	 * @return 生产数据贴装信息
	*/
	ProduceCommonData ProduceData::GetProduceCommonData()
	{
		return m_ProduceCommonData;
	}

	/**
	 * @brief 设置生产数据贴装信息
	*/
	void ProduceData::SetProduceCommonData(ProduceCommonData commondata)
	{
		m_ProduceCommonData = commondata;
	}

	vector<AOI_ProduceDetectionData>& ProduceData::GetAOIProduceList()
	{
		return m_AOI_ProduceList;
	}

	void ProduceData::SetAOIProduceList(vector<AOI_ProduceDetectionData> mountcomplist)
	{
		m_AOI_ProduceList = mountcomplist;
	}

	vector<SPI_ProduceDetectionData>& ProduceData::GetSPIProduceList()
	{
		return m_SPI_ProduceList;
	}

	void ProduceData::SetSPIProduceList(vector<SPI_ProduceDetectionData> mountcomplist)
	{
		m_SPI_ProduceList = mountcomplist;
	}

	//获取生产步骤数据PL打勾数
	int ProduceData::GetAOIProduceListPLNum()
	{
		int pl_num = 0;
		for (int num = 0; num < m_AOI_ProduceList.size(); num++)
		{	
			for (int index = 0; index < m_AOI_ProduceList[num].GetDetectionDataList().size(); index++)
			{
				if (m_AOI_ProduceList[num].GetDetectionDataList()[index].GetCompleteDetection())
				{
					pl_num++;
				}
			}		
		}
		return pl_num;
	}

	//获取生产步骤数据PL打勾数
	int ProduceData::GetSPIProduceListPLNum()
	{
		int pl_num = 0;
		for (int num = 0; num < m_SPI_ProduceList.size(); num++)
		{
			for (int index = 0; index < m_SPI_ProduceList[num].GetDetectionDataList().size(); index++)
			{
				if (m_SPI_ProduceList[num].GetDetectionDataList()[index].GetCompleteDetection())
				{
					pl_num++;
				}
			}
		}
		return pl_num;
	}


}
