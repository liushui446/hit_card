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
	 * @brief 生产过程所用到的机械参数等
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
		ConveyorPara m_cConveyorPara;	//传送带参数
		MachineHead m_cMachineHead;		//机头参数						
	};

	/**
	 * @name ProduceMountList
	 * @file ProduceDataCore.hpp
	 * @brief 生产过程所用到的生产数据包括元件信息、Mark点信息、基板信息
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
		shared_ptr<BaseBoard> m_BaseBoardData;                      // 基板信息
		shared_ptr<ProduceMechData> m_ProduceMechData;              // 机械参数、补偿数据、距离计算等信息
	};

	/**
	 * @name AOI_ProduceDetectionData
	 * @file ProduceDataCore.hpp
	 * @brief AOI生产中用到的检测数据
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

		//清除已经检测过的点
		void ClearDetectedData();

		//清除PL打勾标志
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
	 * @brief SPI生产中用到的检测数据
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

		//清除已经检测过的点
		void ClearDetectedData();

		//清除PL打勾标志
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
	 * @brief 生产过程所用到的所有生产数据类 总接口
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

		//获取生产步骤数据PL打勾数
		int GetAOIProduceListPLNum();         ///AOI
		int GetSPIProduceListPLNum();		  ///SPI
	private:
		ProduceCondition m_ProduceCondition;        //生产条件信息
		ProduceCommonData m_ProduceCommonData;      //生产贴装数据（元件信息、Mark点信息、基板信息）
		vector<AOI_ProduceDetectionData> m_AOI_ProduceList;    
		vector<SPI_ProduceDetectionData> m_SPI_ProduceList;
	};
}

#endif