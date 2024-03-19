#include <corecrt_io.h>
#include <filesystem>
#include <codecvt>

#include "as/LogManager.hpp"

using namespace std;

namespace as
{
    string wstring2string(const std::wstring &ws)
    {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        string result = converter.to_bytes(ws);
        return result;
    }

    string DecIntToHexStr(long long num);
    string DecStrToHexStr(string str);
    std::vector<std::string> split(std::string str, std::string pattern);
    void LogManager::ReadLogIniFile(LogIni &log_ini)
    {
        log_ini.priorityLevel = MapLogLevel(loginifile.ReadIniContent(log_ini.type, "PriorityLevel", "DEBUG"));
        log_ini.file = loginifile.ReadIniContent(log_ini.type, "Appender.type", "RollingFileAppender");
        log_ini.path = loginifile.ReadIniContent(log_ini.type, "Appender.path", log_ini.path);
        log_ini.fileName = loginifile.ReadIniContent(log_ini.type, "Appender.fileName", log_ini.fileName);
        string readstr = loginifile.ReadIniContent(log_ini.type, "Appender.maxFileSize", "1G");
        log_ini.fileNum = atoi(loginifile.ReadIniContent(log_ini.type, "Appender.fileNum", "1").c_str());
        log_ini.timeName = atoi(loginifile.ReadIniContent(log_ini.type, "Appender.fileTimeName", "0").c_str());
        if (readstr.substr(readstr.length() - 1) == "K" || readstr.substr(readstr.length() - 1) == "k")
        {
            log_ini.fileSize = atoi((readstr.substr(0, readstr.length() - 1)).c_str()) * 1024;
        }
        else if (readstr.substr(readstr.length() - 1) == "M" || readstr.substr(readstr.length() - 1) == "m")
        {
            log_ini.fileSize = atoi((readstr.substr(0, readstr.length() - 1)).c_str()) * (1024 * 1024);
        }
        else if (readstr.substr(readstr.length() - 1) == "G" || readstr.substr(readstr.length() - 1) == "g")
        {
            string aa = readstr.substr(0, readstr.length() - 1);
            log_ini.fileSize = atoi((readstr.substr(0, readstr.length() - 1)).c_str()) * (1024 * 1024 * 1024);
        }
        else
        {
            log_ini.fileSize = 10 * 1024 * 1024;
        }
        log_ini.layout = loginifile.ReadIniContent(log_ini.type, "Appender.layout", "%d:[%p]-%m%n");
    }

    // 日志文件类实例分别代表三个日志文件
    log4cpp::Category &HardwareLog = log4cpp::Category::getInstance("HardwareLog");
    log4cpp::Category &SoftwareLog = log4cpp::Category::getInstance("SoftwareLog");
    log4cpp::Category &OperateLog = log4cpp::Category::getInstance("OperateLog");
    log4cpp::Category &ImageProcessLog = log4cpp::Category::getInstance("ImageProcessLog");
    log4cpp::Category &DatabaseLog = log4cpp::Category::getInstance("DatabaseLog");
    log4cpp::Category &ErrorMessageLog = log4cpp::Category::getInstance("ErrorMessageLog");
    log4cpp::Category &OptimizerLog = log4cpp::Category::getInstance("OptimizerLog");
    log4cpp::Category& AlgorithmLog = log4cpp::Category::getInstance("AlgorithmLog");

    // 设置配置文件读取路径
    string LogManager::ReadSMTLogIni()
    {
        // 获取当前路径并查找切割process
        std::wstring current_path = std::filesystem::current_path();
        string fileName = wstring2string(current_path);
        int pos = fileName.find("build");
        fileName.erase(pos);
        fileName += "inifile\\LogIniFile.ini";

        loginifile.SetIniFilePath(fileName);

        for (int i = 8; i >= 1; i--)
        {
            pair<string, log4cpp::Priority::PriorityLevel> loglevelpair;
            loglevelpair.first = loginifile.ReadIniContent("ASLog", "LOGLEVEL" + std::to_string(i), "DEBUG");
            loglevelpair.second = log4cpp::Priority::PriorityLevel((i - 1) * 100);

            logLevelMap.insert(loglevelpair);
        }
        return loginifile.ReadIniContent("ASLog", "FolderPath", "..\\..\\aslog");
    }

    bool LogManager::ReadLogIniTimeNum(string LogIniType)
    {
        LogIni log_ini;
        log_ini.type = LogIniType;
        log_ini.path = "\\" + LogIniType;
        log_ini.fileName = LogIniType + ".log";
        ReadLogIniFile(log_ini);
        return log_ini.timeName;
    }

    log4cpp::Priority::PriorityLevel LogManager::MapLogLevel(string loglevel)
    {
        if (logLevelMap.find(loglevel) == logLevelMap.end())
        {
            return log4cpp::Priority::PriorityLevel::INFO;
        }
        return logLevelMap.find(loglevel)->second;
    }

    LogManager::LogManager()
    {
        // 创建日志文件夹
        folderPath = ReadSMTLogIni();
        if (0 != access(folderPath.c_str(), 0))
        {
            if (!mkdir(folderPath.c_str())) // 返回 0 表示创建成功，-1 表示失败
            {
            }
        }

        time_t now_time = time(NULL);
        tm *t_tm = localtime(&now_time);
        log_time = *t_tm; // 储存创建时间

        HardLogInit();
        SoftLogInit();
        OperateLogInit();
        ImageProcessLogInit();
        DatabaseLogInit();
        ErrorMessageLogInit();
        OptimizerInit();
        AlgorithmLogInit();
    }

    LogManager::~LogManager()
    {
        log4cpp::Category::shutdown();
    }

    LogManager &LogManager::GetInstance()
    {
        static LogManager logmanage;
        return logmanage;
    }

