#include "battle_03.h"

MATCH void func_801E347C(void) {
    PartyMember* work;
    s32          old38;
    s32          old34;

    work = SELF(PartyMember);
    work->header.flags &= ~ACTOR_FLAG_HIDDEN;
    Battle_RequestEnemyScript(0);
    old34                     = SELF(PartyMember)->pos.x.fixed;
    old38                     = SELF(PartyMember)->pos.y.fixed;
    SELF(PartyMember)->unk_0C = 0x80000;
    SELF(PartyMember)->unk_10 = 0;
    SELF(PartyMember)->unk_18 = old34;
    work                      = SELF(PartyMember);
    work->unk_1C              = old38;
    Effect_RotatePosition(work);
    {
        s32 dx;
        s32 dy;
        s32 depth;

        depth                     = SELF(PartyMember)->pos.x.fixed;
        dx                        = SELF(PartyMember)->unk_0C;
        dy                        = SELF(PartyMember)->unk_10;
        SELF(PartyMember)->unk_0C = 0x8000;
        SELF(PartyMember)->unk_10 = 0;
        depth -= dx;
        SELF(volatile PartyMember)->pos.x.fixed = depth;
        depth -= dy;
        work              = SELF(PartyMember);
        work->pos.x.fixed = depth;
        Effect_RotatePosition(work);
    }
    work              = SELF(PartyMember);
    work->header.step = work->header.step + 1;
}
