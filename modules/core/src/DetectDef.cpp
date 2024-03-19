#include "as/core/DetectDef.hpp"

namespace as
{
    std::string ErrorLevel2Name(ERROR_LEVEL _level)
	{
		std::string name = "";
		switch (_level)
		{
		case ERROR_LEVEL::NG:
		{
			name = "NG";
		}
		break;
		case ERROR_LEVEL::OK:
		{
			name = "OK";
		}
		break;
		case ERROR_LEVEL::WARNING:
		{
			name = "WARNING";
		}
		break;
		default:
			break;
		}
		return name;
	};
} // namespace as
