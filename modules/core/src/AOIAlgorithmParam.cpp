#include "as/AOIAlgorithmParam.hpp"

namespace as
{
    AOIAlgorithmParam::AOIAlgorithmParam(void)
	{
		m_eAlgorithmType = AOI_Algorithm_Type::TOC;
		m_eColorChannel = ColorChannel::RGB;
		m_eDefecType = AOI_DefectType::PoorSolder;
		m_eColorMethod = ColorMethod::average;
		m_eDetectionType = AOI_Detection_Type::BodyDot;

		m_blkSearchScope.dX = 0.5;
		m_blkSearchScope.dY = 0.5;
		m_blkSearchScope.dAngle = 6;

		m_blkAllowOffset.dOffsetX = 0.5;
		m_blkAllowOffset.dOffsetY = 0.5;
		m_blkAllowOffset.dAngle = 6;

		m_eReturnValue.m_nReturnValueHigh = 100;
		m_eReturnValue.m_nReturnValueLow = 0;
		m_eReturnValue.return_value = 100;

		m_eReturnStandValue.m_nReturnValueHigh = 100;
		m_eReturnStandValue.m_nReturnValueLow = 0;
		m_eReturnStandValue.return_value = 100;

		m_ColorStandard.m_nBlueHigh = 100;
		m_ColorStandard.m_nBlueLow = 0;
		m_ColorStandard.m_nGreenHigh = 100;
		m_ColorStandard.m_nGreenLow = 0;
		m_ColorStandard.m_nRedHigh = 100;
		m_ColorStandard.m_nRedLow = 0;
		m_ColorStandard.m_nGrayHigh = 100;
		m_ColorStandard.m_nGrayLow = 0;

		m_bAlgorithmUseFlag = false;
		m_Resolution = 15;
	}

	AOIAlgorithmParam& AOIAlgorithmParam::operator=(AOIAlgorithmParam& ref)
	{
		this->m_eDefecType = ref.getDefectTypeData();
		this->m_eAlgorithmType = ref.getAlgorithmTypeData();
		this->m_eColorChannel = ref.getColorChannelData();
		this->m_eColorMethod = ref.getColorMethodData();
		this->m_eReturnValue = ref.getReturnValue();
		this->m_eReturnStandValue = ref.getReturnStandValue();
		this->m_eDetectionType = ref.getDetectionTypeData();
		this->m_blkSearchScope = ref.getSearchScopeData();
		this->m_blkAllowOffset = ref.getAllowOffsetData();
		this->m_ColorStandard = ref.getColorStandard();
		this->m_bAlgorithmUseFlag = ref.getAlgorithmUseFlag();
		this->m_Resolution = ref.getResolution();
		return *this;
	}

	void AOIAlgorithmParam::SetAlgorithmParam(AOIAlgorithmParam& val)
	{
		this->SetAlgorithmTypeData(val.getAlgorithmTypeData());
		this->SetColorChannelData(val.getColorChannelData());
		this->SetColorMethodData(val.getColorMethodData());
		this->SetDetectionTypeData(val.getDetectionTypeData());
		this->SetSearchScopeData(val.getSearchScopeData());
		this->SetAllowOffsetData(val.getAllowOffsetData());
		this->SetReturnValue(val.getReturnValue());
		this->SetReturnStandValue(val.getReturnStandValue());
		this->SetColorStandard(val.getColorStandard());
		this->SetResolution(val.getResolution());
	}

