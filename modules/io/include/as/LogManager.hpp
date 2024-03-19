#pragma once

#ifndef logfilename(x)
#define logfilename(x) strrchr(x, '\\') ? strrchr(x, '\\') + 1 : x
#endif

#include <mutex>
#include <string>
#include <fstream>
#include <iostream>
#include <functional>
#include "direct.h"
#include "as/io.hpp"
#include "as/core/def.h"

#include <log4cpp/Category.hh>
#include <log4cpp/Appender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/Priority.hh>
#include <log4cpp/PatternLayout.hh>
#include <log4cpp/RollingFileAppender.hh>

// 日志等级
enum class LogLevel
{
    FATAL = 0,
    ALERT = 100,
    CRIT = 200,
    ERROR = 300,
    WARN = 400,
    NOTICE = 500,
    INFO = 600,
    DEBUG = 700
};

// 日志类型
enum class LogType
{
    LOG_HARDWARE = 1,     // 硬件日志
    LOG_SOFTWARE = 2,     // 软件日志
    LOG_OPERATE = 3,      // 软件操作日志
    LOG_IMAGE = 4,        // 图像操作日志
    LOG_Database = 5,     // 数据库日志
    LOG_ERRORMESSAGE = 6, // 消息栏消息日志
    LOG_Optimizer = 7,    // 优化日志
    LOG_ALGORITHM = 8, // 检测算法日志
};

namespace as
{
    class AS_EXPORTS LogManager
    {
    public:
        LogManager();
        ~LogManager();

        static LogManager &GetInstance();
        void WriteMessage(std::string message_str, LogLevel log_level, LogType log_type);
        void UpdateLogfile(LogType log_type);
        tm CurLogTime();

    private:
        struct LogIni
        {
            std::string type = "";
            log4cpp::Priority::PriorityLevel priorityLevel = log4cpp::Priority::PriorityLevel::INFO;
            std::string file = "";
            std::string path = "";
            std::string fileName = "";
            int fileNum = 1;
            int timeName = 0;
            int fileSize = 1024 * 1024 * 1024;
            std::string layout = "";
        };

    public:
        std::string ReadSMTLogIni();
        bool ReadLogIniTimeNum(std::string LogIniType);
        void ReadLogIniFile(LogIni &log_ini);

    private:
        void HardLogInit();
        void SoftLogInit();
        void OperateLogInit();
        void ImageProcessLogInit();
        void DatabaseLogInit();
        void ErrorMessageLogInit();
        void OptimizerInit();
        void AlgorithmLogInit();

        std::map<std::string, log4cpp::Priority::PriorityLevel> logLevelMap;
        log4cpp::Priority::PriorityLevel LogManager::MapLogLevel(std::string loglevel);

        tm log_time; // 日志创建时间戳
        IniFile loginifile;
        std::string folderPath; // 日志路径
        std::mutex LogMutex;

        log4cpp::PatternLayout *HardLayout; // 日志样式
        log4cpp::PatternLayout *SoftLayout;
        log4cpp::PatternLayout *OperateLayout;
        log4cpp::PatternLayout *ImageProcessLayout;
        log4cpp::PatternLayout *ImageAlgorithmLayout;
        log4cpp::PatternLayout *BreakDownLayout;
        log4cpp::PatternLayout *CameraProcessLayout;
        log4cpp::PatternLayout *CalibrationErrorMessageLayout;
        log4cpp::PatternLayout *ProduceMessageLayout;
        log4cpp::PatternLayout *DatabaseLayout;
        log4cpp::PatternLayout *OptimizerMessageLayout;
        log4cpp::PatternLayout *ErrorMessageLayout;

        log4cpp::RollingFileAppender *HardAppender; // 日志输出源
        log4cpp::RollingFileAppender *SoftAppender;
        log4cpp::RollingFileAppender *OperateAppender;
        log4cpp::RollingFileAppender *ImageProcessAppender;
        log4cpp::RollingFileAppender *ImageAlgorithmAppender;
        log4cpp::RollingFileAppender *BreakDownAppender;
        log4cpp::RollingFileAppender *CameraProcessAppender;
        log4cpp::RollingFileAppender *CalibrationMessageAppender;
        log4cpp::RollingFileAppender *ProduceMessageAppender;
        log4cpp::RollingFileAppender *DatabaseAppender;
        log4cpp::RollingFileAppender *OptimizerMessageAppender;
        log4cpp::RollingFileAppender *ErrorMessageAppender;

        log4cpp::Priority::PriorityLevel HardLevelOP; // 日志等级
        log4cpp::Priority::PriorityLevel SoftLevelOP;
        log4cpp::Priority::PriorityLevel OperateLevelOP;
        log4cpp::Priority::PriorityLevel ImageProcessLevelOP;
        log4cpp::Priority::PriorityLevel ImageAlgorithmLevelOP;
        log4cpp::Priority::PriorityLevel BreakDownLevelOP;
        log4cpp::Priority::PriorityLevel CameraProcessLevelOP;
        log4cpp::Priority::PriorityLevel CalibrationMessageLevelOP;
        log4cpp::Priority::PriorityLevel ProduceMessageLevelOP;
        log4cpp::Priority::PriorityLevel DatabaseLevelOP;
        log4cpp::Priority::PriorityLevel OptimizerMessageLevelOP;
        log4cpp::Priority::PriorityLevel ErrorMessageLevelOP;
    };

