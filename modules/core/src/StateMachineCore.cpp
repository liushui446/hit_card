#include "as/StateMachineCore.hpp"

namespace as
{
	/**
	 * @brief StateMachineCore状态机核心类构造函数
	*/
	StateMachineCore::StateMachineCore() :m_State_Name(StateID::StateID_Boot), \
		 m_StateCore_Lock(new std::mutex), m_FirstOrigin_Flag(0), \
		m_HardwarePower_Flag(false), m_ConveyerFirstCheck(0)
	{ }

	/**
	 * @brief StateMachineCore状态机核心类单例
	 * @return StateMachineCore状态机核心类单例对象
	*/
	StateMachineCore& StateMachineCore::GetInstance()
	{
		static StateMachineCore instance;
		return instance;
	}

	/**
	 * @brief 获取当前状态名函数
	 * @return 当前状态名
	*/
	StateID StateMachineCore::GetStateID()
	{
		return m_State_Name;
	}


	time_t StateMachineCore::GetCurrentTime()
	{
		std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> tp = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
		auto tmp = std::chrono::duration_cast<std::chrono::milliseconds>(tp.time_since_epoch());
		return tmp.count();
	}


	/**
	 * @brief 获取StateMachineCore互斥锁
	 * @return 互斥锁智能指针
	*/
	shared_ptr<std::mutex> StateMachineCore::GetStateCoreMutex()
	{
		return m_StateCore_Lock;
	}

	/**
	 * @brief 获取机器开机后是否已经实现回原点操作
	 * @return 0=未进行回原点操作  1=已进行第一次回原点操作
	*/
	short StateMachineCore::GetFirstOriginFlag()
	{
		return m_FirstOrigin_Flag;
	}
	/**
	 * @brief 设置机器开机后是否已经实现回原点操作标志位
	 * @param origin_flag 机器开机后是否已经实现回原点操作标志位 0=未进行回原点操作  1=已进行第一次回原点操作
	*/
	void StateMachineCore::SetFirstOriginFlag(short origin_flag)
	{
		m_FirstOrigin_Flag = origin_flag;
	}

	/**
	 * @brief 获得机器是否上电标志位
	 * @return false=未上电  true=已上电
	*/
	bool StateMachineCore::GetHardwarePowerFlag()
	{
		return m_HardwarePower_Flag;
	}

	/**
	 * @brief 设置机器是否上电标志位
	 * @param hardwarepowerflag false=未上电  true=已上电
	*/
	void StateMachineCore::SetHardwarePowerFlag(bool hardwarepowerflag)
	{
		m_StateCore_Lock->lock();
		m_HardwarePower_Flag = hardwarepowerflag;
		m_StateCore_Lock->unlock();
	}

	short StateMachineCore::GetConveyerFirstCheckFlag()
	{
		return m_ConveyerFirstCheck;
	}

	void StateMachineCore::SetConveyerFirstCheckFlag(short boardstate)
	{
		m_StateCore_Lock->lock();
		m_ConveyerFirstCheck = boardstate;
		m_StateCore_Lock->unlock();
	}

	/**
	 * @brief 第一次回原点或者调整板宽时，对传送带上的电路板进行检测
	 * @return true=有电路板 false=没有电路板
	*/
	bool StateMachineCore::ConveyerFirstCheck()
	{
		short temp_state = 0;
		time_t last_time = GetCurrentTime();
		time_t new_time = 0;
		time_t tick = 0;
		do {
			new_time = GetCurrentTime();
			temp_state = m_ConveyerFirstCheck;
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			tick = new_time - last_time;
		} while ((!temp_state) && (tick < 5000));
		//标志位复位
		if (m_ConveyerFirstCheck == 2) {
			return true;
		}
		return false;
	}

	/**
	 * @brief 设置当前状态名
	 * @param StateID 当前状态名
	 * @return 返回执行结果码值
	*/
	StateErr StateMachineCore::SetState(StateID StateID)//设置当前状态
	{
		m_StateCore_Lock->lock();
		m_State_Name = StateID;
		m_StateCore_Lock->unlock();
		return StateErr::State_Success;
	}
}