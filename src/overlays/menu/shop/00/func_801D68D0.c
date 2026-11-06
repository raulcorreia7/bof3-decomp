#include "shop_00.h"

MATCH void func_801D68D0(s32 reset_slots) {
    s32        index;
    s32        id;
    Character* slot;
    u16        max_hp;
    u16        max_ap;

    index = 0;
    do {
        id   = index & 0xFF;
        slot = &g_Characters[id];
        if (reset_slots & 0xFF) {
            slot->fatigue = 0;
            Char_ClearStatus(id, 0xA0, 0);
            slot->willpower = slot->stats.willpower;
        }
        slot->inoculations = 0;
        Char_RebuildStats(slot);
        max_hp             = slot->stats.max_hp;
        max_ap             = slot->stats.max_ap;
        slot->inoculations = 0;
        slot->hp           = max_hp;
        slot->ap           = max_ap;
        Char_ClearStatus(id, 0x2000, 0);
        index += 1;
    } while ((index & 0xFF) < 8U);
    if ((SYS_TestFlag((u8*)g_Characters + 0xBE4, 4) != 0) && (SYS_TestFlag((u8*)g_Characters + 0xBE7, 4) == 0) &&
        (((u8*)g_Characters)[0xB8B] < 0x1EU)) {
        ((u8*)g_Characters)[0xB8B] = 0;
    }
}
