#include "area155_13.h"

MATCH void func_801F2C04(void) {
    u8* record;
    u8  i;

    if (g_UIMessageChoice == 2) {
        record = Item_GetRecord(ITEM_CATEGORY_WEAPON, WEAPON_HOMING_BOMB);
        for (i = 0; i < 12; i++) {
            g_TextVariables[0][i] = record[i];
        }
        D_801490E4[0] = 0;
        if (Item_Add(ITEM_CATEGORY_WEAPON, WEAPON_HOMING_BOMB, 1, 0) & BYTE_MASK) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0x06));
            g_UIMessageRequest = MSG_AREA155_ROBOT_GIVES_ITEM;
        } else {
            g_UIMessageRequest = MSG_AREA155_010;
        }
    } else {
        g_UIMessageRequest = MSG_AREA155_010;
    }
    SYS_SetFlag(D_80144EF0, 1);
}
