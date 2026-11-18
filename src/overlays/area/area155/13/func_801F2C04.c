#include "area155_13.h"

MATCH void func_801F2C04(void) {
    u8* record;
    u8  i;

    if (g_MessageChoice == 2) {
        record = Item_GetRecord(ITEM_CATEGORY_WEAPON, WEAPON_HOMING_BOMB);
        for (i = 0; i < 12; i++) {
            g_TextVariables[0][i] = record[i];
        }
        D_801490E4[0] = 0;
        if (Item_Add(ITEM_CATEGORY_WEAPON, WEAPON_HOMING_BOMB, 1, 0) & BYTE_MASK) {
            SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 0x06));
            g_MessageRequest = MSG_011;
        } else {
            g_MessageRequest = MSG_010;
        }
    } else {
        g_MessageRequest = MSG_010;
    }
    SYS_SetFlag(D_80144EF0, 1);
}
