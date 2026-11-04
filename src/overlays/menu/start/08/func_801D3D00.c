#include "start_08.h"

MATCH void func_801D3D00(void) {
    MenuChoicePanel* panel;
    u8*              state_counter;
    u8               cursor;
    u8               page_start;
    u8               page_start_masked;
    u8               scrolled;
    s32              pressed;
    u32              span;

    Menu_DrawClutStrip(D_80144953);
    D_801484CC = Item_GetDescription(D_8014850E, D_801C893C[D_8014850E][D_80148510]);
    D_80148624 = 1;
    D_80148534 = 0;
    D_80148628 = (u16)D_80148508 + 7;
    span       = (D_80148510 - D_8014850F) * 0xD + 0x1A;
    D_8014862A = (u16)D_8014850A + span;
    panel      = &D_80148504;
    pressed    = INPUT_GetRepeatedButtons(g_InputPressed & (PADLup | PADLdown | PADL1 | PADR1));
    cursor     = D_80148510;
    if (pressed & PADLup) {
        if (cursor != 0) {
            D_80148510 = cursor - 1;
        }
        if ((u32)D_80148510 < (u32)D_8014850F) {
            D_80148516 = 0xF0;
        }
    } else if (pressed & PADLdown) {
        if ((u32)cursor < 0x7FU) {
            D_80148510 = cursor + 1;
        }
        if (D_80148510 >= D_8014850F + 9) {
            D_80148516 = 0x10;
        }
    } else if (pressed & 4) {
        if ((D_8014850F & BYTE_MASK) == 0) {
            D_80148510 = 0;
        } else if ((u32)(D_8014850F & BYTE_MASK) < 9U) {
            D_80148510 = cursor - D_8014850F;
            D_8014850F = 0;
        } else {
            D_80148510 = cursor - 9;
            D_8014850F = D_8014850F - 9;
        }
    } else if (pressed & 8) {
        page_start        = D_8014850F;
        page_start_masked = page_start & BYTE_MASK;
        if (page_start_masked == 0x77) {
            D_80148510 = 0x7F;
        } else if (page_start_masked >= 0x6F) {
            scrolled   = cursor + 0x77;
            D_80148510 = scrolled - page_start;
            D_8014850F = 0x77;
        } else {
            D_80148510 = cursor + 9;
            D_8014850F = page_start + 9;
        }
    }
    s_ChoiceMenuCursors[panel->group] = panel->group_cursor;
    s_ChoiceMenuValues[panel->group]  = panel->group_first;
    if (cursor != panel->group_cursor) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
    }
    if (panel->confirm_gate == 0) {
        if (g_InputPressed & D_80145AC2) {
            if (panel->drawn_cursor == GAME_NONE) {
                SND_PlayCue(EMI_CUE_ID(1, 3));
                if (D_801C893C[panel->group][panel->group_cursor] != 0) {
                    panel->drawn_cursor = panel->group_cursor;
                    return;
                }
                SND_PlayCue(EMI_CUE_ID(1, 7));
                return;
            }
            SND_PlayCue(EMI_CUE_ID(1, 3));
            Menu_SwapBytes(&D_801C893C[panel->group][panel->drawn_cursor],
                           &D_801C893C[panel->group][panel->group_cursor]);
            Menu_SwapBytes(&D_801C8950[panel->group][panel->drawn_cursor],
                           &D_801C8950[panel->group][panel->group_cursor]);
            panel->drawn_cursor = 0xFF;
        } else if (g_InputPressed & D_80145AC4) {
            SND_PlayCue(EMI_CUE_ID(1, 6));
            if (panel->drawn_cursor == GAME_NONE) {
                state_counter  = &D_80148652;
                *state_counter = *state_counter - 1;
                return;
            }
            panel->drawn_cursor = 0xFF;
        }
    }
}
