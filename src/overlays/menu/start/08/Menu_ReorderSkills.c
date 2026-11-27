#include "start_08.h"

extern s8 D_80148656;

/* func_801D8908 */
MATCH void Menu_ReorderSkills(void) {
    SkillOrder* rec;
    u8*         table;
    u8*         entry;
    u8*         cursor;
    u8*         pick;
    u8          value;
    u8          next;
    u8          type;
    u32         buttons;
    u8*         index;
    u8*         flag;

    Menu_DrawClutStrip(g_WindowClut);
    flag                                                      = &g_UiPanelTasks[18].unk_0C;
    *flag                                                     = 0;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].active            = 1;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].pos.vx            = g_UiPanelTasks[16].pos.vx + 7;
    g_UiPanelTasks[MENU_START_PANEL_CURSOR].pos.vy            = (u16)(g_UiPanelTasks[16].pos.vy + ((g_UiPanelTasks[16].unk_0C * 0xD) + 0x1A));
    rec                                                       = (SkillOrder*)((u8*)flag - DECOMP_OFFSETOF(SkillOrder, unk_54));
    index                                                     = Party_GetAbilities(g_UiPanelTasks[16].unk_0A, g_UiPanelTasks[16].unk_0B, 0);
    pick                                                      = index + g_UiPanelTasks[16].unk_0C;
    type                                                      = *pick;
    g_UiPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = g_Abilities[type].description;
    buttons                                                   = INPUT_GetRepeatedButtons(g_PadStates[0].pressed & (PADLup | PADLdown | PADL1 | PADR1));
    value                                                     = g_UiPanelTasks[16].unk_0C;
    if (buttons & PADLup) {
        if (value != 0) {
            next                      = value - 1;
            g_UiPanelTasks[16].unk_0C = next;
        }
    } else if ((buttons & PADLdown) && value < 9) {
        next                      = value + 1;
        g_UiPanelTasks[16].unk_0C = next;
    }
    table  = s_SkillOrderCursors[D_80148656];
    entry  = table + g_UiPanelTasks[16].unk_0B;
    *entry = g_UiPanelTasks[16].unk_0C;
    if (value != rec->cursor) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    }
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if (rec->swap_cursor == GAME_NONE) {
            if (*(Party_GetAbilities(rec->party_slot, rec->ability_group, 0) + rec->cursor)) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
                rec->swap_cursor = rec->cursor;
            } else {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
            }
        } else {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
            cursor = Party_GetAbilities(rec->party_slot, rec->ability_group, 0) + rec->swap_cursor;
            Menu_SwapBytes3(cursor, Party_GetAbilities(rec->party_slot, rec->ability_group, 0) + rec->cursor);
            rec->swap_cursor = 0xFF;
        }
    } else if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        if (rec->swap_cursor == GAME_NONE) {
            D_80148652 -= 1;
        } else {
            rec->swap_cursor = 0xFF;
        }
    }
}