	TOCParam::TOCParam(void)
	{
		this->SetAlgorithmTypeData(AOI_Algorithm_Type::TOC);
		this->SetColorChannelData(ColorChannel::RGB);
		this->SetColorMethodData(ColorMethod::average);
		this->SetDetectionTypeData(AOI_Detection_Type::BodyDot);	

		m_InitColorStand.m_Init_red_high = 180;
		m_InitColorStand.m_Init_red_low = 0;
		m_InitColorStand.m_Init_green_high = 180;
		m_InitColorStand.m_Init_green_low = 0;
		m_InitColorStand.m_Init_blue_high = 180;
		m_InitColorStand.m_Init_blue_low = 0;
		m_InitColorStand.m_Init_gray_high = 255;
		m_InitColorStand.m_Init_gray_low = 0;
		m_InitColorStand.m_judge_score_high = 20;
		m_InitColorStand.m_judge_score_low = 0;
		m_template_grayMean = 10;
		m_Force_Register = false;
	}

	TOCParam& TOCParam::operator=(TOCParam& ref)
	{
		this->SetAlgorithmTypeData(ref.getAlgorithmTypeData());
		this->SetColorChannelData(ref.getColorChannelData());
		this->SetColorMethodData(ref.getColorMethodData());
		this->SetDetectionTypeData(ref.getDetectionTypeData());
		this->SetSearchScopeData(ref.getSearchScopeData());
		this->SetAllowOffsetData(ref.getAllowOffsetData());
		this->SetReturnValue(ref.getReturnValue());
		this->SetReturnStandValue(ref.getReturnStandValue());
		this->SetColorStandard(ref.getColorStandard());
		this->SetlgorithmUseFlag(ref.getAlgorithmUseFlag());

		this->m_InitColorStand = ref.getInitColorStand();
		this->m_template_grayMean = ref.getgrayMean();
		this->m_Force_Register = ref.getForcedRegister();
		return *this;
	}

	MatchParam::MatchParam(void)
	{
		this->SetAlgorithmTypeData(AOI_Algorithm_Type::Match);
		this->SetColorChannelData(ColorChannel::RGB);
		this->SetColorMethodData(ColorMethod::average);
		this->SetDetectionTypeData(AOI_Detection_Type::BodyDot);
		this->SetReturnStandValue(ReturnValue(ERROR_LEVEL::NG, -1, 0, 60, 0));
		this->Setbrightness(0);
		this->Setcontrast(100);
		this->Setenhance(1);
		this->Setgray(0);
		this->Setvalue(40);
	}

	MatchParam& MatchParam::operator=(MatchParam& ref)
	{
		this->SetAlgorithmTypeData(ref.getAlgorithmTypeData());
		this->SetColorChannelData(ref.getColorChannelData());
		this->SetColorMethodData(ref.getColorMethodData());
		this->SetDetectionTypeData(ref.getDetectionTypeData());
		this->SetSearchScopeData(ref.getSearchScopeData());
		this->SetAllowOffsetData(ref.getAllowOffsetData());
		this->SetReturnValue(ref.getReturnValue());
		this->SetReturnStandValue(ref.getReturnStandValue());
		this->SetColorStandard(ref.getColorStandard());
		this->SetlgorithmUseFlag(ref.getAlgorithmUseFlag());

		this->m_StandardTemplateData = ref.getStandardTemplateData();
		this->m_correctmode = ref.getCorrectMode();
		this->m_brightness = ref.getbrightness();
		this->m_contrast = ref.getcontrast();
		this->m_enhance = ref.getenhance();
		this->m_gray = ref.getgray();
		return *this;
	}

	Match2Param::Match2Param(void)
	{
		this->SetAlgorithmTypeData(AOI_Algorithm_Type::Match2);
		this->SetColorChannelData(ColorChannel::RGB);
		this->SetColorMethodData(ColorMethod::average);
		this->SetDetectionTypeData(AOI_Detection_Type::BodyDot);

		mplate_colorchannel = ColorChannel::RGB;
		mplate_colormethod = ColorMethod::average;
		m_Dx = 0;
		m_Dy = 0;
	}

