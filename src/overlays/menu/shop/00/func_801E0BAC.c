#include "shop_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801E0BAC(void) {
    s32 pad;
    u32 scroll;
    u8  scroll_base;
    u32 scroll_hi;
    u8* cursor_ptr;
    u8  new_scroll;
    u8  old;
    u8  slot;
    u8  swapped;

    g_UiPanelTasks[21].active = 1;
    D_80148628                = (s16)g_UiPanelTasks[4].pos.x;
    D_80148340                = *(s16*)&g_Abilities[D_8014546C[g_UiPanelTasks[4].unk_0B]].description;
    D_8014862A                = g_UiPanelTasks[4].pos.y + (((g_UiPanelTasks[4].unk_0B - g_UiPanelTasks[4].unk_0A) * 0xD) + 0x1A);
    pad                       = INPUT_REPEATED(g_PadStates[0].pressed, (PADLup | PADLdown | PADL1 | PADR1));
    old                       = g_UiPanelTasks[4].unk_0B;
    if (pad & PADLup) {
        if (old != 0) {
            g_UiPanelTasks[4].unk_0B -= 1;
        }
        if ((u8)g_UiPanelTasks[4].unk_0B < (u8)g_UiPanelTasks[4].unk_0A) {
            g_UiPanelTasks[4].flags = 0xF0;
        }
    } else if (pad & PADLdown) {
        if (old < 0x7FU) {
            g_UiPanelTasks[4].unk_0B += 1;
        }
        if ((s32)g_UiPanelTasks[4].unk_0B >= (g_UiPanelTasks[4].unk_0A + 9)) {
            g_UiPanelTasks[4].flags = 0x10;
        }
    } else if (pad & 4) {
        scroll_base = g_UiPanelTasks[4].unk_0A;
        scroll      = scroll_base & BYTE_MASK;
        if (scroll == 0) {
            g_UiPanelTasks[4].unk_0B = 0;
        } else if (scroll < 9U) {
            g_UiPanelTasks[4].unk_0B -= scroll_base;
            g_UiPanelTasks[4].unk_0A = 0;
        } else {
            g_UiPanelTasks[4].unk_0B -= 9;
            new_scroll = g_UiPanelTasks[4].unk_0A - 9;
            goto block_22; /* shared scroll join */
        }
    } else if (pad & 8) {
        scroll_hi = g_UiPanelTasks[4].unk_0A & BYTE_MASK;
        if (scroll_hi == 0x77) {
            g_UiPanelTasks[4].unk_0B = 0x7F;
        } else {
            if (scroll_hi >= 0x6FU) {
                g_UiPanelTasks[4].unk_0B = (g_UiPanelTasks[4].unk_0B + 0x77) - g_UiPanelTasks[4].unk_0A;
                new_scroll               = 0x77;
            } else {
                g_UiPanelTasks[4].unk_0B += 9;
                new_scroll = g_UiPanelTasks[4].unk_0A + 9;
            }
        block_22:
            g_UiPanelTasks[4].unk_0A = new_scroll;
        }
    }
    cursor_ptr = &g_UiPanelTasks[4].unk_0B;
    if (old != cursor_ptr[0]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    }
    if (g_UiPanelTasks[4].flags == 0) {
        if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
            if (cursor_ptr[1] == GAME_NONE) {
                if (D_8014546C[cursor_ptr[0]] != 0) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
                    cursor_ptr[1] = cursor_ptr[0];
                    return;
                }
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
                return;
            }
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
            slot                      = D_8014546C[cursor_ptr[0]];
            swapped                   = D_8014546C[cursor_ptr[1]];
            D_8014546C[cursor_ptr[1]] = slot;
            D_8014546C[cursor_ptr[0]] = swapped;
            cursor_ptr[1]             = 0xFFU;
            return;
        }
        if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
            if (cursor_ptr[1] == GAME_NONE) {
                g_UiPanelTasks[5].unk_0B = 0xFF;
                g_MenuStep.state -= 1;
                return;
            }
            cursor_ptr[1] = 0xFF;
        }
    }
}
#else
INCLUDE_ASM(func_801E0BAC);
#endif