    // 硬件日志初始化
    void LogManager::HardLogInit()
    {
        // 读取配置文件获取硬件日志配置
        LogIni hardwareini;
        hardwareini.type = "HardwareLog";
        hardwareini.path = "\\HardWareLog";
        hardwareini.fileName = "HardwareLog.log";
        ReadLogIniFile(hardwareini);

        // 创建硬件日志文件夹
        string logPath = folderPath + hardwareini.path;
        if (0 != access(logPath.c_str(), 0))
        {
            if (!mkdir(logPath.c_str())) // 返回 0 表示创建成功，-1 表示失败
            {
            }
        }

        // 初始化日志记录级别为INFO级别
        HardLevelOP = hardwareini.priorityLevel;

        // 获取当前时间
        time_t now_time = time(NULL);
        tm *t_tm = localtime(&now_time);
        int y = t_tm->tm_year + 1900; // 获取年份
        int m = t_tm->tm_mon + 1;     // 获取当前月份
        int d = t_tm->tm_mday;        // 获得几号
        int h = t_tm->tm_hour;        // 获取当前为几时
        int mm = t_tm->tm_min;        // 获取分钟

        if (HardAppender && HardLayout)
        {
            HardwareLog.removeAppender(HardAppender);
            HardAppender = nullptr;
            HardLayout = nullptr;
            delete HardAppender;
        }

        // 日志文件记录格式为日期+级别+消息内容
        HardLayout = new log4cpp::PatternLayout();
        HardLayout->setConversionPattern("%d:[%p]-%m%n");

        logPath += "\\";
        if (hardwareini.timeName)
        {
            logPath += std::to_string((unsigned long long)(y)) + "-";
            logPath += std::to_string((unsigned long long)(m)) + "-";
            logPath += std::to_string((unsigned long long)(d)) + "-";
        }
        logPath += hardwareini.fileName;

        HardAppender = new log4cpp::RollingFileAppender(hardwareini.file, logPath, hardwareini.fileSize, hardwareini.fileNum);
        HardAppender->setLayout(HardLayout);

        HardwareLog.addAppender(HardAppender);
        HardwareLog.setPriority(HardLevelOP);
    }

    // 软件日志初始化
    void LogManager::SoftLogInit()
    {
        // 读取配置文件获取软件日志配置
        LogIni Softwareini;
        Softwareini.type = "SoftWareLog";
        Softwareini.path = "\\SoftWareLog";
        Softwareini.fileName = "SoftWareLog.log";

        ReadLogIniFile(Softwareini);

        // 创建软件日志文件夹
        string logPath = folderPath + Softwareini.path;
        if (0 != access(logPath.c_str(), 0))
        {
            if (!mkdir(logPath.c_str())) // 返回 0 表示创建成功，-1 表示失败
            {
            }
        }

        // 初始化日志记录级别为INFO级别
        SoftLevelOP = Softwareini.priorityLevel;

        // 获取当前时间
        time_t now_time = time(NULL);
        tm *t_tm = localtime(&now_time);
        int y = t_tm->tm_year + 1900; // 获取年份
        int m = t_tm->tm_mon + 1;     // 获取当前月份
        int d = t_tm->tm_mday;        // 获得几号
        int h = t_tm->tm_hour;        // 获取当前为几时
        int mm = t_tm->tm_min;        // 获取分钟

        if (SoftAppender && SoftLayout)
        {
            SoftwareLog.removeAppender(SoftAppender);
            SoftAppender = nullptr;
            SoftLayout = nullptr;
            delete SoftAppender;
        }

        // 日志文件记录格式为日期+级别+消息内容
        SoftLayout = new log4cpp::PatternLayout();
        SoftLayout->setConversionPattern("%d:[%p]-%m%n");

        logPath += "\\";
        if (Softwareini.timeName)
        {
            logPath += std::to_string((unsigned long long)(y)) + "-";
            logPath += std::to_string((unsigned long long)(m)) + "-";
            logPath += std::to_string((unsigned long long)(d)) + "-";
        }
        logPath += Softwareini.fileName;

        SoftAppender = new log4cpp::RollingFileAppender(Softwareini.file, logPath, Softwareini.fileSize, Softwareini.fileNum);
        SoftAppender->setLayout(SoftLayout);

        SoftwareLog.addAppender(SoftAppender);
        SoftwareLog.setPriority(SoftLevelOP);
    }

    // 操作日志初始化
    void LogManager::OperateLogInit()
    {
        // 读取配置文件获取软件日志配置
        LogIni Operatorini;
        Operatorini.type = "OperateLog";
        Operatorini.path = "\\OperateLog";
        Operatorini.fileName = "OperateLog.log";

        ReadLogIniFile(Operatorini);

        // 创建操作日志文件夹
        string logPath = folderPath + Operatorini.path;
        if (0 != access(logPath.c_str(), 0))
        {
            if (!mkdir(logPath.c_str())) // 返回 0 表示创建成功，-1 表示失败
            {
            }
        }

        // 初始化日志记录级别为INFO级别
        OperateLevelOP = Operatorini.priorityLevel;

        // 获取当前时间
        time_t now_time = time(NULL);
        tm *t_tm = localtime(&now_time);
        int y = t_tm->tm_year + 1900; // 获取年份
        int m = t_tm->tm_mon + 1;     // 获取当前月份
        int d = t_tm->tm_mday;        // 获得几号
        int h = t_tm->tm_hour;        // 获取当前为几时
        int mm = t_tm->tm_min;        // 获取分钟

        if (OperateAppender && OperateLayout)
        {
            OperateLog.removeAppender(OperateAppender);
            OperateAppender = nullptr;
            OperateLayout = nullptr;
            delete OperateAppender;
        }

        // 日志文件记录格式为日期+级别+消息内容
        OperateLayout = new log4cpp::PatternLayout();
        OperateLayout->setConversionPattern("%d:[%p]-%m%n");

        logPath += "\\";
        if (Operatorini.timeName)
        {
            logPath += "\\" + std::to_string((unsigned long long)(y)) + "-";
            logPath += std::to_string((unsigned long long)(m)) + "-";
            logPath += std::to_string((unsigned long long)(d)) + "-";
        }
        logPath += Operatorini.fileName;

        OperateAppender = new log4cpp::RollingFileAppender(Operatorini.file, logPath, Operatorini.fileSize, Operatorini.fileNum);
        OperateAppender->setLayout(OperateLayout);

        OperateLog.addAppender(OperateAppender);
        OperateLog.setPriority(OperateLevelOP);
    }

