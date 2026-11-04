#include "engine/slus/slus.h"

/* fades the full-screen tint in a loop, then exits the callback
 * thread.
 */
MATCH void GFX_RunBlackFade(s32 delta, s32 semi_trans, s32 order) {
    s16 delta16;
    s16 level;
    s32 step;
    s32 blend_mode;
    s32 semi_trans_copy;
    s32 order_copy;

    delta16         = (s16)delta;
    semi_trans_copy = semi_trans;
    order_copy      = order;
    if ((delta << 0x10) <= 0) {
        level = 0x7FFF;
    } else {
        level = 0;
    }
    step       = (s32)delta16;
    blend_mode = 2;
    while ((GFX_StepScreenFade(&level, step, semi_trans_copy & BYTE_MASK, order_copy & BYTE_MASK, blend_mode) &
            BYTE_MASK) == 0) {
        CallbackWait(1);
    }
    if (step > 0) {
        D_80143E07 = 0;
        D_80143E06 = 0;
        D_80143E05 = 0;
        D_80143D77 = 0;
        D_80143D76 = 0;
        D_80143D75 = 0;
    }
    CallbackExit();
}
