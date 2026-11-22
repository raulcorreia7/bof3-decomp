#include "battle_03.h"

MATCH void func_801E347C(void) {
    PartyMember* work;
    s32          old38;
    s32          old34;

    work = TASK(PartyMember);
    work->header.flags &= ~ACTOR_FLAG_HIDDEN;
    Battle_RequestEnemyScript(0);
    old34                     = TASK(PartyMember)->pos.x.fixed;
    old38                     = TASK(PartyMember)->pos.y.fixed;
    TASK(PartyMember)->unk_0C = 0x80000;
    TASK(PartyMember)->unk_10 = 0;
    TASK(PartyMember)->unk_18 = old34;
    work                      = TASK(PartyMember);
    work->unk_1C              = old38;
    Effect_RotatePosition(work);
    {
        s32 dx;
        s32 dy;
        s32 depth;

        depth                     = TASK(PartyMember)->pos.x.fixed;
        dx                        = TASK(PartyMember)->unk_0C;
        dy                        = TASK(PartyMember)->unk_10;
        TASK(PartyMember)->unk_0C = 0x8000;
        TASK(PartyMember)->unk_10 = 0;
        depth -= dx;
        TASK(volatile PartyMember)->pos.x.fixed = depth;
        depth -= dy;
        work              = TASK(PartyMember);
        work->pos.x.fixed = depth;
        Effect_RotatePosition(work);
    }
    work              = TASK(PartyMember);
    work->header.step = work->header.step + 1;
}
