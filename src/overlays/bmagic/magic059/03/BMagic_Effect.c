#include "magic059_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC04);

INCLUDE_ASM(func_801EED0C);

INCLUDE_ASM(func_801EF118);

MATCH void func_801EF1E0(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->header.mode);
}

INCLUDE_ASM(func_801EF224);

MATCH void func_801EF4C4(void) {
    u8* work;

    *(u8*)((u8*)g_Task + 0x09) = 0;
    g_Task->timer              = 0;
    work                       = (u8*)g_Task;
    work[2] += 1;
}

MATCH void func_801EF504(void) {
    PartyBattler* work;

    work = g_Task;
    work->unk_09++;
    work = g_Task;
    work->timer += 2;
    if (work->timer == 32) {
        work = g_Task;
        work->header.step++;
    }
}

MATCH void func_801EF570(void) {
    u8 timer;

    timer          = g_Task->unk_09 + 1;
    g_Task->unk_09 = timer;
    if (timer == 0xA0) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

#include "overlays/bmagic/Effect_CountDownTimer.h"

MATCH void func_801EF638(void) {
    PartyBattler* src;
    SVECTOR       pos;
    SVECTOR       rot;
    MATRIX        matrix;
    long          flags;

    PushMatrix();
    src                      = (PartyBattler*)g_BattleEffectBattler;
    rot.vx                   = 0;
    rot.vy                   = 0;
    rot.vz                   = 0;
    g_Task->pos.x.fixed      = src->pos.x.fixed;
    g_Task->pos.y.fixed      = src->pos.y.fixed;
    COORD_INT(g_Task->pos.z) = COORD_INT(src->pos.z);
    pos.vx                   = (g_Task->pos.x.fixed >> 9) - 0x4000;
    pos.vy                   = (g_Task->pos.y.fixed >> 9) - 0x4000;
    pos.vz                   = -COORD_INT(g_Task->pos.z) / 2;
    RotTrans(&pos, &matrix.t, &flags);
    RotMatrix(&rot, &matrix);
    MulMatrix2(&g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}

INCLUDE_ASM(func_801EF70C);

MATCH void func_801EFE48(void) {
    SYS_DISPATCH_TASK(g_BMagicEffectFuncs + 5, 1, g_Task);
}

INCLUDE_ASM(func_801EFE8C);

INCLUDE_ASM(func_801F0018);

MATCH void func_801F0070(void) {
    PartyBattler* work;

    work = g_Task;
    work->unk_09++;
    work = g_Task;
    work->timer++;
    if (work->timer == 32) {
        work = g_Task;
        work->header.step++;
    }
}

MATCH void func_801F00DC(void) {
    u8 timer;

    timer          = g_Task->unk_09 + 1;
    g_Task->unk_09 = timer;
    if (timer == 160) {
        g_Task->header.step = g_Task->header.step + 1;
    }
}

MATCH void func_801F012C(void) {
    PartyBattler* work;
    u8            count;

    work = g_Task;
    work->unk_09++;
    work        = g_Task;
    count       = work->timer - 1;
    work->timer = count;
    if (count == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B--;
        Actor_Clear();
    }
}

INCLUDE_ASM(func_801F01A4);

/* func_801F0490 */
#include "overlays/bmagic/BMagic_AllocEffect.h"

/* func_801F04F4 */
MATCH void Actor_Clear(void) {
    BMagic_ResetLocalWork();
}

INCLUDE_ASM(func_801F0544);
