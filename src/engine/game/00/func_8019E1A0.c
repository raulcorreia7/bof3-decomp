#include "game_00.h"

MATCH void func_8019E1A0(void) {
    u8     sceneTimer;
    u8     stepTimer;
    Actor* work;
    Actor* record;

    work          = g_SpadWork;
    work->x.fixed = (s32)(work->x.fixed + work->vx);
    work->y.fixed = (s32)(work->y.fixed + work->vy);
    work->z.fixed = (s32)(work->z.fixed + work->vz);
    func_8014D978();
    record     = g_SpadWork;
    sceneTimer = record->unk_09;
    if (sceneTimer != 0) {
        record->unk_09 = (u8)(sceneTimer - 1);
        Area_SetDrawMode();
        return;
    }
    stepTimer = record->unk_0A;
    if (stepTimer != 0) {
        record->unk_0A = (u8)(stepTimer - 1);
        if (g_FrameCount & 1) {
            Area_SetDrawMode();
        }
    } else {
        Actor_Clear();
    }
}
