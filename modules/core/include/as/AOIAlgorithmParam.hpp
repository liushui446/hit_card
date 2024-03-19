#ifndef AOI_ALGORITHM_PARAM_HPP
#define AOI_ALGORITHM_PARAM_HPP

#include "as/core/def.h"
#include "as/core/Color.hpp"
#include "as/core/DetectDef.hpp"
#include "as/core/DefectDef.hpp"
#include "as/AOIDetectRes.hpp"

namespace as
{
	class AOIAlgorithmParam;
	class TOCParam;
	class MatchParam;
	class HISTOParam;
	class OCVParam;
	class CompareParam;
	class DistanceParam;
	class GLUEParam;
	class LengthParam;
	class PadplaceParam;
	class PINParam;
	class PoleParam;
	class ShortParam;
	class Match2Param;
	class OtherParam;
	class ALOffsetParam;
	class CrestParam;
	class HoleParam;
	class BarcodeParam;
}

namespace boost
{
	namespace serialization
	{
		template <class Archive>
		extern void serialize(Archive& ar, as::AOIAlgorithmParam& val, const unsigned int version);

		template <class Archive>
		extern void serialize(Archive& ar, as::TOCParam& val, const unsigned int version);

		template <class Archive>
		extern void serialize(Archive& ar,as::MatchParam& val, const unsigned int version);

		template <class Archive>
		extern void serialize(Archive& ar, as::HISTOParam& val, const unsigned int version);

		template <class Archive>
		extern void serialize(Archive& ar, as::OCVParam& val, const unsigned int version);

		template <class Archive>
		extern void serialize(Archive& ar, as::CompareParam& val, const unsigned int version);

		template <class Archive>
		extern void serialize(Archive& ar, as::DistanceParam& val, const unsigned int version);

		template <class Archive>
		extern void serialize(Archive& ar, as::GLUEParam& val, const unsigned int version);

		template <class Archive>
		extern void serialize(Archive& ar, as::LengthParam& val, const unsigned int version);

		template <class Archive>
		extern void serialize(Archive& ar, as::PINParam& val, const unsigned int version);

		template <class Archive>
		extern void serialize(Archive& ar, as::PoleParam& val, const unsigned int version);

		template <class Archive>
		extern void serialize(Archive& ar, as::Match2Param& val, const unsigned int version);

		template <class Archive>
		extern void serialize(Archive& ar, as::ShortParam& val, const unsigned int version);

		template <class Archive>
		extern void serialize(Archive& ar, as::PadplaceParam& val, const unsigned int version);

		template <class Archive>
		extern void serialize(Archive& ar, as::OtherParam& val, const unsigned int version);

		template <class Archive>
		extern void serialize(Archive& ar, as::ALOffsetParam& val, const unsigned int version);

		template <class Archive>
		extern void serialize(Archive& ar, as::CrestParam& val, const unsigned int version);

		template <class Archive>
		extern void serialize(Archive& ar, as::HoleParam& val, const unsigned int version);

		template <class Archive>
		extern void serialize(Archive& ar, as::BarcodeParam& val, const unsigned int version);
	}
}

namespace as
{
    class AS_EXPORTS AOIAlgorithmParam
	{
	public:
		template <class Archive>
		friend void boost::serialization::serialize(Archive& ar, AOIAlgorithmParam& val, const unsigned int version);

		AOIAlgorithmParam(void);
		virtual ~AOIAlgorithmParam(void) {};

		AOIAlgorithmParam& operator=(AOIAlgorithmParam& ref);

		inline AOI_DefectType& getDefectTypeData() { return m_eDefecType; }
		inline void SetDefectTypeData(AOI_DefectType val) { m_eDefecType = val; }

		inline AOI_Algorithm_Type& getAlgorithmTypeData() { return m_eAlgorithmType; }
		inline void SetAlgorithmTypeData(AOI_Algorithm_Type val) { m_eAlgorithmType = val; }

		inline ColorChannel& getColorChannelData() { return m_eColorChannel; }
		inline void SetColorChannelData(ColorChannel val) { m_eColorChannel = val; }

		inline ColorMethod& getColorMethodData() { return m_eColorMethod; }
		inline void SetColorMethodData(ColorMethod val) { m_eColorMethod = val; }

		inline AOI_Detection_Type& getDetectionTypeData() { return m_eDetectionType; }
		inline void SetDetectionTypeData(AOI_Detection_Type val) { m_eDetectionType = val; }

		inline SearchScope& getSearchScopeData() { return m_blkSearchScope; }
		inline void SetSearchScopeData(SearchScope val) { m_blkSearchScope = val; }

		inline AllowOffset& getAllowOffsetData() { return m_blkAllowOffset; }
		inline void SetAllowOffsetData(AllowOffset val) { m_blkAllowOffset = val; }

		inline ReturnValue& getReturnValue() { return m_eReturnValue; }
		inline void SetReturnValue(ReturnValue val) { m_eReturnValue = val; }

		inline ColorStandard& getColorStandard() { return m_ColorStandard; }
		inline void SetColorStandard(ColorStandard val) { m_ColorStandard = val; }

		inline bool getAlgorithmUseFlag() { return m_bAlgorithmUseFlag; }
		inline void SetlgorithmUseFlag(bool val) { m_bAlgorithmUseFlag = val; }

		void SetAlgorithmParam(AOIAlgorithmParam& val);
		AOIAlgorithmParam& getAlgorithmParam() { return *this; }

		inline ReturnValue& getReturnStandValue() { return m_eReturnStandValue; }
		inline void SetReturnStandValue(ReturnValue val) { m_eReturnStandValue = val; }

		inline double getResolution() { return m_Resolution; }
		inline void SetResolution(double val) { m_Resolution = val; }
	private:
		AOI_DefectType m_eDefecType;
		AOI_Algorithm_Type m_eAlgorithmType;
		ColorChannel m_eColorChannel;
		ColorMethod m_eColorMethod;
		ReturnValue m_eReturnValue;
		ReturnValue m_eReturnStandValue;
		AOI_Detection_Type m_eDetectionType;
		SearchScope m_blkSearchScope;
		AllowOffset m_blkAllowOffset;
		ColorStandard m_ColorStandard;
		bool m_bAlgorithmUseFlag;
		double m_Resolution;
	};

	typedef std::shared_ptr<AOIAlgorithmParam> AOIAlgorithmParamPtr;
	typedef std::shared_ptr<const AOIAlgorithmParam> AOIAlgorithmParamConstPtr;

	class AS_EXPORTS TOCParam : public AOIAlgorithmParam
	{
	public:
		template <class Archive>
		friend void boost::serialization::serialize(Archive& ar, TOCParam& val, const unsigned int version);

		struct InitColorStand {
			int m_Init_red_high;                    // 初始系统阈值
			int m_Init_red_low;                     // 红色范围

			int m_Init_green_high;		        // 初始系统阈值
			int m_Init_green_low;                   // 绿色范围

			int m_Init_blue_high;                   // 初始系统阈值
			int m_Init_blue_low;		        // 蓝色范围

			int m_Init_gray_high;                   // 初始系统阈值
			int m_Init_gray_low;                    // 亮度范围

			int m_judge_score_low;                  // 初始判定范围
			int m_judge_score_high;
		};
	private:
		InitColorStand m_InitColorStand;
		int m_template_grayMean;                // 注册模板图像的亮度均值
		bool m_Force_Register;                  // 是否根据提示框选项进行强制注册

