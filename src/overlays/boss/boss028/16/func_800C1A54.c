#include "boss028_16.h"

MATCH void func_800C1A54(void) {
    u8* value = (u8*)&g_BattleTargetSelector;

    Actor_SelectScript(2);
    *value = 0x80;
    func_800A9820(0x80);
    SPAD_WORK_BYTES[2]++;
}
