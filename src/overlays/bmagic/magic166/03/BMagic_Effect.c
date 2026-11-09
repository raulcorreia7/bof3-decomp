#include "magic166_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    PartyMember* saved_task;
    PartyMember* saved_battler;
    u8           i;

    BMagic_DispatchTaskPair(func_801EED04, Effect_PlayOnZeroTick);

    for (i = 0; i < BMAGIC_EFFECT_COUNT; i++) {
        if (D_801EF724[i].header.flags & BMAGIC_EFFECT_IN_USE) {
            saved_task            = g_Task;
            saved_battler         = g_BattleEffectBattler;
            g_Task                = (PartyMember*)&D_801EF724[i];
            g_BattleEffectBattler = D_801EF724[i].target.party;
            BMagic_DispatchEffectMode();
            g_BattleEffectBattler = saved_battler;
            g_Task                = saved_task;
        }
    }
}

INCLUDE_ASM(func_801EED04);

#include "overlays/bmagic/Effect_PlayOnZeroTick.h"

/* func_801EEEF0 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

MATCH void func_801EEF34(void) {
    SYS_DISPATCH_BYTE(D_801EF71C, g_Task->header.step);
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        func_801EF284();
        func_801EF380();
        PopMatrix();
    }
}

INCLUDE_ASM(func_801EEFBC);

INCLUDE_ASM(func_801EF138);

MATCH void func_801EF284(void) {
    SVECTOR      pos;
    SVECTOR      rot;
    MATRIX       matrix;
    long         flags;
    PartyMember* work;
    s32          roll;

    PushMatrix();
    work   = g_Task;
    rot.vx = 0x400;
    rot.vy = 0xE00;
    if (work->param.unk_0B & 1) {
        roll = g_FrameCount ^ 0x1F;
    } else {
        roll = g_FrameCount;
    }
    rot.vz = (roll & 0x1F) << 7;
    FAKE_BARRIER(); /* FAKE: keeps the roll store before the position load. */
    pos.vx = (g_Task->pos.x.fixed >> 9) - 0x4000;
    pos.vy = (g_Task->pos.y.fixed >> 9) - 0x4000;
    pos.vz = -COORD_INT(g_Task->pos.z) / 2;
    RotTrans(&pos, (VECTOR*)matrix.t, &flags);
    RotMatrix(&rot, &matrix);
    MulMatrix2(&g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}

INCLUDE_ASM(func_801EF380);

/* func_801EF69C */
#include "overlays/bmagic/BMagic_AllocEffect.h"
