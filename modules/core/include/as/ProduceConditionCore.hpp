#ifndef AS_PRODUCECONDITIONCORE_HPP
#define AS_PRODUCECONDITIONCORE_HPP

#include "as/CommonCore.hpp"

namespace as
{
	//�������궨ģʽ�ж�
	enum class ZeroCalFlag {
		ProduceBegin = 0x00,
		ProduceNomal = 0x10,
		ProduceContinue = 0x20,
		ProduceZeroOffset_mode2 = 0x21,
		ProduceNewBoard = 0x22,
		ProduceContinueMountStart = 0x23,
	};

	//�������ڱ�־
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

	//ģʽѡ��
	enum ProduceMode
	{
		 m_nNormalTest = 0,		//��������
		 m_nOfflineTesting = 1,	//���߲���
		 m_nDebugTests = 2	 	//���Բ���
	};

	/**
	 * @name StaticProduceCondition
	 * @file ProduceConditionCore.hpp
	 * @brief �������̿�ʼǰ��ȷ��������������
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
	 * @brief �������̿�ʼ���Կɶ�̬����������������
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
		//�ٶȵȼ�
		int m_ucPCBSpeed;				//PCB�����ٶ�                                                                      
		int m_SpeedSlider;				//XY����ٶ�                                                                       
		int m_ucZDelaySpeed;			//Z����װ��ʱ  
		int m_ucSpeedLevMinXY;			//��ǰ��������XY���ٶȵ�λ
		int m_ucSpeedLevDefaultXY;		//Ĭ��XY���ٶȵ�λ
		int m_ucSpeedLevDefaultM;		//Ĭ��M���ٶȵ�λ
		int m_ucSpeedLevDefaultZ;		//Ĭ��Z���ٶȵ�λ
		int m_ucSpeedLevDefaultR;		//Ĭ��R���ٶȵ�λ

		//��������������־λ
		ZeroCalFlag m_eZeroCalFlag;         //������ʼ��ڱ�־λ
		ProduceID produce_id;				//��������
		Station current_board_station;		//վ��
	};

	/**
	 * @name ProduceCondition
	 * @file ProduceConditionCore.hpp
	 * @brief �����������������ӿ���
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
		StaticProduceCondition m_StaticProduceCondition;                 //�������̿�ʼǰ��ȷ�������������� ����
		shared_ptr<DynamicProduceCondition> m_pDynamicProduceCondition;  //�������̿�ʼ���Կɶ�̬���������������� ָ��
	};

}
#endif