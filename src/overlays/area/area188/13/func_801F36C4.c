#include "area188_13.h"

MATCH void func_801F36C4(void) {
    Actor* task;
    u8     frame;
    u8     remaining;

    frame               = SELF(Actor)->unk_06;
    SELF(Actor)->unk_06 = frame + 1;
    if (!(frame & 3)) {
        Area_ClaimSpawnSlot();
    }
    Area_UpdateSpawnSlots();
    AREA_SPAWN_TICK();
    Area_DrawYellowLine(&SELF(Actor)->unk_18, &SELF(Actor)->pos.x, 0x40);
    task = SELF(Actor);
    task->vx -= 0x800;
    task->vy -= 0x200;
    task->unk_18 += task->vx;
    task->unk_03 -= 4;
    task->unk_1C += task->vy;
    ACTOR_COUNT_DOWN(SELF(Actor), remaining, timer);
    if (!(remaining & 0xFF)) {
        SELF(Actor)->timer = 16;
        SELF(Actor)->header.mode += 1;
    }
}
