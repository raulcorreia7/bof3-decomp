#include "battle_15.h"

MATCH void func_800A65BC(void) {
    /* FAKE: retail keeps the cursor pair base in a2 for every access; cse folds the +2 word into
     * g_BattleTargetCursorCol+2. */
    FAKE_REG(u16*, cursor_words, "a2");
    s16  cursor_col;
    s16  cursor_row;
    u16  cursor_total;
    s32  input;
    u16  pad;
    u16* pad_state;
    u8*  state;

    D_801EB5B4[((D_801EC328 - 1) & 0xF) * 2] = Message_GetText(0x60);
    pad_state                                = &g_InputPressed;
    input                                    = INPUT_REPEATED(*pad_state, (PADLup | PADLdown | PADL1 | PADR1));
    pad                                      = *pad_state;
    if (pad & g_InputMasks[BATTLE_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        state = (u8*)&g_Battle.ui_state;
        *state += 1;
        return;
    }
    if (pad & (g_InputMasks[BATTLE_INPUT_CONFIRM] | PADRup)) {
        if (g_BattleTargetRows[g_BattleTargetCursorCol + D_801485CA].gate_03 == GAME_NONE) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
        } else {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
            g_Battle.ui_state = 2;
            return;
        }
    }
    if (g_InputPressed & PADRup) {
        if (g_BattleTargetRows[g_BattleTargetCursorCol + D_801485CA].gate_03 != GAME_NONE) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
            g_Battle.ui_state = 2;
            return;
        }
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
    }
    cursor_words = (u16*)&g_BattleTargetCursorCol;
    /* FAKE: hides the constant base from cse so the row word stays 2(a2). */
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
        if (cursor_col + cursor_row < 5) {
            if (cursor_col == 2) {
                cursor_words[1] = cursor_row + 1;
            }
            if (cursor_col < 2) {
                cursor_words[0] = cursor_col + 1;
            }
        }
    } else if (input & 0x8) {
        if (cursor_row == 3) {
            cursor_words[0] = 2;
        } else if (cursor_row + cursor_col + 3 < 4) {
            cursor_words[1] = cursor_row + 3;
        } else {
            cursor_words[1] = 3;
        }
    }

    if (*(s16*)&g_BattleTargetCursorCol + D_801485CA != cursor_total) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
    }
}
