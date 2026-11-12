#include "area098_13.h"

MATCH void func_801F3BD4(void) {
    Actor* task;
    u8     frame;
    u8     remaining;

    frame          = g_Task->unk_06;
    g_Task->unk_06 = frame + 1;
    if (!(frame & 3)) {
        Area_ClaimSpawnSlot();
    }
    Area_UpdateSpawnSlots();
    func_801F5940();
    func_801F48E8(&g_Task->unk_18, &g_Task->pos.x, 0x40);
    task = g_Task;
    task->vx -= 0x800;
    task->vy -= 0x200;
    task->unk_18 += task->vx;
    task->unk_03 -= 4;
    task->unk_1C += task->vy;
    remaining     = g_Task->timer - 1;
    g_Task->timer = remaining;
    if (!(remaining & 0xFF)) {
        g_Task->timer = 128;
        g_Task->header.mode += 1;
    }
}
