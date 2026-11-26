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

    wrap_key                   = 0;
    record                     = SELF(FishingState);
    wrap_flag                  = 1;
    record->bounce.half.key    = 0;
    record->bounce.half.unk_3C = 0;
    /* FAKE: scan copy holds the retail a0 loop base; one pointer scores 89.06%. */
    scan                       = record;
loop:
    index = scan->bounce.half.key;
    if (g_FishingBestCatch[index] == 0) {
        next                  = index + 1;
        scan->bounce.half.key = next;
        if (next >= 0x20) {
            scan->bounce.half.key = 0;
        }
        if (scan->bounce.half.key != wrap_key) {
            goto loop; /* retail branches back to the loop head */
        }
        scan->bounce.half.unk_3C = wrap_flag;
    }
    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0U);
    mask = 0;
    if (D_80145E93[0] >= 3) {
        mask = (1 << SELF(FishingState)->cue_index) & BYTE_MASK;
    }
    func_801D7C10(FISHING_SHOP_COLUMNS_X, FISHING_SHOP_COLUMNS_Y, mask);
    SELF(FishingState)->timer = 4;
    SELF(FishingState)->handler_index += 1;
}