    // 图像接口日志初始化
    void LogManager::ImageProcessLogInit()
    {
        // 读取配置文件获取软件日志配置
        LogIni ImageProcessini;
        ImageProcessini.type = "ImageProcessLog";
        ImageProcessini.path = "\\ImageProcessLog";
        ImageProcessini.fileName = "ImageProcessLog.log";

        ReadLogIniFile(ImageProcessini);

        // 创建操作日志文件夹
        string logPath = folderPath + ImageProcessini.path;
        if (0 != access(logPath.c_str(), 0))
        {
            if (!mkdir(logPath.c_str())) // 返回 0 表示创建成功，-1 表示失败
            {
            }
        }

        // 初始化日志记录级别为INFO级别
        ImageProcessLevelOP = ImageProcessini.priorityLevel;

        // 获取当前时间
        time_t now_time = time(NULL);
        tm *t_tm = localtime(&now_time);
        int y = t_tm->tm_year + 1900; // 获取年份
        int m = t_tm->tm_mon + 1;     // 获取当前月份
        int d = t_tm->tm_mday;        // 获得几号
        int h = t_tm->tm_hour;        // 获取当前为几时
        int mm = t_tm->tm_min;        // 获取分钟

        if (ImageProcessAppender && ImageProcessLayout)
        {
            ImageProcessLog.removeAppender(ImageProcessAppender);
            ImageProcessAppender = nullptr;
            ImageProcessLayout = nullptr;
            delete ImageProcessAppender;
        }

        // 日志文件记录格式为日期+级别+消息内容
        ImageProcessLayout = new log4cpp::PatternLayout();
        ImageProcessLayout->setConversionPattern("%d:[%p]-%m%n");

        logPath += "\\";
        if (ImageProcessini.timeName)
        {
            logPath += "\\" + std::to_string((unsigned long long)(y)) + "-";
            logPath += std::to_string((unsigned long long)(m)) + "-";
            logPath += std::to_string((unsigned long long)(d)) + "-";
        }
        logPath += ImageProcessini.fileName;

        ImageProcessAppender = new log4cpp::RollingFileAppender(ImageProcessini.file, logPath, ImageProcessini.fileSize, ImageProcessini.fileNum);
        ImageProcessAppender->setLayout(ImageProcessLayout);

        ImageProcessLog.addAppender(ImageProcessAppender);
        ImageProcessLog.setPriority(ImageProcessLevelOP);
    }

    // 数据库日志初始化
    void LogManager::DatabaseLogInit()
    {
        // 读取配置文件获取软件日志配置
        LogIni Databaseini;
        Databaseini.type = "DatabaseLog";
        Databaseini.path = "\\DatabaseLog";
        Databaseini.fileName = "DatabaseLog.log";

        ReadLogIniFile(Databaseini);

        // 创建操作日志文件夹
        string logPath = folderPath + Databaseini.path;
        if (0 != access(logPath.c_str(), 0))
        {
            if (!mkdir(logPath.c_str())) // 返回 0 表示创建成功，-1 表示失败
            {
            }
        }

        // 初始化日志记录级别为INFO级别
        DatabaseLevelOP = Databaseini.priorityLevel;

        // 获取当前时间
        time_t now_time = time(NULL);
        tm *t_tm = localtime(&now_time);
        int y = t_tm->tm_year + 1900; // 获取年份
        int m = t_tm->tm_mon + 1;     // 获取当前月份
        int d = t_tm->tm_mday;        // 获得几号
        int h = t_tm->tm_hour;        // 获取当前为几时
        int mm = t_tm->tm_min;        // 获取分钟

        if (DatabaseAppender && DatabaseLayout)
        {
            DatabaseLog.removeAppender(DatabaseAppender);
            DatabaseAppender = nullptr;
            DatabaseLayout = nullptr;
            delete DatabaseAppender;
        }

        // 日志文件记录格式为日期+级别+消息内容
        DatabaseLayout = new log4cpp::PatternLayout();
        DatabaseLayout->setConversionPattern("%d:[%p]-%m%n");

        logPath += "\\";
        if (Databaseini.timeName)
        {
            logPath += "\\" + std::to_string((unsigned long long)(y)) + "-";
            logPath += std::to_string((unsigned long long)(m)) + "-";
            logPath += std::to_string((unsigned long long)(d)) + "-";
        }
        logPath += Databaseini.fileName;

        DatabaseAppender = new log4cpp::RollingFileAppender(Databaseini.file, logPath, Databaseini.fileSize, Databaseini.fileNum);
        DatabaseAppender->setLayout(DatabaseLayout);

        DatabaseLog.addAppender(DatabaseAppender);
        DatabaseLog.setPriority(DatabaseLevelOP);
    }

