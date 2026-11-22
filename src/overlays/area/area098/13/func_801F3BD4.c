#include "area098_13.h"

MATCH void func_801F3BD4(void) {
    Actor* task;
    u8     frame;
    u8     remaining;

    frame               = TASK(Actor)->unk_06;
    TASK(Actor)->unk_06 = frame + 1;
    if (!(frame & 3)) {
        Area_ClaimSpawnSlot();
    }
    Area_UpdateSpawnSlots();
    func_801F5940();
    Area_DrawYellowLine(&TASK(Actor)->unk_18, &TASK(Actor)->pos.x, 0x40);
    task = TASK(Actor);
    task->vx -= 0x800;
    task->vy -= 0x200;
    task->unk_18 += task->vx;
    task->unk_03 -= 4;
    task->unk_1C += task->vy;
    ACTOR_COUNT_DOWN(TASK(Actor), remaining, timer);
    if (!(remaining & 0xFF)) {
        TASK(Actor)->timer = 128;
        TASK(Actor)->header.mode += 1;
    }
}
