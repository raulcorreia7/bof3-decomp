#include "battle_15.h"

/* The two cursor halfwords at D_801485EC and D_801485EE: the row within the page, then the page. */
typedef struct BattleMenuCursor {
    u16 index;
    u16 page;
} BattleMenuCursor;

/* Battle menu cursor bounds: the index runs over the three rows of a page and the page over ten pages of three rows;
 * the target's own header declares none of them under these names. */
#define CURSOR_INDEX_MAX 2
#define CURSOR_PAGE_MAX  9
#define CURSOR_PAGE_STEP 3
#define CURSOR_TOTAL_MAX 10

MATCH void func_800A5AE4(void) {
    s16 cursor_index;
    s16 cursor_page;
    u16 cursor_sum;
    /* FAKE: cursor base pinned to a2 so the page word loads as 2(a2); pure C folds it into the constant address
     * D_801485EE (72.73%). */
    FAKE_REG(BattleMenuCursor*, cursor, "a2");
    u16* pad_state;
    u16  pad_bits;
    s32  input;
    u8*  cue_counter;

    if (*(s16*)&D_801485E0 != 0x5B) {
        return;
    }

    pad_state = &g_InputPressed;
    input     = INPUT_REPEATED(*pad_state, (PADLup | PADLdown | PADL1 | PADR1));
    pad_bits  = *pad_state;

    if (pad_bits & g_InputMasks[BATTLE_INPUT_CANCEL]) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        cue_counter  = (u8*)&g_Battle.ui_state;
        *cue_counter = *cue_counter + 1;
        return;
    }
    if (pad_bits & g_InputMasks[BATTLE_INPUT_CONFIRM]) {
        if (func_800A5D00() & BYTE_MASK) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 4));
            g_Battle.ui_state = 5;
            return;
        }
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
    }

    cursor = (BattleMenuCursor*)&D_801485EC;
    /* FAKE: hides the constant base from cse; with the pin it keeps 2(a2) (pure-C best 72.73%). */
    FAKE_OPAQUE(cursor);
    cursor_index = cursor->index;
    cursor_page  = cursor->page;
    cursor_sum   = cursor_index + cursor_page;
    if (input & PADLup) {
        if (cursor_index + cursor_page > 0) {
            if (cursor_index == 0) {
                cursor->page = cursor_page - 1;
            }
            if (cursor_index > 0) {
                cursor->index = cursor_index - 1;
            }
        }
    } else if (input & 0x4) {
        if (cursor_page >= CURSOR_PAGE_STEP) {
            cursor->page = cursor_page - CURSOR_PAGE_STEP;
        } else if (cursor_page == 0) {
            cursor->index = 0;
        } else {
            cursor->page = 0;
        }
    } else if (input & PADLdown) {
        if (cursor_index + cursor_page < CURSOR_TOTAL_MAX + 1) {
            if (cursor_index == CURSOR_INDEX_MAX) {
                cursor->page = cursor_page + 1;
            }
            if (cursor_index < CURSOR_INDEX_MAX) {
                cursor->index = cursor_index + 1;
            }
        }
    } else if (input & 0x8) {
        if (cursor_page == CURSOR_PAGE_MAX) {
            cursor->index = CURSOR_INDEX_MAX;
        } else if (cursor_page + cursor_index + CURSOR_PAGE_STEP < CURSOR_TOTAL_MAX) {
            cursor->page = cursor_page + CURSOR_PAGE_STEP;
        } else {
            cursor->page = CURSOR_PAGE_MAX;
        }
    }
    if (*(s16*)&D_801485EC + D_801485EE != cursor_sum) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
    }
}
