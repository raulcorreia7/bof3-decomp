#include "area114_13.h"

MATCH s32 func_801F2E48(void) {
    s32 message;
    s32 result;

    switch (D_801454EC) {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        default:
            message = 1;
            goto set_result_1;

        case 10: {
            u8* flags = g_SceneEventFlags;

            if (SYS_TestFlag(flags, 0x96) != 0) {
                goto set_msg5_result1;
            }
            Item_Add(ITEM_CAT_OPTION, OPTION_ITEM_DING_FROG, 3, 0);
            SYS_SetFlag(flags, 0x96);
            message = 2;
            result  = 5;
            break;
        }

        case 11: {
            u8* flags = g_SceneEventFlags;

            if (SYS_TestFlag(flags, 0x97) != 0) {
                message = 5;
                goto set_result_1;
            }
            Item_Add(ITEM_CAT_OPTION, OPTION_ITEM_MASTERS_ROD, 1, 0);
            SYS_SetFlag(flags, 0x97);
            message = 6;
            result  = 5;
            if (SYS_TestFlag(flags, 0x96) == 0) {
                Item_Add(ITEM_CAT_OPTION, OPTION_ITEM_DING_FROG, 3, 0);
                SYS_SetFlag(flags, 0x96);
                message = 3;
            }
            break;
        }

        case 12:
            if (Item_VitalHas(VITAL_ITEM_FOUNTAIN_PEN) != 0) {
                message = 5;
                goto set_result_1;
            }
            Item_VitalAdd(VITAL_ITEM_FOUNTAIN_PEN);
            message = 8;
            {
                u8* flags = g_SceneEventFlags;

                if (SYS_TestFlag(flags, 0x97) == 0) {
                    Item_Add(ITEM_CAT_OPTION, OPTION_ITEM_MASTERS_ROD, 1, 0);
                    SYS_SetFlag(flags, 0x97);
                    message = 7;
                    if (SYS_TestFlag(flags, 0x96) == 0) {
                        Item_Add(ITEM_CAT_OPTION, OPTION_ITEM_DING_FROG, 3, 0);
                        SYS_SetFlag(flags, 0x96);
                        message = 4;
                    }
                }
            }
            result = 10;
            break;
    }

    goto tail;

set_msg5_result1:
    message = 5;
set_result_1:
    result = 1;

tail:
    Message_StartAreaMessage(message);
    g_GameStateIndex = 2;
    return result;
}
