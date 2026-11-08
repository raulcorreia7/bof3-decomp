#include "battle_15.h"

void func_8009A744(void); /* extern */

/* nonmatching unmeasured: tried opcode@+0x8: prologue and the 0xF00C/0x500C pad split do not reproduce the retail
 * order; scroll/confirm logic is in place. resume: rebuild the two INPUT_GetRepeatedButtons calls and the scroll
 * compare grouping from the asm. */
#ifdef NON_MATCHING
NON_MATCHING void func_80099830(void) {
    s32  pad;
    u16* row_base;
    u32  scroll_lo;
    u32  scroll_hi;
    u8*  choice;
    u8   new_scroll;

    if (D_80148597 == 0) {
        D_801485DC = 1;
        D_801485E0 = D_80148598 + 7;
        D_801485E2 = D_8014859A + (((g_BattleListCursor - D_8014859E) * 0xD) + 0x1A);
    } else {
        D_801485DC = 0;
    }
    INPUT_REPEATED(g_InputPressed, (INPUT_DIRECTIONAL | PADL1 | PADR1));
    pad      = INPUT_REPEATED(g_InputPressed, (PADLup | PADLdown | PADL1 | PADR1));
    row_base = (u16*)&D_80148594;
    if (pad & PADLup) {
        if (g_BattleListCursor != 0) {
            g_BattleListCursor -= 1;
        }
        if ((u8)g_BattleListCursor < (u8)D_8014859E) {
            D_801485A4 = 0xF0;
        }
    } else if (pad & PADLdown) {
        if ((u8)g_BattleListCursor < 0x7FU) {
            g_BattleListCursor += 1;
        }
        if ((s32)g_BattleListCursor >= (D_8014859E + 7)) {
            D_801485A4 = 0x10;
        }
    } else if (pad & 4) {
        scroll_lo = D_8014859E & BYTE_MASK;
        if (scroll_lo == 0) {
            g_BattleListCursor = 0;
        } else if (scroll_lo < 7U) {
            g_BattleListCursor -= D_8014859E;
            D_8014859E = 0;
        } else {
            g_BattleListCursor -= 7;
            new_scroll = D_8014859E - 7;
            goto block_25; /* shared scroll/confirm join */
        }
    } else if (pad & 8) {
        scroll_hi = D_8014859E & BYTE_MASK;
        if (scroll_hi == 0x79) {
            g_BattleListCursor = 0x7F;
        } else {
            if (scroll_hi >= 0x73U) {
                g_BattleListCursor = (g_BattleListCursor + 0x79) - D_8014859E;
                new_scroll         = 0x79;
            } else {
                g_BattleListCursor += 7;
                new_scroll = D_8014859E + 7;
            }
        block_25:
            D_8014859E = new_scroll;
        }
    }
    if (g_BattleListCursor != FIELD(u8, row_base, 0xBu)) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
    }
    choice = (u8*)D_801485A1;
    D_801EB5B4[((D_801EC328 - 1) & 0xF) * 2] =
        Resource_GetText(Item_GetDescription((s32)D_8014859C, (s32)choice) & HALF_MASK);
    if (g_InputMasks[BATTLE_INPUT_CANCEL] & g_InputPressed) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        goto block_33; /* shared scroll/confirm join */
    }
    func_8009AAE8();
    if (g_InputMasks[BATTLE_INPUT_CONFIRM] & g_InputPressed) {
        if (choice != NULL) {
            SND_PlayCue(EMI_CUE_ID(1, 3));
            func_8009A744();
        block_33:
            g_BattleListCursor = 0xFF;
            D_801485C3         = 0xFF;
            D_801485C5         = 1;
            g_Battle.ui_state -= 1;
            return;
        }
        SND_PlayCue(EMI_CUE_ID(1, 7));
    }
}
#else
INCLUDE_ASM(func_80099830);
#endif
