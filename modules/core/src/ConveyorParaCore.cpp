#include "as/ConveyorParaCore.hpp"

namespace as
{
	ConveyorPara::ConveyorPara()
	{
		for (int i = 0; i < static_cast<int>(Station::size); i++)
		{
			StationRegion station_;
			station_.m_belt.m_bRunState = false;
			station_.m_belt.m_TransState = PCBState::NONE;
			m_mStation.insert(pair<Station, StationRegion>(static_cast<Station>(i), station_));
		}
	}

	Rail::Rail()
	{
		m_dWidth = 450;
		m_dMinWidth = 40;
		m_dMaxWidth = 400;
		m_dMinLength = 40;
		m_dWidthMargin = 0;
		m_nTranModel = 0;
		m_TransDirection = 1;
		m_vMaxLength.assign(3, 460);
	}

	TimeSetting::TimeSetting()
	{
		m_nStopperTime = 0;
		m_nBackupTableTime = 0;
		m_nInStationTime = 0;
		m_nOutStationTime = 0;
		m_nBoardEntryTime = 0;
		m_nShuttleHomingTime = 0;
		m_nShuttleLimitTime = 0;
		m_nShuttleMoveTime = 0;
		m_nRailHomingTime = 0;
		m_nRailLimitTime = 0;
		m_nRailMoveTime = 0;
	}

	ConveyorPara& ConveyorPara::operator=(ConveyorPara& ref)
	{
		this->m_bConveyFixedTrack = ref.GetConveyFixedTrack();
		this->m_mStation.clear();
		StationRegion temp_station;
		for (int i = 0; i < static_cast<int>(Station::size); i++)
		{
			temp_station = ref.GetStation(static_cast<Station>(i));
			this->m_mStation.insert(pair<Station, StationRegion>(static_cast<Station>(i), temp_station));
		}
		this->m_cTimeSetting.m_nStopperTime = ref.GetStopperTime();
		this->m_cTimeSetting.m_nBackupTableTime = ref.GetButTime();
		this->m_cTimeSetting.m_nInStationTime = ref.GetButINStationTime();
		this->m_cTimeSetting.m_nOutStationTime = ref.GetButOutStationTime();
		this->m_cTimeSetting.m_nBoardEntryTime = ref.GetBoardEntryTime();
		this->m_cTimeSetting.m_nShuttleHomingTime = ref.GetShuttleHomingTime();
		this->m_cTimeSetting.m_nShuttleLimitTime = ref.GetShuttleLimitTime();
		this->m_cTimeSetting.m_nShuttleMoveTime = ref.GetShuttleMoveTime();
		this->m_cTimeSetting.m_nRailHomingTime = ref.GetRailHomingTime();
		this->m_cTimeSetting.m_nRailLimitTime = ref.GetRailLimitTime();
		this->m_cTimeSetting.m_nRailMoveTime = ref.GetRailMoveTime();
		this->m_cTimeSetting.m_nPCBLockDelay = ref.GetPCBLockDelay();
		this->m_cTimeSetting.m_nEdgeFixerDelay = ref.GetEdgeFixerDelay();
		this->m_cTimeSetting.m_nSensorRecheckDelay = ref.GetSensorRecheckDelay();

		this->m_rail.m_dMaxWidth = ref.GetTransMaxWidth();
		this->m_rail.m_dMinLength = ref.GetTransMinLength();
		this->m_rail.m_dMinWidth = ref.GetTransMinWidth();
		this->m_rail.m_dWidth = ref.GetTransWidth();
		this->m_rail.m_dWidthMargin = ref.GetTransWidthMargin();
		this->m_rail.m_nTranModel = ref.GetTransModel();
		this->m_rail.m_TransDirection = ref.GetTransDirection();
	
		//this->m_rail.m_vMaxLength = ref. m_vMaxLength;
		return *this;
	}

	StationRegion& ConveyorPara::GetStation(Station staion)
	{
		return m_mStation.find(staion)->second;
	}

	void ConveyorPara::SetSensorPos(Station station, Point pos)
	{
		m_mStation[station].m_stopper.m_StopperPos = pos;
	}

	Point ConveyorPara::GetSensorPos(Station station)
	{
		return m_mStation[station].m_stopper.m_StopperPos;
	}

	bool ConveyorPara::GetStopperState(Station station)
	{
		return m_mStation[station].m_stopper.m_StopperState;
	}

