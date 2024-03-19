#ifndef AS_PRODUCECONDITIONCORE_HPP
#define AS_PRODUCECONDITIONCORE_HPP

#include "as/CommonCore.hpp"

namespace as
{
	//用于零点标定模式判断
	enum class ZeroCalFlag {
		ProduceBegin = 0x00,
		ProduceNomal = 0x10,
		ProduceContinue = 0x20,
		ProduceZeroOffset_mode2 = 0x21,
		ProduceNewBoard = 0x22,
		ProduceContinueMountStart = 0x23,
	};

	//生产环节标志
	enum class ProduceID {
		Zero,
		Trans,
		Proready,
		Mark,
		MarkEnd,
		BadMark,
		BadMarkEnd,
		Attutide,
		AttutideEnd,
		End
	};

	//模式选择
	enum ProduceMode
	{
		 m_nNormalTest = 0,		//正常测试
		 m_nOfflineTesting = 1,	//离线测试
		 m_nDebugTests = 2	 	//调试测试
	};

	/**
	 * @name StaticProduceCondition
	 * @file ProduceConditionCore.hpp
	 * @brief 生产过程开始前已确定的生产条件类
	*/

	class AS_EXPORTS StaticProduceCondition
	{
	public:
		StaticProduceCondition();
		~StaticProduceCondition();
		StaticProduceCondition& operator=(StaticProduceCondition &ref);

		ProduceMode GetModeselection();
		void SetModeselection(ProduceMode Mode);
	private:
		ProduceMode m_Modeselection;
	};

	/**
	 * @name DynamicProduceCondition
	 * @file ProduceConditionCore.hpp
	 * @brief 生产过程开始后仍可动态调整的生产条件类
	*/
	class AS_EXPORTS DynamicProduceCondition
	{
	public:
		DynamicProduceCondition();
		~DynamicProduceCondition();
		DynamicProduceCondition& operator=(DynamicProduceCondition &ref);

		int GetPCBSpeed(void);
		void SetPCBSpeed(int nucPCBSpeed);
		int GetMachineSpeedSlider(void);
		void SetMachineSpeedSlider(int slider);
		int GetZDelaySpeed(void);
		void SetZDelaySpeed(int nucZDelaySpeed);
		int GetSpeedLevMinXY(void);
		int SetSpeedLevMinXY(int nucXYSpeed);
		int GetSpeedLevDefaultXY(void);
		void SetSpeedLevDefaultXY(int nucXSpeed);
		int GetSpeedLevDefaultM(void);
		void SetSpeedLevDefaultM(int nucYSpeed);
		int GetSpeedLevDefaultZ(void);
		void SetSpeedLevDefaultZ(int nucZSpeed);
		int GetSpeedLevDefaultR(void);
		void SetSpeedLevDefaultR(int nucRSpeed);

		ZeroCalFlag GetZeroCalFlag(void);
		void SetZeroCalFlag(ZeroCalFlag nbZeroCalFlag);

		ProduceID GetProduceId();
		void SetProduceId(ProduceID state);

		Station GetCurrentBoardStation();
		void SetCurrentBoardStation(Station station);
	private:
		//速度等级
		int m_ucPCBSpeed;				//PCB传输速度                                                                      
		int m_SpeedSlider;				//XY电机速度                                                                       
		int m_ucZDelaySpeed;			//Z轴贴装延时  
		int m_ucSpeedLevMinXY;			//当前周期最慢XY轴速度档位
		int m_ucSpeedLevDefaultXY;		//默认XY轴速度档位
		int m_ucSpeedLevDefaultM;		//默认M轴速度档位
		int m_ucSpeedLevDefaultZ;		//默认Z轴速度档位
		int m_ucSpeedLevDefaultR;		//默认R轴速度档位

		//其他生产条件标志位
		ZeroCalFlag m_eZeroCalFlag;         //生产开始入口标志位
		ProduceID produce_id;				//生产环节
		Station current_board_station;		//站号
	};

	/**
	 * @name ProduceCondition
	 * @file ProduceConditionCore.hpp
	 * @brief 生产过程生产条件接口类
	*/
	class AS_EXPORTS ProduceCondition
	{
	public:
		ProduceCondition();
		~ProduceCondition();
		ProduceCondition& operator=(ProduceCondition &ref);

		StaticProduceCondition& GetStaticProduceCondition();
		shared_ptr<DynamicProduceCondition> GetDynamicProduceCondition();
		void SetStaticProduceCondition(StaticProduceCondition condition);
		void SetDynamicProduceCondition(shared_ptr<DynamicProduceCondition> condition);
	private:
		StaticProduceCondition m_StaticProduceCondition;                 //生产过程开始前已确定的生产条件类 对象
		shared_ptr<DynamicProduceCondition> m_pDynamicProduceCondition;  //生产过程开始后仍可动态调整的生产条件类 指针
	};

}
#endif