#include "area030_04.h"

/* On the two gate states, clamps the shared selection byte and
 * repositions the cursor, then queues the panel icon selected by the low bit. */
MATCH void func_801DCCF4(void) {
    FishingState* record;
    s32           value;

    if ((u8)(g_SpawnedActors[6].header.mode - 3) < 2) {
        value                     = g_SpawnedActors[6].unk_07 & 0x7F;
        g_SpawnedActors[6].unk_07 = value;
        UI_CursorDraw(28, ((value << 4) + 88), 0);

        record          = SELF(FishingState);
        record->flag_04 = (record->flag_04 + 1);
    }

    if ((g_SpawnedActors[6].unk_07 & 0x1) == 0) {
        UI_TextDraw(29, 20, 0, TEXT_LENGTH_MAX, (u8*)(MEM(u16, 0x800100A2u) + 0x80010000u));
    } else {
        UI_TextDraw(29, 20, 0, TEXT_LENGTH_MAX, (u8*)(MEM(u16, 0x800100A4u) + 0x80010000u));
    }
}
