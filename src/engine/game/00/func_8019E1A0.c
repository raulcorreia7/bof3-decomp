#include "game_00.h"

MATCH void func_8019E1A0(void) {
    u8     sceneTimer;
    u8     stepTimer;
    Actor* work;
    Actor* record;

    work = g_Task;
    work->pos.x.fixed += work->vx;
    work->pos.y.fixed += work->vy;
    work->pos.z.fixed += work->vz;
    Actor_StepAnimLoop();
    record     = g_Task;
    sceneTimer = record->timer;
    if (sceneTimer != 0) {
        record->timer = (u8)(sceneTimer - 1);
        Area_SetDrawMode();
        return;
    }
    stepTimer = record->unk_0A;
    if (stepTimer != 0) {
        record->unk_0A = (u8)(stepTimer - 1);
        if (g_FrameCount & 0x1) {
            Area_SetDrawMode();
        }
    } else {
        Actor_Clear();
    }
}
