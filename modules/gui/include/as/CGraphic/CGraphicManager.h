#pragma once
#include "as/CGraphic/CGraphic.hpp"
#include <QObject>
#include <QGraphicsObject>
 
namespace as
{
	class CGraphicManager :public QObject
	{
		//单例
		Q_OBJECT
	public:
		CGraphicManager();
		~CGraphicManager();

		struct PadCGraphic
		{
			CGraphic* m_PadObject;
			DWORD m_Pad_id;
			~PadCGraphic();
			PadCGraphic() = default;//默认构造
			PadCGraphic(DWORD pad_id, CGraphic* padObject) : m_PadObject(padObject), m_Pad_id(pad_id) {};
		};

		struct CADCGraphic
		{
			CGraphic* m_CADObject = nullptr;//当前元件所有框
			int m_block_id = -1;//当前元件所在当前块索引
			int m_array_id = -1;//当前元件所在当前拼索引
			int m_compo_id = -1;//当前元件在所有元件中索引
			//double m_angle = 0; //当前元件角度
			~CADCGraphic();
			CADCGraphic() = default;//默认构造
			CADCGraphic(int block_id, int array_id, int compo_id, CGraphic* cgObjectPtr) :
				m_block_id(block_id),
				m_array_id(array_id),
				m_compo_id(compo_id),
				m_CADObject(cgObjectPtr) {};

		};

		//添加焊盘
		void AddPad(shared_ptr<as::ImportPadData> padData, long padID);
		//获取所有item
		vector<PadCGraphic*> GetPadAllItems();

		CGraphic* GetPadItem(int index);

		void DeletePad(int id);
		//添加CAD位置
		void AddCAD(as::Point CADPos, int block_id, int array_id, int compo_id);
		//删除某个CAD的Graphic, 需要块|板|元件索引
		void DeleteCAD(int block_id, int array_id, int compo_id);
		//外部调用:通过块、拼、元件索引返回元件图元
		CGraphic* GetCADitem(int block_id, int array_id, int compo_id);
		// 获取当前视图所有CAD数据
		vector<CGraphicManager::CADCGraphic*> GetAllCADItems() const;
		// 获取当前视图所有CAD的Items
		vector<CGraphic*> GetAllCADCGraphic() const;


		// 图元管理类
		static CGraphicManager& GetInstance()
		{
			static CGraphicManager m_CGraphicManager;
			return m_CGraphicManager;
		}
	private:
		vector<PadCGraphic*> m_Pad_AllItems;
		vector<CADCGraphic*> m_CAD_AllItems;
	};
}