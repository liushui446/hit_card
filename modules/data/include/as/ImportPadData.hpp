#ifndef AS_IMPORTPADDATA_HPP
#define AS_IMPORTPADDATA_HPP
#include "as/core/def.h"
#include "as/CommonCore.hpp"
#include "as/ApertureDef.hpp"

namespace as
{

	/* 类名：ImportPadData
	* 创建日期： 2023/10/17
	* By ypk
	*	@file	ImportPadData.hpp
	*	@brief	待预处理焊盘数据类
	*	@version 1.0
	*/
	class AS_EXPORTS ImportPadData
	{
	public:
		ImportPadData();
		ImportPadData& operator=(ImportPadData& ref);

		void SetPadId(DWORD val);
		DWORD GetPadId();

		void SetPadPos(Point val);
		Point& GetPadPos();

		void SetPadAperture(string val);
		string GetPadAperture();

		void SetPadShape(PadShape val);
		PadShape GetPadShape();

		void SetPadAngle(double angle);
		double GetPadAngle();

		double GetLength();
		void SetLength(double val);

		double GetWidth();
		void SetWidth(double val);

		double GetOutDiameter();
		void SetOutDiameter(double val);

		double GetInDiameter();
		void SetInDiameter(double val);

	private:
		DWORD m_PadId;		//焊盘ID
		string m_apertureCode;      //光圈码
		PadShape m_shape;	//焊盘形状
		double m_angle;		//焊盘角度
		Point m_pos;		//焊盘位置
		double m_dlength;	//焊盘长
		double m_dwidth;    //焊盘宽
		double m_dOutsideDiameter;  //外径
		double m_dInsideDiameter;	//内径
	};

	/* 类名：ImportPadDataSet
	* 创建日期： 2023/10/17
	* By ypk
	*	@file	ImportPadData.hpp
	*	@brief	待预处理焊盘数据集
	*	@version 1.0
	*/
	class AS_EXPORTS ImportPadDataSet
	{
	public:
		ImportPadDataSet();
		//======================焊盘=========================//
		//获取所有预处理焊盘数据
		map<string, map<DWORD, shared_ptr<ImportPadData>>> GetAllImportPadData();
		//获取层预处理焊盘数据
		map<DWORD, shared_ptr<ImportPadData>> GetLayerImportPadData(string layername);
		//获取单个预处理焊盘数据
		shared_ptr<ImportPadData> GetSingleImportPadData(string layername, DWORD name);
		//插入单个预处理焊盘数据
		void InsertSingleImportPadData(string layername, DWORD name, shared_ptr<ImportPadData> data);
		//查找层预处理数据
		bool FindLayerImportPadData(string layername);
		//查找单个预处理焊盘数据
		bool FindSingleImportPadData(string layername, DWORD padid);
		//删除单个焊盘数据
		void DeleteSingleImportPadData(string layername, DWORD name);
		//删除单个Gerber层焊盘数据
		void DeleteGerberImportpadData(string layername);         

		//======================光圈===========================//
		//获取所有预处理光圈数据
		map<string, map<string, Aperture>> GetAllImportApertureData();
		//获取层预处理光圈数据
		map<string, Aperture> GetLayerImportApertureData(string layername);
		//获取单个预处理光圈数据
		Aperture GetSingleImportApertureData(string layername, string code);
		//插入单个预处理光圈数据
		void InsertSingleApertureData(string layername, string code, Aperture aperture_data);
		//查找层预处理光圈数据
		bool FindLayerImportApertureData(string layername);
		//查找单个预处理光圈数据
		bool FindSingleImportApertureData(string layername, string code);
		//删除单个光圈数据
		void DeleteSingleImportApertureData(string layername, string code);
		//删除单个Gerber层光圈数据
		void DeleteGerberImportApertureData(string layername);

	private:
		map<string, map<DWORD, shared_ptr<ImportPadData>>> m_pImportPadDataSet;	   //焊盘预处理数据
		map<string, map<string, Aperture>>  m_pApertureDataSet;				   //自定义光圈数据
	};

	/*
	* 类名：ImportPadContext
	* 创建日期： 2023/11/9
	* By ypk
	*	@file	ImportPadData.hpp
	*	@brief	SPI预处理焊盘数据管理类
	*	@version 1.0
	*/
	class AS_EXPORTS ImportPadContext
	{
	public:
		/*template <class Archive>
		friend void boost::serialization::serialize(Archive& ar, AOIContext& val, const unsigned int version);*/

		ImportPadContext();
		static ImportPadContext& GetInstance();

		shared_ptr<ImportPadDataSet> GetImportPadDataSet();
	private:
		shared_ptr<ImportPadDataSet> m_ptrImportPadDataSet;
	};
}

#endif