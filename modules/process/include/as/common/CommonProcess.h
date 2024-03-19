#ifndef AS_COMMONPROCESS_H
#define AS_COMMONPROCESS_H

#include "as/CommonCore.hpp"
#include "as/BaseBoardCore.hpp"
#include "as/CADCore.hpp"
#include "as/ErrorCode.hpp"

namespace as
{
	enum class MsgLevel
	{
		EVENT,			// 事件
		EMEG,			// EMEG
		WARNING,		// WARNING
		MPU_STOP,		// MPU-STOP
		MESSGAE,		// MESSAGE
		CURRENTSTATE,	// 当前机器状态
		KEYOPERATION	// 按键操作
	};

	enum class SoftErrCode
	{
		OperateSuccessfully = 0X0100,
		OperateSuccessfullyFid = 0X0101,
		OperateParameterFail = 0X0102,
		OperateFail = 0X0103,
		Uninitialized = 0X0104,
		ProPartTemplate = 0X0105,
		ImageDetectionANC = 0X0106,
		ImageDetectionANCFail = 0X0107,
		//MarkNoCalibration = 0X0108,//Mark点没有标定
		//MarkCalibrationOperationFail = 0X0109,//Mark点标定操作失败
		MarkLightUninitialized = 0X010A,
		MarkIgnoreCalibration = 0X010B,
		BadMarkCalibration = 0X010C,
		AcceptMarkCalibration = 0X010D,
		BoardWidthFail = 0X010E,//下发查询板宽指令执行失败
		ReturnIDLE = 0X010F,
		CheckBoard = 0X0110,//请检查板子是否到位或重新传入电路板
		HardwareFail = 0X0111,
		CheckBlowFail = 0X0112,
		CheckFallFail = 0X0113, 
		ImageSkylineFail = 0X0114,//图像轮廓线接口错误
		ImageCamFail = 0X0116,//图像相机接口错误
		ThreeTransErr = 0X0117,//3号传送带传感器返回结果异常
		ThreeTransPCB = 0X0118,//3号传送带有电路板，无法传出当前电路板
		SearchPCBTransFail = 0X0119, //下发查询电路板传感器状态指令执行失败
		SearchPCBWidthFail = 0X011A,//下发查询板宽指令执行失败
		PCBWidthDifferent = 0X011B,//当前电路板与目标贴装电路板板宽不一致
		ButOverTime = 0X011D,//平台上升超时
		MarkInfoDefect = 0X011E,//基板Mark信息缺失
		PCBSensorAbnormal = 0x011F,//请检查生产电路板被取出或传送装置传感器异常
		PCBMarkFail = 0X0123,//基板Mark检测失败
		ChipMarkFail = 0X0124,//芯片Mark检测失败
		MountingChipMarkFail = 0X0125,//贴装元件过程中Mark点未识别通过
		SearchPACKFail = 0X0126,//查询电源指令执行失败
		PACKFail = 0X0127,//设备电源开启失败
		EmgNosolve = 0X0128,//导致急停事件未解决
		SearchTransFail = 0X0129,//查询传感器指令执行失败
		PumpPowerErr = 0X012A,//真空泵故障
		SearchTransErr = 0X012D,//查询传送带定位传感器指令执行失败
		CloseBuzzerCtrFail = 0X012E,
		WarmUpMoveFail = 0X012F,
		ZAixsAndSWAixsFail = 0X0130,//Z轴和SW轴归零失败
		AixsMotionALMLimitPosition = 0X0131,
		WarmUpMirrorFail = 0X0132,
		UnReady = 0X0133,//机器还没有准备好
		PickupPos = 0X0134,//贴装位置临近传送带
		FeederFail = 0X0135,//查询飞达传感器指令执行失败
		NumoneBoard = 0X0136,//1号传送带上有电路板
		NumtwoBoard = 0X0137,//2号传送带上有电路板
		NumthreeBoard = 0X0138,//3号传送带上有电路板
		FidOpenFail = 0X0139,//基准相机打开失败
		LANFile = 0X013C,//局域网内有外部文件传入
		QueryBoardFail = 0X013F,//查询卡板指令执行失败
		BoardStatus = 0X0140,//卡板状态
		ReturnSuccess = 0X0141,//机器回原点成功
		ConveyorbeltBoardFail = 0X0142,//传送带卡板
		ConveyorbeltBoard = 0X0143,//传送带中有电路板
		ControlpanelReady = 0X0145,//控制面板按下 Ready
		ControlpanelStart = 0X0146,//控制面板按下 Start
		ControlpanelStop = 0X0147,//控制面板按下 Stop
		ControlpanelEmg = 0X0148,//控制面板按下 Emg
		ControlpanelReset = 0X0149,//控制面板按下 Reset
		ControlpanelRFD = 0X014A,//控制面板按下 RFD
		ControlpanelFFD = 0X014B,//控制面板按下 FFD
		FDoorOpen = 0X014C,//前门开
		BDoorOpen = 0X014D,//后门开
		CheckFBDoor = 0X014E,//查询前后门开关状态指令执行失败
		XAxisoriginFail = 0X0155,//X轴回原点失败
		YAxisoriginFail = 0X0156,//Y轴回原点失败
		WDAxisoriginFail = 0X0157,//WD轴回原点失败
		Producesimulation = 0X0158,//

		MoveXYFail = 0X0302,//移动XY失败
		MachineCalibration = 0X0303,
		FidMoveANCFail = 0X0305,
		OpenFidFail = 0X0306,
		OpenFixFail = 0X0307,
		ChangeANCFail = 0X0308,
		AutomaticChangeANCFail = 0X0309,
		HeadMoveFixFail = 0X030A,
		CamCheckFail = 0X030B,
		GetXYFail = 0X030C,
		FidMoveFixFail = 0X030D,
		OpenFidLightFail = 0X0314,
		OpenFixLightFail = 0X0315,
		OpenFlyLightFail = 0X0316,

