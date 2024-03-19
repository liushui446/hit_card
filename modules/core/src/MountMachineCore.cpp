#include "as/MountMachineCore.hpp"

namespace as
{
	MountMachine::MountMachine()
	{
	}

	MachineHead& MountMachine::GetMachineHead()
	{
		return m_cMachineHead;
	}

	ConveyorPara& MountMachine::GetConveyorPara()
	{
		return m_cConveyorPara;
	}
}