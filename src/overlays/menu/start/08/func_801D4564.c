#include "start_08.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801D4564(void) {
    s32 tmp0;
    u32 tmp1;
    u32 tmp2;
    u8  val1;

    Menu_DrawClutStrip(D_80144953);
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id =
        Item_GetDescription(g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0A, D_801C893C[D_8014850E][g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0C]);
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].active = 1;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].pos.x  = (u16)g_MenuPanelTasks[MENU_START_PANEL_ITEMS].pos.x + 7;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].pos.y =
        (u16)g_MenuPanelTasks[MENU_START_PANEL_ITEMS].pos.y + (((g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0C - g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0B) * 0xD) + 0x1A);
    tmp0 = INPUT_GetRepeatedButtons(g_InputPressed & (PADLup | PADLdown | PADL1 | PADR1));
    if (tmp0 & PADLup) {
        if (g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0C != 0) {
            g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0C -= 1;
        }
        if ((u8)g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0C < (u8)g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0B) {
            g_MenuPanelTasks[MENU_START_PANEL_ITEMS].u.list.scroll = 0xF0;
        }
    } else if (tmp0 & PADLdown) {
        if ((u8)g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0C < 0x1FU) {
            g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0C += 1;
        }
        if ((s32)g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0C >= (g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0B + 9)) {
            g_MenuPanelTasks[MENU_START_PANEL_ITEMS].u.list.scroll = 0x10;
        }
    } else if (tmp0 & 4) {
        tmp1 = g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0B & BYTE_MASK;
        if (tmp1 == 0) {
            g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0C = 0;
        } else if (tmp1 < 9U) {
            g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0C -= g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0B;
            g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0B = 0;
        } else {
            g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0C -= 9;
            val1 = g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0B - 9;
            goto block_22; /* retail branch */
        }
    } else if (tmp0 & 8) {
        tmp2 = g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0B & BYTE_MASK;
        if (tmp2 == 0x17) {
            g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0C = 0x1F;
        } else {
            if (tmp2 >= 0xFU) {
                g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0C = (D_80148510 + 0x17) - g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0B;
                val1                                            = 0x17;
            } else {
                g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0C += 9;
                val1 = g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0B + 9;
            }
        block_22:
            g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0B = val1;
        }
    }
    s_ChoiceMenuCursors[D_80148504.group] = D_80148504.group_cursor;
    s_ChoiceMenuValues[D_80148504.group]  = D_80148504.group_first;
    if (g_MenuPanelTasks[MENU_START_PANEL_ITEMS].unk_0C != D_80148504.group_cursor) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
    }
    if ((D_80148504.confirm_gate == 0) && (g_InputMasks[MENU_INPUT_CANCEL] & g_InputPressed)) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        D_80148504.group               = 0U;
        D_80148504.group_cursor        = 0xFFU;
        FIELD(s8, (&D_80148504), 0xDu) = 0xFF;
        g_MenuStep.sub_step -= 7;
        D_80148504.group_first = (u8)*s_ChoiceMenuValues;
    }
}
#else
INCLUDE_ASM(func_801D4564);
#endif
