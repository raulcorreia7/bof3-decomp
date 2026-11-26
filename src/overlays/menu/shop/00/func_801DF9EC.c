#include "shop_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801DF9EC(void) {
    s32  input;
    s8   selected;
    u8   has_item;
    u16  item_count;
    u16* pressed;

    selected                        = D_801E6260;
    g_UiPanelTasks[1].unk_0B        = 0xFF;
    g_UiPanelTasks[0].u.addr.unk_10 = selected + 0x73;
    if (g_UiPanelTasks[1].state == 0) {
        g_UiPanelTasks[21].active = 1;
        g_UiPanelTasks[21].pos.vx = g_UiPanelTasks[1].pos.vx + selected * 0x30;
        g_UiPanelTasks[21].pos.vy = g_UiPanelTasks[1].pos.vy + 4;
    } else {
        g_UiPanelTasks[21].active = 0;
    }

    pressed = &g_PadStates[0].pressed;
    input   = INPUT_GetRepeatedButtons(*pressed & (PADLleft | PADLright));
    if (input & (PADLleft | PADLright)) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        D_801E6260 ^= 1;
    }
    if (*pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if (*(s8*)&D_801E6260 != 0) {
            has_item = Item_VitalHas(VITAL_ITEM_FOUNTAIN_PEN);
            if (has_item == 0) {
                item_count = Item_Count(ITEM_CATEGORY_ITEM, ITEM_SKILL_INK, 0);
                if (item_count == 0) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
                    return;
                }
            }
            has_item = Item_VitalHas(VITAL_ITEM_FOUNTAIN_PEN);
            if (has_item == 0) {
                D_80148651++;
                D_8014865B = 1;
            } else {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
                g_UiPanelTasks[2].mode           = 13;
                *(s16*)&g_UiPanelTasks[2].pos.vx = -150;
                g_UiPanelTasks[2].pos.vy         = 116;
                g_UiPanelTasks[3].mode           = 12;
                g_UiPanelTasks[3].unk_0C         = 0xFF;
                g_UiPanelTasks[2].panel          = 7;
                g_UiPanelTasks[3].panel          = 7;
                D_801E625C                       = 0;
                g_UiPanelTasks[2].state          = 2;
                g_UiPanelTasks[2].active         = 1;
                g_UiPanelTasks[3].state          = 2;
                g_UiPanelTasks[3].active         = 1;
                g_UiPanelTasks[3].unk_0B         = 0;
                g_UiPanelTasks[3].flags          = 0;
                g_UiPanelTasks[3].pos.vx         = 320;
                g_UiPanelTasks[3].pos.vy         = 62;
                D_80148652                       = 1;
                g_UiPanelTasks[2].unk_0A         = D_801E6264[0];
                g_UiPanelTasks[3].unk_0A         = D_801E6264[0];
                g_MenuStep.sub_step++;
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
                g_UiPanelTasks[1].unk_0B = D_801E6260;
                D_80148654               = 5;
                return;
            }
        } else {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 4));
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
            g_UiPanelTasks[4].panel          = 7;
            g_UiPanelTasks[4].mode           = 11;
            g_BattleMessageState             = 3;
            g_UiPanelTasks[4].active         = 1;
            g_UiPanelTasks[4].unk_0C         = 0xFF;
            g_UiPanelTasks[4].unk_0A         = 0;
            g_UiPanelTasks[4].unk_0B         = 0;
            g_UiPanelTasks[4].flags          = 0;
            *(s16*)&g_UiPanelTasks[4].pos.vx = -170;
            g_UiPanelTasks[4].pos.vy         = 62;
            g_MenuStep.sub_step += 2;
        }
        g_UiPanelTasks[1].unk_0B = D_801E6260;
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
        D_80148654 = 5;
        D_80148652 = 0;
    } else if (*pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        g_UiPanelTasks[0].state   = 1;
        g_UiPanelTasks[1].state   = 1;
        g_UiPanelTasks[21].active = 0;
        has_item                  = Item_VitalHas(VITAL_ITEM_FOUNTAIN_PEN);
        if (has_item == 0) {
            g_UiPanelTasks[6].state = 1;
        }
        D_80148654 = 5;
        D_80148651 = 4;
    }
}
#else
INCLUDE_ASM(func_801DF9EC);
#endif
