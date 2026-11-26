#include "magic062_03.h"
#include "menu/clock.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/Effect_LaunchFromRing.h"

MATCH void func_801EFD80(void) {
    s32          timer;
    s32          vel;
    PartyMember* task;
    PartyMember* reset;

    Battle_ProjectRange();
    func_801F0910((RANDOM_MASK(3)) | 0x18);
    BMAGIC_DRAW_IN_ACTOR_MATRIX(func_801F026C);
    if (g_FrameCount & 0x1) {
        SELF(PartyMember)->unk_09 += 1;
    }
    task         = SELF(PartyMember);
    timer        = task->timer - 1;
    vel          = task->unk_14 + task->unk_20;
    task->timer  = timer;
    task->unk_14 = vel;
    task->pos.z.part.integer += vel;
    if ((timer & BYTE_MASK) == 0) {
        reset         = SELF(PartyMember);
        reset->unk_14 = -0x10;
        reset->timer  = 8;
        reset->unk_20 = 4;
        SELF(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EFE74(void) {
    s32          timer;
    s32          vel;
    PartyMember* task;

    Battle_ProjectRange();
    func_801F0910((RANDOM_MASK(3)) | 0x18);
    BMAGIC_DRAW_IN_ACTOR_MATRIX(func_801F026C);
    if (g_FrameCount & 0x1) {
        SELF(PartyMember)->unk_09 += 1;
    }
    task         = SELF(PartyMember);
    timer        = task->timer - 1;
    vel          = task->unk_14 + task->unk_20;
    task->timer  = timer;
    task->unk_14 = vel;
    task->pos.z.part.integer += vel;
    if ((timer & BYTE_MASK) == 0) {
        SELF(PartyMember)->timer = 28 - SELF(PartyMember)->param.unk_0B;
        SELF(PartyMember)->header.step += 1;
    }
}
