#include "game_00.h"

MATCH void func_8019EB38(void) {
    Actor* work;
    Actor* flags;
    Actor* state;
    s32    step;

    SELF(Actor)->direction = (u8)g_Game.members[0].facing;
    work                   = SELF(Actor);
    work->pos.x.fixed      = g_Game.members[0].pos.x.fixed + g_FacingSteps[work->direction].x;
    work->pos.y.fixed      = g_Game.members[0].pos.y.fixed + g_FacingSteps[work->direction].y;
    COORD_INT(work->pos.z) = (s16)((u16)COORD_INT(g_Game.members[0].pos.z) + 0xC0);
    work->vx               = g_FacingOffsets[work->direction].x * 0x10;
    step                   = g_FacingOffsets[work->direction].y * 0x10;
    work->unk_0A           = 0xE;
    flags                  = SELF(Actor);
    work->vy               = step;
    flags->param.unk_0B    = 0;
    state                  = SELF(Actor);
    state->header.mode     = (u8)(state->header.mode + 1);
}