	public:
		TOCParam();
		~TOCParam() {};

		TOCParam& operator=(TOCParam& ref);

		inline TOCParam& getTOC_PARAM() { return *this; }
		// 仅设置RGBI颜色范围
		inline void SetTOC_PARAM(TOCParam& val) {
			this->SetAlgorithmParam(val.getAlgorithmParam());
			this->SetgrayMean(val.getgrayMean());
		}

		inline InitColorStand& getInitColorStand() { return m_InitColorStand; }
		inline void SetInitColorStand(InitColorStand val) { m_InitColorStand = val; }

		inline int getInit_red_high() { return m_InitColorStand.m_Init_red_high; }
		inline void SetInit_red_high(int val) { m_InitColorStand.m_Init_red_high = val; }

		inline int getInit_red_low() { return m_InitColorStand.m_Init_red_low; }
		inline void SetInit_red_low(int val) { m_InitColorStand.m_Init_red_low = val; }

		inline int getInit_green_high() { return m_InitColorStand.m_Init_green_high; }
		inline void SetInit_green_high(int val) { m_InitColorStand.m_Init_green_high = val; }

		inline int getInit_green_low() { return m_InitColorStand.m_Init_green_low; }
		inline void SetInit_green_low(int val) { m_InitColorStand.m_Init_green_low = val; }

		inline int getInit_blue_high() { return m_InitColorStand.m_Init_blue_high; }
		inline void SetInit_blue_high(int val) { m_InitColorStand.m_Init_blue_high = val; }

		inline int getInit_blue_low() { return m_InitColorStand.m_Init_blue_low; }
		inline void SetInit_blue_low(int val) { m_InitColorStand.m_Init_blue_low = val; }

		inline int getInit_gray_high() { return m_InitColorStand.m_Init_gray_high; }
		inline void SetInit_gray_high(int val) { m_InitColorStand.m_Init_gray_high = val; }

		inline int getInit_gray_low() { return m_InitColorStand.m_Init_gray_low; }
		inline void SetInit_gray_low(int val) { m_InitColorStand.m_Init_gray_low = val; }

		inline int getjudge_score_low() { return m_InitColorStand.m_judge_score_low; }
		inline void Setjudge_score_low(int val) { m_InitColorStand.m_judge_score_low = val; }

		inline int getjudge_score_high() { return m_InitColorStand.m_judge_score_high; }
		inline void Setjudge_score_high(int val) { m_InitColorStand.m_judge_score_high = val; }

		inline int getgrayMean() { return m_template_grayMean; }
		inline void SetgrayMean(int val) { m_template_grayMean = val; }

		inline bool getForcedRegister() { return m_Force_Register; }
		inline void SetForcedRegister(bool val) { m_Force_Register = val; }

	};
	typedef std::shared_ptr<TOCParam> TOCParamPtr;
	typedef std::shared_ptr<const TOCParam> TOCParamConstPtr;

	class AS_EXPORTS MatchParam : public AOIAlgorithmParam
	{
	public:
		MatchParam();
		~MatchParam() {};
		MatchParam& operator = (MatchParam& ref);
		template <class Archive>
		friend void boost::serialization::serialize(Archive& ar, MatchParam& val, const unsigned int version);

	public:
		// 校正方式
		enum  CorrectMode
		{
			image = 1,       // 图像
			gravity = 2,      // 重心
			ellipse = 3,       // 椭圆
			rectangle = 4,  // 矩形
		};

		// 检测方式
		enum  DetType
		{
			Offset = 1,       // 图像
			WrongPart = 2,      // 重心
		};

		struct StandardTemplateData 
		{
			float error_x;             // x方向误差
			float error_y;             // y方向误差
			float bodycenter_x;        // 模板元件中心x
			float bodycenter_y;        // 模板元件中心y
			float alllength;           // 允许偏移距离
		};

	private:
		CorrectMode m_correctmode; // 校正方式
		DetType     m_dettppe;     //检测类型
		int m_brightness;      //亮度
		int m_contrast;        //对比度
		int m_enhance;         //增强
		int m_gray;            //灰度
		int m_vlaue;           //相似度
		StandardTemplateData m_StandardTemplateData;//模板注册的其他数据
	public:
		inline CorrectMode getCorrectMode() { return m_correctmode; }
		inline void setCorrectMode(CorrectMode val) { m_correctmode = val; }

		inline DetType getDetType() { return m_dettppe; }
		inline void setDetType(DetType val) { m_dettppe = val; }

		inline int getbrightness() { return m_brightness; }
		inline void Setbrightness(int val) { m_brightness = val; }

		inline int getcontrast() { return m_contrast; }
		inline void Setcontrast(int val) { m_contrast = val; }

		inline int getgray() { return m_gray; }
		inline void Setgray(int val) { m_gray = val; }

		inline int getvalue() { return m_vlaue; }
		inline void Setvalue(int val) { m_vlaue = val; }

		inline int getenhance() { return m_enhance; }
		inline void Setenhance(int val) { m_enhance = val; }

		inline StandardTemplateData getStandardTemplateData() { return m_StandardTemplateData; }
		inline void SetStandardTemplateData(StandardTemplateData val) { m_StandardTemplateData = val; }

	};
	typedef std::shared_ptr<MatchParam> MatchParamPtr;
	typedef std::shared_ptr<const MatchParam> MatchParamConstPtr;

	class AS_EXPORTS Match2Param : public AOIAlgorithmParam
	{
	private:
		float m_Dx;
		float m_Dy;
		ColorChannel mplate_colorchannel;
		ColorMethod mplate_colormethod;
	public:
		template <class Archive>
		friend void boost::serialization::serialize(Archive& ar, Match2Param& val, const unsigned int version);

		Match2Param();
		~Match2Param() {};

		Match2Param& operator=(Match2Param& ref);

		inline float getDx() { return m_Dx; }
		inline void SetDx(float val) { m_Dx = val; }

		inline float getDy() { return m_Dy; }
		inline void SetDy(float val) { m_Dy = val; }

		inline ColorChannel getplate_ColorChannel() { return mplate_colorchannel; }
		inline void Setplate_ColorChannel(ColorChannel val) { mplate_colorchannel = val; }

		inline ColorMethod getplate_ColorMethod() { return mplate_colormethod; }
		inline void plate_ColorMethod(ColorMethod val) { mplate_colormethod = val; }

	};
	typedef std::shared_ptr<Match2Param> Match2ParamPtr;
	typedef std::shared_ptr<const Match2Param> Match2ParamConstPtr;

	/// <summary>
	/// PoleParam
	/// </summary>
	class AS_EXPORTS PoleParam : public AOIAlgorithmParam {
	public:
		PoleParam();
		PoleParam& operator=(PoleParam& ref);

		int StandardArea;
	private:
	};
	typedef std::shared_ptr<PoleParam> PoleParamPtr;
	typedef std::shared_ptr<const PoleParam> PoleParamConstPtr;

	/// <summary>
	/// Length算法
	/// </summary>
	class AS_EXPORTS LengthParam : public AOIAlgorithmParam {
	public:
		template <class Archive>
		friend void boost::serialization::serialize(Archive& ar, LengthParam& val, const unsigned int version);
		LengthParam();
		~LengthParam() {};
		LengthParam& operator=(LengthParam& ref);

	public:
		/// <summary>
		/// 测距方式
		/// </summary>
		enum DetectDisTAB
		{
			innerDis = 1,
			outerDis = 2
		};

