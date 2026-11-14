#include "start_08.h"

extern s8 D_80148656;

/* The stride of one D_801CA71E kind entry. */
#define START08_TYPE_STRIDE 0x14

MATCH void func_801D8908(void) {
    SkillOrder* rec;
    u8*         table;
    u8*         entry;
    u8*         cursor;
    u8*         pick;
    u8          value;
    u8          next;
    u8          kind;
    u32         buttons;
    u8*         index;
    u8*         flag;

    Menu_DrawClutStrip(D_80144953);
    flag                                                        = &D_801485C4;
    *flag                                                       = 0;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].active            = 1;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].pos.x             = g_MenuPanelTasks[16].pos.x + 7;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR].pos.y             = g_MenuPanelTasks[16].pos.y + ((g_MenuPanelTasks[16].unk_0C * 0xD) + 0x1A);
    rec                                                         = (SkillOrder*)((u8*)flag - DECOMP_OFFSETOF(SkillOrder, unk_54));
    index                                                       = Party_GetAbilities(g_MenuPanelTasks[16].unk_0A, g_MenuPanelTasks[16].unk_0B, 0);
    pick                                                        = index + g_MenuPanelTasks[16].unk_0C;
    kind                                                        = *pick;
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = *(u16*)(D_801CA71E + kind * START08_TYPE_STRIDE);
    buttons                                                     = INPUT_GetRepeatedButtons(g_InputPressed & (PADLup | PADLdown | PADL1 | PADR1));
    value                                                       = g_MenuPanelTasks[16].unk_0C;
    if (buttons & PADLup) {
        if (value != 0) {
            next                        = value - 1;
            g_MenuPanelTasks[16].unk_0C = next;
        }
    } else if ((buttons & PADLdown) && value < 9) {
        next                        = value + 1;
        g_MenuPanelTasks[16].unk_0C = next;
    }
    table  = s_SkillOrderCursors[D_80148656];
    entry  = table + g_MenuPanelTasks[16].unk_0B;
    *entry = g_MenuPanelTasks[16].unk_0C;
    if (value != rec->cursor) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        if (rec->swap_cursor == GAME_NONE) {
            if (*(Party_GetAbilities(rec->party_slot, rec->ability_group, 0) + rec->cursor)) {
                SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
                rec->swap_cursor = rec->cursor;
            } else {
                SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
            }
        } else {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
            cursor = Party_GetAbilities(rec->party_slot, rec->ability_group, 0) + rec->swap_cursor;
            Menu_SwapBytes3(cursor, Party_GetAbilities(rec->party_slot, rec->ability_group, 0) + rec->cursor);
            rec->swap_cursor = 0xFF;
        }
    } else if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        if (rec->swap_cursor == GAME_NONE) {
            D_80148652 -= 1;
        } else {
            rec->swap_cursor = 0xFF;
        }
    }
}
