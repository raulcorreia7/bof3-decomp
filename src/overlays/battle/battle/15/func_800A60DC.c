#include "battle_15.h"

MATCH void func_800A60DC(void) {
    /* FAKE: retail keeps the cursor pair base in a2 for all nine accesses; 76.28% in pure C (cse folds the +2 word
     * into D_801485EC+2). */
    FAKE_REG(u16*, cursor_words, "a2");
    u16* pad_state;
    s32  input;
    u16  pad;
    s16  cursor_col;
    s16  cursor_row;
    u16  cursor_total;
    u8   state;
    u8*  resource;
    resource                                 = Message_GetText(0x61);
    pad_state                                = &g_InputPressed;
    D_801EB5B4[((D_801EC328 - 1) & 0xF) * 2] = resource;
    input                                    = INPUT_REPEATED(*pad_state, (PADLup | PADLdown | PADL1 | PADR1));
    pad                                      = *pad_state;

    if (pad & g_InputMasks[BATTLE_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        g_Battle.ui_state = 5;
        return;
    }
    if (pad & g_InputMasks[BATTLE_INPUT_CONFIRM]) {
        if ((&D_8014551B)[(*(s16*)&D_801485EC + D_801485EE) * 4] == GAME_NONE) {
            state = 4;
        } else {
            D_801463B4 = 0;
            state      = 3;
        }
        g_Battle.ui_state = state;
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
    }

    cursor_words = (u16*)&D_801485EC;
    /* FAKE: hides the constant base from cse so the row word stays 2(a2), pure-C best 76.28%. */
    FAKE_OPAQUE(cursor_words);
    cursor_col   = cursor_words[0];
    cursor_row   = cursor_words[1];
    cursor_total = cursor_col + cursor_row;

    if (input & PADLup) {
        if (cursor_col + cursor_row > 0) {
            if (cursor_col == 0) {
                cursor_words[1] = cursor_row - 1;
            }
            if (cursor_col > 0) {
                cursor_words[0] = cursor_col - 1;
            }
        }
    } else if (input & 0x4) {
        if (cursor_row >= 3) {
            cursor_words[1] = cursor_row - 3;
        } else if (cursor_row == 0) {
            cursor_words[0] = 0;
        } else {
            cursor_words[1] = 0;
        }
    } else if (input & PADLdown) {
        if (cursor_col + cursor_row < 11) {
            if (cursor_col == 2) {
                cursor_words[1] = cursor_row + 1;
            }
            if (cursor_col < 2) {
                cursor_words[0] = cursor_col + 1;
            }
        }
    } else if (input & 0x8) {
        if (cursor_row == 9) {
            cursor_words[0] = 2;
        } else if (cursor_row + cursor_col + 3 < 0xA) {
            cursor_words[1] = cursor_row + 3;
        } else {
            cursor_words[1] = 9;
        }
    }

    if (*(s16*)&D_801485EC + D_801485EE != cursor_total) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
    }
}