	private:
		DetectDisTAB m_detectDisTAB;   //!外距/内距
		int m_binary_threshold;        //亮度阈值
		int m_projection_threshold;	   //投影阈值
		int m_standard_length;		   //标准长度
		int m_adjust_intensity;        //调节图像亮度(图像整体灰度值增大或减少, 有正有负)
		int m_adjust_contrast;         //调节图像对比度(图像灰度跨度的增大或减少,以比例方式呈现, %)
		int m_judge_low;               //!默认判定参数-低
		int m_judge_high;			   //!默认判定参数-高
		int m_length_return_Value;     //!仅在测试时的返回值(位于45-55之间OK)

	public:

		inline DetectDisTAB& get_DetectDisTAB(void) { return m_detectDisTAB; }
		inline void Set_DetectDisTAB(DetectDisTAB val) { m_detectDisTAB = val; }

		inline int& get_Binary_Threshold(void) { return m_binary_threshold; }
		inline void Set_Binary_Threshold(int val) { m_binary_threshold = val; }

		inline int& get_Projection_Threshold(void) { return m_projection_threshold; }
		inline void Set_Projection_Threshold(int val) { m_projection_threshold = val; }

		inline int& get_Standard_Length(void) { return m_standard_length; }
		inline void Set_Standard_Length(int val) { m_standard_length = val; }

		inline int& get_Adjust_Intensity(void) { return m_adjust_intensity; }
		inline void Set_Adjust_Intensity(int val) { m_adjust_intensity = val; }

		inline int& get_Adjust_Contrast(void) { return m_adjust_contrast; }
		inline void Set_Adjust_Contrast(int val) { m_adjust_contrast = val; }

		inline int& get_Length_Judge_Low(void) { return m_judge_low; }
		inline void Set_Length_Judge_Low(int val) { m_judge_low = val; }

		inline int& get_Length_Judge_High(void) { return m_judge_high; }
		inline void Set_Length_Judge_High(int val) { m_judge_high = val; }

		inline int& get_Length_Return_Value(void) { return m_length_return_Value; }
		inline void Set_Length_Return_Value(int val) { m_length_return_Value = val; }

	};
	typedef std::shared_ptr<LengthParam> LengthParamPtr;
	typedef std::shared_ptr<const LengthParam> LengthParamConstPtr;

	/// <summary>
	/// 直方图Histogram
	/// </summary>
	class AS_EXPORTS HISTOParam : public AOIAlgorithmParam
	{
	public:
		template <class Archive>
		friend void boost::serialization::serialize(Archive& ar, HISTOParam& val, const unsigned int version);

		HISTOParam();
		~HISTOParam() {};

		HISTOParam& operator=(HISTOParam& ref);
	public:
	enum DetectMethod
	{
		Min = 1,		// 检测方法
		Max = 2,
		Range = 3
	};

	enum FilterLevels { //滤波级别
		Level0 = 0,
		Level1 = 1,
		Level2 = 2,
		Level3 = 3,
		Level4 = 4,
		Level5 = 5
	};

	struct Min_Gray {
		int m_min_lower;          // 较小灰度值区域的灰度下限
		int m_min_grayAve;        // 较小灰度值区域的灰度均值
		int m_min_upper;          // 较小灰度值区域的灰度上限
	};

	struct Max_Gray {
		int m_max_lower;          // 较大灰度值区域的灰度下限
		int m_max_grayAve;        // 较大灰度值区域的灰度均值
		int m_max_upper;          // 较大灰度值区域的灰度上限
	};

	struct Range_Gray {
		int m_range_lower;        // 中间灰度值区域的灰度下限
		int m_range_grayAve;      // 中间灰度值区域的灰度均值
		int m_range_upper;        // 中间灰度值区域的灰度上限
	};

	private:
		DetectMethod m_HistoDetectMethod;// 直方图检测方法(Min Max Range)
		double m_ratio;                  // 选取区域的比例
		Min_Gray m_Min_Gray;             //
		Max_Gray m_Max_Gray;             //
		Range_Gray m_Range_Gray;         //
		int m_Init_Judge_Lower;          // 不同缺陷默认的判定正常亮度下限值
		int m_Init_Judge_Upper;          // 不同缺陷默认的判定正常亮度上限值
		int m_total_gray_Ave;            // 整张图像的灰度均值(三种计算方法)
		int m_output_gray;               // 最终输出亮度值(待检测)
		FilterLevels m_Filter_Level;     // 滤波级别 TODO:待补充(高斯滤波函数实现)
		std::vector<int> m_gray_Img;     //用于显示直方图的灰阶图像(已经执行过预处理)
	public:
		
		inline DetectMethod getHistoDetectMethod(void) { return m_HistoDetectMethod; }
		inline void SetHistoDetectMethod(DetectMethod val) { m_HistoDetectMethod = val; }

		inline double& getRatio(void) { return m_ratio; }
		inline void SetRatio(double val) { m_ratio = val; }

		inline Min_Gray getMinGray(void) { return m_Min_Gray; }
		inline void SetMinGray(Min_Gray val) { m_Min_Gray = val; }

		inline Max_Gray getMaxGray(void) { return m_Max_Gray; }
		inline void SetMaxGray(Max_Gray val) { m_Max_Gray = val; }

		inline Range_Gray getRangeGray(void) { return m_Range_Gray; }
		inline void SetRangeGray(Range_Gray val) { m_Range_Gray = val; }

		inline int get_Judge_Lower(void) { return m_Init_Judge_Lower; }
		inline void Set_Judge_Lower(int val) { m_Init_Judge_Lower = val; }

		inline int get_Judge_Upper(void) { return m_Init_Judge_Upper; }
		inline void Set_Judge_Upper(int val) { m_Init_Judge_Upper = val; }

		inline int& get_Total_Gray_Ave(void) { return m_total_gray_Ave; }
		inline void Set_Total_Gray_Ave(int val) { m_total_gray_Ave = val; }

		inline int get_output_gray(void) { return m_output_gray; }
		inline void Set_output_gray(int val) { m_output_gray = val; }

		inline std::vector<int> getgray_Img() { return m_gray_Img; }
		inline void setgray_Img(std::vector<int> val) {
			m_gray_Img.assign(val.begin(), val.end());
		}

		inline FilterLevels& get_Filter_Level(void) { return m_Filter_Level; }
		inline void Set_Filter_Level(FilterLevels val) { m_Filter_Level = val; }

	};
	typedef std::shared_ptr<HISTOParam> HISTOParamPtr;
	typedef std::shared_ptr<const HISTOParam> HISTOParamConstPtr;
	
	/// <summary>
	/// PIN
	/// </summary>
	class AS_EXPORTS PINParam : public AOIAlgorithmParam {
	public:
		template <class Archive>
		friend void boost::serialization::serialize(Archive& ar, PINParam& val, const unsigned int version);

		PINParam() 
        : m_PinModechoose(PinModechoose::lesstin), 
        m_lesstin_colorstand(ColorStandard(60, 0, 90, 0, 180, 65, 180, 0)), 
        m_EmptyWelding_colorstand(ColorStandard(180, 65, 70, 0, 60, 0, 255, 65)), 
        m_VirtualSol_colorstand(ColorStandard(65, 0, 75, 0, 180, 65, 255, 65)), 
        m_lesstin_JudgeHigh(100), 
        m_lesstin_JudgeLow(60), 
        m_EmptyWelding_JudgeHigh(20), 
        m_EmptyWelding_JudgeLow(0), 
        m_VirtualSol_JudgeHigh(20), 
        m_VirtualSol_JudgeLow(0), 
        m_judgeHigh(0), 
        m_judgeLow(0), 
        m_lesstin_extract_reback(false), 
        m_EmptyWelding_extract_reback(false), 
        m_VirtualSol_extract_reback(false), 
        m_lesstin_redundancy_val(0.15), 
        m_EmptyWelding_redundancy_val(0.15), 
        m_VirtualSol_redundancy_val(0.15) { 
            this->SetAlgorithmTypeData(AOI_Algorithm_Type::PIN); 
            };

