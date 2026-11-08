#include "shop_00.h"

/* nonmatching unmeasured: tried opcode@+0x0: frame 0x18 without s0; retail keeps the D_801483CB address in s0 across
 * the input branches, while the pointer local folds away in our source (43.60 to 58.77 after the old-cursor compare
 * fix). resume: force the cursor address to stay live: compare through a pointer whose value is read after the branches
 * without other uses folding it. */
#ifdef NON_MATCHING
NON_MATCHING void func_801E05E0(void) {
    s32 pad;
    u16 cue;
    u32 scroll;
    u32 scroll_hi;
    u8* item_ptr;
    u8* cursor_ptr;
    u8  slot;
    u8  swapped;
    u8  new_scroll;
    u8  old;

    D_80148624 = 1;
    D_80148628 = D_801483C4 + 7;
    D_80148340 = *(s16*)(D_801CA71E + (D_8014546C[D_801483CB] * 0x14));
    D_8014862A = D_801483C6 + (((D_801483CB - D_801483CA) * 0xD) + 0x1A);
    pad        = INPUT_REPEATED(g_InputPressed, (PADLup | PADLdown | PADL1 | PADR1));
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
    } else if (pad & 4) {
        scroll = D_801483CA & BYTE_MASK;
        if (scroll == 0) {
            D_801483CB = 0;
        } else if (scroll < 9U) {
            D_801483CB -= D_801483CA;
            D_801483CA = 0;
        } else {
            D_801483CB -= 9;
            new_scroll = D_801483CA - 9;
            goto block_22; /* shared confirm join */
        }
    } else if (pad & 8) {
        scroll_hi = D_801483CA & BYTE_MASK;
        if (scroll_hi == 0x77) {
            D_801483CB = 0x7F;
        } else {
            if (scroll_hi >= 0x6FU) {
                D_801483CB = (D_801483CB + 0x77) - D_801483CA;
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
    if (old != *cursor_ptr) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
    }
    if (D_801483CD == 0) {
        if (g_InputMasks[MENU_INPUT_CONFIRM] & g_InputPressed) {
            slot     = D_8014546C[D_801483CB];
            item_ptr = &g_Characters[D_801483A6].abilities.skill[D_801483A7];
            if ((slot != 0) || (*item_ptr != 0)) {
                swapped                = *item_ptr;
                *item_ptr              = slot;
                D_8014546C[D_801483CB] = swapped;
                cue                    = 0x103;
                goto block_32; /* shared confirm join */
            }
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
            return;
        }
        cue = 0x106;
        if (g_InputMasks[MENU_INPUT_CANCEL] & g_InputPressed) {
        block_32:
            SND_PlayCue(cue);
            g_MenuStep.state -= 1;
        }
    }
}
#else
INCLUDE_ASM(func_801E05E0);
#endif
