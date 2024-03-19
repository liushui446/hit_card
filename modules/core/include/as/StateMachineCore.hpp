#ifndef AS_STATEMACHINECORE_HPP
#define AS_STATEMACHINECORE_HPP

#include "as/CommonCore.hpp"

namespace as
{   //状态子类名枚举
	enum StateID
	{
		StateID_Boot = 0x00,
		StateID_Idle_0 = 0x10,
		StateID_Idle_1 = 0x11,
		StateID_Idle_2 = 0x12,
		StateID_Wait = 0x13,
		StateID_Run = 0x20,
		StateID_Pause = 0x22,
		StateID_Emg = 0x30,
		StateID_Adjust = 0x31
	};

	//状态机驱动指令
	enum class StateBuffer
	{
		//机械面板
		BootToIdle0_buff = 0x1000,                    //Boot到Idle0自检
		ControlPanelStart_buff = 0x1001,			  //机械面板开始按键
		ControlPanelStop_buff = 0x1002,               //机械面板停止按键
		ControlPanelPause_buff = 0x1002,              //机械面板暂停按键
		ControlPanelReset_buff = 0x1003,              //机械面板复位按键
		ControlPanelReady_buff = 0x1004,              //机械面板准备按键
		ControlPanelEmergency_buff = 0x1005,          //机械面板急停按键
		ControlPanelEmergencyUp_buff = 0x1006,        //机械面板急停抬起

		InterfaceStop_buff = 0x2001,                  //上位机停止按钮
		InterfaceInitialization_buff = 0x2004,        //上位机初始化按钮

		SetAdjust_buff = 0x3001,                      //设置当前状态为Adjust状态
		RecoveryAdjust_buff = 0x3002,                 //设置当前状态为Adjust状态之前原状态
		SetEmergency_buff = 0x3003,                   //设置当前状态为Emergency状态
		SetWait_buff = 0x3004,                        //设置当前状态为Wait状态
		RecoveryWait_buff = 0x3005                   //设置当前状态为Wait状态之前原状态IDLE2
	};

	//状态机执行错误码
	enum class StateErr
	{
		State_Success = 0x00,
		State_Fail = 0x10
	};
	
	/**
	 * @name StateMachineCore
	 * @file StateMachineCore.hpp
	 * @brief 状态机核心类
	*/
	class AS_EXPORTS StateMachineCore {
		StateMachineCore();
	public:
		static StateMachineCore& GetInstance();
		StateID GetStateID();
		shared_ptr<std::mutex> GetStateCoreMutex();
		short GetFirstOriginFlag();
		void SetFirstOriginFlag(short origin_flag);
		bool GetHardwarePowerFlag();
		void SetHardwarePowerFlag(bool hardwarepowerflag);
		short GetConveyerFirstCheckFlag();
		void SetConveyerFirstCheckFlag(short boardstate);
		bool ConveyerFirstCheck();
	private:
		friend class StateMachineThread;  //设置友元
		StateErr SetState(StateID StateID);
		time_t GetCurrentTime();
	private:
		StateID m_State_Name;                            //状态子类名
		StateID m_Freeze_Pre_State_Name;                 //冻结状态前一状态名
		vector<unsigned short> m_Freeze_Events;          //存储触发冻结状态的事件
		shared_ptr<std::mutex> m_StateCore_Lock;         //互斥量用于线程锁保护
		short m_FirstOrigin_Flag;                        //第一次回原点标志位
		bool m_HardwarePower_Flag;                       //第一次上电标志位
		short m_ConveyerFirstCheck;                      //第一次动板宽回原点、调整传送带均需要检测有无电路板  =0缺省 =1无板 =2有板
	};

}

#endif