		~PINParam() {};
		PINParam& operator=(PINParam& ref);

		//PIN算法模式选择
		enum PinModechoose
		{
			//少锡
			lesstin = 0,
			//空焊
			EmptyWelding = 1,
			//虚焊
			VirtualSol = 2
		};

		struct PinRect {
			int left_top_x;
			int left_top_y;
			int right_down_x;
			int right_down_y;
		};

	private:
		PinModechoose m_PinModechoose;//少锡界面中的三种检测类型

		/// <summary>
		/// 少锡检测类型
		/// </summary>
		ColorStandard m_lesstin_colorstand;//少锡(正常锡的颜色标准)
		int m_lesstin_returnValue;//少锡检测--返回值
		//ReturnValue m_lesstin_retVal;//少锡检测类型--注册
		//ReturnValue m_lesstin_retRes;//少锡检测类型--测试
		int m_lesstin_JudgeHigh;//少锡(OK元件高阈值)
		int m_lesstin_JudgeLow;//少锡(OK元件低阈值)
		bool m_lesstin_extract = false;//少锡(确定提取自定义区域的色度参数并更改默认阈值)
		bool m_lesstin_extract_reback;//少锡(是否恢复手动提取的色度参数阈值, 恢复为默认值)
		double m_lesstin_redundancy_val;//少锡(手动提取的色度参数的冗余比例)

		/// <summary>
		/// 空焊检测类型
		/// </summary>
		ColorStandard m_EmptyWelding_colorstand;//空焊(正常焊的颜色标准)
		int m_EmptyWelding_returnValue;//空焊检测--返回值
		//ReturnValue m_EmptyWelding_retVal;//空焊检测类型--注册
		//ReturnValue m_EmptyWelding_retRes;//空焊检测类型--测试
		int m_EmptyWelding_JudgeHigh;//空焊(OK元件高阈值)
		int m_EmptyWelding_JudgeLow;//空焊(OK元件低阈值)
		bool m_EmptyWelding_extract = false;//空焊(确定提取自定义区域的色度参数并更改默认阈值)
		bool m_EmptyWelding_extract_reback;//空焊(是否恢复手动提取的色度参数阈值, 恢复为默认值)
		double m_EmptyWelding_redundancy_val;//空焊(手动提取的色度参数的冗余比例)

		/// <summary>
		/// 虚焊检测类型
		/// </summary>
		ColorStandard m_VirtualSol_colorstand;//虚焊(正常焊的颜色标准)
		int m_VirtualSol_returnValue;//虚焊检测--返回值
		//ReturnValue m_VirtualSol_retVal;//虚焊检测类型--注册
		//ReturnValue m_VirtualSol_retRes;//虚焊检测类型--测试
		int m_VirtualSol_JudgeHigh;//虚焊(OK元件高阈值)
		int m_VirtualSol_JudgeLow;//虚焊(OK元件低阈值)
		bool m_VirtualSol_extract = false;//虚焊(确定提取自定义区域的色度参数并更改默认阈值)
		bool m_VirtualSol_extract_reback;//虚焊(是否恢复手动提取的色度参数阈值, 恢复为默认值)
		double m_VirtualSol_redundancy_val;//虚焊(手动提取的色度参数的冗余比例)

		/// <summary>
		/// 少锡界面公共
		/// </summary>
		int m_return_val;//返回值, 检测焊锡位置存在几种缺陷(少锡、空焊、虚焊)
		int m_judgeHigh;//判断上限(少锡界面的缺陷, 默认为0)
		int m_judgeLow;//判断下限(少锡界面的缺陷, 默认为0)

		PinRect m_detectedRect;//待检测框
		PinRect m_positionRect;//定位框
		PinRect m_crossRect;//重叠区域的待检测框
		PinRect m_manualRect;//自定义抽取参数框(与待检测框和定位框无关联)

		//TODO:声明为static???
		std::vector<int> m_overallImg;//界面传入的整体图像
		//TODO:没有封装为一个函数的形式？
		std::vector<int> m_outdisplayImg;//以供输出显示的图像(界面调用)
	public:
		int m_overallImg_width;//界面传入的整体图像宽(传入图像时设置)
		int m_overallImg_height;//界面传入的整体图像高

	public:

		/// <summary>
		/// 少锡检测方法
		/// </summary>	
		inline ColorStandard& get_lesstin_colorstand(void) { return m_lesstin_colorstand; }
		inline void set_lesstin_colorstand(ColorStandard val) { m_lesstin_colorstand = val; }

		inline int get_lesstin_returnValue(void) { return m_lesstin_returnValue; }
		inline void set_lesstin_returnValue(int val) { m_lesstin_returnValue = val; }

		//inline ReturnValue get_lesstin_retVal(void) { return m_lesstin_retVal; }
		//inline void set_lesstin_retVal(ReturnValue val) { m_lesstin_retVal = val; }

		//inline ReturnValue get_lesstin_retRes(void) { return m_lesstin_retRes; }
		//inline void set_lesstin_retRes(ReturnValue val) { m_lesstin_retRes = val; }

		inline int getlesstin_JudgeHigh(void) { return m_lesstin_JudgeHigh; }
		inline void setlesstin_JudgeHigh(int val) { m_lesstin_JudgeHigh = val; }

		inline int getlesstin_JudgeLow(void) { return m_lesstin_JudgeLow; }
		inline void setlesstin_JudgeLow(int val) { m_lesstin_JudgeLow = val; }

		inline bool get_lesstin_extract(void) { return m_lesstin_extract; }
		inline void set_lesstin_extract(bool val) { m_lesstin_extract = val; }

		inline bool get_lesstin_extract_reback(void) { return m_lesstin_extract_reback; }
		inline void set_lesstin_extract_reback(bool val) { m_lesstin_extract_reback = val; }

		inline double get_lesstin_redundancy_val(void) { return m_lesstin_redundancy_val; }
		inline void set_lesstin_redundancy_val(double val) { m_lesstin_redundancy_val = val; }

		/// <summary>
		/// 空焊检测方法
		/// </summary>
		inline ColorStandard& get_EmptyWelding_colorstand(void) { return m_EmptyWelding_colorstand; }
		inline void set_EmptyWelding_colorstand(ColorStandard val) { m_EmptyWelding_colorstand = val; }

		inline int get_EmptyWelding_returnValue(void) { return m_EmptyWelding_returnValue; }
		inline void set_EmptyWelding_returnValue(int val) { m_EmptyWelding_returnValue = val; }

		//inline ReturnValue get_EmptyWelding_retVal(void) { return m_EmptyWelding_retVal; }
		//inline void set_EmptyWelding_retVal(ReturnValue val) { m_EmptyWelding_retVal = val; }

		//inline ReturnValue get_EmptyWelding_retRes(void) { return m_EmptyWelding_retRes; }
		//inline void set_EmptyWelding_retRes(ReturnValue val) { m_EmptyWelding_retRes = val; }