    void LogManager::ErrorMessageLogInit()
    {
        // 读取配置文件获取软件日志配置
        LogIni ErrorMessageini;
        ErrorMessageini.type = "ErrorMessageLog";
        ErrorMessageini.path = "\\ErrorMessageLog";
        ErrorMessageini.fileName = "ErrorMessageLog.log";

        ReadLogIniFile(ErrorMessageini);

        // 创建操作日志文件夹
        string logPath = folderPath + ErrorMessageini.path;
        if (0 != access(logPath.c_str(), 0))
        {
            if (!mkdir(logPath.c_str())) // 返回 0 表示创建成功，-1 表示失败
            {
            }
        }

        // 初始化日志记录级别为INFO级别
        ErrorMessageLevelOP = ErrorMessageini.priorityLevel;

        // 获取当前时间
        time_t now_time = time(NULL);
        tm *t_tm = localtime(&now_time);
        int y = t_tm->tm_year + 1900; // 获取年份
        int m = t_tm->tm_mon + 1;     // 获取当前月份
        int d = t_tm->tm_mday;        // 获得几号
        int h = t_tm->tm_hour;        // 获取当前为几时
        int mm = t_tm->tm_min;        // 获取分钟

        if (ErrorMessageAppender && ErrorMessageLayout)
        {
            ErrorMessageLog.removeAppender(ErrorMessageAppender);
            ErrorMessageAppender = nullptr;
            ErrorMessageLayout = nullptr;
            delete ErrorMessageAppender;
        }

        // 日志文件记录格式为日期+级别+消息内容
        ErrorMessageLayout = new log4cpp::PatternLayout();
        ErrorMessageLayout->setConversionPattern("%d:[%p]-%m%n");

        logPath += "\\";
        if (ErrorMessageini.timeName)
        {
            logPath += "\\" + std::to_string((unsigned long long)(y)) + "-";
            logPath += std::to_string((unsigned long long)(m)) + "-";
            logPath += std::to_string((unsigned long long)(d)) + "-";
        }
        logPath += ErrorMessageini.fileName;

        ErrorMessageAppender = new log4cpp::RollingFileAppender(ErrorMessageini.file, logPath, ErrorMessageini.fileSize, ErrorMessageini.fileNum);
        ErrorMessageAppender->setLayout(ErrorMessageLayout);

        ErrorMessageLog.addAppender(ErrorMessageAppender);
        ErrorMessageLog.setPriority(ErrorMessageLevelOP);
    }

    // 生产日志初始化
    void LogManager::OptimizerInit()
    {
        // 读取配置文件获取校正日志配置
        LogIni Softwareini;
        Softwareini.type = "OptimizerLog";
        Softwareini.path = "\\OptimizerLog";
        Softwareini.fileName = "OptimizerLog.log";

        ReadLogIniFile(Softwareini);

        // 创建校正日志文件夹
        string logPath = folderPath + Softwareini.path;
        if (0 != access(logPath.c_str(), 0))
        {
            if (!mkdir(logPath.c_str())) // 返回 0 表示创建成功，-1 表示失败
            {
            }
        }

        // 初始化日志记录级别为INFO级别
        OptimizerMessageLevelOP = Softwareini.priorityLevel;

        // 获取当前时间
        time_t now_time = time(NULL);
        tm *t_tm = localtime(&now_time);
        int y = t_tm->tm_year + 1900; // 获取年份
        int m = t_tm->tm_mon + 1;     // 获取当前月份
        int d = t_tm->tm_mday;        // 获得几号
        int h = t_tm->tm_hour;        // 获取当前为几时
        int mm = t_tm->tm_min;        // 获取分钟

        if (OptimizerMessageAppender && OptimizerMessageLayout)
        {
            OptimizerLog.removeAppender(OptimizerMessageAppender);
            OptimizerMessageAppender = nullptr;
            OptimizerMessageLayout = nullptr;
            delete OptimizerMessageAppender;
        }

        // 日志文件记录格式为日期+级别+消息内容
        OptimizerMessageLayout = new log4cpp::PatternLayout();
        OptimizerMessageLayout->setConversionPattern("%d:[%p]-%m%n");

        logPath += "\\";
        if (Softwareini.timeName)
        {
            logPath += std::to_string((unsigned long long)(y)) + "-";
            logPath += std::to_string((unsigned long long)(m)) + "-";
            logPath += std::to_string((unsigned long long)(d)) + "-";
        }
        logPath += Softwareini.fileName;

        OptimizerMessageAppender = new log4cpp::RollingFileAppender(Softwareini.file, logPath, Softwareini.fileSize, Softwareini.fileNum);
        OptimizerMessageAppender->setLayout(OptimizerMessageLayout);

        OptimizerLog.addAppender(OptimizerMessageAppender);
        OptimizerLog.setPriority(OptimizerMessageLevelOP);
    }

    // 图像算法日志初始化
    void LogManager::AlgorithmLogInit()
    {
        // 读取配置文件获取校正日志配置
        LogIni Softwareini;
        Softwareini.type = "AlgorithmLog";
        Softwareini.path = "\\AlgorithmLog";
        Softwareini.fileName = "AlgorithmLog.log";

        ReadLogIniFile(Softwareini);

        // 创建校正日志文件夹
        string logPath = folderPath + Softwareini.path;
        if (0 != access(logPath.c_str(), 0))
        {
            if (!mkdir(logPath.c_str())) // 返回 0 表示创建成功，-1 表示失败
            {
            }
        }

        // 初始化日志记录级别为INFO级别
        ImageAlgorithmLevelOP = Softwareini.priorityLevel;

        // 获取当前时间
        time_t now_time = time(NULL);
        tm* t_tm = localtime(&now_time);
        int y = t_tm->tm_year + 1900; // 获取年份
        int m = t_tm->tm_mon + 1;     // 获取当前月份
        int d = t_tm->tm_mday;        // 获得几号
        int h = t_tm->tm_hour;        // 获取当前为几时
        int mm = t_tm->tm_min;        // 获取分钟

        if (ImageAlgorithmAppender && ImageAlgorithmLayout)
        {
            AlgorithmLog.removeAppender(ImageAlgorithmAppender);
            ImageAlgorithmAppender = nullptr;
            ImageAlgorithmLayout = nullptr;
            delete ImageAlgorithmAppender;
        }

        // 日志文件记录格式为日期+级别+消息内容
        ImageAlgorithmLayout = new log4cpp::PatternLayout();
        ImageAlgorithmLayout->setConversionPattern("%d:[%p]-%m%n");

        logPath += "\\";
        if (Softwareini.timeName)
        {
            logPath += std::to_string((unsigned long long)(y)) + "-";
            logPath += std::to_string((unsigned long long)(m)) + "-";
            logPath += std::to_string((unsigned long long)(d)) + "-";
        }
        logPath += Softwareini.fileName;

        ImageAlgorithmAppender = new log4cpp::RollingFileAppender(Softwareini.file, logPath, Softwareini.fileSize, Softwareini.fileNum);
        ImageAlgorithmAppender->setLayout(ImageAlgorithmLayout);

        AlgorithmLog.addAppender(ImageAlgorithmAppender);
        AlgorithmLog.setPriority(ImageAlgorithmLevelOP);
    }


