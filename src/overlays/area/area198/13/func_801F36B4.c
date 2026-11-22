#include "area198_13.h"

MATCH void func_801F36B4(void) {
    Actor* work;
    s16    slot;
    u8     x;
    u8     y;

    work = TASK(Actor);
    slot = g_ScratchPad.cells.halves[0] = Actor_FindFreeField();
    if (slot != GAME_NONE) {
        Actor_SpawnFromRecord(D_801F43C0);
        TASK(Actor)->vz                 = 8;
        TASK(Actor)->vy                 = 0;
        TASK(Actor)->vx                 = 0;
        TASK(Actor)->timer              = 0x10;
        TASK(Actor)->pos.z.part.integer = ((rand() % 30) - 6) << 5;
        TASK(Actor)->unk_2B             = 1;
        do {
            x = rand() % 14 + 0x10;
            y = rand() % 25 + 0xB;
        } while (x - 0x15 < 5 && y - 0x10 < 5);
        TASK(Actor)->pos.x.fixed = x << 16;
        TASK(Actor)->pos.y.fixed = y << 16;
    }
    TASK_SET(work);
    work->param.unk_0B += 1;
}