	Match2Param& Match2Param::operator=(Match2Param& ref)
	{
		this->SetAlgorithmTypeData(ref.getAlgorithmTypeData());
		this->SetColorChannelData(ref.getColorChannelData());
		this->SetColorMethodData(ref.getColorMethodData());
		this->SetDetectionTypeData(ref.getDetectionTypeData());
		this->SetSearchScopeData(ref.getSearchScopeData());
		this->SetAllowOffsetData(ref.getAllowOffsetData());
		this->SetReturnValue(ref.getReturnValue());
		this->SetReturnStandValue(ref.getReturnStandValue());
		this->SetColorStandard(ref.getColorStandard());
		this->SetlgorithmUseFlag(ref.getAlgorithmUseFlag());

		this->m_Dx = ref.getDx();
		this->m_Dy = ref.getDy();
		this->mplate_colorchannel = ref.getplate_ColorChannel();
		this->mplate_colormethod = ref.getplate_ColorMethod();
		return *this;
	}

	PoleParam::PoleParam()
	{
		this->SetAlgorithmTypeData(AOI_Algorithm_Type::Pole);
		StandardArea = 0;
	}

	PoleParam& PoleParam::operator=(PoleParam& ref)
	{
		this->SetAlgorithmTypeData(ref.getAlgorithmTypeData());
		this->SetColorChannelData(ref.getColorChannelData());
		this->SetColorMethodData(ref.getColorMethodData());
		this->SetDetectionTypeData(ref.getDetectionTypeData());
		this->SetSearchScopeData(ref.getSearchScopeData());
		this->SetAllowOffsetData(ref.getAllowOffsetData());
		this->SetReturnValue(ref.getReturnValue());
		this->SetReturnStandValue(ref.getReturnStandValue());
		this->SetColorStandard(ref.getColorStandard());
		this->SetlgorithmUseFlag(ref.getAlgorithmUseFlag());

		this->StandardArea = ref.StandardArea;
		return *this;
	}

	LengthParam::LengthParam(void)
	{
		// 基类中的成员变量初始化
		// 基础信息
		this->SetAlgorithmTypeData(AOI_Algorithm_Type::Length);
		this->SetDetectionTypeData(AOI_Detection_Type::BodyDot);
		this->SetColorChannelData(ColorChannel::RG);
		this->SetColorMethodData(ColorMethod::average);
		this->SetReturnStandValue(ReturnValue(ERROR_LEVEL::NG, -1, 0, 0, 0));

		m_detectDisTAB = DetectDisTAB::innerDis;
		m_binary_threshold = 0;
		m_projection_threshold = 0;
		m_standard_length = 0;
		m_adjust_intensity = 0;
		m_adjust_contrast = 0;
		m_judge_low = 0;
		m_judge_high = 0;
		m_length_return_Value = 0;
	}

	LengthParam& LengthParam::operator=(LengthParam& ref)
	{
		this->SetAlgorithmTypeData(ref.getAlgorithmTypeData());
		this->SetColorChannelData(ref.getColorChannelData());
		this->SetColorMethodData(ref.getColorMethodData());
		this->SetDetectionTypeData(ref.getDetectionTypeData());
		this->SetSearchScopeData(ref.getSearchScopeData());
		this->SetAllowOffsetData(ref.getAllowOffsetData());
		this->SetReturnValue(ref.getReturnValue());
		this->SetReturnStandValue(ref.getReturnStandValue());
		this->SetColorStandard(ref.getColorStandard());
		this->SetlgorithmUseFlag(ref.getAlgorithmUseFlag());

		this->m_detectDisTAB = ref.get_DetectDisTAB();
		this->m_binary_threshold = ref.get_Binary_Threshold();
		this->m_projection_threshold = ref.get_Projection_Threshold();
		this->m_standard_length = ref.get_Standard_Length();
		this->m_adjust_intensity = ref.get_Adjust_Intensity();
		this->m_adjust_contrast = ref.get_Adjust_Contrast();
		this->m_judge_low = ref.get_Length_Judge_Low();
		this->m_judge_high = ref.get_Length_Judge_High();
		this->m_length_return_Value = ref.get_Length_Return_Value();
		return *this;
	}

