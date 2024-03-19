#ifndef AS_PADCORE_HPP
#define AS_PADCORE_HPP
#include "as/CommonCore.hpp"
#include "as/CADCore.hpp"
#include "as/ApertureDef.hpp"
#include "as/SPIAlgorithmParam.hpp"

namespace as
{
	class PadGroupManager;
	class PadDataSet;
	class DetectionPadData;
	class PadGroupManager;
	enum class PadShape;
}

namespace as
{
	//焊盘自定义分组
	class AS_EXPORTS PadCustomizeGroup
	{
	public:
		PadCustomizeGroup();
		PadCustomizeGroup& operator=(PadCustomizeGroup& ref);
		string m_CustomizeGroupName;   //自定义分组别名
		vector<DWORD> m_vPadNameSet;  //焊盘名称集合
	};

	//焊盘形状分组
	class AS_EXPORTS PadShapeGroup
	{
	public:
		PadShapeGroup();
		PadShapeGroup& operator=(PadShapeGroup& ref);
		PadShape m_padshape;     //焊盘形状
		vector<DWORD> m_vPadNameSet;  //焊盘名称集合
	};

	//元件编号分组
	class AS_EXPORTS PartNumberGroup
	{
	public:
		PartNumberGroup();
		PartNumberGroup& operator=(PartNumberGroup& ref);
		string Ref;
		vector<DWORD> m_vPadNameSet;  //焊盘名称集合
	};


	//Gerber光圈定义
	struct ApertureDefinate
	{
		int m_id;			
		string D_Code;      //码号
		PadShape m_shape;   //光圈形状
		double m_dLength;   //长
		double m_dWidth;	//宽
		double m_dArea;		//面积
	};

	/* 类名：PadGroupManager
	* 创建日期： 2023/10/13
	* By ypk
	*	@file	PadCore.hpp
	*	@brief	焊盘分组管理类
	*	@version 1.0
	*/
	class AS_EXPORTS PadGroupManager
	{
	public:
		//焊盘特定分组
		struct PadSpecialGroup
		{
		};

		//焊盘属元件封装类型分组
		struct PadPackageGroup
		{
		};

	public:
		PadGroupManager();
		PadGroupManager& operator=(PadGroupManager& ref);
		map<PadShape, PadShapeGroup>& GetAllPadShapeGroup();
		map<string, PadCustomizeGroup>& GetAllCustomizeGroup();
		map<string, PartNumberGroup>& GetAllPartNumberGroup();

		//============自定义分组管理================//
		//新建分组
		void InsertCustomizeGroup(string groupname, PadCustomizeGroup custgroup);
		//自定义分组全部清空
		void ClearAllCustomizeGroup();
		//删除单个自定义组
		void ClearSingleCustomizeGroup(string groupname);

		//============元件编号分组管理================//
		//新建元件组
		void InsertPartGroup(string groupname, vector<DWORD> parts);
		bool FindSinglePartGroup(string groupname);
		void ClearAllPartGroup();
		void ClearSinglePartGroup(string groupname);
	private:
		map<PadShape, PadShapeGroup> m_pPadShapeGroupMger;          //形状分组管理
		map<string, PadCustomizeGroup> m_pPadCustomizeGroupMger;	//自定义分组管理
		map<string, PartNumberGroup> m_pPartNumberGroupMger;        //元件编号分组管理
	};

	/*
	* 类名：DetectionPadData
	* 创建日期： 2023/10/13
	* By ypk
	*	@file	PadCore.hpp
	*	@brief	焊盘参数类
	*	@version 1.0
	*/
	class AS_EXPORTS DetectionPadData :public DetectionDataBase
	{
	public:
		DetectionPadData();
		DetectionPadData& operator=(DetectionPadData& ref);

		//焊盘分组标识
		struct Groupflag
		{
			bool m_FlagofPadCustomizeGroup;
			bool m_FlagofPadShapeGroup; 
			Groupflag()
			{
				m_FlagofPadCustomizeGroup = false;
				m_FlagofPadShapeGroup = false;
			}
		};
		void SetPadName(int padid);
		int GetPadName();

		void SetPadArea(double area);
		double GetPadArea();

		void SetPadThickness(double thickness);
		double GetPadThickness();

		void SetPadRoiPos(Point roi_pos);
		Point GetPadRoiPos();

		double GetOutDiameter();
		void SetOutDiameter(double val);

		double GetInDiameter();
		void SetInDiameter(double val);

		PadShape GetPadShape();
		void SetPadShape(PadShape shape);

		SPIAlgorithmParamPtr GetSpiAlgorithmParam();
		void SetSpiAlgorithmParam(SPIAlgorithmParamPtr algoparam);

	private:
		int m_PadName;	//焊盘名称
		double m_dOutsideDiameter;  //外径
		double m_dInsideDiameter;	//内径
		double m_PadArea;   //焊盘面积
		double m_PadThickness; // 锡膏厚度
		Point m_RoiPosition;         //Roi位置（图像坐标系）
		PadShape m_padshape_grpname; //焊盘形状组标识
		string m_custom_grpname;     //焊盘自定义组标识
		Groupflag m_groupcondition;  //分组情况
		SPIAlgorithmParamPtr m_ptrSpiAlgorithmParam;    //算法参数
	};

	using DetectionPadDataPtr = std::shared_ptr<DetectionPadData>;

	/*
	* 类名：PadDataSet
	* 创建日期： 2023/10/13
	* By ypk
	*	@file	PadCore.hpp
	*	@brief	焊盘数据集类
	*	@version 1.0
	*/
	class AS_EXPORTS PadDataSet
	{
	public:
		PadDataSet();
		//==========焊盘数据============//
		map<string, map<DWORD, shared_ptr<DetectionPadData>>> GetAllPadData();	 //焊盘预处理数据
		map<DWORD, shared_ptr<DetectionPadData>> GetLayerPadData(string layername);
		//获取单个焊盘数据
		shared_ptr<DetectionPadData> GetSinglePadData(string layername, DWORD name);
		//插入单个焊盘数据
		void InsertSinglePadData(string layername, DWORD name, shared_ptr<DetectionPadData> data);
		//查找层预处理数据
		bool FindLayerPadData(string layername);
		//删除单个Gerber层焊盘数据
		void DeleteSingleLayerPadData(string name);
		//查找单个焊盘数据
		bool FindSinglePadData(string layername, DWORD padid);
		//删除单个焊盘数据
		void DeleteSinglePadData(string layername, DWORD name);

		//==========焊盘分组数据==============//
		shared_ptr<PadGroupManager> GetPadGroupManager();

		//==========Gerber文件光圈数据==============//
		map<string, Aperture> GetAllApertureData();
		bool FindApertureData(string code);
		Aperture GetSingleApertureData(string code);
		void InsertSingleApertureData(string code, Aperture aperture_data);

	private:
		map<string, map<DWORD, shared_ptr<DetectionPadData>>> m_pDetectionPadDataSet;          //焊盘数据
		shared_ptr<PadGroupManager> m_pPadGroupManager;						       //焊盘分组数据	   
		map<string, Aperture>  m_pApertureDefinateSet;					           //自定义光圈
	};
}

#endif