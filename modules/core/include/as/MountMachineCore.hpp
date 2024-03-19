#ifndef AS_MOUNTMACHINECORE_HPP
#define AS_MOUNTMACHINECORE_HPP

#include "as/CommonCore.hpp"
#include "as/MachineHeadCore.hpp"
#include "as/ConveyorParaCore.hpp"

namespace as
{
	class MountMachine;
}

namespace boost
{
	namespace serialization
	{
		template <class Archive>
		void serialize(Archive& ar, as::MountMachine& val, const unsigned int version);
	}
}

namespace as
{
	//����
	class AS_EXPORTS MountMachine
	{
	public:
		MountMachine();
		template <class Archive>
		friend void boost::serialization::serialize(Archive& ar, MountMachine& val, const unsigned int version);

		MachineHead& GetMachineHead();		
		ConveyorPara& GetConveyorPara();	
	private:
		MachineHead m_cMachineHead;		//��ͷ
		ConveyorPara m_cConveyorPara;	//���ʹ�
	};
}
#endif // DEBUG
