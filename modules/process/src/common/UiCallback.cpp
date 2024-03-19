#include "as/Common/UiCallback.h"


namespace as
{
	UiCallback& UiCallback::GetInstance()
	{
		static UiCallback instance;
		return instance;
	}

	void UiCallback::SetUiCallback(std::function<int(WidgetType widget_type, std::string info, int key_amount, bool diff_thread, bool isSplit)> func)
	{
		callback_func = func;
	}

	int UiCallback::GetUiCallback(WidgetType widget_type, std::string info, int key_amount, bool diff_thread, bool isSplit) {
		std::string log_info;
		if (widget_type == WidgetType::Error)
		{
			log_info = "[����Ի���]  " + info;
		}
		else if (widget_type == WidgetType::Warning)
		{
			log_info = "[����Ի���]  " + info;
		}
		else if (widget_type == WidgetType::Tip)
		{
			log_info = "[��ʾ�Ի���]  " + info;
		}
		else if (widget_type == WidgetType::Question)
		{
			log_info = "[ѯ�ʶԻ���]  " + info;
		}
		return callback_func(widget_type, info, key_amount, diff_thread, isSplit);
	}

	/***********Ԫ��ģ�����Ự��Ԫ�����ʹ���********/
	//�����㷨���������
	/*void UiCallback::SendSaveCompData(bool save_type, string ng_id)
	{
		m_SetSaveCompDataFunc(save_type, ng_id);
	}*/

	/*****Ԫ��ģ�����Ự��Ԫ�����ͻص�**************/
	//�����㷨�����������Ӧ
	/*void UiCallback::SetSaveCompDataFunc(std::function<void(bool save_type, string ng_id)> func)
	{
		m_SetSaveCompDataFunc = func;
	}*/

}