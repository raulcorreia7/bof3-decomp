#include "area030_04.h"

/* On the two gate states, clamps the shared selection byte and
 * repositions the cursor, then queues the panel icon selected by the low bit. */
MATCH void func_801DCCF4(void) {
    FishingState* record;
    s32           value;

    if ((u8)(D_80144281 - 3) < 2) {
        value      = D_80144287 & 0x7F;
        D_80144287 = value;
        Menu_DrawCursorSprite(28, ((value << 4) + 88), 0);

        record          = FISHING_STATE;
        record->flag_04 = (record->flag_04 + 1);
    }

    if ((D_80144287 & 0x1) == 0) {
        UI_DrawText(29, 20, 0, 0xFF, (u8*)(MEM(u16, 0x800100A2u) + 0x80010000u));
    } else {
        UI_DrawText(29, 20, 0, 0xFF, (u8*)(MEM(u16, 0x800100A4u) + 0x80010000u));
    }
}
