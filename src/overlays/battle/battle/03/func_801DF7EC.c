#include "battle_03.h"

/* writes the shared sprite value into the selected 0xC-byte palette fade
 * row, then restarts the stance when the enemy re-selected it and the step
 * byte is set.
 */
MATCH void func_801DF7EC(void) {
    s32          offset;
    PaletteFade* entry;
    u8           sprite;
    u8           value;

    offset                           = g_Task->unk_07 * 0xC;
    entry                            = (PaletteFade*)((u8*)D_80145BD4 + offset);
    sprite                           = D_80146308;
    entry->blue_offset               = sprite;
    entry->green_offset              = sprite;
    *(u8*)((u8*)D_80145BD6 + offset) = sprite;
    if ((g_BattleSelectionLatch == 0) ||
        (((value = D_801EB4D8[0]) != g_Task->slot) && ((value & BATTLE_TARGET_PARTY_SIDE) == 0))) {
        GFX_FreePaletteFade(g_Task->unk_07);
        g_Task->step = 0;
    }
}