    AS_EXPORTS void WriteHardLog(std::string message_str, LogLevel log_level);
    AS_EXPORTS void WriteSoftLog(std::string message_str, LogLevel log_level);
    AS_EXPORTS void WriteOperateLog(std::string message_str, LogLevel log_level);
    std::string FuncSplit(std::string func_name, std::string pattern);
    AS_EXPORTS void WriteImageProcessLog(std::string message_str, LogLevel log_level);
    AS_EXPORTS void WriteImageProcessLog(const char *funcname, const unsigned long line, std::string filename, int flag);
    AS_EXPORTS void WriteImageProcessMessageLog(const char *funcname, std::string message, const unsigned long line, std::string filename);
    AS_EXPORTS void WriteImageProcessErrorLog(const char* funcname, std::string Exp, const unsigned long line, std::string filename);
    AS_EXPORTS void WriteImageProcessErrorLog(const char* funcname, std::string Exp, unsigned int error_code, const unsigned long line, std::string filename);
    AS_EXPORTS void WriteDatabaseLog(std::string message_str, LogLevel log_level);
    AS_EXPORTS void WriteErrorMessageLog(std::string message_str, LogLevel log_level);
    AS_EXPORTS void WriteOptimizerLog(std::string message_str, LogLevel log_level);
    AS_EXPORTS void WriteImageAlgorithmLog(const char* funcname, const unsigned long line, std::string filename, int flag);
    AS_EXPORTS void WriteImageAlgorithmMessageLog(const char* funcname, std::string message, const unsigned long line, std::string filename);
    AS_EXPORTS void WriteImageAlgorithmErrorLog(const char* funcname, std::string Exp, const unsigned long line, std::string filename);
    AS_EXPORTS void WriteImageAlgorithmErrorLog(const char* funcname, std::string Exp, unsigned int error_code, const unsigned long line, std::string filename);


    class AS_EXPORTS OperateLogfunc
    {
    public:
        // 单例
        static OperateLogfunc &GetInstance();

        // INFO等级 按钮点击记录    __FUNCTION__  __LINE__
        void InfoClickRecord(std::string message_infor, const unsigned long line);

        // INFO等级 实体按钮点击记录    __FUNCTION__  __LINE__
        void InfoPhysicalKeyRecord(std::string message_infor, const unsigned long line);

        // DEBUGD等级 按扭点击记录
        void DebugRecord(std::string message_infor, std::string function_name);

        // 窗口打开记录
        void windowsOpenRecord(std::string message_infor, std::string function_name);

        // 窗口关闭记录
        void windowsCloseRecord(std::string message_infor, std::string function_name);

        // INFO等级 下拉框选择记录
        void InfoComRecord(std::string message_infor, std::string function_name, const unsigned long line);

        // DEBUG等级 下拉框选择记录
        void DebugComRecord(std::string message_infor, std::string function_name);

        // INFO等级 列表修改记录
        void InfoListChangeRecord(std::string message_infor, const unsigned long line);

        // DEBUG等级 列表修改记录
        void DEBUGListChangeRecord(std::string message_infor, std::string function_name);

        // INFO等级 数据修改
        void InfoDataChangeRecord(std::string message_infor, double num, const unsigned long line);
        void InfoDataChangeRecord(std::string message_infor, std::string str, const unsigned long line);

        // DEBUG等级 数据修改
        void DEBUGDataChangeRecord(std::string message_infor, std::string function_name);

        // INFO 表格改变
        void InfoTableChangeRecord(std::string tablename, std::string message_infor, int x, std::string y_value, const unsigned long line);

        // INFO等级 勾选 控件名 ,   __LINE__
        void InfoCheckRrcord(std::string message_infor, unsigned char value, const unsigned long line);

        // INFO等级 快捷键使用记录     __LINE__
        void InfoHotkeyRecord(std::string key, std::string message_infor, const unsigned long line);
    };

    class AS_EXPORTS SoftwareLogfunc
    {
    public:
        // 单例
        static SoftwareLogfunc &GetInstance();

        // 信息输出
        void TipRecord(std::string moduletype, std::string message_info, const unsigned long line);

        void EnterFunction(std::string funcName, std::string fileName, const unsigned long line);
        void LeaveFunction(std::string funcName, std::string fileName, const unsigned long line);
        // 数据库记录操作
        void DatabaseRecord(std::string basename, std::string tablename, std::string opreate, const unsigned long line);

        // 与外系统交互 文件操作 信息传输

        // 处理任务

        // ERROR  数据库  指针  数据  流程
        void ErrorRecord(std::string partname, std::string err, const unsigned long line);

        // WARN  可以运行但有错
        void DatabaseWarn(std::string basename, std::string tablename, std::string warn_str, const unsigned long line);

        // 对话框回调函数使用
        void UiCallbackRecord(std::string info);
    };

    class AS_EXPORTS DatabaseLogfunc
    {
    public:
        // 单例
        static DatabaseLogfunc &GetInstance();

        // 数据库数据记录
        void databaseRecord(std::string message_info);

        void EnterFunction(std::string funcName, std::string fileName, const unsigned long line);
        void LeaveFunction(std::string funcName, std::string fileName, const unsigned long line);
    };

    class AS_EXPORTS ErrorMessageLogfunc
    {
    public:
        // 单例
        static ErrorMessageLogfunc &GetInstance();

        // 消息栏消息数据记录
        void ErrorMessageRecord(std::string message_info);
    };
}