#include "area198_13.h"

MATCH void func_801F36B4(void) {
    Actor* work;
    s16    slot;
    u8     x;
    u8     y;

    work = g_Task;
    slot = g_ScratchPad.cells.halves[0] = Actor_FindFreeField();
    if (slot != GAME_NONE) {
        Actor_SpawnFromRecord(D_801F43C0);
        g_Task->vz                 = 8;
        g_Task->vy                 = 0;
        g_Task->vx                 = 0;
        g_Task->timer              = 0x10;
        g_Task->pos.z.part.integer = ((rand() % 30) - 6) << 5;
        g_Task->unk_2B             = 1;
        do {
            x = rand() % 14 + 0x10;
            y = rand() % 25 + 0xB;
        } while (x - 0x15 < 5 && y - 0x10 < 5);
        g_Task->pos.x.fixed = x << 16;
        g_Task->pos.y.fixed = y << 16;
    }
    TASK_SET(work);
    work->param.unk_0B += 1;
}
