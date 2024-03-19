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
		NONE = 0,	//传送带无板
		NORMAL = 1,	//传送带有板
		STUCK = 2		//传送带卡板
	};

	enum class BoardRelease
	{
		QUICK_LOAD = 0,			//快速装载
		SEQUENTIAL = 1			//连续的
	};

	class AS_EXPORTS Stopper
	{
	public:
		bool m_StopperEnable;            //是否启用该止挡梢
		Point m_StopperPos;              //止挡梢坐标
		bool m_StopperState;			 //止挡梢状态 TRUE : 上升状态 FALSE : 下降状态
		int	m_StoppperUpDelay;		     //止挡器上升延时
		int	m_StopperDownDelay;		     //止挡器下降延时
	};

	class AS_EXPORTS BUT
	{
	public:
		bool m_bBUTEnable;               //是否易用直升板
		bool m_bBUTState;				//BUT平台状态 TRUE : 上升状态 FALSE : 下降状态
		int m_nBUTUpDelay;				//工作台上升延迟
		int m_nBUTDownDelay;				//工作台下降延迟
	};

	class AS_EXPORTS ConveyorBelt
	{
	public:
		bool m_bRunState;				//传送带运行状态 TRUE : 运行 FALSE : 停止
		PCBState m_TransState;			//传送带板子状态
	};

	class AS_EXPORTS StationRegion
	{
	public:
		Stopper m_stopper;
		BUT m_but;
		Point m_cWorkSensorPos; //传感器坐标
		ConveyorBelt m_belt;
	};

	class AS_EXPORTS TimeSetting
	{
	public:
		// 定时器
		TimeSetting();
		int		m_nStopperTime;			//止挡器定时器
		int     m_nBackupTableTime;     //but定时器           暂未使用
		int     m_nInStationTime;		//进工作台时间
		int     m_nOutStationTime;		//出工作台时间
		int     m_nBoardEntryTime;		//板子进入时间
		int     m_nShuttleHomingTime;	//电磁阀归位时间
		int     m_nShuttleLimitTime;	//电磁阀时间限制
		int     m_nShuttleMoveTime;		//电磁阀运动时间
		int     m_nRailHomingTime;		//轨道归位时间
		int     m_nRailLimitTime;		//轨道时间限制
		int     m_nRailMoveTime;		//轨道运动时间

		// 延时
		int     m_nPCBLockDelay;			//PCB锁定延迟
		int     m_nEdgeFixerDelay;		//边缘固定器延迟
		int		m_nSensorRecheckDelay;	//传感器复核时间
	};

	class AS_EXPORTS Rail
	{
	public:
		Rail();
		//template <class Archive>
		//friend void boost::serialization::serialize(Archive& ar, Rail& val, const unsigned int version);

		double	m_dWidth;				//传送带的宽度
		double  m_dMinWidth;			//传送带最小宽度
		double  m_dMaxWidth;			//传送带最大宽度 
		double  m_dMinLength;			//传送带最小长度
		double  m_dWidthMargin;			//传送带宽度补偿
		int		m_nTranModel;			//传板模式 0 : 正常传板 1 : 可编辑长板 2 : 通用长板 3:旧的长板模式
		int     m_TransDirection;       //传板方向 1 正向 0 反向 (硬件 0 正向 1 反向)
		vector<double>  m_vMaxLength;	//传送带最大长度 对应三种传板模式
	};

	//传送带
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

		//传送带状态
		int GetBeltPCBState(Station station);
		void SetBeltPCBState(Station station, int State);

		//But平台上升时间
		int GetButTime();
		void SetButTime(int but_time);

		int GetButINStationTime();
		void SetButInStationTime(int instation_time);

		int GetButOutStationTime();
		void SetButOutStationTime(int outstation_time);

		//传板模式
		int GetTransModel();
		void SetTranModel(int model);

		//传板方向
		int GetTransDirection();
		void SetTranDirection(int direction);

		//板子宽度
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
		bool m_bConveyFixedTrack;		    //传送带固定 true Front  
	};
}
#endif
