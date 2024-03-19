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
	//��װ����
	enum PackageType
	{
		CHIP_R = 1,//����
		CHIP_C = 2,//����
		DIODE = 3,//������
		TRIODE = 4,//������
		COLOR_R = 5,//ɫ������
		SOP = 6,//SOP
		QFP = 7,//QFP
		BGA = 8,//BGA
		BARCODE = 9,//������
		PLUGINUNIT = 10,//���
		SINGLERECT = 11,//����
		SOLDERJOINT = 12,//����
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

		// ��е����
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

		inline string GetNGID();//��ȡԪ��NG��ID
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
		Point m_singleNGMechPos;//NG���еλ��
		Point m_cRoiPos;	//NG��λ��
		double m_dRoiWidth; //��
		double m_dRoiHight;	//��
		double m_dRoiAngle;    //�Ƕ�
		double m_Resolution;  //�ֱ���
		AOI_DefectType m_eDefectType;
		bool m_tRegistration;//ע��ģ���ʶ
		string m_strNGID;			//Ԫ��NG��ID
		map<AOI_Algorithm_Type, shared_ptr<AOIAlgorithmParam>> m_pAlgorithmParam;
		vector<unsigned char> m_NgImageBase;
		string m_strApplicationType;  //Ӧ��ģʽ
	};

	//Ԫ������
	class AS_EXPORTS Component
	{
	public:
		Component();
		Component& operator=(Component& ref);

		//template <class Archive>
		//friend void boost::serialization::serialize(Archive& ar, Component& val, const unsigned int version);

		inline PackageType GetPackageType();//��ȡԪ����װ����
		inline void SetPackageType(PackageType package_type);

		inline string GetPackageTypeName();//��ȡԪ����װ����
		inline void SetPackageTypeName(string package_type);

		inline string GetCompName();//��ȡԪ����װ����
		inline void SetCompName(string name);

		inline map<string, NoGoodParam> GetAllNoGoodParam();//��ȡԪ��ģ�棨�൱��һ��Ԫ����
		inline void InsertNoGoodParam(string ng_id, NoGoodParam ng_param);
		inline void DeleteNoGoodParam(string ng_id);
		inline bool FindNoGoodParam(string ng_id);
		inline NoGoodParam& GetNoGoodParam(string ng_id);//��ȡԪ��ģ�����һ��NG�ࣨԪ����һ��NG�ࣩ
		inline void UpdateNoGoodParam(string ng_id, NoGoodParam ng_param);

		inline vector<unsigned char> GetImageData();
		inline void SetImageData(vector<unsigned char> image_data);

		inline void SetIsExistInDB(bool flag);
		inline bool GetIsExistInDB();

		double ComputeCompoentWidth();
		double ComputeCompoentHeight();
	private:
		PackageType m_ePackageType;
		string m_strPackageType;					//��װ����
		string m_strCompName;						//��װ��������
		map<string, NoGoodParam> m_vpNGParam;
		vector<unsigned char> m_vImageData;
		double m_dCompWidth;						//Ԫ���������ã�
		double m_dCompHeight;						//Ԫ���ߣ������ã�
		bool m_bIsExistInDB;                         //���ݿ����Ƿ����
	};

	//Ԫ�����ݹ���
	class AS_EXPORTS ComponentData
	{
	public:
		ComponentData();
		inline map<string, shared_ptr<Component>> GetAllComponent();//��ȡԪ���б�
		inline void InsertComponent(string package_name, shared_ptr<Component> component);
		inline void DeleteComponent(string package_name);
		inline bool FindComponent(string package_name);
		inline shared_ptr<Component> GetComponent(string package_name);
		
	private:
		map<string, shared_ptr<Component>> m_mCompList;
	};
}
#endif