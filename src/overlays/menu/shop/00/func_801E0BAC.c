#include "shop_00.h"

#ifdef NON_MATCHING
/* Moves the ability-stock cursor and swaps two stock entries on confirm. */
NON_MATCHING void func_801E0BAC(void) {
    s32 pad;
    s32 cursor_y;
    u32 scroll;
    u32 scroll_hi;
    u8* cursor_ptr;
    u8  slot;
    u8  swapped;
    u8  new_scroll;
    u8  old;

    D_80148340 = *(s16*)&g_Abilities[D_8014546C[D_801483CB]].description;
    D_80148624 = 1;
    D_80148628 = D_801483C4;
    cursor_y   = ((D_801483CB - D_801483CA) * 0xD) + 0x1A;
    D_8014862A = cursor_y + D_801483C6;
    pad        = INPUT_REPEATED(g_PadStates[0].pressed, (PADLup | PADLdown | PADL1 | PADR1));
    old        = D_801483CB;
    if (pad & PADLup) {
        if (old != 0) {
            D_801483CB -= 1;
        }
        if ((u8)D_801483CB < (u8)D_801483CA) {
            D_801483CD = 0xF0;
        }
    } else if (pad & PADLdown) {
        if (old < 0x7FU) {
            D_801483CB += 1;
        }
        if ((s32)D_801483CB >= (D_801483CA + 9)) {
            D_801483CD = 0x10;
        }
    } else if (pad & PADL1) {
        scroll = D_801483CA & BYTE_MASK;
        if (scroll == 0) {
            D_801483CB = 0;
        } else if (scroll < 9U) {
            D_801483CB -= D_801483CA;
            D_801483CA = 0;
        } else {
            D_801483CB -= 9;
            new_scroll = D_801483CA - 9;
            goto block_22; /* shared scroll join */
        }
    } else if (pad & PADR1) {
        scroll_hi = D_801483CA & BYTE_MASK;
        if (scroll_hi == 0x77) {
            D_801483CB = 0x7F;
        } else {
            if (scroll_hi >= 0x6FU) {
                scroll     = D_801483CB + 0x77;
                D_801483CB = scroll - D_801483CA;
                new_scroll = 0x77;
            } else {
                D_801483CB += 9;
                new_scroll = D_801483CA + 9;
            }
        block_22:
            D_801483CA = new_scroll;
        }
    }
    cursor_ptr = &D_801483CB;
    if (old != cursor_ptr[0]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
    }
    if (D_801483CD == 0) {
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
            cursor_ptr[1]             = GAME_NONE;
            return;
        }
        if (g_PadStates[0].pressed & g_InputMasks[MENU_INPUT_CANCEL]) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
            if (cursor_ptr[1] == GAME_NONE) {
                D_801483EF = GAME_NONE;
                g_MenuStep.state -= 1;
                return;
            }
            cursor_ptr[1] = GAME_NONE;
        }
    }
}
#else
INCLUDE_ASM(func_801E0BAC);
#endif
