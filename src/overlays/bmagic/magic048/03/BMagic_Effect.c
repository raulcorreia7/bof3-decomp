#include "magic048_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

INCLUDE_ASM(func_801EEC70);

#include "overlays/bmagic/Effect_CountDownTimerQueueFx.h"

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEE70 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEEB4(void) {
    SYS_DISPATCH_BYTE(D_801EF81C, g_Task->header.step);
    if (g_Task->header.step != 0 && g_Task->header.flags != 0) {
        func_801EF5C8();
        func_801EF234();
        PopMatrix();
    }
}

MATCH s32 func_801EEF3C(void) {
    PartyMember* work;
    FAKE_REG(s32, scroll, "a1"); /* FAKE: pins the scroll offset to retail a1; the best plain form differs in 6 instructions (scroll and battler registers). */
    u8 count;

    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if ((count & BYTE_MASK) == 0) {
        func_801EF6A0();
        g_Task->unk_0C = 0x10000;
        g_Task->unk_10 = 0;
        func_801DD350(g_Task);
        g_Task->pos.x.fixed = g_BattleEffectBattler->pos.x.fixed + g_Task->unk_0C;
        g_Task->pos.y.fixed = g_BattleEffectBattler->pos.y.fixed + g_Task->unk_10;
        g_Task->unk_0C      = 0x80000;
        g_Task->unk_10      = 0;
        func_801DD350(g_Task);
        work = g_Task;
        work->unk_0C += g_AreaScrollTargetX;
        FAKE_BARRIER(); /* FAKE: keeps the height read below the velocity store. */
        work->unk_14 = COORD_INT(work->pos.z) + 0x100;
        scroll       = g_AreaScrollTargetY;
        work->unk_10 += scroll;
        COORD_INT(work->pos.z) = COORD_INT(g_BattleEffectBattler->pos.z) + 0x100;
        work->unk_09           = 0;
        g_Task->timer          = 0;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF05C(void) {
    VECTOR pos;

    g_Task->unk_09 += 1;
    pos.vx = (g_Task->unk_0C >> 9) - 0x4000;
    pos.vy = (g_Task->unk_10 >> 9) - 0x4000;
    pos.vz = g_Task->unk_14 >> 1;
    func_800AF3A0(pos, 0x10);
    if (g_Task->timer != 16) {
        g_Task->timer += 1;
    }
    if (func_800AF6B8(g_Task->unk_0C, g_Task->unk_10, g_Task->pos.z.fixed, 0x60000) != 0) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF158(void) {
    VECTOR pos;
    u8     count;

    pos.vx = (g_Task->unk_0C >> 9) - 0x4000;
    pos.vy = (g_Task->unk_10 >> 9) - 0x4000;
    pos.vz = g_Task->unk_14 >> 1;
    func_800AF3A0(pos, 0x10);
    g_Task->unk_09 = g_Task->unk_09 + 1;
    count          = g_Task->timer - 1;
    g_Task->timer  = count;
    if (!(count & BYTE_MASK)) {
        g_BattleEffectBattler->param.unk_0B -= 1;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF234);

MATCH void func_801EF5C8(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = ratan2(g_Task->unk_10 - g_Task->pos.y.fixed, g_Task->unk_0C - g_Task->pos.x.fixed) & ANGLE_MASK;
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
}

INCLUDE_ASM(func_801EF6A0);
