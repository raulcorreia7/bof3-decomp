#include "start_08.h"

/* One 8-byte label row: glyph count, signed x nudge (read through (s8)), then
 * the text. */
typedef struct StartLabel {
    u8 length;
    u8 offset_x;
    u8 text[6];
} StartLabel;

extern StartLabel D_801ECD24[];
/* Per-group first label row and label count. */

MATCH void func_801E2C00(u16 x, s32 y, s32 group, s32 selected, s32 mode) {
    StartLabel* label;
    u8          flag;
    s16         i;

    label = &D_801ECD24[D_801ECDAC[group & 0xFF]];
    for (i = 0; i < D_801ECDB4[group & 0xFF]; label++, i++) {
        flag = ((selected & 0xFF) == i) * 2;
        if ((selected & 0xFF) == i && mode == 3) {
            UI_DrawText(x + (s8)label->offset_x - label->length * 4 + 116, y - 2, flag, label->length, label->text);
        } else {
            UI_DrawTextString(x + (s8)label->offset_x - label->length * 4 + 116, y + 2, flag, label->length,
                              label->text);
        }
    }
}