		inline int getEmptyWelding_JudgeHigh(void) { return m_EmptyWelding_JudgeHigh; }
		inline void setEmptyWelding_JudgeHigh(int val) { m_EmptyWelding_JudgeHigh = val; }

		inline int getEmptyWelding_JudgeLow(void) { return m_EmptyWelding_JudgeLow; }
		inline void setEmptyWelding_JudgeLow(int val) { m_EmptyWelding_JudgeLow = val; }

		inline bool get_EmptyWelding_extract(void) { return m_EmptyWelding_extract; }
		inline void set_EmptyWelding_extract(bool val) { m_EmptyWelding_extract = val; }

		inline bool get_EmptyWelding_extract_reback(void) { return m_EmptyWelding_extract_reback; }
		inline void set_EmptyWelding_extract_reback(bool val) { m_EmptyWelding_extract_reback = val; }

		inline double get_EmptyWelding_redundancy_val(void) { return m_EmptyWelding_redundancy_val; }
		inline void set_EmptyWelding_redundancy_val(double val) { m_EmptyWelding_redundancy_val = val; }

		/// <summary>
		/// 虚焊检测方法
		/// </summary>
		inline ColorStandard& get_VirtualSol_colorstand(void) { return m_VirtualSol_colorstand; }
		inline void set_VirtualSol_colorstand(ColorStandard val) { m_VirtualSol_colorstand = val; }

		inline int get_VirtualSol_returnValue(void) { return m_VirtualSol_returnValue; }
		inline void set_VirtualSol_returnValue(int val) { m_VirtualSol_returnValue = val; }

		//inline ReturnValue get_VirtualSol_retVal(void) { return m_VirtualSol_retVal; }
		//inline void set_VirtualSol_retVal(ReturnValue val) { m_VirtualSol_retVal = val; }
		//
		//inline ReturnValue get_VirtualSol_retRes(void) { return m_VirtualSol_retRes; }
		//inline void set_VirtualSol_retRes(ReturnValue val) { m_VirtualSol_retRes = val; }

		inline int getVirtualSol_JudgeHigh(void) { return m_VirtualSol_JudgeHigh; }
		inline void setVirtualSol_JudgeHigh(int val) { m_VirtualSol_JudgeHigh = val; }

		inline int getVirtualSol_JudgeLow(void) { return m_VirtualSol_JudgeLow; }
		inline void setVirtualSol_JudgeLow(int val) { m_VirtualSol_JudgeLow = val; }

		inline bool get_VirtualSol_extract(void) { return m_VirtualSol_extract; }
		inline void set_VirtualSol_extract(bool val) { m_VirtualSol_extract = val; }

		inline bool get_VirtualSol_extract_reback(void) { return m_VirtualSol_extract_reback; }
		inline void set_VirtualSol_extract_reback(bool val) { m_VirtualSol_extract_reback = val; }

		inline double get_VirtualSol_redundancy_val(void) { return m_VirtualSol_redundancy_val; }
		inline void set_VirtualSol_redundancy_val(double val) { m_VirtualSol_redundancy_val = val; }

		/// <summary>
		/// 少锡界面公共接口
		/// </summary>
		inline int get_return_val(void) { return m_return_val; }
		inline void set_return_val(int val) { m_return_val = val; }

		inline int getjudgeHigh(void) { return m_judgeHigh; }
		inline void setjudgeHigh(int val) { m_judgeHigh = val; }

		inline int getjudgeLow(void) { return m_judgeLow; }
		inline void setjudgeLow(int val) { m_judgeLow = val; }

		inline std::vector<int>& get_overallImg(void) { return m_overallImg; }
		inline void set_overallImg(std::vector<int> val) { m_overallImg.assign(val.begin(), val.end()); }

		inline std::vector<int>& get_outdisplayImg(void) { return m_outdisplayImg; }
		inline void set_outdisplayImg(std::vector<int> val) { m_outdisplayImg.assign(val.begin(), val.end()); }

		inline PinRect get_detectedRect(void) { return m_detectedRect; }
		inline void set_detectedRect(PinRect val) { m_detectedRect = val; }

		inline PinRect get_positionRect(void) { return m_positionRect; }
		inline void set_positionRect(PinRect val) { m_positionRect = val; }

		inline PinRect get_crossRect(void) { return m_crossRect; }
		inline void set_crossRect(PinRect val) { m_crossRect = val; }

		inline PinRect get_manualRect(void) { return m_manualRect; }
		inline void set_manualRect(PinRect val) { m_manualRect = val; }

		inline PinModechoose get_PinModechoose(void) { return m_PinModechoose; }
		inline void set_PinModechoose(PinModechoose val) { m_PinModechoose = val; }

	};
	typedef std::shared_ptr<PINParam> PINParamPtr;
	typedef std::shared_ptr<const PINParam> PINParamConstPtr;

	/// <summary>
	/// DistanceParam
	/// </summary>
	class AS_EXPORTS DistanceParam : public AOIAlgorithmParam {
	public:
		template <class Archive>
		friend void boost::serialization::serialize(Archive& ar, DistanceParam& val, const unsigned int version);

		DistanceParam();
		DistanceParam& operator=(DistanceParam& ref);

		int stanedge;
		int birthre;
	private:
	};
	typedef std::shared_ptr<DistanceParam> DistanceParamPtr;
	typedef std::shared_ptr<const DistanceParam> DistanceParamConstPtr;

	/// <summary>
	/// Compare参数
	/// </summary>
	class AS_EXPORTS CompareParam : public AOIAlgorithmParam {
	public:
		template <class Archive>
		friend void boost::serialization::serialize(Archive& ar, CompareParam& val, const unsigned int version);

		CompareParam();
		~CompareParam() {};
		CompareParam& operator=(CompareParam& ref);

		struct CompareRect {
			int left_top_x;
			int left_top_y;
			int right_down_x;
			int right_down_y;
		};

	private:
		int m_brightness;			   //亮度
		int m_contrast;				   //对比度
		int m_grayDiff;				   //极性与非极性区域的灰度差值
		bool m_displaySwitch = false;  //显示效果控件
		bool m_polaritySwitch = false; //极性控件
		CompareRect m_polarityRect;    //极性区域ROI
		int m_score_high;              //高阈值
		int m_score_low;               //低阈值


	public:
		int m_gray;					   //灰度(仅用作显示相关处理后的灰度值显示, 不用于注册和测试时的传递)
		inline void setbrightness(int val) { m_brightness = val; }
		inline int getbrightness(void) { return m_brightness; }

		inline void setcontrast(int val) { m_contrast = val; }
		inline int getcontrast(void) { return m_contrast; }

		inline void setgrayDiff(int val) { m_grayDiff = val; }
		inline int getgrayDiff(void) { return m_grayDiff; }

		inline void setdisplaySwitch(int val) { m_displaySwitch = val; }
		inline int getdisplaySwitch(void) { return m_displaySwitch; }

		inline void setpolaritySwitch(int val) { m_polaritySwitch = val; }
		inline int getpolaritySwitch(void) { return m_polaritySwitch; }

		inline void setpolarityRect(CompareRect val) { m_polarityRect = val; }
		inline CompareRect getpolarityRect(void) { return m_polarityRect; }

		inline void setscore_high(int val) { m_score_high = val; }
		inline int getscore_high(void) { return m_score_high; }