		PCBTransFail = 0X0401,
		MarkCalibrationFail = 0X0402,//Mark点标定失败
		BadBoardCheckFail = 0X0403,
		CheckChipFail = 0X0406,
		MountingChipFail = 0X0407,
		DiscardChipFail = 0X0408,
		MarkNoCalibration = 0X0409,//Mark点未标定
		MoveFirstMarkFail = 0X040A,
		TransPCBANCFail = 0X040B,
		PrePickupChipFail = 0X040C,//生产过程预拾取操作执行失败
		Continuation = 0X040D,//续贴开始
		NextCycle = 0X040E,
		StopThread = 0X040F,
		NoPickupPoint = 0X0410,
		UnarriveMarkPoint = 0X0411,
		ChangStepNotData = 0X0412,
		ChangStep = 0X0413,
		NoPickupData = 0X0414,
		NochipPriority = 0X0415,
		ChipNoLogon = 0X0416,
		PickupNozzleNotEnough = 0X0417,
		XYUseFix = 0X041B,
		UnCorrespondingFeeder = 0X0401D,
		PassPCBPosition = 0X0423,
		PositionUnmove = 0X0424,
		MarkOutPosition = 0X0425,
		MarkUnarrive = 0X0426,
		InvalidPickup = 0X0427,
		PositionUnarrive = 0X0428,
		ProduceMarkFail = 0X042F,//生产时Mark点扫描失败，请调整


		BOOT = 0X0500,
		IDLE = 0X0501,
		RUNREADY = 0X0502,
		RUN = 0X0503,
		PAUSE = 0X0504,
		FREEZE = 0X0505,
		WAIT = 0X0506,
		EMG = 0X0507,
		ADJUST = 0X0508,
		STEPMOUNT = 0X0509,
		TakeOuttime = 0X050A,
		WasteAdjust = 0X050B,
		MarkFailAdjust = 0X050C,
		ChangeNozzleFailAdjust = 0X050D,
		TFNumAdjust = 0X050E,
		PCBComplete = 0X050F,
		HardorImageAdjust = 0X0510,
		ProduceNumAdjust = 0X0511,
		WasteStop = 0X0512,
		PCBFailAdjust = 0X0513,
		ScatterOverAdjust = 0X0514,
		/*CheckBlowFailAdjust = 0X0515,*/
		AppWarmUpWait = 0X0518,
		ZRAxisZero = 0X051A,
		UnMove = 0X051B,
		UnGet = 0X051C,
		UnState = 0X051D,
		LevelCore = 0X051E,

		SearchXTransFail = 0X0700,//查询X轴传感器指令执行失败
		SearchYTransFail = 0X0701,//查询Y轴传感器指令执行失败
		SearchWDTransFail = 0X0712,//查询WD轴传感器指令执行失败

		XAxisPLimitPosition = 0X0713, //X轴电机处于正限位
		YAxisPLimitPosition = 0X0714, //Y轴电机处于正限位

		XAxisNLimitPosition = 0X071F, //X轴电机处于负限位
		YAxisNLimitPosition = 0X0720, //Y轴电机处于负限位

		XAxisALMPosition = 0X072B, //X轴电机处于ALM限位
		YAxisALMPosition = 0X072C, //Y轴电机处于ALM限位
		WDAxisALMPosition = 0X073D, //WD轴电机处于ALM限位

		CVCANFail = 0X0740,//CV板CAN通信初始化失败
		FIXCANFail = 0X0741,//FIX板CAN通信初始化失败
		HDCANFail = 0X0742,//HD飞达CAN通信初始化失败

		UnknownError = 0X0800,//发生未知错误
	};

	enum class LanguegeType
	{
		CHS = 0,
		ENG,
		KOR
	};

	class AS_EXPORTS CommonProcess
	{
	public:
		CommonProcess();
		~CommonProcess() {};

		static CommonProcess& GetInstance();
		void SetMessageBoardFunc(std::function<void(std::string, std::string, int error_code)> func);
		void SetGUIFunc(std::function<void(int)> func);
		void SetRefCompListFunc(std::function<void(int block_id, int array_id, int index, bool ref_flag)> func);
		string string_To_UTF8(const string& str);
		bool isChineseChar(char c);
		vector<string> SplitString(string str, bool isSplit=true);
		//判断值范围
		bool JudgeValueRange(string valueOfMin, string valueOfMax, string input);

		//消息发送
		void SoftSendQMessage(MsgLevel level, SoftErrCode error_code, bool messageestate = true, string error_info = "");
		//void SendQMessage(MsgLevel level, int error_code);
		//void ImgSendQMessage(MsgLevel level, imgproc::ImgErrorCode error_code, bool messageestate = true, string error_info = "");
		//bool ImagErrCodeTip(APIErrCode img_errCode);

		//工具接口
		string intToHex(int n);
		char hexUnit(unsigned char unit);


	private:
		mutex mtx;
		std::function<void(int)> m_GUIFunc;
		std::function<void(int block_id, int array_id, int index, bool ref_flag)> m_RefCompListFunc;
		std::function<void(std::string, std::string, int error_code)> m_MessageBoardFunc;
		string m_strProgramName; //项目名称
		string m_strDataSavePath;//数据保存路径
	};

	

	// 共有检查类
	class AS_EXPORTS CommonCheck
	{
	public:
		static bool StateMachineCheck(bool moveaction);  // true：Move动作，false：Get动作
	};
}

#endif