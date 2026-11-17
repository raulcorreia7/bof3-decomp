#include "shop_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801DF9EC(void) {
    s32  input;
    s8   selected;
    u8   has_item;
    u16  item_count;
    u16* pressed;

    selected                          = D_801E6260;
    g_MenuPanelTasks[1].unk_0B        = 0xFF;
    g_MenuPanelTasks[0].u.addr.unk_10 = selected + 0x73;
    if (g_MenuPanelTasks[1].state == 0) {
        g_MenuPanelTasks[21].active = 1;
        g_MenuPanelTasks[21].pos.x  = g_MenuPanelTasks[1].pos.x + selected * 0x30;
        g_MenuPanelTasks[21].pos.y  = g_MenuPanelTasks[1].pos.y + 4;
    } else {
        g_MenuPanelTasks[21].active = 0;
    }

    pressed = &g_InputPressed;
    input   = INPUT_GetRepeatedButtons(*pressed & 0xA000);
    if (input & 0xA000) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
        D_801E6260 ^= 1;
    }
    if (*pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        selected = (s8)D_801E6260;
        if (selected != 0) {
            has_item = Item_VitalHas(VITAL_ITEM_FOUNTAIN_PEN);
            if (has_item == 0) {
                item_count = Item_Count(ITEM_CATEGORY_ITEM, ITEM_SKILL_INK, 0);
                if (item_count == 0) {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
                    return;
                }
            }
            has_item = Item_VitalHas(VITAL_ITEM_FOUNTAIN_PEN);
            if (has_item != 0) {
                SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
                g_MenuPanelTasks[2].mode    = 13;
                g_MenuPanelTasks[2].pos.x   = -150;
                g_MenuPanelTasks[2].pos.y   = 116;
                g_MenuPanelTasks[3].mode    = 12;
                g_MenuPanelTasks[2].handler = 7;
                g_MenuPanelTasks[3].handler = 7;
                D_801E625C                  = 0;
                g_MenuPanelTasks[2].state   = 2;
                g_MenuPanelTasks[2].active  = 1;
                g_MenuPanelTasks[3].state   = 2;
                g_MenuPanelTasks[3].active  = 1;
                g_MenuPanelTasks[3].unk_0B  = 0;
                g_MenuPanelTasks[3].flags   = 0;
                g_MenuPanelTasks[3].pos.x   = 320;
                g_MenuPanelTasks[3].pos.y   = 62;
                D_80148652                  = 1;
                g_MenuPanelTasks[2].unk_0A  = D_801E6264[0];
                g_MenuPanelTasks[3].unk_0A  = D_801E6264[0];
                D_80148651++;
                SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
                g_MenuPanelTasks[1].unk_0B = D_801E6260;
                D_80148654                 = 5;
                return;
            }
            D_8014865B = 1;
            D_80148651++;
        } else {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
            g_MenuPanelTasks[4].handler = 7;
            g_MenuPanelTasks[4].mode    = 11;
            g_BattleMessageState        = 3;
            g_MenuPanelTasks[4].active  = 1;
            g_MenuPanelTasks[4].unk_0C  = 0xFF;
            g_MenuPanelTasks[4].unk_0A  = 0;
            g_MenuPanelTasks[4].unk_0B  = 0;
            g_MenuPanelTasks[4].flags   = 0;
            g_MenuPanelTasks[4].pos.x   = -170;
            g_MenuPanelTasks[4].pos.y   = 62;
            D_80148651 += 2;
        }
        g_MenuPanelTasks[1].unk_0B = D_801E6260;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
        D_80148654 = 5;
        D_80148652 = 0;
    } else if (*pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        g_MenuPanelTasks[0].state   = 1;
        g_MenuPanelTasks[1].state   = 1;
        g_MenuPanelTasks[21].active = 0;
        if (!Item_VitalHas(VITAL_ITEM_FOUNTAIN_PEN)) {
            g_MenuPanelTasks[6].state = 1;
        }
        D_80148654 = 5;
        D_80148651 = 4;
    }
}
#else
INCLUDE_ASM(func_801DF9EC);
#endif