		inline void setscore_low(int val) { m_score_low = val; }
		inline int getscore_low(void) { return m_score_low; }
	};
	typedef std::shared_ptr<CompareParam> CompareParamPtr;
	typedef std::shared_ptr<const CompareParam> CompareParamConstPtr;

	/// <summary>
	/// OCV参数
	/// </summary>
	class  AS_EXPORTS OCVParam : public AOIAlgorithmParam
	{
	public:
		OCVParam();
		~OCVParam() {};
		OCVParam& operator=(OCVParam& ref);

		template <class Archive>
		friend void boost::serialization::serialize(Archive& ar, OCVParam& val, const unsigned int version);
	public:

		enum  ImgType
		{
			clear = 1,
			obscure1 = 2,
			obscure2 = 3,
			obscure3 = 4,
			OCI = 5,
			OCR = 6,
		};

		enum FilterLevels { //滤波级别
			Level0 = 0,
			Level1 = 1,
			Level2 = 2,
			Level3 = 3,
			Level4 = 4,
			Level5 = 5
		};

		struct OCVRect {
			int left_top_x;
			int left_top_y;
			int right_down_x;
			int right_down_y;
		};

	private:
		ImgType m_imgtype;			//检测模式
		FilterLevels m_filterlevel;	//滤波级别
		int m_brightness;			//亮度
		int m_contrast;				//对比度
		int m_gray;					//灰度
		int m_BinaThreshold;		//二值化阈值(预先设定上下限为100 10)
		double m_matchAngle;		//最佳匹配角度
		double m_matchscore;		//匹配分数
		double m_char_matchRatio;	//单个字符的匹配成功占比(0-100)
		int m_clContourNumThre;		//封闭轮廓的像素数目阈值
		bool m_enhancedDetectState; //是否进行加强检测
		double m_zoomVal;           //放大倍数(0.5 0.75 1.0 1.25 1.5 2)

		double m_allCharRatio;      //所有深粉色字符占总像素数量比例
		int m_standImgWidth;		//标准图像宽
		int m_standImgHeight;		//标准图像高

		std::vector<std::vector<std::pair<int, int>>> m_InitContours;//默认参数下提取的字符轮廓
		std::vector<OCVRect> m_stand_char_rect;//注册标准图像中的所有字符的最小外接矩形图像

	public:

		inline double getallCharRatio() { return m_allCharRatio; }
		inline void setallCharRatio(double val) { m_allCharRatio = val; }

		inline std::vector<std::vector<std::pair<int, int>>> getInitContours(void) { return m_InitContours; }
		inline void setInitContours(std::vector<std::vector<std::pair<int, int>>> val) { m_InitContours.assign(val.begin(), val.end()); }

		inline FilterLevels getFilterLevels(void) { return m_filterlevel; }
		inline void setFilterLevels(FilterLevels val) { m_filterlevel = val; }

		inline double getzoomVal() { return m_zoomVal; }
		inline void setzoomVal(double val) { m_zoomVal = val; }

		inline bool getenhancedDetectState() { return m_enhancedDetectState; }
		inline void setenhancedDetectState(bool val) { m_enhancedDetectState = val; }

		inline int getclosedContourNum() { return m_clContourNumThre; }
		inline void setclosedContourNum(int val) { m_clContourNumThre = val; }

		inline double getCharMatchRatio() { return m_char_matchRatio; }
		inline void setCharMatchRatio(double val) { m_char_matchRatio = val; }

		inline int getBinaThreshold() { return m_BinaThreshold; }
		inline void setBinaThreshold(int val) { m_BinaThreshold = val; }

		inline int getStandWeight() { return m_standImgWidth; }
		inline void setStandWeight(int val) { m_standImgWidth = val; }

		inline int getStandHeight() { return m_standImgHeight; }
		inline void setStandHeight(int val) { m_standImgHeight = val; }

		inline double getMatchAngle() { return m_matchAngle; }
		inline void setMatchAngle(double val) { m_matchAngle = val; }

		inline double getMatchScore() { return m_matchscore; }
		inline void setMatchScore(double val) { m_matchscore = val; }

		inline std::vector<OCVRect> getStandCharRectImg() { return m_stand_char_rect; }
		inline void setStandCharRectImg(std::vector<OCVRect> val) {
			m_stand_char_rect.assign(val.begin(), val.end());
		}

		inline ImgType getImgType() { return m_imgtype; }
		inline void setImgType(ImgType val) { m_imgtype = val; }

		inline int getbrightness() { return m_brightness; }
		inline void Setbrightness(int val) { m_brightness = val; }

		inline int getcontrast() { return m_contrast; }
		inline void Setcontrast(int val) { m_contrast = val; }

		inline int getgray() { return m_gray; }
		inline void Setgray(int val) { m_gray = val; }

	};
	typedef std::shared_ptr<OCVParam> OCVParamPtr;
	typedef std::shared_ptr<const OCVParam> OCVParamConstPtr;

	/// <summary>
	//代码实现
	/// GLUE
	/// </summary>
	class AS_EXPORTS GLUEParam : public AOIAlgorithmParam
	{
	public:
		template <class Archive>
		friend void boost::serialization::serialize(Archive& ar, GLUEParam& val, const unsigned int version);

		struct GLUERect {
			int left_top_x;
			int left_top_y;
			int right_down_x;
			int right_down_y;
		};
	private:
		int m_red_threshold;              // 红色阈值
		int m_green_threshold;            // 绿色阈值
		int m_inten_threshold;            // 亮度阈值
		int m_horizontal_offset;      // 水平分割线偏移值
		int m_vertical_offset;        // 竖直分割线偏移值
		double m_judge_low;               // 默认判定参数-低(OK)
		double m_judge_high;              // 默认判定参数-高(OK)
		int m_glue_return_Value;          // 返回值
		std::vector<int> m_outdisplayImg; // 输出的二值图像以作显示

	public:
		std::vector<int>m_manual_glueImg; // 用户手动框选的标准红胶图像(界面传入)
		int m_manual_width;
		int m_manual_height;
	public:
		GLUEParam();
		~GLUEParam() {};

		GLUEParam& operator=(GLUEParam& ref);

		inline std::vector<int>& getoutdisplayImg(void) { return m_outdisplayImg; }
		inline void setoutdisplayImg(std::vector<int> val) {
			m_outdisplayImg.assign(val.begin(), val.end());
		}

		inline int get_Red_Threshold(void) { return m_red_threshold; }
		inline void Set_Red_Threshold(int val) { m_red_threshold = val; }

		inline int get_Green_Threshold(void) { return m_green_threshold; }
		inline void Set_Green_Threshold(int val) { m_green_threshold = val; }

		inline int get_Inten_Threshold(void) { return m_inten_threshold; }
		inline void Set_Inten_Threshold(int val) { m_inten_threshold = val; }

		inline int get_Horizontal_Offset(void) { return m_horizontal_offset; }
		inline void Set_Horizontal_Offset(int val) { m_horizontal_offset = val; }

		inline int get_Vertical_Offset(void) { return m_vertical_offset; }
		inline void Set_Vertical_Offset(int val) { m_vertical_offset = val; }

		inline double get_Judge_Low(void) { return m_judge_low; }
		inline void Set_Judge_Low(double val) { m_judge_low = val; }

		inline double get_Judge_High(void) { return m_judge_high; }
		inline void Set_Judge_High(double val) { m_judge_high = val; }

