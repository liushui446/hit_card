#ifndef AS_COMPONENTCORE_HPP
#define AS_COMPONENTCORE_HPP

#include "as/AOIAlgorithmParam.hpp"

namespace as
{
	class NoGoodParam;
	class Component;
}

namespace boost
{
	namespace serialization
	{
		/*template <class Archive>
		void serialize(Archive& ar, as::NoGoodParam& val, const unsigned int version);
		template <class Archive>
		void serialize(Archive& ar, as::Component& val, const unsigned int version);*/
	}
}

namespace as
{
	//封装类型
	enum PackageType
	{
		CHIP_R = 1,//电阻
		CHIP_C = 2,//电容
		DIODE = 3,//二极管
		TRIODE = 4,//三极管
		COLOR_R = 5,//色环电阻
		SOP = 6,//SOP
		QFP = 7,//QFP
		BGA = 8,//BGA
		BARCODE = 9,//条形码
		PLUGINUNIT = 10,//插件
		SINGLERECT = 11,//单框
		SOLDERJOINT = 12,//焊点
	};

	class AS_EXPORTS NoGoodParam
	{
	public:
		//template <class Archive>
		//friend void boost::serialization::serialize(Archive& ar, NoGoodParam& val, const unsigned int version);

		NoGoodParam();
		NoGoodParam& operator=(NoGoodParam& ref);

		inline Point GetRoiPosition();
		inline void SetRoiPosition(Point pos);

		// 机械坐标
		inline Point GetRoiMechPosition();
		inline void SetRoiMechPosition(Point pos);

		inline double GetRoiWidth();
		inline void SetRoiWidth(double length);

		inline double GetRoiHight();
		inline void SetRoiHight(double hight);

		inline double GetRoiAngle();
		inline void SetRoiAngle(double angle);

		inline bool GetRegistration();
		inline void SetRegistration(bool registration);

		inline AOI_DefectType GetDefectType();
		inline void SetDefectType(AOI_DefectType defect_type);

		inline string GetNGID();//获取元件NG的ID
		inline void SetNGID(string ng_id);

		inline map<AOI_Algorithm_Type, shared_ptr<AOIAlgorithmParam>> GetAllAlgorithmParam();
		inline void ClearAlgorithmParam();
		inline void InsertAlgorithmParam(AOI_Algorithm_Type algorithm_type, shared_ptr<AOIAlgorithmParam> algorithm_param);
		inline void DeleteAlgorithmParam(AOI_Algorithm_Type algorithm_type);
		inline bool FindAlgorithm(AOI_Algorithm_Type algorithm_type);
		inline shared_ptr<AOIAlgorithmParam> GetAlgorithmParam(AOI_Algorithm_Type algorithm_type);
		shared_ptr<AOIAlgorithmParam> GetUseAlgorithmParam();
		void SetUseAlgorithmParam(AOI_Algorithm_Type algorithm_type);

		inline vector<unsigned char> GetNGImage() { return m_NgImageBase; }
		inline void SetNGImage(vector<unsigned char>& val) { m_NgImageBase = val; }

		inline string GetApplicationType();
		inline void SetApplicationType(string applica_type);

		inline double GetResolution() { return m_Resolution; }
		inline void SetResolution(double resolution) { m_Resolution = resolution; }
	private:
		Point m_singleNGMechPos;//NG框机械位置
		Point m_cRoiPos;	//NG框位置
		double m_dRoiWidth; //宽
		double m_dRoiHight;	//高
		double m_dRoiAngle;    //角度
		double m_Resolution;  //分辨率
		AOI_DefectType m_eDefectType;
		bool m_tRegistration;//注册模板标识
		string m_strNGID;			//元件NG的ID
		map<AOI_Algorithm_Type, shared_ptr<AOIAlgorithmParam>> m_pAlgorithmParam;
		vector<unsigned char> m_NgImageBase;
		string m_strApplicationType;  //应用模式
	};

	//元件数据
	class AS_EXPORTS Component
	{
	public:
		Component();
		Component& operator=(Component& ref);

		//template <class Archive>
		//friend void boost::serialization::serialize(Archive& ar, Component& val, const unsigned int version);

		inline PackageType GetPackageType();//获取元件封装类型
		inline void SetPackageType(PackageType package_type);

		inline string GetPackageTypeName();//获取元件封装类型
		inline void SetPackageTypeName(string package_type);

		inline string GetCompName();//获取元件封装名称
		inline void SetCompName(string name);

		inline map<string, NoGoodParam> GetAllNoGoodParam();//获取元件模版（相当于一个元件）
		inline void InsertNoGoodParam(string ng_id, NoGoodParam ng_param);
		inline void DeleteNoGoodParam(string ng_id);
		inline bool FindNoGoodParam(string ng_id);
		inline NoGoodParam& GetNoGoodParam(string ng_id);//获取元件模版里的一条NG类（元件的一个NG类）
		inline void UpdateNoGoodParam(string ng_id, NoGoodParam ng_param);

		inline vector<unsigned char> GetImageData();
		inline void SetImageData(vector<unsigned char> image_data);

		inline void SetIsExistInDB(bool flag);
		inline bool GetIsExistInDB();

		double ComputeCompoentWidth();
		double ComputeCompoentHeight();
	private:
		PackageType m_ePackageType;
		string m_strPackageType;					//封装类型
		string m_strCompName;						//封装类型名称
		map<string, NoGoodParam> m_vpNGParam;
		vector<unsigned char> m_vImageData;
		double m_dCompWidth;						//元件宽（已弃用）
		double m_dCompHeight;						//元件高（已弃用）
		bool m_bIsExistInDB;                         //数据库里是否存在
	};

	//元件数据管理
	class AS_EXPORTS ComponentData
	{
	public:
		ComponentData();
		inline map<string, shared_ptr<Component>> GetAllComponent();//获取元件列表
		inline void InsertComponent(string package_name, shared_ptr<Component> component);
		inline void DeleteComponent(string package_name);
		inline bool FindComponent(string package_name);
		inline shared_ptr<Component> GetComponent(string package_name);
		
	private:
		map<string, shared_ptr<Component>> m_mCompList;
	};
}
#endif