    tm LogManager::CurLogTime()
    {
        return log_time;
    }

    void LogManager::UpdateLogfile(LogType log_type)
    {
        time_t now_time = time(NULL);
        tm *t_tm = localtime(&now_time);
        int y = t_tm->tm_year; // 获取年份
        int m = t_tm->tm_mon;  // 获取当前月份
        int d = t_tm->tm_mday; // 获得日期

        int log_y = log_time.tm_year; // 获取日志年份
        int log_m = log_time.tm_mon;  // 获取日志当前月份
        int log_d = log_time.tm_mday; // 获得日志日期
        log_time = *t_tm;             // 储存创建时间
        t_tm = nullptr;
        delete t_tm;
        if (log_y != y || log_m != m || log_d != d)
        {
            HardLogInit();
            SoftLogInit();
            OperateLogInit();
            ImageProcessLogInit();
            DatabaseLogInit();
            ErrorMessageLogInit();
            AlgorithmLogInit();
        }
    }

    void LogManager::WriteMessage(string message_str, LogLevel log_level, LogType log_type)
    {
        LogMutex.lock();

        UpdateLogfile(log_type); // 更新日志文件

        switch (log_type)
        {
        case LogType::LOG_HARDWARE:
            HardwareLog.log((log4cpp::Priority::PriorityLevel)log_level, message_str);
            break;
        case LogType::LOG_SOFTWARE:
            SoftwareLog.log((log4cpp::Priority::PriorityLevel)log_level, message_str);
            break;
        case LogType::LOG_OPERATE:
            OperateLog.log((log4cpp::Priority::PriorityLevel)log_level, message_str);
            break;
        case LogType::LOG_IMAGE:
            ImageProcessLog.log((log4cpp::Priority::PriorityLevel)log_level, message_str);
            break;
        case LogType::LOG_Database:
            DatabaseLog.log((log4cpp::Priority::PriorityLevel)log_level, message_str);
            break;
        case LogType::LOG_ERRORMESSAGE:
            ErrorMessageLog.log((log4cpp::Priority::PriorityLevel)log_level, message_str);
            break;
        case LogType::LOG_Optimizer:
            OptimizerLog.log((log4cpp::Priority::PriorityLevel)log_level, message_str);
            break;
        case LogType::LOG_ALGORITHM:
            AlgorithmLog.log((log4cpp::Priority::PriorityLevel)log_level, message_str);
            break;
        default:
            break;
        }
        LogMutex.unlock();
    }

    // 输出硬件日志
    void WriteHardLog(string message_str, LogLevel log_level)
    {
        LogManager::GetInstance().WriteMessage(message_str, log_level, LogType::LOG_HARDWARE);
    }

    // 输出软件日志
    void WriteSoftLog(string message_str, LogLevel log_level)
    {
        LogManager::GetInstance().WriteMessage(message_str, log_level, LogType::LOG_SOFTWARE);
    }

    // 输出操作日志
    void WriteOperateLog(string message_str, LogLevel log_level)
    {
        LogManager::GetInstance().WriteMessage(message_str, log_level, LogType::LOG_OPERATE);
    }

