#ifndef _PROJECTOR_DEF_HPP_
#define _PROJECTOR_DEF_HPP_


namespace as
{
    enum class PROJECTORID{
        PROJECTOR_ID_NONE = 0x00,
        PROJECTOR_ID_UP = 0x01,
        PROJECTOR_ID_DOWN = 0x02,
        PROJECTOR_ID_LEFT = 0x04,
        PROJECTOR_ID_RIGHT = 0x08
    };

    inline int PROJECTORID2Int(PROJECTORID id) {
        switch (id)
        {
        case PROJECTORID::PROJECTOR_ID_UP:
            return 0;
        case PROJECTORID::PROJECTOR_ID_DOWN:
            return 1;
        case PROJECTORID::PROJECTOR_ID_LEFT:
            return 2;
        case PROJECTORID::PROJECTOR_ID_RIGHT:
            return 3;
        default:
            return -1;
        }

        return -1;
    };

    inline PROJECTORID Int2PROJECTORID(int _num) {
        switch (_num)
        {
        case 0:
            return PROJECTORID::PROJECTOR_ID_UP;
        case 1:
            return PROJECTORID::PROJECTOR_ID_DOWN;
        case 2:
            return PROJECTORID::PROJECTOR_ID_LEFT;
        case 3:
            return PROJECTORID::PROJECTOR_ID_RIGHT;
        default:
            return PROJECTORID::PROJECTOR_ID_NONE;
        }
        return PROJECTORID::PROJECTOR_ID_NONE;
    };
}

#endif