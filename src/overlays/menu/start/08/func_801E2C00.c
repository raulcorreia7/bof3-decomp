#include "start_08.h"

/* Per-group first label row and label count. */

MATCH void func_801E2C00(u16 x, s32 y, s32 group, s32 selected, s32 mode) {
    StartLabel* label;
    u8          flag;
    s16         i;

    label = &D_801ECD24[D_801ECDAC[group & BYTE_MASK]];
    for (i = 0; i < D_801ECDB4[group & BYTE_MASK]; label++, i++) {
        flag = ((selected & BYTE_MASK) == i) * 2;
        if ((selected & BYTE_MASK) == i && mode == 3) {
            UI_DrawText(x + (s8)label->offset_x - label->length * 4 + 116, y - 2, flag, label->length, label->text);
        } else {
            UI_DrawTextString(x + (s8)label->offset_x - label->length * 4 + 116, y + 2, flag, label->length,
                              label->text);
        }
    }
}
