#ifndef AS_CONVEYORPARACORE_HPP
#define AS_CONVEYORPARACORE_HPP

#include "as/CommonCore.hpp"

namespace as
{
	class Rail;
	class ConveyorPara;
}

namespace boost
{
	namespace serialization
	{
		//template <class Archive>
		//void serialize(Archive& ar, aoi::Rail& val, const unsigned int version);

		//template <class Archive>
		//void serialize(Archive& ar, aoi::ConveyorPara& val, const unsigned int version);
	}
}

namespace as
{
	enum class PCBState
	{
		NONE = 0,	//���ʹ��ް�
		NORMAL = 1,	//���ʹ��а�
		STUCK = 2		//���ʹ�����
	};

	enum class BoardRelease
	{
		QUICK_LOAD = 0,			//����װ��
		SEQUENTIAL = 1			//������
	};

	class AS_EXPORTS Stopper
	{
	public:
		bool m_StopperEnable;            //�Ƿ����ø�ֹ����
		Point m_StopperPos;              //ֹ��������
		bool m_StopperState;			 //ֹ����״̬ TRUE : ����״̬ FALSE : �½�״̬
		int	m_StoppperUpDelay;		     //ֹ����������ʱ
		int	m_StopperDownDelay;		     //ֹ�����½���ʱ
	};

	class AS_EXPORTS BUT
	{
	public:
		bool m_bBUTEnable;               //�Ƿ�����ֱ����
		bool m_bBUTState;				//BUTƽ̨״̬ TRUE : ����״̬ FALSE : �½�״̬
		int m_nBUTUpDelay;				//����̨�����ӳ�
		int m_nBUTDownDelay;				//����̨�½��ӳ�
	};

	class AS_EXPORTS ConveyorBelt
	{
	public:
		bool m_bRunState;				//���ʹ�����״̬ TRUE : ���� FALSE : ֹͣ
		PCBState m_TransState;			//���ʹ�����״̬
	};

	class AS_EXPORTS StationRegion
	{
	public:
		Stopper m_stopper;
		BUT m_but;
		Point m_cWorkSensorPos; //����������
		ConveyorBelt m_belt;
	};

	class AS_EXPORTS TimeSetting
	{
	public:
		// ��ʱ��
		TimeSetting();
		int		m_nStopperTime;			//ֹ������ʱ��
		int     m_nBackupTableTime;     //but��ʱ��           ��δʹ��
		int     m_nInStationTime;		//������̨ʱ��
		int     m_nOutStationTime;		//������̨ʱ��
		int     m_nBoardEntryTime;		//���ӽ���ʱ��
		int     m_nShuttleHomingTime;	//��ŷ���λʱ��
		int     m_nShuttleLimitTime;	//��ŷ�ʱ������
		int     m_nShuttleMoveTime;		//��ŷ��˶�ʱ��
		int     m_nRailHomingTime;		//�����λʱ��
		int     m_nRailLimitTime;		//���ʱ������
		int     m_nRailMoveTime;		//����˶�ʱ��

		// ��ʱ
		int     m_nPCBLockDelay;			//PCB�����ӳ�
		int     m_nEdgeFixerDelay;		//��Ե�̶����ӳ�
		int		m_nSensorRecheckDelay;	//����������ʱ��
	};

	class AS_EXPORTS Rail
	{
	public:
		Rail();
		//template <class Archive>
		//friend void boost::serialization::serialize(Archive& ar, Rail& val, const unsigned int version);

		double	m_dWidth;				//���ʹ��Ŀ��
		double  m_dMinWidth;			//���ʹ���С���
		double  m_dMaxWidth;			//���ʹ������ 
		double  m_dMinLength;			//���ʹ���С����
		double  m_dWidthMargin;			//���ʹ���Ȳ���
		int		m_nTranModel;			//����ģʽ 0 : �������� 1 : �ɱ༭���� 2 : ͨ�ó��� 3:�ɵĳ���ģʽ
		int     m_TransDirection;       //���巽�� 1 ���� 0 ���� (Ӳ�� 0 ���� 1 ����)
		vector<double>  m_vMaxLength;	//���ʹ���󳤶� ��Ӧ���ִ���ģʽ
	};

	//���ʹ�
	class AS_EXPORTS ConveyorPara
	{
	public:
		ConveyorPara();

		//template <class Archive>
		//friend void boost::serialization::serialize(Archive& ar, ConveyorPara& val, const unsigned int version);

		ConveyorPara& operator=(ConveyorPara& ref);

		StationRegion& GetStation(Station staion);
		void SetSensorPos(Station station, Point pos);
		Point GetSensorPos(Station station);
		bool GetStopperState(Station station);
		void SetStopperState(Station station, bool state);

		void SetWorkPos(Station station, Point pos);
		Point GetWorkPos(Station station);

		//���ʹ�״̬
		int GetBeltPCBState(Station station);
		void SetBeltPCBState(Station station, int State);

		//Butƽ̨����ʱ��
		int GetButTime();
		void SetButTime(int but_time);

		int GetButINStationTime();
		void SetButInStationTime(int instation_time);

		int GetButOutStationTime();
		void SetButOutStationTime(int outstation_time);

		//����ģʽ
		int GetTransModel();
		void SetTranModel(int model);

		//���巽��
		int GetTransDirection();
		void SetTranDirection(int direction);

		//���ӿ��
		double GetTransWidth();
		void SetTransWidth(double width);

		double GetTransMinWidth();
		void SetTransMinWidth(double minWidth_);

		double GetTransMaxWidth();
		void SetTransMaxWidth(double max_width);

		double GetTransMinLength();
		void SetTransMinLength(double transMinLength);

		double GetTransMaxLength();
		double GetTransMaxLength(int index);

		void SetTransMaxLength(double maxLength);
		void SetTransMaxLength(int tranModel, double maxLength);
		void InsertTransMaxLength(double maxLength);

		double GetTransWidthMargin();
		void SetTransWidthMargin(double widthMargin_);

		bool GetBUTState(Station station);
		void SetBUTState(Station station, bool state);

		int GetStopperTime();
		void SetStopperTime(int stop_time);

		int GetBoardEntryTime();
		void SetBoardEntryTime(int board_entry_time);

		int GetRailHomingTime();
		void SetRailHomingTime(int rail_homing_time);

		int GetRailLimitTime();
		void SetRailLimitTime(int rail_limit_time);

		int GetRailMoveTime();
		void SetRailMoveTime(int rail_move_time);

		int GetPCBLockDelay();
		void SetPCBLockDelay(int pcb_lock_delay);

		int GetEdgeFixerDelay();
		void SetEdgeFixerDelay(int edge_fixer_delay);

		int GetSensorRecheckDelay();
		void SetSensorRecheckDelay(int sensor_recheck_delay);

		int GetShuttleHomingTime();
		void SetShuttleHomingTime(int shuttle_homing_time);

		int GetShuttleLimitTime();
		void SetShuttleLimitTime(int shuttle_limit_time);

		int GetShuttleMoveTime();
		void SetShuttleMoveTime(int shuttle_move_time);

		bool GetBeltRunState(Station belt_index);
		void SetBeltRunState(Station belt_index, bool run_state);

		bool GetConveyFixedTrack();
		void SetConveyFixedTrack(bool convey_fixed_track);
	private:
		map<Station, StationRegion> m_mStation;
		TimeSetting	m_cTimeSetting;
		Rail m_rail;
		bool m_bConveyFixedTrack;		    //���ʹ��̶� true Front  
	};
}
#endif
