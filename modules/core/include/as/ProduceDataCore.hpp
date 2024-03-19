#ifndef AS_PRODUCEDATACORE_HPP
#define AS_PRODUCEDATACORE_HPP

#include "as/ProduceConditionCore.hpp"
#include <as/ConveyorParaCore.hpp>
#include <as/MachineHeadCore.hpp>
#include <as/BaseBoardCore.hpp>
#include <as/CADCore.hpp>
#include <as/PadCore.hpp>

namespace as
{

	/**
	 * @name ProduceMechData
	 * @file ProduceDataCore.hpp
	 * @brief �����������õ��Ļ�е������
	*/
	class AS_EXPORTS ProduceMechData
	{
	public:
		ProduceMechData();
		~ProduceMechData();
		
		ConveyorPara GetConveyorPara();
		void SetConveyorPara(ConveyorPara conveyor_para);

		MachineHead GetMachineHead();
		void SetMachineHead(MachineHead machine_head);
	private:
		ConveyorPara m_cConveyorPara;	//���ʹ�����
		MachineHead m_cMachineHead;		//��ͷ����						
	};

	/**
	 * @name ProduceMountList
	 * @file ProduceDataCore.hpp
	 * @brief �����������õ����������ݰ���Ԫ����Ϣ��Mark����Ϣ��������Ϣ
	*/
	class AS_EXPORTS ProduceCommonData
	{
	public:
		ProduceCommonData();
		~ProduceCommonData();

		shared_ptr<BaseBoard> GetBaseBoardData();
		void InsertBaseBoardData(shared_ptr<BaseBoard> base_board);
		shared_ptr<ProduceMechData> GetProduceMechData();
	private:
		shared_ptr<BaseBoard> m_BaseBoardData;                      // ������Ϣ
		shared_ptr<ProduceMechData> m_ProduceMechData;              // ��е�������������ݡ�����������Ϣ
	};

	/**
	 * @name AOI_ProduceDetectionData
	 * @file ProduceDataCore.hpp
	 * @brief AOI�������õ��ļ������
	*/
	class AS_EXPORTS AOI_ProduceDetectionData
	{
	public:
		AOI_ProduceDetectionData();

		Point GetCenterPos();
		void SetCenterPos(Point pos);

		int GetBlock();
		void SetBlock(int block);

		int GetArray();
		void SetArray(int array);

		vector<DetectionPointData>& GetDetectionDataList();
		void SetDetectionDataList(vector<DetectionPointData> detect_datalist);

		//����Ѿ������ĵ�
		void ClearDetectedData();

		//���PL�򹴱�־
		void ClearCompDetectionFlag();
	private:
		Point m_cVisionCenterPos;
		int m_nBlock;
		int m_nArray;
		vector<DetectionPointData> m_vDetectionDataList;
	};

	/**
	 * @name SPI_ProduceDetectionData
	 * @file ProduceDataCore.hpp
	 * @brief SPI�������õ��ļ������
	*/
	class AS_EXPORTS SPI_ProduceDetectionData
	{
	public:
		SPI_ProduceDetectionData();

		Point GetCenterPos();
		void SetCenterPos(Point pos);

		int GetBlock();
		void SetBlock(int block);

		int GetArray();
		void SetArray(int array);

		vector<DetectionPadData>& GetDetectionDataList();
		void SetDetectionDataList(vector<DetectionPadData> detect_datalist);

		//����Ѿ������ĵ�
		void ClearDetectedData();

		//���PL�򹴱�־
		void ClearCompDetectionFlag();
	private:
		Point m_cVisionCenterPos;
		int m_nBlock;
		int m_nArray;
		vector<DetectionPadData> m_vDetectionDataList;
	};

	/**
	 * @name ProduceData
	 * @file ProduceDataCore.hpp
	 * @brief �����������õ����������������� �ܽӿ�
	*/
	class AS_EXPORTS ProduceData
	{
	public:
		ProduceData();
		~ProduceData();

		ProduceCondition& GetProduceCondition();
		void SetProduceCondition(ProduceCondition& conditiondata);

		ProduceCommonData GetProduceCommonData();
		void SetProduceCommonData(ProduceCommonData commondata);

		vector<AOI_ProduceDetectionData>& GetAOIProduceList();
		void SetAOIProduceList(vector<AOI_ProduceDetectionData> detectcomplist);

		vector<SPI_ProduceDetectionData>& GetSPIProduceList();
		void SetSPIProduceList(vector<SPI_ProduceDetectionData> detectcomplist);

		//��ȡ������������PL����
		int GetAOIProduceListPLNum();         ///AOI
		int GetSPIProduceListPLNum();		  ///SPI
	private:
		ProduceCondition m_ProduceCondition;        //����������Ϣ
		ProduceCommonData m_ProduceCommonData;      //������װ���ݣ�Ԫ����Ϣ��Mark����Ϣ��������Ϣ��
		vector<AOI_ProduceDetectionData> m_AOI_ProduceList;    
		vector<SPI_ProduceDetectionData> m_SPI_ProduceList;
	};
}

#endif