	HISTOParam::HISTOParam()
	{
		Min_Gray m_min_gray;
		Max_Gray m_max_gray;
		Range_Gray m_range_gray;
		m_min_gray.m_min_upper = 20;
		m_min_gray.m_min_grayAve = 20;
		m_min_gray.m_min_lower = 20;
		m_max_gray.m_max_upper = 20;
		m_max_gray.m_max_grayAve = 2;
		m_max_gray.m_max_lower = 2;
		m_range_gray.m_range_upper = 2;
		m_range_gray.m_range_grayAve = 2;
		m_range_gray.m_range_lower = 2;
		this->SetMinGray(m_min_gray);
		this->SetMaxGray(m_max_gray);
		this->SetRangeGray(m_range_gray);
		this->SetAlgorithmTypeData(AOI_Algorithm_Type::Histogram);

		m_HistoDetectMethod = DetectMethod::Min;
		m_ratio = 0;
		m_Init_Judge_Lower = 0;
		m_Init_Judge_Upper = 0;
		m_total_gray_Ave = 0;
		m_output_gray = 0;
		m_Filter_Level = FilterLevels::Level0;
	}

	HISTOParam& HISTOParam::operator=(HISTOParam& ref)
	{
		this->SetAlgorithmTypeData(ref.getAlgorithmTypeData());
		this->SetColorChannelData(ref.getColorChannelData());
		this->SetColorMethodData(ref.getColorMethodData());
		this->SetDetectionTypeData(ref.getDetectionTypeData());
		this->SetSearchScopeData(ref.getSearchScopeData());
		this->SetAllowOffsetData(ref.getAllowOffsetData());
		this->SetReturnValue(ref.getReturnValue());
		this->SetReturnStandValue(ref.getReturnStandValue());
		this->SetColorStandard(ref.getColorStandard());
		this->SetlgorithmUseFlag(ref.getAlgorithmUseFlag());

		this->m_HistoDetectMethod = ref.getHistoDetectMethod();         
		this->m_ratio = ref.getRatio();
		this->m_Min_Gray = ref.getMinGray();
		this->m_Max_Gray = ref.getMaxGray();
		this->m_Range_Gray = ref.getRangeGray();
		this->m_Init_Judge_Lower = ref.get_Judge_Lower();
		this->m_Init_Judge_Upper = ref.get_Judge_Upper();
		this->m_total_gray_Ave = ref.get_Total_Gray_Ave();
		this->m_output_gray = ref.get_output_gray();
		this->m_Filter_Level = ref.get_Filter_Level();
		this->m_gray_Img = ref.getgray_Img();
		return *this;
	}

