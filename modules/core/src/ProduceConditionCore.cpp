#include "as/ProduceConditionCore.hpp"

namespace as {

	/**
 * @brief StaticProduceCondition�๹�캯��
*/
	StaticProduceCondition::StaticProduceCondition()
	{
		m_Modeselection = ProduceMode::m_nNormalTest;
	}

	/*
	 * @brief StaticProduceCondition����������
	*/
	StaticProduceCondition::~StaticProduceCondition()
	{
	}

	/**
	 * @brief �Կ�ʼ����ǰ��ȷ�����������п���
	 * @param ref ������������
	 * @return �������
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
	 * @brief DynamicProduceCondition�๹�캯��
	*/
	DynamicProduceCondition::DynamicProduceCondition() :m_ucPCBSpeed(1), m_SpeedSlider(30), m_ucZDelaySpeed(0), \
														m_ucSpeedLevMinXY(1), m_ucSpeedLevDefaultXY(1), m_ucSpeedLevDefaultM(1), m_ucSpeedLevDefaultZ(1),\
														m_ucSpeedLevDefaultR(1), m_eZeroCalFlag(ZeroCalFlag::ProduceBegin), \
														current_board_station(Station::StationF2)
	{
		
	}

	/**
	 * @brief DynamicProduceCondition����������
	*/
	DynamicProduceCondition::~DynamicProduceCondition()
	{ 
	}

	/**
	 * @brief �Կɶ�̬�����������������п���
	 * @param ref ������������
	 * @return �������
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
	 * @brief ��ȡPCB�����ٶ�
	 * @param  void
	 * @return PCB�����ٶ�
	*/
	int DynamicProduceCondition::GetPCBSpeed(void)
	{
		return m_ucPCBSpeed;
	}

	/**
	 * @brief ����PCB�����ٶ�
	 * @param nucPCBSpeed PCB�����ٶ�
	*/
	void DynamicProduceCondition::SetPCBSpeed(int nucPCBSpeed)
	{
		m_ucPCBSpeed = nucPCBSpeed;
	}

	/**
	 * @brief ��ȡ�����ٶ����ðٷֱ�
	 * @param  void
	 * @return �������ٶ�
	*/
	int DynamicProduceCondition::GetMachineSpeedSlider(void)
	{
		return m_SpeedSlider;
	}

	/**
	 * @brief ���û����ٶ����ðٷֱ�
	 * @param slider �������ٶ�
	*/
	void DynamicProduceCondition::SetMachineSpeedSlider(int slider)
	{
		m_SpeedSlider = slider;
	}

	/**
	 * @brief ��ȡZ����װ��ʱ
	 * @param  void
	 * @return Z����װ��ʱʱ��
	*/
	int DynamicProduceCondition::GetZDelaySpeed(void)
	{
		return m_ucZDelaySpeed;
	}

	/**
	 * @brief ����Z����װ��ʱ
	 * @param nucZDelaySpeed Z����װ��ʱ
	*/
	void DynamicProduceCondition::SetZDelaySpeed(int nucZDelaySpeed)
	{
		m_ucZDelaySpeed = nucZDelaySpeed;
	}
	/**
	 * @brief ��ȡXY������ٶȵȼ�
	 * @param  void
	 * @return XY������ٶȵȼ�
	*/
	int DynamicProduceCondition::GetSpeedLevMinXY(void)
	{
		return m_ucSpeedLevMinXY;
	}
	/**
	 * @brief ����XY������ٶȵȼ�
	 * @param nucXYSpeed XY������ٶȵȼ�
	*/
	int DynamicProduceCondition::SetSpeedLevMinXY(int nucXYSpeed)
	{
		m_ucSpeedLevMinXY = nucXYSpeed;
		return m_ucSpeedLevMinXY;
	}