		inline int get_GLUE_Return_Value(void) { return m_glue_return_Value; }
		inline void Set_GLUE_Return_Value(int val) { m_glue_return_Value = val; }

	};
	typedef std::shared_ptr<GLUEParam> GLUEParamPtr;
	typedef std::shared_ptr<const GLUEParam> GLUEParamConstPtr;

	/// <summary>
	/// ICParam
	/// </summary>
	class AS_EXPORTS ICParam : public AOIAlgorithmParam {
	public:
		ICParam();
		~ICParam() {};
	public:
		enum ICDefectType
		{
			CHECK_LOCKATION = 0,		//引脚定位
			CHECK_LENGTH =1,			//长度检查
			CHECK_FAULTY =2,				//虚焊检查
			CHECK_EMPTY = 3,				//空焊检查
			CHECK_CIRCUIT = 4,			//短路检查
		};

	private:
		int m_lead_num;				//引脚数
		double m_lead_width;			//脚宽
		double m_lead_length;			//脚长
		double m_lead_gap;				//脚间距
		double m_lower_boundary;   //下边界
		double m_upper_boundary;  //上边界
	public:
		inline int& get_Lead_Num(void) { return m_lead_num; }
		inline void Set_Lead_Num(int& val) { m_lead_num = val; }

		inline double& get_Lead_Width(void) { return m_lead_width; }
		inline void Set_Lead_Width(double& val) { m_lead_width = val; }

		inline double& get_Lead_Length(void) { return m_lead_length; }
		inline void Set_Lead_Length(double& val) { m_lead_length = val; }

		inline double& get_Lead_Gap(void) { return m_lead_gap; }
		inline void Set_Lead_Gap(double& val) { m_lead_gap = val; }

		inline double& get_Lower_Boundary(void) { return m_lower_boundary; }
		inline void Set_Lower_Boundary(double& val) { m_lower_boundary = val; }

		inline double& get_Upper_Boundary(void) { return m_upper_boundary; }
		inline void Set_Upper_Boundary(double& val) { m_upper_boundary = val; }
	};
	typedef std::shared_ptr<ICParam> ICParamPtr;
	typedef std::shared_ptr<const ICParam> ICParamConstPtr;	

	/// <summary>
	/// PadplaceParam
	/// </summary>
	class AS_EXPORTS PadplaceParam : public AOIAlgorithmParam
	{
	public:
		PadplaceParam() { this->SetAlgorithmTypeData(AOI_Algorithm_Type::Padplace); };

		template <class Archive>
		friend void boost::serialization::serialize(Archive& ar, PadplaceParam& val, const unsigned int version);
	};
	typedef std::shared_ptr<PadplaceParam> PadplaceParamPtr;
	typedef std::shared_ptr<const PadplaceParam> PadplaceParamConstPtr;

	/// <summary>
	/// ShortParam
	/// </summary>
	class AS_EXPORTS ShortParam : public AOIAlgorithmParam
	{
	public:
		template <class Archive>
		friend void boost::serialization::serialize(Archive& ar, ShortParam& val, const unsigned int version);
		
		ShortParam();
		~ShortParam() {};
		ShortParam& operator=(ShortParam& ref);

		enum class BackGroundNum
		{
			BACKGROUND_ZEROTH,
			BACKGROUND_FIRST,
			BACKGROUND_SECOND
		};

		enum class ExtractColor						// 抽色
		{
			FILTERING_DARKNESS = 0,				// 滤暗色
			FILTERING_BRIGHTNESS = 1,			// 滤亮色
			EXTRACT_FILTERING_DARKNESS = 2,		// 抽色后滤暗色
			EXTRACT_FILTERING_BRIGHTNESS = 3	// 抽后滤亮色
		};

		enum class ColorSelect						//操作模式选择
		{
			 m_proj=0,				// 选择投影
			 m_extract				// 选择抽色
		};

		struct PreProcessData
		{
			int m_blue_channel_low = 40;   // 蓝色下限
			int m_green_channel_low = 120;  // 绿色下限
			int m_red_channel_low = 180;    // 红色下限
			int m_brightness_high = 255;     // 亮度上限

			PreProcessData(int bcl, int gcl, int rcl, int bl) : m_blue_channel_low(bcl), m_green_channel_low(gcl), m_red_channel_low(rcl), m_brightness_high(bl) {}
			PreProcessData() {}
		};

		struct ExtractMode
		{
			bool m_background_1;		// 背景1
			bool m_background_2;		// 背景2
			bool m_pretreatment;		// 预处理
			bool m_need_pretreatment;	// 需要预处理

			ExtractMode(int b1, int b2, int p, int np) : m_background_1(b1), m_background_2(b2), m_pretreatment(p), m_need_pretreatment(np) {}
			ExtractMode() {}
		};

		/// <summary>
		/// 颜色抽取值
		/// </summary>
		struct ColorRange
		{
			//红色范围
			int m_nRedLow = 0;
			int m_nRedHigh = 180;
			//绿色范围
			int m_nGreenLow = 0;
			int m_nGreenHigh = 180;
			//蓝色范围
			int m_nBlueLow = 0;
			int m_nBlueHigh = 180;
			//亮度范围
			int m_nGrayLow = 0;
			int m_nGrayHigh = 255;
			ColorRange(int rLow, int rHigh, int gLow, int gHigh, int bLow, int bHigh, int iLow, int iHigh) :m_nRedLow(rLow), m_nRedHigh(rHigh), m_nGreenLow(gLow), m_nGreenHigh(gHigh), m_nBlueLow(bLow), m_nBlueHigh(bHigh),m_nGrayLow(iLow), m_nGrayHigh(iHigh) { }
			ColorRange() = default;
		};

	private:
		// 投影输入
		int m_mini_width;					// 最小宽度
		int m_project_threshold;			// 投影阈值
		int m_diff_threshold;				// 差异阈值

		bool m_allow_auto_calculate;		// 是否允许自动计算


		// 投影输出
		int m_diff_current;					// 差异当前值

		int m_average_brightness;			// 平均亮度
		int m_straight_thread_num;			// 直通线数
		int m_straight_thread_num_current;	// 当前值


		// 抽色输入
		BackGroundNum m_background_num;		// 确定背景数
		ExtractColor m_extract_color;		// 确定抽色方式
		PreProcessData m_preprocess_data;	// 确定预处理的参数
		ExtractMode m_extract_mode;			// 抽色模式选择
		ColorRange m_color_range_1;			// 背景1抽取的颜色
		ColorRange m_color_range_2;			// 背景2抽取的颜色
		ColorSelect m_ColorSelect;			// 操作模式选择

		// 观察输入
		bool m_observe;


	public:
		// 投影输入
		
		inline int& get_Mini_Width(void) { return m_mini_width; }
		inline void Set_Mini_Width(int val) { m_mini_width = val; }

		inline int& get_Project_Threshold(void) { return m_project_threshold; }
		inline void Set_Project_Threshold(int val) { m_project_threshold = val; }

		inline int& get_Diff_Threshold(void) { return m_diff_threshold; }
		inline void Set_Diff_Threshold(int val) { m_diff_threshold = val; }

		inline bool& get_Allow_Auto_Calculate(void) { return m_allow_auto_calculate; }
		inline void Set_Allow_Auto_Calculate(bool val) { m_allow_auto_calculate = val; }


		// 投影输出
		inline int& get_Diff_Current(void) { return m_diff_current; }
		inline void Set_Diff_Current(int val) { m_diff_current = val; }

		inline int& get_Average_Brightness(void) { return m_average_brightness; }
		inline void Set_Average_Brightness(int val) { m_average_brightness = val; }