    // 输出图像接口日志
    std::string FuncSplit(std::string func_name, std::string pattern)
    {
        std::string funcname_;
        if (func_name.find(pattern) != string::npos)
        {
            std::vector<std::string> result = split(func_name, pattern);
            int i = result.size();
            funcname_ = result[i - 2] + "::" + result[i - 1];
        }
        else
        {
            funcname_ = func_name;
        }
        return funcname_;
    }
    void WriteImageProcessLog(string message_str, LogLevel log_level)
    {
        LogManager::GetInstance().WriteMessage(message_str, log_level, LogType::LOG_IMAGE);
    }
    void WriteImageProcessLog(const char *funcname, const unsigned long line, std::string filename, int flag)
    {
        if (flag == 1)
        { // 代表进入函数
            std::string funcname_ = FuncSplit(funcname, "::");
            // string转化char*
            char *file = filename.data();
            filename = logfilename(file);
            std::string str = "Enter " + funcname_ + ", " + filename + ": " + to_string(line);
            LogManager::GetInstance().WriteMessage(str, LogLevel::INFO, LogType::LOG_IMAGE);
        }
        else if (flag == 0)
        { // 代表正常离开函数
            std::string funcname_ = FuncSplit(funcname, "::");
            // string转化char*
            char *file = filename.data();
            filename = logfilename(file);
            std::string str = "Exit " + funcname_ + "Success, " + filename + ": " + to_string(line);
            LogManager::GetInstance().WriteMessage(str, LogLevel::INFO, LogType::LOG_IMAGE);
        }
        else if (flag == 2)
        { // 分割两个最外层接口，输出一个空行
            std::string str = "";
            LogManager::GetInstance().WriteMessage(str, LogLevel::INFO, LogType::LOG_IMAGE);
        }
    }
    void WriteImageProcessMessageLog(const char *funcname, string message, const unsigned long line, std::string filename)
    {
        // 输出INFO信息
        std::string message_str;
        std::string funcname_ = FuncSplit(funcname, "::");
        message_str = funcname_ + ", [" + message + "]";
        // string转化char*
        char *file = filename.data();
        filename = logfilename(file);
        std::string str = message_str + ", " + filename + ": " + to_string(line);
        LogManager::GetInstance().WriteMessage(str, LogLevel::INFO, LogType::LOG_IMAGE);
    }
    void WriteImageProcessErrorLog(const char *funcname, std::string Exp, const unsigned long line, std::string filename)
    {
        // 输出错误日志，没有错误码
        std::string message_str;
        std::string funcname_ = FuncSplit(funcname, "::");

        char ercode[20];
        message_str = "Exit " + funcname_ + " [" + Exp + "]";
        // string转化char*
        char *file = filename.data();
        filename = logfilename(file);
        std::string str = message_str + ", " + filename + ": " + to_string(line);
        LogManager::GetInstance().WriteMessage(str, LogLevel::ERROR, LogType::LOG_IMAGE);
    }
    void WriteImageProcessErrorLog(const char* funcname, std::string Exp, unsigned int error_code, const unsigned long line, std::string filename)
    {
		std::string message_str;
		std::string funcname_ = FuncSplit(funcname, "::");
		char ercode[20];
		sprintf(ercode, "%02x", error_code);
		message_str = "Exit " + funcname_ + " ErrorCode:[" + std::string(ercode) + "], " + "[" + Exp + "]";
		//string转化char*
		char* file = filename.data();
		filename = logfilename(file);
		std::string str = message_str + ", " + filename + ": " + to_string(line);
        LogManager::GetInstance().WriteMessage(str, LogLevel::ERROR, LogType::LOG_IMAGE);
    }

    void WriteDatabaseLog(string message_str, LogLevel log_level)
    {
        LogManager::GetInstance().WriteMessage(message_str, log_level, LogType::LOG_Database);
    }
    // 输出消息栏消息日志
    void WriteErrorMessageLog(string message_str, LogLevel log_level)
    {
        LogManager::GetInstance().WriteMessage(message_str, log_level, LogType::LOG_ERRORMESSAGE);
    }

    // 输出优化日志
    void WriteOptimizerLog(string message_str, LogLevel log_level)
    {
        LogManager::GetInstance().WriteMessage(message_str, log_level, LogType::LOG_Optimizer);
    }

    // 输出图像算法日志
    void WriteImageAlgorithmLog(const char* funcname, const unsigned long line, std::string filename, int flag)
    {
        if (flag == 1)
        { // 代表进入函数
            std::string funcname_ = FuncSplit(funcname, "::");
            // string转化char*
            char* file = filename.data();
            filename = logfilename(file);
            std::string str = "Enter " + funcname_ + ", " + filename + ": " + to_string(line);
            LogManager::GetInstance().WriteMessage(str, LogLevel::INFO, LogType::LOG_ALGORITHM);
        }
        else if (flag == 0)
        { // 代表正常离开函数
            std::string funcname_ = FuncSplit(funcname, "::");
            // string转化char*
            char* file = filename.data();
            filename = logfilename(file);
            std::string str = "Exit " + funcname_ + "Success, " + filename + ": " + to_string(line);
            LogManager::GetInstance().WriteMessage(str, LogLevel::INFO, LogType::LOG_ALGORITHM);
        }
        else if (flag == 2)
        { // 分割两个最外层接口，输出一个空行
            std::string str = "";
            LogManager::GetInstance().WriteMessage(str, LogLevel::INFO, LogType::LOG_ALGORITHM);
        }
    }
    void WriteImageAlgorithmMessageLog(const char* funcname, std::string message, const unsigned long line, std::string filename)
    {
        // 输出INFO信息
        std::string message_str;
        std::string funcname_ = FuncSplit(funcname, "::");
        message_str = funcname_ + ", [" + message + "]";
        // string转化char*
        char* file = filename.data();
        filename = logfilename(file);
        std::string str = message_str + ", " + filename + ": " + to_string(line);
        LogManager::GetInstance().WriteMessage(str, LogLevel::INFO, LogType::LOG_ALGORITHM);
    }
    void WriteImageAlgorithmErrorLog(const char* funcname, std::string Exp, const unsigned long line, std::string filename)
    {
        // 输出错误日志，没有错误码
        std::string message_str;
        std::string funcname_ = FuncSplit(funcname, "::");

        char ercode[20];
        message_str = "Exit " + funcname_ + " [" + Exp + "]";
        // string转化char*
        char* file = filename.data();
        filename = logfilename(file);
        std::string str = message_str + ", " + filename + ": " + to_string(line);
        LogManager::GetInstance().WriteMessage(str, LogLevel::ERROR, LogType::LOG_ALGORITHM);
    }
    void WriteImageAlgorithmErrorLog(const char* funcname, std::string Exp, unsigned int error_code, const unsigned long line, std::string filename)
    {
        std::string message_str;
        std::string funcname_ = FuncSplit(funcname, "::");
        char ercode[20];
        sprintf(ercode, "%02x", error_code);
        message_str = "Exit " + funcname_ + " ErrorCode:[" + std::string(ercode) + "], " + "[" + Exp + "]";
        //string转化char*
        char* file = filename.data();
        filename = logfilename(file);
        std::string str = message_str + ", " + filename + ": " + to_string(line);
        LogManager::GetInstance().WriteMessage(str, LogLevel::ERROR, LogType::LOG_ALGORITHM);
    }

    OperateLogfunc &OperateLogfunc::GetInstance()
    {
        static OperateLogfunc instance;
        return instance;
    }

