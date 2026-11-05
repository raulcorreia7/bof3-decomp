#include "magic078_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC04);

INCLUDE_ASM(func_801EECFC);

#include "overlays/bmagic/Effect_PlayOnIdleTick.h"

MATCH void func_801EEEE4(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EEF28);

INCLUDE_ASM(func_801EF08C);

#include "overlays/bmagic/Effect_CountDownAndStep.h"

INCLUDE_ASM(func_801EF12C);

MATCH void func_801EF1CC(void) {
    u8 count;

    count                             = g_SpadWork->word_08.byte.timer_0A - 1;
    g_SpadWork->word_08.byte.timer_0A = count;
    if (count == 0) {
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B = 1;
        g_SpadWork->unk_02                      = g_SpadWork->unk_02 + 1;
    }
}

void func_801EF228(void) {
    if (D_801EB4E0->word_08.byte.unk_0B == 2) {
        g_SpadWork->word_08.byte.timer_0A = 0;
        g_SpadWork->unk_02 += 1;
    }
}

INCLUDE_ASM(func_801EF278);

INCLUDE_ASM(func_801EF2CC);

INCLUDE_ASM(func_801EF318);

INCLUDE_ASM(func_801EFE14);

/* Follows BMAGIC_PROJECT_ACTOR_MATRIX (bmagic.h), but the work pointer lives in $a1 and a
 * type-13 branch loads a word into the rotation before the projection. */
MATCH void func_801EFEB8(void) {
    PartyBattler* work;
    SVECTOR       pos;
    SVECTOR       rot;
    MATRIX        matrix;
    long          flags;

    PushMatrix();
    work   = g_SpadWork;
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = 0;
    if (work->slot == 0xD) {
        rot.vz = work->unk_0C;
    }
    pos.vx = (work->coord_x_34.raw >> 9) - 0x4000;
    pos.vy = (work->coord_y_38.raw >> 9) - 0x4000;
    pos.vz = -work->word_3C.half.span_3E / 2;
    RotTrans(&pos, &matrix.t, &flags);
    RotMatrix(&rot, &matrix);
    MulMatrix2((MATRIX*)g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}

INCLUDE_ASM(func_801EFF84);

INCLUDE_ASM(func_801F00A0);

INCLUDE_ASM(func_801F00EC);

INCLUDE_ASM(func_801F014C);

MATCH void func_801F01D0(void) {
    PartyBattler* work;

    work                        = g_SpadWork;
    work->word_08.byte.timer_0A = work->word_08.byte.timer_0A - 1;
    if (work->word_08.byte.timer_0A == 0) {
        SND_QueueSelectionFx(0x102);
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

INCLUDE_ASM(func_801F0230);

MATCH void func_801F02B4(void) {
    u8 timer;

    timer                             = g_SpadWork->word_08.byte.timer_0A + 1;
    g_SpadWork->word_08.byte.timer_0A = timer;
    if (timer == 8) {
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F02FC);

#include "overlays/bmagic/Effect_SetActorMatrix.h"
