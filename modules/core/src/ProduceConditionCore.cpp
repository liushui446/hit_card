#include "as/ProduceConditionCore.hpp"

namespace as {

	/**
 * @brief StaticProduceCondition类构造函数
*/
	StaticProduceCondition::StaticProduceCondition()
	{
		m_Modeselection = ProduceMode::m_nNormalTest;
	}

	/*
	 * @brief StaticProduceCondition类析构函数
	*/
	StaticProduceCondition::~StaticProduceCondition()
	{
	}

	/**
	 * @brief 对开始生产前已确定的条件进行拷贝
	 * @param ref 生产条件拷贝
	 * @return 拷贝结果
	*/
	StaticProduceCondition& StaticProduceCondition::operator=(StaticProduceCondition& ref)
	{
		m_Modeselection = ref.GetModeselection();
		return *this;
	}

	ProduceMode StaticProduceCondition::GetModeselection()
	{
		return m_Modeselection;
	}

	void StaticProduceCondition::SetModeselection(ProduceMode Mode)
	{
		m_Modeselection = Mode;
	}

	/**
	 * @brief DynamicProduceCondition类构造函数
	*/
	DynamicProduceCondition::DynamicProduceCondition() :m_ucPCBSpeed(1), m_SpeedSlider(30), m_ucZDelaySpeed(0), \
														m_ucSpeedLevMinXY(1), m_ucSpeedLevDefaultXY(1), m_ucSpeedLevDefaultM(1), m_ucSpeedLevDefaultZ(1),\
														m_ucSpeedLevDefaultR(1), m_eZeroCalFlag(ZeroCalFlag::ProduceBegin), \
														current_board_station(Station::StationF2)
	{
		
	}

	/**
	 * @brief DynamicProduceCondition类析构函数
	*/
	DynamicProduceCondition::~DynamicProduceCondition()
	{ 
	}

	/**
	 * @brief 对可动态调整的生产条件进行拷贝
	 * @param ref 生产条件拷贝
	 * @return 拷贝结果
	*/
	DynamicProduceCondition& DynamicProduceCondition::operator=(DynamicProduceCondition &ref)
	{
		m_ucPCBSpeed = ref.m_ucPCBSpeed;
		m_SpeedSlider = ref.m_SpeedSlider;
		m_ucZDelaySpeed = ref.m_ucZDelaySpeed;

		m_ucSpeedLevMinXY = ref.m_ucSpeedLevMinXY;
		m_ucSpeedLevDefaultXY = ref.m_ucSpeedLevDefaultXY;
		m_ucSpeedLevDefaultM = ref.m_ucSpeedLevDefaultM;
		m_ucSpeedLevDefaultZ = ref.m_ucSpeedLevDefaultZ;
		m_ucSpeedLevDefaultR = ref.m_ucSpeedLevDefaultR;
		m_eZeroCalFlag = ref.m_eZeroCalFlag;
		return *this;
	}

	/**
	 * @brief 获取PCB传输速度
	 * @param  void
	 * @return PCB传输速度
	*/
	int DynamicProduceCondition::GetPCBSpeed(void)
	{
		return m_ucPCBSpeed;
	}

	/**
	 * @brief 设置PCB传输速度
	 * @param nucPCBSpeed PCB传输速度
	*/
	void DynamicProduceCondition::SetPCBSpeed(int nucPCBSpeed)
	{
		m_ucPCBSpeed = nucPCBSpeed;
	}

	/**
	 * @brief 获取机器速度设置百分比
	 * @param  void
	 * @return 机器轴速度
	*/
	int DynamicProduceCondition::GetMachineSpeedSlider(void)
	{
		return m_SpeedSlider;
	}

	/**
	 * @brief 设置机器速度设置百分比
	 * @param slider 机器轴速度
	*/
	void DynamicProduceCondition::SetMachineSpeedSlider(int slider)
	{
		m_SpeedSlider = slider;
	}

	/**
	 * @brief 获取Z轴贴装延时
	 * @param  void
	 * @return Z轴贴装延时时间
	*/
	int DynamicProduceCondition::GetZDelaySpeed(void)
	{
		return m_ucZDelaySpeed;
	}

	/**
	 * @brief 设置Z轴贴装延时
	 * @param nucZDelaySpeed Z轴贴装延时
	*/
	void DynamicProduceCondition::SetZDelaySpeed(int nucZDelaySpeed)
	{
		m_ucZDelaySpeed = nucZDelaySpeed;
	}
	/**
	 * @brief 获取XY轴最低速度等级
	 * @param  void
	 * @return XY轴最低速度等级
	*/
	int DynamicProduceCondition::GetSpeedLevMinXY(void)
	{
		return m_ucSpeedLevMinXY;
	}
	/**
	 * @brief 设置XY轴最低速度等级
	 * @param nucXYSpeed XY轴最低速度等级
	*/
	int DynamicProduceCondition::SetSpeedLevMinXY(int nucXYSpeed)
	{
		m_ucSpeedLevMinXY = nucXYSpeed;
		return m_ucSpeedLevMinXY;
	}

