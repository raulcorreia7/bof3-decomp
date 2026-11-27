#include "shop_00.h"

MATCH void func_801E032C(void) {
    s32 input;
    s32 row;
    u8* cell;
    u8* entry;
    u8* cursor;
    u8* index;
    u8  previous;
    s8  next;

    entry      = (u8*)&g_Characters[g_UiPanelTasks[3].unk_0A] + DECOMP_OFFSETOF(Character, abilities.skill) + g_UiPanelTasks[3].unk_0B;
    D_80148340 = g_Abilities[*entry].description;
    if (g_UiPanelTasks[3].state == 0) {
        g_UiPanelTasks[21].active = 1;
        g_UiPanelTasks[21].pos.vx = g_UiPanelTasks[3].pos.vx + 7;
        row                       = g_UiPanelTasks[3].unk_0B * 0xD + 0x1A;
        g_UiPanelTasks[21].pos.vy = g_UiPanelTasks[3].pos.vy + row;
    } else {
        g_UiPanelTasks[21].active = 0;
    }
    input    = INPUT_REPEATED(g_PadStates[0].pressed, INPUT_DIRECTIONAL);
    cursor   = &g_UiPanelTasks[3].unk_0B;
    previous = *cursor;
    if (input & PADLup) {
        next    = previous - 1;
        *cursor = next;
        if (next < 0) {
            *cursor = 0;
        }
    } else if (input & PADLdown) {
        next    = previous + 1;
        *cursor = next;
        if ((u8)next >= 0xA) {
            *cursor = 9;
        }
    }
    index = &g_UiPanelTasks[3].unk_0B;
    if (previous != *index) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    }
    g_UiPanelTasks[3].unk_0C = 0xFF;
    cell                     = (u8*)&g_Characters[g_UiPanelTasks[3].unk_0A] + DECOMP_OFFSETOF(Character, abilities.skill) + *index;
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        u8* step;

        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
        g_UiPanelTasks[3].unk_0C = *index;
        step                     = &D_80148652;
        (*step)++;
        return;
    }
    if (g_PadStates[0].pressed & PADRleft) {
        if (*cell != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
            Char_AbilityAdd(*cell, 0, 1, 0);
            *cell = 0;
            return;
        }
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
        return;
    }
    if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        u8* step;

        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        g_UiPanelTasks[2].state  = 2;
        g_UiPanelTasks[3].state  = 4;
        g_UiPanelTasks[3].unk_0C = 0xFF;
        g_BattleMessageState     = 1;
        step                     = &D_80148652;
        (*step)--;
    }
}
