#include "boss008_16.h"

MATCH void func_800C1B48(void) {
    u32 value;
    u32 value2;
    u8  value3;

    func_800C236C(g_Task->unk_09);
    value3 = g_Task->unk_09;
    if (value3 == 0) {
        g_Task->unk_48 = 0;
        Area_FindSceneRecord(0x83);
        Actor_SelectScript(0U);
        Battle_CollectEnemySpoils();
        g_Task->flags &= ~ACTOR_FLAG_HIDDEN;
        g_Task->mode = 6;
        g_Task->step = 4;
        g_Task->unk_03 += 1;
        g_Task->unk_04 = 0;
        return;
    }
    g_Task->unk_09 = value3 - 4;
    value          = g_Task->scale_x;
    if ((s32)value > 0) {
        g_Task->scale_x = value - 0x2000;
    } else {
        g_Task->scale_x = 0;
    }
    value2 = g_Task->scale_y;
    if ((s32)value2 > 0) {
        g_Task->scale_y = value2 - 0x2000;
        return;
    }
    g_Task->scale_y = 0;
}
