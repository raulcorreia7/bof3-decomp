#include "area047_13.h"

MATCH u8 func_801F330C(void) {
    AreaRingEffect* ring;
    s32*            pos;
    u8              alive;
    u8              timer;
    u8              shade;
    u8              i;

    alive = 0;
    ring  = MEM_PTR(AreaRingEffect, AREA_WORK);
    i     = 0;
    shade = 0x20;
    pos   = &g_Game.members[0].pos.x.fixed;
    for (; i < AREA_RING_COUNT; i++) {
        if (ring->active != 0) {
            alive = 1;
            switch (ring->stage) {
                case 0:
                    ring->size       = 0;
                    ring->size_delta = 0x10;
                    ring->shade      = shade;
                    ring->timer      = shade;
                    ring->stage += 1;
                    break;
                case 1:
                    ring->pos.x.fixed = pos[0];
                    ring->pos.y.fixed = pos[1];
                    ring->pos.z.fixed = pos[2] + TO_COORD(0x80);
                    ring->size += 8;
                    timer       = ring->timer - 1;
                    ring->timer = timer;
                    ring->shade -= 1;
                    if (timer == 0) {
                        ring->active = 0;
                    }
                    Area_DrawRingQuads(ring);
                    break;
            }
        }
        ring += 1;
    }
    return alive;
}
