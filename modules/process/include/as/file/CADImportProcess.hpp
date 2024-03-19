#ifndef AS_CADIMPORTPROCESS_H
#define AS_CADIMPORTPROCESS_H

#include "as/CommonCore.hpp"
#include "as/CADCore.hpp"
#include "as/Common/UiCallback.h"

namespace as
{
	//�ı�����
	enum class TEXT_TYPE
	{
		TEXT_ANSI = 0,
		TEXT_UTF8 = 1,
		TEXT_UTF8_BOM = 2,
		TEXT_UTF16_LE = 3,
		TEXT_UTF16_BE = 4,
		TEXT_UNKNOW = 5,
	};
	//CAD�ؼ���
	enum class SectionKey
	{
		VERSION = 0,
		PCB = 1, 
		BOARD = 2, 
		PLACEMENT = 3
	};
	//�����txt����
	enum class ColunmName
	{
		Reference = 0,           //PCBԪ��λ�ú�
		CompId = 1,				 //Ԫ��ID
		CompName = 2,			 //Ԫ����
		BlockID = 3,			 //��ID
		ArrayID = 4,			 //ƴ��ID
		Skip = 5,				 //����
		Position_x = 6,			 //����x
		Position_y = 7,			 //����y 
		Angle = 8,               //�Ƕ�
		BodyPosition_x = 9,		 //��ѡ����x
		BodyPosition_y = 10,	 //��ѡ����y
		BodyWidth = 11,			 //��ѡ��
		BodyHeight = 12,		 //��ѡ��
		SmtName = 13,			 //��Ƭ����
		SlotNum = 14,			 //վλ��
		NozzleName = 15,		 //�����
		RoiWidth = 16,			 //��ѡ��
		RoiHeight = 17,			 //��ѡ��
		PL = 18,			     //PL
		Comment = 19,			 //�����ѡ��
		FidShape = 20,			 //Mark����״
		Fid1X = 21,				 //Mark��1����
		Fid1Y = 22,
		Fid2X = 23,				 //Mark��2����
		Fid2Y = 24,
		MachineNo = 25,			 //������
		PartName = 26,			 //Ԫ����
		Description = 27,		 //����
		Position_z = 28          //���Ӻ��
	};

	//cad��ת�Ƕ�
	enum class Cad_Rotation
	{
		_0 = 0,
		_90 = 1, 
		_180 = 2,
		_270 = 3
	};
	//�̶ȵ�λ
	enum class Unit
	{
		Inches = 0, 
		Mils = 1, 
		Centimeters = 2, 
		Micrometers = 3, 
		Micron = 4, 
		SCALE = 5
	};

	class AS_EXPORTS CADImportProcess
	{
	public:
		CADImportProcess::CADImportProcess();

		
	private:
		
	};
}

#endif