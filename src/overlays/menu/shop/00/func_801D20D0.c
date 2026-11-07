#include "shop_00.h"

/* nonmatching unmeasured: tried panel-task struct members for the flag stores, cursor pointer local, flag row
 * -fno-rerun-cse-after-loop, a search over source rewrites. resume: a source shape that keeps the cursor la out of the
 * prologue and loads the cursor before the store. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D20D0(void) {
    s32 buttons;
    u8  count;
    u8  old;
    u8* cursor;
    s8  i;

    TEXT_SetVariable(0, 0xC, Item_GetRecord(g_ShopItemCategory, g_ShopItemId));
    cursor                         = &D_80148656;
    g_MenuPanelTasks[0].unk_10     = 0x4B;
    g_MenuPanelTasks[21].unk_00[0] = 0;
    g_MenuPanelTasks[20].unk_00[0] = 1;
    D_80148604                     = g_MenuPanelTasks[(s8)*cursor + 3].pos.x.raw;
    D_80148606                     = g_MenuPanelTasks[(s8)*cursor + 3].pos.y.raw;
    count                          = Party_CountOrder(PARTY_ORDER_FIELD);
    buttons                        = INPUT_REPEATED(g_InputPressed, (PADLup | PADLdown));
    old                            = *cursor;
    if (buttons & PADLup) {
        if ((s8)(*cursor = old - 1) < 0) {
            *cursor = count - 1;
        }
    } else if (buttons & PADLdown) {
        if ((s8)(*cursor = old + 1) > (s8)count - 1) {
            *cursor = 0;
        }
    }
    cursor = &D_80148656;
    if ((s8)old != (s8)*cursor) {
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }
    if (g_InputPressed & g_InputMasks[INPUT_SLOT_CONFIRM]) {
        if ((Item_GetEquipability(g_ShopItemCategory, g_ShopItemId) >> g_CharSlot[g_PartyFieldOrder[(s8)*cursor]]) &
            1) {
            for (i = 0; i < (u8)Party_CountOrder(PARTY_ORDER_FIELD); i++) {
                if (i == (s8)D_80148656) {
                    g_MenuPanelTasks[i + 3].state = 3;
                } else {
                    g_MenuPanelTasks[i + 3].state = 1;
                }
            }
            D_80148408         = 1;
            D_80148409         = 7;
            D_8014840A         = 6;
            D_8014840B         = 2;
            *(s16*)&D_8014840C = -0x96;
            D_8014840E         = 0x74;
            D_80148412         = D_80148656;
            SND_PlayCue(EMI_CUE_ID(1, 3));
            D_80148600 = 0;
            D_801E6054 = 0;
            D_80148654 = 5;
            D_80148652 += 1;
        } else {
            SND_PlayCue(EMI_CUE_ID(1, 7));
        }
    } else if (g_InputPressed & g_InputMasks[INPUT_SLOT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        D_80148600 = 0;
        D_80148652 -= 4;
    }
}
#else
INCLUDE_ASM(func_801D20D0);
#endif
