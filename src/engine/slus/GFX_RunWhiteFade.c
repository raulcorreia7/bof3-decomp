#include "engine/slus/slus.h"

/* fades the full-screen tint in a loop, then exits the callback
 * thread.
 */
MATCH void GFX_RunWhiteFade(s32 delta, s32 semi_trans, s32 order) {
    s32 step;
    s16 delta16;
    u16 level;
    s32 blend_mode;
    s32 semi_trans_copy;
    s32 order_copy;

    delta16         = delta;
    semi_trans_copy = semi_trans;
    order_copy      = order;
    if ((delta << 0x10) <= 0) {
        level = 0x7FFF;
    } else {
        level = 0;
    }
    if ((delta16) <= 0) {
        D_80143E07 = 0;
        D_80143E06 = 0;
        D_80143E05 = 0;
        D_80143D77 = 0;
        D_80143D76 = 0;
        D_80143D75 = 0;
    }
    step       = delta16;
    blend_mode = 1;
    while ((GFX_UpdateScreenFade(&level, step, semi_trans_copy & BYTE_MASK, order_copy & BYTE_MASK, blend_mode) & BYTE_MASK) == 0) {
        SYS_ThreadWait(1);
    }
    if (step > 0) {
        D_80143E07 = 0xFF;
        D_80143E06 = 0xFF;
        D_80143E05 = 0xFF;
        D_80143D77 = 0xFF;
        D_80143D76 = 0xFF;
        D_80143D75 = 0xFF;
    }
    SYS_ThreadExit();
}