	/**
	 * @brief ��ȡXY��Ĭ���ٶȵȼ�
	 * @param  void
	 * @return XY��Ĭ���ٶȵȼ�
	*/
	int DynamicProduceCondition::GetSpeedLevDefaultXY(void)
	{
		return m_ucSpeedLevDefaultXY;
	}
	/**
	 * @brief ����XY��Ĭ���ٶȵȼ�
	 * @param nucXSpeed XY��Ĭ���ٶȵȼ�
	*/
	void DynamicProduceCondition::SetSpeedLevDefaultXY(int nucXYSpeed)
	{
		m_ucSpeedLevDefaultXY = nucXYSpeed;
	}
	/**
	 * @brief ��ȡM��Ĭ���ٶȵȼ�
	 * @param  void
	 * @return Y��Ĭ���ٶȵȼ�
	*/
	int DynamicProduceCondition::GetSpeedLevDefaultM(void)
	{
		return m_ucSpeedLevDefaultM;
	}
	/**
	 * @brief ����M��Ĭ���ٶȵȼ�
	 * @param nucMSpeed M��Ĭ���ٶȵȼ�
	*/
	void DynamicProduceCondition::SetSpeedLevDefaultM(int nucMSpeed)
	{
		m_ucSpeedLevDefaultM = nucMSpeed;
	}

	/**
	 * @brief ��ȡZ��Ĭ���ٶȵȼ�
	 * @param  void
	 * @return Z��Ĭ���ٶȵȼ�
	*/
	int DynamicProduceCondition::GetSpeedLevDefaultZ(void)
	{
		return m_ucSpeedLevDefaultZ;
	}

	/**
	 * @brief ����Z��Ĭ���ٶȵȼ�
	 * @param nucZSpeed Z��Ĭ���ٶȵȼ�
	*/
	void DynamicProduceCondition::SetSpeedLevDefaultZ(int nucZSpeed)
	{
		m_ucSpeedLevDefaultZ = nucZSpeed;
	}

	/**
	 * @brief ��ȡR��Ĭ���ٶȵȼ�
	 * @param  void
	 * @return R��Ĭ���ٶȵȼ�
	*/
	int DynamicProduceCondition::GetSpeedLevDefaultR(void)
	{
		return m_ucSpeedLevDefaultR;
	}

	/**
	 * @brief ����R��Ĭ���ٶȵȼ�
	 * @param nucRSpeed R��Ĭ���ٶȵȼ�
	*/
	void DynamicProduceCondition::SetSpeedLevDefaultR(int nucRSpeed)
	{
		m_ucSpeedLevDefaultR = nucRSpeed;
	}

	/**
	 * @brief ��ȡ�Ƿ�������궨��־λ
	 * @param  void
	 * @return ���궨��־λ true �궨; false ���궨
	*/
	ZeroCalFlag DynamicProduceCondition::GetZeroCalFlag(void)
	{
		return m_eZeroCalFlag;
	}

	/**
	 * @brief �����Ƿ�������궨
	 * @param nbZeroCalFlag ���궨��־λ true �궨; false ���궨
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
	 * @brief ProduceCondition�๹�캯��
	*/
	ProduceCondition::ProduceCondition() :m_pDynamicProduceCondition(make_shared<DynamicProduceCondition>())
	{
	}

	/**
	 * @brief ProduceCondition����������
	*/
	ProduceCondition::~ProduceCondition()
	{
	}

	/**
	 * @brief �����������ӿڽ��п���
	 * @param ref ��������
	 * @return �������
	*/
	ProduceCondition& ProduceCondition::operator=(ProduceCondition& ref)
	{
		m_StaticProduceCondition = ref.GetStaticProduceCondition();
		m_pDynamicProduceCondition = ref.GetDynamicProduceCondition();
		return *this;
	}

	/**
	 * @brief ��ȡ��������ǰ��ȷ��������������
	 * @return ������ȷ������������Ķ���
	*/
	StaticProduceCondition& ProduceCondition::GetStaticProduceCondition()
	{
		return m_StaticProduceCondition;
	}

	/**
	 * @brief ��ȡ�����������Կ��Ըı�Ķ�̬����������
	 * @return ���ض�̬�����������ָ��
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