    // INFO等级 按钮点击记录   控件名 , __LINE__
    void OperateLogfunc::InfoClickRecord(string message_infor, const unsigned long line)
    {
        string message_str = " Click[" + message_infor + "]";
        message_str += "  Rows:" + to_string(line);
        WriteOperateLog(message_str, LogLevel::INFO);
    }

    void OperateLogfunc::InfoPhysicalKeyRecord(string message_infor, const unsigned long line)
    {
        string message_str = "[" + message_infor + "]";
        message_str += "  Rows:" + to_string(line);

        WriteOperateLog(message_str, LogLevel::INFO);
    }

    // DEBUGD等级 按扭点击记录
    void OperateLogfunc::DebugRecord(string message_infor, string function_name)
    {
        string parameter = message_infor.substr(message_infor.find(function_name) + function_name.size());
        string message_str = "[";
        message_str += message_infor.substr(0, message_infor.find(function_name));
        message_str +="]";
        message_str += "Clicked";
        message_str += function_name;
        message_str += "{";
        message_str += parameter;
        message_str +="}";
        WriteOperateLog(message_str, LogLevel::DEBUG);
    }

    // 窗口打开记录  打开了什么窗口中的什么窗口
    void OperateLogfunc::windowsOpenRecord(std::string message_infor, std::string function_name)
    {
        string message_str;
        message_str  = "Open " + message_infor;
        message_str += " window ";
		message_str += "[" + function_name + "]";
		WriteOperateLog(message_str, LogLevel::INFO);
    }

    // 窗口关闭记录
    void OperateLogfunc::windowsCloseRecord(string message_infor, string function_name)
    {
        string message_str;
        message_str = "Close " + message_infor;
        message_str += " in window ";
		message_str += "[" + function_name + "]";
		WriteOperateLog(message_str, LogLevel::INFO);
    }

    // INFO等级 下拉框选择记录  //控件名  当前文本  __LINE__
    void OperateLogfunc::InfoComRecord(string message_infor, string function_name, const unsigned long line)
    {
        string message_str = "[" + message_infor + "] drop-down box";
        message_str += "choose  " + function_name + ";  Rows:" + to_string(line);
        WriteOperateLog(message_str, LogLevel::INFO);
    }

    // DEBUG等级 下拉框选择记录
    void OperateLogfunc::DebugComRecord(string message_infor, string function_name)
    {
        string message_str = "[" + message_infor.substr(0, message_infor.find(function_name));
        message_str += "::" + function_name + "]";
        string parameter = message_infor.substr(message_infor.find(function_name) + function_name.size());
        message_str += "ComboBOX Change";
        message_str += "{" + parameter + "}";
        WriteOperateLog(message_str, LogLevel::DEBUG);
    }

    // INFO等级 列表修改记录
    void OperateLogfunc::InfoListChangeRecord(string message_infor, const unsigned long line)
    {
        string message_str = "[" + message_infor + " list change]  Rows:" + to_string(line);

        WriteOperateLog(message_str, LogLevel::INFO);
    }

    // DEBUG等级 列表修改记录
    void OperateLogfunc::DEBUGListChangeRecord(string message_infor, string function_name)
    {
        string message_str = "[" + message_infor.substr(0, message_infor.find(function_name)) + "]";
        message_str += "List Change ";
        string parameter = message_infor.substr(message_infor.find(function_name) + function_name.size());
        message_str += parameter.substr(0, parameter.find(""));
        message_str += "{" + parameter.substr(parameter.find("")) + "}";

        WriteOperateLog(message_str, LogLevel::DEBUG);
    }

    // INFO等级 数据修改
    void OperateLogfunc::InfoDataChangeRecord(string message_infor, double num, const unsigned long line)
    {
        // string message_str = "[" + message_infor.substr(0, message_infor.find(function_name));
        // message_str += "::" + function_name + "]";
        // message_str += "Data Change";
        string message_str = message_infor + " data changes to " + to_string(num) + "  Rows:" + to_string(line);
        WriteOperateLog(message_str, LogLevel::INFO);
    }

    void OperateLogfunc::InfoDataChangeRecord(string message_infor, string str, const unsigned long line)
    {
        string message_str = message_infor + " data changes to" + str + "  Rows:" + to_string(line);
        WriteOperateLog(message_str, LogLevel::INFO);
    }

    // DEBUG等级 数据修改
    void OperateLogfunc::DEBUGDataChangeRecord(string message_infor, string function_name)
    {
        string message_str = "[" + message_infor.substr(0, message_infor.find(function_name));
        message_str += "::" + function_name + "]";
        message_str += "Data Change";
        string parameter = message_infor.substr(message_infor.find(function_name) + function_name.size());
        message_str += "{" + parameter + "}";
        WriteOperateLog(message_str, LogLevel::INFO);
    }

    // INFO 表格改变
    void OperateLogfunc::InfoTableChangeRecord(string tablename, string message_infor, int x, string y_value, const unsigned long line)
    {
        string message_str;
        message_str = "[";
        message_str += tablename;
        message_str += "]data table ";
        message_str += "Rows:  ";
        message_str += to_string(x);
        message_str += "Cols: ";
        message_str += y_value;
        message_str += " changes to ";
        message_str += message_infor;
        message_str += " Rows:";
        message_str += to_string(line);

        WriteOperateLog(message_str, LogLevel::INFO);
    }

    void OperateLogfunc::InfoCheckRrcord(string message_infor, const unsigned char value, const unsigned long line)
    {
        string message_str;
        if (value == 0)
        {
            message_str = "Unchecked [" + message_infor + "] " + "  Rows:" + to_string(line);
        }
        else
        {
            message_str = "Ticked[" + message_infor + "]   Rows:" + to_string(line);
        }
        WriteOperateLog(message_str, LogLevel::INFO);
    }

