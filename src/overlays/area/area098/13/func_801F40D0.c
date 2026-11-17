#include "area098_13.h"

MATCH void func_801F40D0(s32 unused) {
    AreaStreakSlot* slot;
    s32             speed;
    u16             angle;
    u8              i;
    u8              shade;

    slot = MEM_PTR(AreaStreakSlot, AREA_WORK);
    i    = 0;
    do {
        if (slot->active == 0) {
            slot->active     = 1;
            slot->kind       = 0;
            slot->life       = 8;
            angle            = rand() & 0xFFF;
            speed            = ((rand() & 0xFFF) << 5) + 0x10000;
            shade            = speed / 0x300;
            slot->tail_shade = shade;
            slot->head_shade = shade;
            slot->tail.x     = g_Task->pos.x.fixed + ((speed * rcos(angle)) >> 12);
            slot->head.x     = slot->tail.x;
            slot->tail.y     = g_Task->pos.y.fixed + ((speed * rsin(angle)) >> 12);
            slot->head.y     = slot->tail.y;
            slot->tail.z     = g_Task->pos.z.fixed;
            slot->head.z     = slot->tail.z;
            slot->vel[0]     = (-rcos(angle)) << 1;
            slot->vel[1]     = (-rsin(angle)) << 1;
            slot->vel[2]     = 0;
            return;
        }
        i++;
        slot++;
    } while ((u8)i < 0x18);
}
