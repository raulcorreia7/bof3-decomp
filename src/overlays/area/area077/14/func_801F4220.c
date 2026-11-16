#include "area077_14.h"

MATCH void func_801F4220(void) {
    AreaSlot* slot;
    s32       cos;
    s32       sin;
    u8        i;

    slot = (AreaSlot*)AREA_WORK + (AREA_SLOT_COUNT - 2);
    i    = 0;
    do {
        slot[1] = slot[0];
        i++;
        slot--;
    } while (i < AREA_SLOT_COUNT - 1);

    slot        = (AreaSlot*)AREA_WORK;
    slot->pos.x = g_Task->pos.x.fixed;
    slot->pos.y = g_Task->pos.y.fixed;
    slot->pos.z = g_Task->pos.z.fixed + (rsin((u16) ~(g_FrameCount << 7)) << 10);
    slot->angle = D_800E5500;
    if (D_800E5502 != 0) {
        D_800E5500 += 0x40;
        if (D_800E5500 == 0) {
            D_800E5502 = 0;
        }
    }

    i = 0;
    do {
        cos               = rcos(slot->angle) << 3;
        sin               = rsin(slot->angle) << 11;
        slot->edges[0].vx = slot->pos.x;
        slot->edges[0].vy = slot->pos.y + cos;
        slot->edges[0].vz = slot->pos.z + sin;
        slot->edges[1].vx = slot->pos.x;
        slot->edges[1].vy = slot->pos.y - cos;
        slot->edges[1].vz = slot->pos.z - sin;
        i++;
        slot++;
    } while (i < AREA_SLOT_COUNT);
}
