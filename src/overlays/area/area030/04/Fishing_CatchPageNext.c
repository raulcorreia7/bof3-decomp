#include "area030_04.h"

/* Scans the 0x20-entry table at 0x80144FE4 from the work record's key
 * word, advancing the key until it hits an occupied entry or wraps back to the
 * start, then seeds the menu panel, the cue mask and the step timer. */
/* func_801D4884 */
MATCH void Fishing_CatchPageNext(void) {
    FishingState* record;
    FishingState* scan;
    s16           index;
    s16           next;
    u32           mask;
    s32           wrap_key;  /* the key value that marks the table scan wrapping */
    s32           wrap_flag; /* the flag the work record gets when it wraps */

    wrap_key                      = 0;
    record                        = FISHING_STATE;
    wrap_flag                     = 1;
    record->bounce_3C.half.key_3E = 0;
    record->bounce_3C.half.unk_3C = 0;
    /* FAKE: scan copy holds the retail a0 loop base; one pointer scores 89.06%. */
    scan                          = record;
loop:
    index = scan->bounce_3C.half.key_3E;
    if (g_FishingBestCatch[index] == 0) {
        next                        = index + 1;
        scan->bounce_3C.half.key_3E = next;
        if (next >= 0x20) {
            scan->bounce_3C.half.key_3E = 0;
        }
        if (scan->bounce_3C.half.key_3E != wrap_key) {
            goto loop; /* retail branches back to the loop head */
        }
        scan->bounce_3C.half.unk_3C = wrap_flag;
    }
    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0U);
    mask = 0;
    if (D_80145E93[0] >= 3) {
        mask = (1 << FISHING_STATE->cue_index_06) & BYTE_MASK;
    }
    func_801D7C10(FISHING_SHOP_COLUMNS_X, FISHING_SHOP_COLUMNS_Y, mask);
    FISHING_STATE->step_timer_09 = 4;
    FISHING_STATE->handler_index_01 += 1;
}
