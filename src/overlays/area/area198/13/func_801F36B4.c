#include "area198_13.h"

MATCH void func_801F36B4(void) {
    Actor* work;
    s16    slot;
    u8     x;
    u8     y;

    work = SELF(Actor);
    slot = g_ScratchPad.cells.halves[0] = Actor_FindFreeField();
    if (slot != GAME_NONE) {
        Actor_SpawnFromRecord(D_801F43C0);
        SELF(Actor)->vz                 = 8;
        SELF(Actor)->vy                 = 0;
        SELF(Actor)->vx                 = 0;
        SELF(Actor)->timer              = 0x10;
        SELF(Actor)->pos.z.part.integer = ((rand() % 30) - 6) << 5;
        SELF(Actor)->unk_2B             = 1;
        do {
            x = rand() % 14 + 0x10;
            y = rand() % 25 + 0xB;
        } while (x - 0x15 < 5 && y - 0x10 < 5);
        SELF(Actor)->pos.x.fixed = x << 16;
        SELF(Actor)->pos.y.fixed = y << 16;
    }
    SELF_SET(work);
    work->param.unk_0B += 1;
}
