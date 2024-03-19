﻿#include "as/ASContext.hpp"

namespace as
{
	ASContext::ASContext()
	{
		m_baseboard = make_shared<BaseBoard>();
		m_mountmachine = make_shared<MountMachine>();
		m_cad_detection_data = make_shared<CADDetectionData>();
		m_componentData = make_shared<ComponentData>();
		m_padDataset = make_shared<PadDataSet>();
	}

	ASContext& ASContext::GetInstance()
	{
		static ASContext as_context;
		return as_context;
	}

	shared_ptr<BaseBoard> ASContext::GetBaseBoard()
	{
		return m_baseboard;
	}

	shared_ptr<MountMachine> ASContext::GetMountMachine()
	{
		return m_mountmachine;
	}

	shared_ptr<CADDetectionData> ASContext::GetCADDetectionData()
	{
		return m_cad_detection_data;
	}

	shared_ptr<ComponentData> ASContext::GetComponentData()
	{
		return m_componentData;
	}

	shared_ptr<PadDataSet> ASContext::GetPadDataSet()
	{
		return m_padDataset;
	}
}