	PINParam& PINParam::operator=(PINParam& ref)
	{
		this->SetAlgorithmTypeData(ref.getAlgorithmTypeData());
		this->SetColorChannelData(ref.getColorChannelData());
		this->SetColorMethodData(ref.getColorMethodData());
		this->SetDetectionTypeData(ref.getDetectionTypeData());
		this->SetSearchScopeData(ref.getSearchScopeData());
		this->SetAllowOffsetData(ref.getAllowOffsetData());
		this->SetReturnValue(ref.getReturnValue());
		this->SetReturnStandValue(ref.getReturnStandValue());
		this->SetColorStandard(ref.getColorStandard());
		this->SetlgorithmUseFlag(ref.getAlgorithmUseFlag());

		this->set_PinModechoose(ref.get_PinModechoose());

		this->set_lesstin_colorstand(ref.get_lesstin_colorstand());
		this->set_EmptyWelding_colorstand(ref.get_EmptyWelding_colorstand());
		this->set_VirtualSol_colorstand(ref.get_VirtualSol_colorstand());

		this->setlesstin_JudgeHigh(ref.getlesstin_JudgeHigh());
		this->setlesstin_JudgeLow(ref.getlesstin_JudgeLow());
		this->setEmptyWelding_JudgeHigh(ref.getEmptyWelding_JudgeHigh());
		this->setEmptyWelding_JudgeLow(getEmptyWelding_JudgeLow());
		this->setVirtualSol_JudgeHigh(getVirtualSol_JudgeHigh());
		this->setVirtualSol_JudgeLow(ref.getVirtualSol_JudgeLow());
		this->setjudgeHigh(ref.getjudgeHigh());
		this->setjudgeLow(ref.getjudgeLow());
		this->m_return_val = ref.m_return_val;

		this->set_lesstin_extract(ref.get_lesstin_extract());
		this->set_EmptyWelding_extract(ref.get_EmptyWelding_extract());
		this->set_VirtualSol_extract(ref.get_VirtualSol_extract());

		this->set_lesstin_extract_reback(ref.get_lesstin_extract_reback());
		this->set_EmptyWelding_extract_reback(ref.get_EmptyWelding_extract_reback());
		this->set_VirtualSol_extract_reback(ref.get_VirtualSol_extract_reback());

		this->set_lesstin_redundancy_val(ref.get_lesstin_redundancy_val());
		this->set_EmptyWelding_redundancy_val(ref.get_EmptyWelding_redundancy_val());
		this->set_VirtualSol_redundancy_val(ref.get_VirtualSol_redundancy_val());

		this->set_lesstin_returnValue(ref.get_lesstin_returnValue());
		this->set_EmptyWelding_returnValue(ref.get_EmptyWelding_returnValue());
		this->set_VirtualSol_returnValue(ref.get_VirtualSol_returnValue());

		this->set_detectedRect(ref.get_detectedRect());
		this->set_positionRect(ref.get_positionRect());
		this->set_crossRect(ref.get_crossRect());
		this->set_manualRect(ref.get_manualRect());

		this->set_overallImg(ref.get_overallImg());
		this->set_outdisplayImg(ref.get_outdisplayImg());

		return *this;
	}

	DistanceParam::DistanceParam()
	{
		this->SetAlgorithmTypeData(AOI_Algorithm_Type::Distance);

		stanedge = 0;
		birthre = 0;
	}

	DistanceParam& DistanceParam::operator=(DistanceParam& ref)
	{
		this->SetAlgorithmTypeData(ref.getAlgorithmTypeData());
		this->SetColorChannelData(ref.getColorChannelData());
		this->SetColorMethodData(ref.getColorMethodData());
		this->SetDetectionTypeData(ref.getDetectionTypeData());
		this->SetSearchScopeData(ref.getSearchScopeData());
		this->SetAllowOffsetData(ref.getAllowOffsetData());
		this->SetReturnValue(ref.getReturnValue());
		this->SetReturnStandValue(ref.getReturnStandValue());
		this->SetColorStandard(ref.getColorStandard());
		this->SetlgorithmUseFlag(ref.getAlgorithmUseFlag());

		this->stanedge = ref.stanedge;
		this->birthre = ref.birthre;
		return *this;
	}

	CompareParam::CompareParam()
	{
		this->SetAlgorithmTypeData(AOI_Algorithm_Type::Compare);
	}

	CompareParam& CompareParam::operator=(CompareParam& ref)
	{
		this->SetAlgorithmTypeData(ref.getAlgorithmTypeData());
		this->SetColorChannelData(ref.getColorChannelData());
		this->SetColorMethodData(ref.getColorMethodData());
		this->SetDetectionTypeData(ref.getDetectionTypeData());
		this->SetSearchScopeData(ref.getSearchScopeData());
		this->SetAllowOffsetData(ref.getAllowOffsetData());
		this->SetReturnValue(ref.getReturnValue());
		this->SetReturnStandValue(ref.getReturnStandValue());
		this->SetColorStandard(ref.getColorStandard());
		this->SetlgorithmUseFlag(ref.getAlgorithmUseFlag());

		this->m_brightness = ref.m_brightness;
		this->m_contrast = ref.m_contrast;
		this->m_gray = ref.m_gray;
		this->m_displaySwitch = ref.m_displaySwitch;
		this->m_polaritySwitch = ref.m_polaritySwitch;
		this->m_grayDiff = ref.m_grayDiff;

		return *this;
	}