	void ConveyorPara::SetStopperState(Station station, bool state)
	{
		m_mStation[station].m_stopper.m_StopperState = state;
	}

	void ConveyorPara::SetWorkPos(Station station, Point pos)
	{
		m_mStation[station].m_cWorkSensorPos = pos;
	}

	Point ConveyorPara::GetWorkPos(Station station)
	{
		return m_mStation[station].m_cWorkSensorPos;
	}

	int ConveyorPara::GetBeltPCBState(Station station)
	{
		int state = 0;
		switch (m_mStation[station].m_belt.m_TransState)
		{
		case PCBState::NONE:
			state = 0;
			break;
		case PCBState::NORMAL:
			state = 1;
			break;
		case PCBState::STUCK:
			state = 2;
			break;
		default:
			break;
		}
		return state;
	}

	void ConveyorPara::SetBeltPCBState(Station station, int State)
	{
		switch (State)
		{
		case 0:
			m_mStation[station].m_belt.m_TransState = PCBState::NONE;
			break;
		case 1:
			m_mStation[station].m_belt.m_TransState = PCBState::NORMAL;
			break;
		case 2:
			m_mStation[station].m_belt.m_TransState = PCBState::STUCK;
			break;
		default:
			break;
		}
		return;
	}

	int ConveyorPara::GetButTime()
	{
		return m_cTimeSetting.m_nBackupTableTime;
	}

	void ConveyorPara::SetButTime(int but_time)
	{
		m_cTimeSetting.m_nBackupTableTime = but_time;
	}

	int ConveyorPara::GetTransModel()
	{
		return m_rail.m_nTranModel;
	}

	void ConveyorPara::SetTranModel(int model)
	{
		m_rail.m_nTranModel = model;
	}

	void ConveyorPara::SetTranDirection(int direction)
	{
		m_rail.m_TransDirection = direction;
	}

	int ConveyorPara::GetTransDirection()
	{
		return m_rail.m_TransDirection;
	}

	double ConveyorPara::GetTransWidth()
	{
		return m_rail.m_dWidth;
	}

	void ConveyorPara::SetTransWidth(double width)
	{
		m_rail.m_dWidth = width;
		return;
	}

	double ConveyorPara::GetTransMinWidth()
	{
		return m_rail.m_dMinWidth;
	}

	void ConveyorPara::SetTransMinWidth(double minWidth_)
	{
		m_rail.m_dMinWidth = minWidth_;
	}

	double ConveyorPara::GetTransMaxWidth()
	{
		return m_rail.m_dMaxWidth;
	}

	void ConveyorPara::SetTransMaxWidth(double max_width)
	{
		m_rail.m_dMaxWidth = max_width;
	}

	double ConveyorPara::GetTransMinLength()
	{
		return m_rail.m_dMinLength;
	}

	void ConveyorPara::SetTransMinLength(double transMinLength)
	{
		m_rail.m_dMinLength = transMinLength;
	}

	double ConveyorPara::GetTransMaxLength()
	{
		return m_rail.m_vMaxLength.at(m_rail.m_nTranModel);
	}

	double ConveyorPara::GetTransMaxLength(int index)
	{
		return m_rail.m_vMaxLength.at(index);
	}

	void ConveyorPara::SetTransMaxLength(double maxLengthSingleLine_)
	{
		m_rail.m_vMaxLength.at(m_rail.m_nTranModel) = maxLengthSingleLine_;
	}

	void ConveyorPara::SetTransMaxLength(int tranModel, double maxLengthSingleLine_)
	{
		m_rail.m_vMaxLength.at(tranModel) = maxLengthSingleLine_;
	}

	void ConveyorPara::InsertTransMaxLength(double maxLengthSingleLine_)
	{
		m_rail.m_vMaxLength.push_back(maxLengthSingleLine_);
	}

	double ConveyorPara::GetTransWidthMargin()
	{
		return m_rail.m_dWidthMargin;
	}

	void ConveyorPara::SetTransWidthMargin(double widthMargin_)
	{
		m_rail.m_dWidthMargin = widthMargin_;
	}

	bool ConveyorPara::GetBUTState(Station station)
	{
		return m_mStation[station].m_but.m_bBUTState;
	}

	void ConveyorPara::SetBUTState(Station station, bool state)
	{
		m_mStation[station].m_but.m_bBUTState = state;
		return;
	}

	int ConveyorPara::GetStopperTime()
	{
		return m_cTimeSetting.m_nStopperTime;
	}

