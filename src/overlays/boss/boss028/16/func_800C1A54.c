#include "boss028_16.h"
#include "area/spad.h"

MATCH void func_800C1A54(void) {
    u8* value = (u8*)&g_Battle.target_selector;

    Actor_SelectScript(2);
    *value = 0x80;
    Battle_MarkDamaged(0x80);
    g_Task->header.step++;
}