	OCVParam::OCVParam()
	{
		this->SetAlgorithmTypeData(AOI_Algorithm_Type::OCV);
		m_imgtype = ImgType::clear;
		m_filterlevel = FilterLevels::Level1;
		m_brightness = 0;
		m_contrast = 100;
		m_gray = 1;
		m_BinaThreshold = 2;
		m_matchAngle = 6;
		m_matchscore = 60;
		m_char_matchRatio = 85;
		m_clContourNumThre = 6;
		m_enhancedDetectState = 0;
		m_zoomVal = 1;
		m_standImgWidth = 400;
		m_standImgHeight = 400;
		m_allCharRatio = 100;
		m_InitContours.clear();
		m_stand_char_rect.clear();
	}
	
	OCVParam& OCVParam::operator=(OCVParam& ref)
	{
		this->SetAlgorithmTypeData(ref.getAlgorithmTypeData());
		this->SetColorChannelData(ref.getColorChannelData());
		this->SetColorMethodData(ref.getColorMethodData());
		this->SetDetectionTypeData(ref.getDetectionTypeData());
		this->SetSearchScopeData(ref.getSearchScopeData());
		this->SetAllowOffsetData(ref.getAllowOffsetData());
		this->SetReturnValue(ref.getReturnValue());
		this->SetReturnStandValue(ref.getReturnStandValue());
		this->SetColorStandard(ref.getColorStandard());
		this->SetlgorithmUseFlag(ref.getAlgorithmUseFlag());

		this->m_imgtype = ref.getImgType();
		this->m_brightness = ref.getbrightness();
		this->m_contrast = ref.getcontrast();
		this->m_BinaThreshold = ref.getBinaThreshold();
		this->m_gray = ref.getgray();
		this->m_matchAngle = ref.getMatchAngle();
		this->m_matchscore = ref.getMatchScore();
		this->m_char_matchRatio = ref.getCharMatchRatio();
		this->m_clContourNumThre = ref.getclosedContourNum();
		this->m_enhancedDetectState = ref.getenhancedDetectState();
		this->m_zoomVal = ref.getzoomVal();
		this->m_standImgWidth = ref.getStandWeight();
		this->m_standImgHeight = ref.getStandHeight();
		this->m_filterlevel = ref.getFilterLevels();

		this->m_stand_char_rect = ref.getStandCharRectImg();

		return *this;
	}

	GLUEParam::GLUEParam()
	{
		this->SetAlgorithmTypeData(AOI_Algorithm_Type::Glue);
		m_red_threshold = 0;
		m_green_threshold = 0;
		m_inten_threshold = 0;
		m_horizontal_offset = 0;
		m_vertical_offset = 0;
		m_judge_low = 0;
		m_judge_high = 0;
		m_glue_return_Value = 0;
		m_outdisplayImg.clear();
		m_manual_glueImg.clear();
		m_manual_width = 0;
		m_manual_height = 0;
	}

