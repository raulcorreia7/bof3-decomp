#include "boss008_16.h"

MATCH void func_800C1B48(void) {
    u32 value;
    u32 value2;
    u8  value3;

    func_800C236C(g_Task->unk_09);
    value3 = g_Task->unk_09;
    if (value3 == 0) {
        g_Task->unk_48 = 0;
        Area_SelectSceneRecord(0x83);
        Actor_SelectScript(0U);
        Battle_DefeatEnemy();
        g_Task->header.flags &= ~ACTOR_FLAG_HIDDEN;
        g_Task->header.mode = 6;
        g_Task->header.step = 4;
        g_Task->unk_03 += 1;
        g_Task->unk_04 = 0;
        return;
    }
    g_Task->unk_09 = value3 - 4;
    value          = g_Task->scale.x;
    if ((s32)value > 0) {
        g_Task->scale.x = value - 0x2000;
    } else {
        g_Task->scale.x = 0;
    }
    value2 = g_Task->scale.y;
    if ((s32)value2 > 0) {
        g_Task->scale.y = value2 - 0x2000;
        return;
    }
    g_Task->scale.y = 0;
}