		inline int& get_Straight_Thread_Num(void) { return m_straight_thread_num; }
		inline void Set_Straight_Thread_Num(int val) { m_straight_thread_num = val; }

		inline int& get_Straight_Thread_Num_Current(void) { return m_straight_thread_num_current; }
		inline void Set_Straight_Thread_Num_Current(int val) { m_straight_thread_num_current = val; }

		//操作模式选择
		inline ColorSelect& getColorSelect(void) { return m_ColorSelect; }
		inline void SetColorSelect(ColorSelect val) { m_ColorSelect = val; }
		// 背景数
		inline BackGroundNum& getBackGroundNum(void) { return m_background_num; }
		inline void SetBackGroundNum(BackGroundNum val) { m_background_num = val; }
		// 抽色
		inline ExtractColor& getExtractColor(void) { return m_extract_color; }
		inline void SetExtractColor(ExtractColor val) { m_extract_color = val; }
		// 预处理数据
		inline PreProcessData& getPreProcessData(void) { return m_preprocess_data; }
		inline void SetPreProcessData(PreProcessData val) { m_preprocess_data = val; }
		// 抽色模式
		inline ExtractMode& getExtractMode(void) { return m_extract_mode; }
		inline void SetExtractMode(ExtractMode val) { m_extract_mode = val; }
		// 背景1抽取的颜色
		inline ColorRange& getColorRange1(void) { return m_color_range_1; }
		inline void SetColorRange1(ColorRange val) { m_color_range_1 = val; }
		// 背景2抽取的颜色
		inline ColorRange& getColorRange2(void) { return m_color_range_2; }
		inline void SetColorRange2(ColorRange val) { m_color_range_2 = val; }


		// 观察输入
		inline bool& get_Observe(void) { return m_observe; }
		inline void Set_Observe(bool val) { m_observe = val; }
	};
	typedef std::shared_ptr<ShortParam> ShortParamPtr;
	typedef std::shared_ptr<const ShortParam> ShortParamConstPtr;

	/// <summary>
	/// OtherParam
	/// </summary>
	class AS_EXPORTS OtherParam : public AOIAlgorithmParam
	{
	public:
	private:
		int m_brightness;        // 亮度
		int m_contrast;		    //  对比度
		int m_enhance;          //  增强
		int m_gray;                 //  灰度
		int m_detlength;        //  检测长度
		int m_learnnum;		   //   学习次数
	public:
		template <class Archive>
		friend void boost::serialization::serialize(Archive& ar, OtherParam& val, const unsigned int version);
		OtherParam();
		~OtherParam() {};

		OtherParam& operator=(OtherParam& ref);

		inline int getbrightness() { return m_brightness; }
		inline void Setbrightness(int val) { m_brightness = val; }

		inline int getcontrast() { return m_contrast; }
		inline void Setcontrast(int val) { m_contrast = val; }

		inline int getgray() { return m_gray; }
		inline void Setgray(int val) { m_gray = val; }

		inline int getenhance() { return m_enhance; }
		inline void Setenhance(int val) { m_enhance = val; }

		inline int getdetlength() { return m_detlength; }
		inline void Setdetlength(int val) { m_detlength = val; }

		inline int getlearnnum() { return m_learnnum; }
		inline void Setlearnnum(int val) { m_learnnum = val; }
	};
	typedef std::shared_ptr<OtherParam> OtherParamPtr;
	typedef std::shared_ptr<const OtherParam> OtherParamConstPtr;

	/// <summary>
	/// ALOffsetParam
	/// </summary>
	class AS_EXPORTS ALOffsetParam : public AOIAlgorithmParam
	{
	public:
		ALOffsetParam() { this->SetAlgorithmTypeData(AOI_Algorithm_Type::ALOffset); };

		template <class Archive>
		friend void boost::serialization::serialize(Archive& ar, ALOffsetParam& val, const unsigned int version);
	};
	typedef std::shared_ptr<ALOffsetParam> ALOffsetParamPtr;
	typedef std::shared_ptr<const ALOffsetParam> ALOffsetParamConstPtr;

	/// <summary>
	/// CrestParam
	/// </summary>
	class AS_EXPORTS CrestParam : public AOIAlgorithmParam
	{
	public:
		template <class Archive>
		friend void boost::serialization::serialize(Archive& ar, CrestParam& val, const unsigned int version);
		CrestParam() { this->SetAlgorithmTypeData(AOI_Algorithm_Type::Crest); };
		virtual~CrestParam() {};
	public:
		// 波峰焊检测项
		enum CrestDefectType
		{
			CHECK_LOCKATION = 0,		//定位
			CHECK_LEAD = 1,					//引脚
			CHECK_POOR = 2,				    //少锡
			CHECK_EXCESS= 3,		        //包锡
			CHECK_Solder = 4,				    //气孔
		};

		// 焊盘极性
		enum PadPolarity
		{
			NonPolarity = 1,
			Polarity = 2,
			NonDirectional = 3,
		};

		// 焊盘形状
		enum PadShape
		{
			ellipse = 1,
			rectangle = 2,
		};
	};
	typedef std::shared_ptr<CrestParam> CrestParamPtr;
	typedef std::shared_ptr<const CrestParam> CrestParamConstPtr;

	/// <summary>
	/// HoleParam
	/// </summary>
	class AS_EXPORTS HoleParam : public AOIAlgorithmParam
	{
	public:
		HoleParam() { this->SetAlgorithmTypeData(AOI_Algorithm_Type::Hole); };

		template <class Archive>
		friend void boost::serialization::serialize(Archive& ar, HoleParam& val, const unsigned int version);
	};
	typedef std::shared_ptr<HoleParam> HoleParamPtr;
	typedef std::shared_ptr<const HoleParam> HoleParamConstPtr;

	/// <summary>
	/// Barcode算法
	/// </summary>
	class AS_EXPORTS BarcodeParam : public AOIAlgorithmParam {
	public:
		template <class Archive>
		friend void boost::serialization::serialize(Archive& ar, BarcodeParam& val, const unsigned int version);
		BarcodeParam();
		~BarcodeParam() {};
		BarcodeParam& operator=(BarcodeParam& ref);

	public:
		/// <summary>
		/// 条码类别
		/// </summary>
		enum BarcodeType
		{
			Industrial_25 = 1,
			Interleaved_25 = 2,
			Code_39 = 3,
			Code_128 =4,
			EAN_13 = 5,
			EAN_8 = 6,
			Data_Matrix_ECC_200 = 7,
			QR_Code = 8,
			PDF_417 = 9,
		};

	private:
		BarcodeType m_barcodetype;                    // 条码类型
		double m_scope;                               // 范围
		double m_size;	                              // 大小
		double m_length;                              // 条码长度
	public:

		inline BarcodeType& get_Barcodetype(void) { return m_barcodetype; }
		inline void Set_Barcodetype(BarcodeType val) { m_barcodetype = val; }

		inline double& get_Scope(void) { return m_scope; }
		inline void Set_Scope(int val) { m_scope = val; }

		inline double& get_Size(void) { return m_size; }
		inline void Set_Size(int val) { m_size = val; }

		inline double& get_Length(void) { return m_length; }
		inline void Set_Length(int val) { m_length = val; }

	};
	typedef std::shared_ptr<BarcodeParam> BarcodeParamPtr;
	typedef std::shared_ptr<const BarcodeParam> BarcodeParamConstPtr;
}

#endif