	GLUEParam& GLUEParam::operator=(GLUEParam& ref)
	{
		this->SetAlgorithmTypeData(ref.getAlgorithmTypeData());
		this->SetColorChannelData(ref.getColorChannelData());
		this->SetColorMethodData(ref.getColorMethodData());
		this->SetDetectionTypeData(ref.getDetectionTypeData());
		this->SetSearchScopeData(ref.getSearchScopeData());
		this->SetAllowOffsetData(ref.getAllowOffsetData());
		this->SetReturnValue(ref.getReturnValue());
		this->SetReturnStandValue(ref.getReturnStandValue());
		this->SetColorStandard(ref.getColorStandard());
		this->SetlgorithmUseFlag(ref.getAlgorithmUseFlag());

		this->m_red_threshold = ref.get_Red_Threshold();
		this->m_green_threshold = ref.get_Green_Threshold();
		this->m_inten_threshold = ref.get_Inten_Threshold();
		this->m_vertical_offset = ref.get_Vertical_Offset();
		this->m_horizontal_offset = ref.get_Horizontal_Offset();
		this->m_judge_low = ref.get_Judge_Low();
		this->m_judge_high = ref.get_Judge_High();
		this->m_glue_return_Value = ref.get_GLUE_Return_Value();
		this->m_manual_glueImg = ref.m_manual_glueImg;
		this->m_manual_width = ref.m_manual_width;
		this->m_manual_height = ref.m_manual_height;

		return *this;
	}

	ICParam::ICParam()
	{
		this->SetAlgorithmTypeData(AOI_Algorithm_Type::Match2);
	}

	ShortParam::ShortParam()
	{
		// 基类中的成员变量初始化
		// 基础信息
		this->SetAlgorithmTypeData(AOI_Algorithm_Type::Short);						// 使用算法
		this->SetDetectionTypeData(AOI_Detection_Type::BodyDot);						// 检测点类别
		// 投影信息
		this->SetColorChannelData(ColorChannel::RGB);							// 通道选择
		this->SetColorMethodData(ColorMethod::average);							// 转灰度算法
		// 返回值
		this->SetReturnStandValue(ReturnValue(ERROR_LEVEL::NG, -1, 0, 0, 0));				// 返回数据

		// 投影输入
		this->SetColorSelect(ShortParam::ColorSelect::m_proj);
		this->Set_Mini_Width(20);
		this->Set_Project_Threshold(76);
		this->Set_Diff_Threshold(17);

		this->Set_Allow_Auto_Calculate(false);

		// 投影输出
		this->Set_Diff_Current(0);

		this->Set_Average_Brightness(0);
		this->Set_Straight_Thread_Num(-1);
		this->Set_Straight_Thread_Num_Current(0);

		// 背景数
		this->SetBackGroundNum(BackGroundNum::BACKGROUND_ZEROTH);
		// 抽色
		this->SetExtractColor(ExtractColor::FILTERING_DARKNESS);
		// 预处理数据
		this->SetPreProcessData(PreProcessData(20, 30, 35, 255));
		// 抽色模式
		this->SetExtractMode(ExtractMode(false, false, true, true));
		// 背景1抽取的颜色
		this->SetColorRange1(ColorRange(0, 180, 0, 180, 0, 180, 0, 255));
		// 背景2抽取的颜色
		this->SetColorRange2(ColorRange(0, 180, 0, 180, 0, 180, 0, 255));

		// 观察输入
		this->Set_Observe(true);
	}

	ShortParam& ShortParam::operator=(ShortParam& ref)
	{
		this->SetAlgorithmTypeData(ref.getAlgorithmTypeData());
		this->SetColorChannelData(ref.getColorChannelData());
		this->SetColorMethodData(ref.getColorMethodData());
		this->SetDetectionTypeData(ref.getDetectionTypeData());
		this->SetSearchScopeData(ref.getSearchScopeData());
		this->SetAllowOffsetData(ref.getAllowOffsetData());
		this->SetReturnValue(ref.getReturnValue());
		this->SetReturnStandValue(ref.getReturnStandValue());
		this->SetColorStandard(ref.getColorStandard());
		this->SetlgorithmUseFlag(ref.getAlgorithmUseFlag());

		this->m_mini_width = ref.get_Mini_Width();
		this->m_project_threshold = ref.get_Project_Threshold();
		this->m_diff_threshold = ref.get_Diff_Threshold();
		this->m_allow_auto_calculate = ref.get_Allow_Auto_Calculate();
		this->m_diff_current = ref.get_Diff_Current();
		this->m_average_brightness = ref.get_Average_Brightness();
		this->m_straight_thread_num = ref.get_Straight_Thread_Num();
		this->m_straight_thread_num_current = ref.get_Straight_Thread_Num_Current();
		this->m_background_num = ref.getBackGroundNum();
		this->m_extract_color = ref.getExtractColor();
		this->m_preprocess_data = ref.getPreProcessData();
		this->m_extract_mode = ref.getExtractMode();
		this->m_color_range_1 = ref.getColorRange1();
		this->m_color_range_2 = ref.getColorRange2();
		this->m_observe = ref.get_Observe();

		return *this;
	}