    void OperateLogfunc::InfoHotkeyRecord(string key, string message_infor, const unsigned long line)
    {
        string message_str;
        message_str = "使用了【 " + key + " 】快捷键, " + message_infor + "  rows:" + to_string(line);
        WriteOperateLog(message_str, LogLevel::INFO);
    }

    SoftwareLogfunc &SoftwareLogfunc::GetInstance()
    {
        static SoftwareLogfunc instance;
        return instance;
    }

    void SoftwareLogfunc::TipRecord(string moduletype, string message_info, const unsigned long line)
    {
        string message_str = "[" + moduletype + "] :" + message_info + " rows:" + to_string(line);
        WriteSoftLog(message_str, LogLevel::NOTICE);
    }

    void SoftwareLogfunc::EnterFunction(string funcName, string fileName, const unsigned long line)
    {
        if (funcName.find(".cpp") != funcName.npos)
        {
            string temp = funcName;
            funcName = fileName;
            fileName = temp;
        }
        if (fileName.find_last_of("\\") != fileName.npos)
        {
            fileName = fileName.substr(fileName.find_last_of("\\") + 1, fileName.size());
        }
        string message_str;
        message_str = "[Enter the function]";
        message_str += funcName;
        message_str += "(";
        message_str += fileName;
        message_str +=")  rows: ";
        message_str += to_string(line);
        WriteSoftLog(message_str, LogLevel::INFO);
    }

    void SoftwareLogfunc::LeaveFunction(string funcName, string fileName, const unsigned long line)
    {
        if (funcName.find(".cpp") != funcName.npos)
        {
            string temp = funcName;
            funcName = fileName;
            fileName = temp;
        }
        if (fileName.find_last_of("\\") != fileName.npos)
        {
            fileName = fileName.substr(fileName.find_last_of("\\") + 1, fileName.size());
        }
        string message_str = "[Leave the function]";
        message_str += funcName;
        message_str += "( ";
        message_str += fileName;
        message_str +=") rows: ";
        message_str += to_string(line);
        WriteSoftLog(message_str, LogLevel::INFO);
    }

    void SoftwareLogfunc::DatabaseRecord(string basename, string tablename, string operate, const unsigned long line)
    {
        string message_str = "[" + basename + " database]  " + tablename + " table " + operate + "  rows: " + to_string(line);
        WriteSoftLog(message_str, LogLevel::INFO);
    }

    void SoftwareLogfunc::ErrorRecord(string partname, string err, const unsigned long line)
    {
        string message_str = "[" + partname + "]" + err + "  Rows: " + to_string(line);
        WriteSoftLog(message_str, LogLevel::ERROR);
    }

    void SoftwareLogfunc::DatabaseWarn(string basename, string tablename, string warn_str, const unsigned long line)
    {
        string message_str = "[" + basename + " database] " + tablename + " table  error:" + warn_str + "  rows: " + to_string(line);
        WriteSoftLog(message_str, LogLevel::WARN);
    }

    // 对话框回调函数使用
    void SoftwareLogfunc::UiCallbackRecord(std::string info)
    {
        WriteSoftLog(info, LogLevel::INFO);
    }

    // 数据库
    DatabaseLogfunc &DatabaseLogfunc::GetInstance()
    {
        static DatabaseLogfunc instance;
        return instance;
    }

    ErrorMessageLogfunc &ErrorMessageLogfunc::GetInstance()
    {
        static ErrorMessageLogfunc instance;
        return instance;
    }

    // 消息栏消息
    void ErrorMessageLogfunc::ErrorMessageRecord(string message_info)
    {
        WriteErrorMessageLog(message_info, LogLevel::ERROR);
    }

    void DatabaseLogfunc::EnterFunction(string funcName, string fileName, const unsigned long line)
    {
        if (funcName.find(".cpp") != funcName.npos)
        {
            string temp = funcName;
            funcName = fileName;
            fileName = temp;
        }
        string message_str;
        message_str = "[Enter the function]";
        message_str += funcName;
        message_str += "(";
        message_str += fileName;
        message_str += ") rows: ";
        message_str += to_string(line);
        WriteDatabaseLog(message_str, LogLevel::INFO);
    }

    void DatabaseLogfunc::LeaveFunction(string funcName, string fileName, const unsigned long line)
    {
        if (funcName.find(".cpp") != funcName.npos)
        {
            string temp = funcName;
            funcName = fileName;
            fileName = temp;
        }
        string message_str;
        message_str = "[Leave the function]";
        message_str += funcName;
        message_str += "( ";
        message_str += fileName;
        message_str += ") rows: ";
        message_str += to_string(line);
        WriteDatabaseLog(message_str, LogLevel::INFO);
    }

    void DatabaseLogfunc::databaseRecord(string message_info)
    {
        WriteDatabaseLog(message_info, LogLevel::INFO);
    }

    // 十进制转换十六进制
    string DecIntToHexStr(long long num)
    {
        string str;
        long long Temp = num / 16;
        int left = num % 16;
        if (Temp > 0)
            str += DecIntToHexStr(Temp);
        if (left < 10)
            str += (left + '0');
        else
            str += ('A' + left - 10);
        return str;
    }

    // 十进制转换十六进制
    string DecStrToHexStr(string str)
    {
        long long Dec = 0;
        for (int i = 0; i < str.size(); ++i)
            Dec = Dec * 10 + str[i] - '0'; // 得到相应的整数：ASCII码中：字符0的码值是48；
        return DecIntToHexStr(Dec);
    }

    std::vector<std::string> split(std::string str, std::string pattern)
    {
        std::string::size_type pos;
        std::vector<std::string> result;
        str += pattern; // 扩展字符串以方便操作
        int size = str.size();
        for (int i = 0; i < size; i++)
        {
            pos = str.find(pattern, i);
            if (pos < size)
            {
                std::string s = str.substr(i, pos - i);
                result.push_back(s);
                i = pos + pattern.size() - 1;
            }
        }
        return result;
    }
}