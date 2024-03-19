#include "as/core/DefectDef.hpp"

namespace as
{
    std::string SPI_Defect2Name(SPI_Defect _ng)
    {
        std::string ng_name;
        switch (_ng)
        {
		case SPI_Defect::Normal:
		{
			ng_name = "Normal";
			break;
		}
		case SPI_Defect::UnNormal:
		{
			ng_name = "UnNormal";
			break;
		}
        case SPI_Defect::Bridge:
        {    
            ng_name = "Bridge";
            break;
        }
        case SPI_Defect::Insufficient:
        {
            ng_name = "Bridge";
            break;
        }
        case SPI_Defect::Excessive:
        {
            ng_name = "Excessive";
            break;
        }
        case SPI_Defect::Shape:
        {
            ng_name = "Shape";
            break;
        }
        case SPI_Defect::Position:
        {
            ng_name = "Position";
            break;
        }
        case SPI_Defect::GoldTab:
        {
            ng_name = "GoldTab";
            break;
        }
        case SPI_Defect::UpperHeight:
        {
            ng_name = "UpperHeight";
            break;
        }
        case SPI_Defect::LowerHeight:
        {
            ng_name = "LowerHeight";
            break;
        }
        case SPI_Defect::HighArea:
        {
            ng_name = "HighArea";
            break;
        }
        case SPI_Defect::LowArea:
        {
            ng_name = "LowArea";
            break;
        }
        case SPI_Defect::Coplanarity:
        {
            ng_name = "Coplanarity";
            break;
        }
        case SPI_Defect::Smear:
        {
            ng_name = "Smear";
            break;
        }
        default:
            ng_name = "UnNormal";
            break;
        }
        return ng_name;
    };

    std::string AOI_Defect2Name(AOI_DefectType _ng)
	{
		std::string ng_name;
		switch (_ng)
		{
		case AOI_DefectType::Offset:
		{
			ng_name = "Offset";
			break;
		}
		case AOI_DefectType::MissingPart:
		{
			ng_name = "MissingPart";
			break;
		}
		case AOI_DefectType::WrongPart:
		{
			ng_name = "WrongPart";
			break;
		}
		case AOI_DefectType::PoorSolder:
		{
			ng_name = "PoorSolder";
			break;
		}
		case AOI_DefectType::EmptySolder:
		{
			ng_name = "EmptySolder";
			break;
		}
		case AOI_DefectType::Reverse:
		{
			ng_name = "Reverse";
			break;
		}
		case AOI_DefectType::Rotate:
		{
			ng_name = "Rotate";
			break;
		}
		case AOI_DefectType::Contamination:
		{
			ng_name = "Contamination";
			break;
		}
		case AOI_DefectType::Damage:
		{
			ng_name = "Damage";
			break;
		}
		case AOI_DefectType::ExcessSolder:
		{
			ng_name = "ExcessSolder";
			break;
		}
		case AOI_DefectType::ExtraPart:
		{
			ng_name = "ExtraPart";
			break;
		}
		case AOI_DefectType::FaultySolder:
		{
			ng_name = "FaultySolder";
			break;
		}
		case AOI_DefectType::GlueOverflow:
		{
			ng_name = "GlueOverflow";
			break;
		}
		case AOI_DefectType::LeadFloat:
		{
			ng_name = "LeadFloat";
			break;
		}
		case AOI_DefectType::SolderBridge:
		{
			ng_name = "SolderBridge";
			break;
		}
		case AOI_DefectType::Tombstone:
		{
			ng_name = "Tombstone";
			break;
		}
		case AOI_DefectType::Upturned:
		{
			ng_name = "Upturned";
			break;
		}
		case AOI_DefectType::Size:
		{
			ng_name = "Size";
			break;
		}
		default:
			ng_name = "";
			break;
		}
		return ng_name;
	};
} // namespace as