	/**
	 * @brief 获取XY轴默认速度等级
	 * @param  void
	 * @return XY轴默认速度等级
	*/
	int DynamicProduceCondition::GetSpeedLevDefaultXY(void)
	{
		return m_ucSpeedLevDefaultXY;
	}
	/**
	 * @brief 设置XY轴默认速度等级
	 * @param nucXSpeed XY轴默认速度等级
	*/
	void DynamicProduceCondition::SetSpeedLevDefaultXY(int nucXYSpeed)
	{
		m_ucSpeedLevDefaultXY = nucXYSpeed;
	}
	/**
	 * @brief 获取M轴默认速度等级
	 * @param  void
	 * @return Y轴默认速度等级
	*/
	int DynamicProduceCondition::GetSpeedLevDefaultM(void)
	{
		return m_ucSpeedLevDefaultM;
	}
	/**
	 * @brief 设置M轴默认速度等级
	 * @param nucMSpeed M轴默认速度等级
	*/
	void DynamicProduceCondition::SetSpeedLevDefaultM(int nucMSpeed)
	{
		m_ucSpeedLevDefaultM = nucMSpeed;
	}

	/**
	 * @brief 获取Z轴默认速度等级
	 * @param  void
	 * @return Z轴默认速度等级
	*/
	int DynamicProduceCondition::GetSpeedLevDefaultZ(void)
	{
		return m_ucSpeedLevDefaultZ;
	}

	/**
	 * @brief 设置Z轴默认速度等级
	 * @param nucZSpeed Z轴默认速度等级
	*/
	void DynamicProduceCondition::SetSpeedLevDefaultZ(int nucZSpeed)
	{
		m_ucSpeedLevDefaultZ = nucZSpeed;
	}

	/**
	 * @brief 获取R轴默认速度等级
	 * @param  void
	 * @return R轴默认速度等级
	*/
	int DynamicProduceCondition::GetSpeedLevDefaultR(void)
	{
		return m_ucSpeedLevDefaultR;
	}

	/**
	 * @brief 设置R轴默认速度等级
	 * @param nucRSpeed R轴默认速度等级
	*/
	void DynamicProduceCondition::SetSpeedLevDefaultR(int nucRSpeed)
	{
		m_ucSpeedLevDefaultR = nucRSpeed;
	}

	/**
	 * @brief 获取是否进行零点标定标志位
	 * @param  void
	 * @return 零点标定标志位 true 标定; false 不标定
	*/
	ZeroCalFlag DynamicProduceCondition::GetZeroCalFlag(void)
	{
		return m_eZeroCalFlag;
	}

	/**
	 * @brief 设置是否进行零点标定
	 * @param nbZeroCalFlag 零点标定标志位 true 标定; false 不标定
	*/
	void DynamicProduceCondition::SetZeroCalFlag(ZeroCalFlag nbZeroCalFlag)
	{
		m_eZeroCalFlag = nbZeroCalFlag;
	}

	ProduceID DynamicProduceCondition::GetProduceId()
	{
		return produce_id;
	}

	void DynamicProduceCondition::SetProduceId(ProduceID state)
	{
		produce_id = state;
	}

	Station DynamicProduceCondition::GetCurrentBoardStation()
	{
		return current_board_station;
	}

	void DynamicProduceCondition::SetCurrentBoardStation(Station station)
	{
		current_board_station = station;
	}

	/**
	 * @brief ProduceCondition类构造函数
	*/
	ProduceCondition::ProduceCondition() :m_pDynamicProduceCondition(make_shared<DynamicProduceCondition>())
	{
	}

	/**
	 * @brief ProduceCondition类析构函数
	*/
	ProduceCondition::~ProduceCondition()
	{
	}

	/**
	 * @brief 对生产条件接口进行拷贝
	 * @param ref 拷贝对象
	 * @return 拷贝结果
	*/
	ProduceCondition& ProduceCondition::operator=(ProduceCondition& ref)
	{
		m_StaticProduceCondition = ref.GetStaticProduceCondition();
		m_pDynamicProduceCondition = ref.GetDynamicProduceCondition();
		return *this;
	}

	/**
	 * @brief 获取生产过程前已确定的生产条件类
	 * @return 返回已确定生产条件类的对象
	*/
	StaticProduceCondition& ProduceCondition::GetStaticProduceCondition()
	{
		return m_StaticProduceCondition;
	}

	/**
	 * @brief 获取生产过程中仍可以改变的动态生产条件类
	 * @return 返回动态生产条件类的指针
	*/
	shared_ptr<DynamicProduceCondition> ProduceCondition::GetDynamicProduceCondition()
	{
		return m_pDynamicProduceCondition;
	}

	void ProduceCondition::SetStaticProduceCondition(StaticProduceCondition condition)
	{
		m_StaticProduceCondition = condition;
	}

	void ProduceCondition::SetDynamicProduceCondition(shared_ptr<DynamicProduceCondition> condition)
	{
		m_pDynamicProduceCondition = condition;
	}
}