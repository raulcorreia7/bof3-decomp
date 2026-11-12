#include "area030_04.h"

/* Draws the AREA030 status banner: queues the current mode's label
 * strip, then the icon quad with the elapsed-battle count clamped to 0..4. */

MATCH void func_801D1F38(void) {
    u8 label;
    s8 count;
    s8 elapsed;

    if (g_FrameCount & 0x40) {
        label = g_FishingRod;
        UI_DrawText(138, 200, 0, 12, (u8*)((label * ACCESSORY_STRIDE) + (u32)g_Accessories));
    } else {
        label = g_FishingLure;
        UI_DrawText(138, 200, 0, 12, (u8*)((label * ACCESSORY_STRIDE) + (u32)g_Accessories));
    }

    count = (g_ActorSlots[0].unk_07 - g_FishingLureRow->unk_0F);
    if (count >= 0) {
        elapsed = count;
        if (count >= 5) {
            elapsed = 4;
        }
    } else {
        elapsed = 0;
    }

    count = elapsed;
    if (count != 0) {
        func_801D2034((g_ActorSlots[0].unk_2E + 0xA), (g_ActorSlots[0].unk_30 - 0x18), 2, (u8)count);
    }
}
