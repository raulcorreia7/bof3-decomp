#include "start_08.h"

/* Updates the start menu's ability order list: the group and entry cursors, the
 * selected ability's description, the confirm that learns it or opens the
 * character's ability list, and the cancel. */
MATCH void func_801D78FC(void) {
    MenuPanelTask* panel;
    u8*            abilities;
    s32            buttons;
    u8             ability_id;
    u8             old_cursor;
    u8             i;
    s8             result;

    Menu_DrawClutStrip(g_WindowClut);
    panel = &g_UiPanelTasks[MENU_START_PANEL_CURSOR_FRAME];
    if (g_BattleMessageState == 0) {
        panel->active = 1;
        D_801485E7    = 0;
        g_UiPanelTasks[19].pos.vx    = D_801483C4;
        g_UiPanelTasks[19].pos.vy    = D_801483C6 + D_8014857A * 54;
    } else {
        panel->active = 0;
    }
    abilities  = Party_GetAbilities(D_8014857A, D_8014857B, 0);
    ability_id = abilities[D_8014857C];
    panel      = &g_UiPanelTasks[16];
    D_801484CC = g_Abilities[ability_id].description;
    if (g_BattleChoicePhase == 0) {
        D_80148624 = 1;
        D_80148628 = D_80148574 + 7;
        D_8014862A = D_80148576 + (D_8014857C * 13 + 26);
    } else {
        D_80148624 = 0;
    }
    buttons = INPUT_REPEATED(g_PadStates[0].pressed, INPUT_DIRECTIONAL);
    if (D_801ED648 != 2) {
        if (buttons & PADLleft) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
            panel->unk_09 = 0x32;
            if ((s8)--panel->unk_0B < 0) {
                panel->unk_0B = 3;
            }
            D_8014857C = s_SkillOrderCursors[g_PartyCursor][D_8014857B];
        } else if (buttons & PADLright) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
            panel->unk_09 = 0x31;
            if (++panel->unk_0B >= 4) {
                panel->unk_0B = 0;
            }
            D_8014857C = s_SkillOrderCursors[g_PartyCursor][D_8014857B];
        }
    }
    old_cursor = panel->unk_0C;
    if (buttons & PADLup) {
        if (old_cursor != 0) {
            panel->unk_0C = old_cursor - 1;
        }
    } else if ((buttons & PADLdown) && old_cursor < 9) {
        panel->unk_0C = old_cursor + 1;
    }
    if (old_cursor != panel->unk_0C) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    }
    s_SkillOrderCursors[g_PartyCursor][D_8014857B] = D_8014857C;
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        ability_id = Party_GetAbilities(panel->unk_0A, panel->unk_0B, 0)[panel->unk_0C];
        if (ability_id == 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
            return;
        }
        if (D_801ED648 == 0) {
            if (func_801AF5B0(panel->unk_08, panel->unk_0A, ability_id) == 0) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
                return;
            }
            if (g_Abilities[ability_id].targeting_flags & ABILITY_TARGET_FLAG_ALL) {
                result     = func_801E7D20(g_CharSlot[g_PartyFieldOrder[panel->unk_0A]], 0, Party_GetAbilities(panel->unk_0A, panel->unk_0B, 0)[panel->unk_0C], 0);
                D_801ED654 = result;
                if (result == 1 || result == 5) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 9));
                    return;
                }
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
                return;
            }
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
            for (i = 0; i < Party_CountOrder(PARTY_ORDER_FIELD); i++) {
                panel                       = &g_UiPanelTasks[MENU_START_PANEL_ITEMS + i];
                panel->unk_0A               = i;
                panel->panel                = 6;
                panel->active               = 1;
                panel->state                = 10;
                panel->pos.vx               = 320;
                panel->mode                 = 0;
                panel->unk_0B               = 0;
                panel->unk_0C               = 0;
                panel->pos.vy               = i * 54 + 62;
                g_UiPanelTasks[i + 4].state = 7;
            }
            g_BattleChoicePhase = 4;
            D_80148624          = 1;
            g_UiPanelTasks[19].active          = 0;
            D_80148658[0]       = 0;
            D_8014857D          = D_8014857C;
            D_80148651++;
        } else if (func_801AF5B0(panel->unk_08, panel->unk_0A, ability_id) != 0) {
            D_8014865B = 0;
            D_8014857D = D_8014857C;
            D_80148651 += 2;
        } else {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
            return;
        }
    } else if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        D_8014857C = 0xFF;
        D_8014857D = 0xFF;
        D_80148651--;
    } else {
        return;
    }
}
