#include "boss028_16.h"

MATCH void func_800C1A54(void) {
    u8* value = (u8*)&g_Battle.target_selector;

    Script_Select(2);
    *value = 0x80;
    Battle_MarkDamaged(0x80);
    SELF(Actor)->header.step++;
}