	void ConveyorPara::SetStopperTime(int stop_time)
	{
		m_cTimeSetting.m_nStopperTime = stop_time;
	}

	int ConveyorPara::GetButINStationTime()
	{
		return m_cTimeSetting.m_nInStationTime;
	}

	void ConveyorPara::SetButInStationTime(int instation_time)
	{
		m_cTimeSetting.m_nInStationTime = instation_time;
	}

	int ConveyorPara::GetButOutStationTime()
	{
		return m_cTimeSetting.m_nOutStationTime;
	}

	void ConveyorPara::SetButOutStationTime(int outstation_time)
	{
		m_cTimeSetting.m_nOutStationTime = outstation_time;
	}

	int ConveyorPara::GetBoardEntryTime()
	{
		return m_cTimeSetting.m_nBoardEntryTime;
	}

	void ConveyorPara::SetBoardEntryTime(int board_entry_time)
	{
		m_cTimeSetting.m_nBoardEntryTime = board_entry_time;
	}

	int ConveyorPara::GetRailHomingTime()
	{
		return m_cTimeSetting.m_nRailHomingTime;
	}

	void ConveyorPara::SetRailHomingTime(int rail_homing_time)
	{
		m_cTimeSetting.m_nRailHomingTime = rail_homing_time;
	}

	int ConveyorPara::GetRailLimitTime()
	{
		return m_cTimeSetting.m_nRailLimitTime;
	}

	void ConveyorPara::SetRailLimitTime(int rail_limit_time)
	{
		m_cTimeSetting.m_nRailLimitTime = rail_limit_time;
	}

	int ConveyorPara::GetRailMoveTime()
	{
		return m_cTimeSetting.m_nRailMoveTime;
	}

	void ConveyorPara::SetRailMoveTime(int rail_move_time)
	{
		m_cTimeSetting.m_nRailMoveTime = rail_move_time;
	}

	int ConveyorPara::GetPCBLockDelay()
	{
		return m_cTimeSetting.m_nPCBLockDelay;
	}

	void ConveyorPara::SetPCBLockDelay(int pcb_lock_delay)
	{
		m_cTimeSetting.m_nPCBLockDelay = pcb_lock_delay;
	}

	int ConveyorPara::GetEdgeFixerDelay()
	{
		return m_cTimeSetting.m_nEdgeFixerDelay;
	}

	void ConveyorPara::SetEdgeFixerDelay(int edge_fixer_delay)
	{
		m_cTimeSetting.m_nEdgeFixerDelay = edge_fixer_delay;
	}

	int ConveyorPara::GetSensorRecheckDelay()
	{
		return m_cTimeSetting.m_nSensorRecheckDelay;
	}

	void ConveyorPara::SetSensorRecheckDelay(int sensor_recheck_delay)
	{
		m_cTimeSetting.m_nSensorRecheckDelay = sensor_recheck_delay;
	}

	int ConveyorPara::GetShuttleHomingTime()
	{
		return m_cTimeSetting.m_nShuttleHomingTime;
	}

	void ConveyorPara::SetShuttleHomingTime(int shuttle_homing_time)
	{
		m_cTimeSetting.m_nShuttleHomingTime = shuttle_homing_time;
	}

	int ConveyorPara::GetShuttleLimitTime()
	{
		return m_cTimeSetting.m_nShuttleLimitTime;
	}

	void ConveyorPara::SetShuttleLimitTime(int shuttle_limit_time)
	{
		m_cTimeSetting.m_nShuttleLimitTime = shuttle_limit_time;
	}

	int ConveyorPara::GetShuttleMoveTime()
	{
		return m_cTimeSetting.m_nShuttleMoveTime;
	}

	void ConveyorPara::SetShuttleMoveTime(int shuttle_move_time)
	{
		m_cTimeSetting.m_nShuttleMoveTime = shuttle_move_time;
	}

	bool ConveyorPara::GetBeltRunState(Station belt_index)
	{
		return m_mStation.at(belt_index).m_belt.m_bRunState;
	}

	void ConveyorPara::SetBeltRunState(Station belt_index, bool run_state)
	{
		m_mStation.at(belt_index).m_belt.m_bRunState = run_state;
		return;
	}

	bool ConveyorPara::GetConveyFixedTrack()
	{
		return m_bConveyFixedTrack;
	}

	void ConveyorPara::SetConveyFixedTrack(bool convey_fixed_track)
	{
		m_bConveyFixedTrack = convey_fixed_track;
	}

}