	OtherParam::OtherParam(void)
	{
		m_brightness = 0;
		m_contrast = 0;
		m_enhance = 0;
		m_gray = 0;
		m_detlength = 0;
		m_learnnum = 0;
		this->SetAlgorithmTypeData(AOI_Algorithm_Type::Other);
		this->SetColorChannelData(ColorChannel::RGB);
		this->SetColorMethodData(ColorMethod::average);
		this->SetDetectionTypeData(AOI_Detection_Type::BodyDot);
		this->SetReturnStandValue(ReturnValue(ERROR_LEVEL::NG, -1, 0, 60, 0));
	}

	OtherParam& OtherParam::operator=(OtherParam& ref)
	{
		this->SetAlgorithmTypeData(ref.getAlgorithmTypeData());
		this->SetColorChannelData(ref.getColorChannelData());
		this->SetColorMethodData(ref.getColorMethodData());
		this->SetDetectionTypeData(ref.getDetectionTypeData());
		this->SetSearchScopeData(ref.getSearchScopeData());
		this->SetAllowOffsetData(ref.getAllowOffsetData());
		this->SetReturnValue(ref.getReturnValue());
		this->SetReturnStandValue(ref.getReturnStandValue());
		this->SetColorStandard(ref.getColorStandard());
		this->SetlgorithmUseFlag(ref.getAlgorithmUseFlag());

		this->m_brightness = ref.getbrightness();
		this->m_contrast = ref.getcontrast();
		this->m_enhance = ref.getenhance();
		this->m_gray = ref.getgray();
		this->m_detlength = ref.getdetlength();
		this->m_learnnum = ref.getlearnnum();
		return *this;
	}

	BarcodeParam::BarcodeParam(void)
	{
		// 基类中的成员变量初始化
		// 基础信息
		this->SetAlgorithmTypeData(AOI_Algorithm_Type::Barcode);
		this->SetDetectionTypeData(AOI_Detection_Type::BodyDot);
		this->SetColorChannelData(ColorChannel::RGB);
		this->SetColorMethodData(ColorMethod::color);
		this->SetReturnStandValue(ReturnValue(ERROR_LEVEL::NG, -1, 0, 0, 0));

		m_barcodetype = BarcodeType::Code_128;
	}

	BarcodeParam& BarcodeParam::operator=(BarcodeParam& ref)
	{
		this->SetAlgorithmTypeData(ref.getAlgorithmTypeData());
		this->SetColorChannelData(ref.getColorChannelData());
		this->SetColorMethodData(ref.getColorMethodData());
		this->SetDetectionTypeData(ref.getDetectionTypeData());
		this->SetSearchScopeData(ref.getSearchScopeData());
		this->SetAllowOffsetData(ref.getAllowOffsetData());
		this->SetReturnValue(ref.getReturnValue());
		this->SetReturnStandValue(ref.getReturnStandValue());
		this->SetColorStandard(ref.getColorStandard());
		this->SetlgorithmUseFlag(ref.getAlgorithmUseFlag());

		this->m_barcodetype = ref.get_Barcodetype();
		this->m_scope = ref.get_Scope();
		this->m_size = ref.get_Size();
		this->m_length = ref.get_Length();

		return *this;
	}
} // namespace as
