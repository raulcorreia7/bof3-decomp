#include "magic132_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC18.h"

INCLUDE_ASM(func_801EEC88);

INCLUDE_ASM(func_801EEDD0);

INCLUDE_ASM(func_801EEEF4);

#include "overlays/bmagic/Effect_RequestTargetOnTimerZero.h"

MATCH void func_801EF0A4(void) {
    if (g_Task->param.unk_0B == 0xFF) {
        D_8014637C->unk_29 = 4;
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}

/* func_801EF114 */
#include "overlays/bmagic/BMagic_DispatchEffectMode.h"

extern Callback D_801EFD5C[];

MATCH void func_801EF158(void) {
    D_801EFD5C[g_Task->header.step]();
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) {
        if (g_Task->header.step >= 2) {
            g_Task->timer += 1;
        }
        func_801EF4A4();
        func_801EF5B0();
        func_801EF914();
        PopMatrix();
    }
}

MATCH void func_801EF200(void) {
    u8  timer;
    s32 z;

    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if ((timer & BYTE_MASK) == 0) {
        g_Task->facing = g_BattleEffectBattler->facing;
        g_Task->unk_0C = -0x80000;
        g_Task->unk_10 = -0xF0000;
        func_801DD350(g_Task);
        g_Task->pos.x.fixed = g_AreaScrollTargetX + g_Task->unk_0C;
        g_Task->pos.y.fixed = g_AreaScrollTargetY + g_Task->unk_10;
        z                   = g_BattleEffectBattler->pos.z.fixed + 0x800000;
        g_Task->unk_0C      = 0x8000;
        g_Task->unk_10      = 0;
        g_Task->pos.z.fixed = z;
        func_801DD350(g_Task);
        g_Task->param.unk_0B = 0x1A;
        g_Task->unk_09       = 0x2C;
        g_Task->timer        = 0;
        g_Task->unk_1C       = 0;
        g_Task->unk_20       = 0x80;
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF324(void) {
    PartyMember* work;
    u8           count;

    work         = g_Task;
    count        = work->unk_09 - 1;
    work->unk_09 = count;
    work->pos.x.fixed += work->unk_0C;
    work->pos.y.fixed += work->unk_10;
    if (count == 0) {
        g_Task->header.step++;
    }
}

MATCH void func_801EF388(void) {
    s32 phase;

    g_Task->param.unk_0B = (g_Task->param.unk_0B - 1) & 0x3F;
    phase                = g_Task->unk_1C + 2;
    g_Task->unk_1C       = phase;
    if (phase == 0x80) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF3E0(void) {
    g_Task->param.unk_0B = (g_Task->param.unk_0B - 1) & 0x3F;
    g_Task->unk_1C -= 2;
    g_Task->unk_20 -= 2;
    if (g_Task->unk_1C == 0x20) {
        g_Task->header.step += 1;
    }
}

MATCH void func_801EF44C(void) {
    g_Task->unk_1C -= 1;
    g_Task->unk_20 -= 2;
    if (g_Task->unk_1C == 0) {
        BATTLE_ACTIVE_WORK->param.unk_0B = 0xFF;
        func_801E5988();
    }
}

MATCH void func_801EF4A4(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    switch (g_Task->facing) {
        case 0:
            rot.vz = 0x400;
            break;
        case 1:
            rot.vz = 0x800;
            break;
        case 2:
            rot.vz = 0xC00;
            break;
        default:
            rot.vz = 0;
            break;
    }
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
}

INCLUDE_ASM(func_801EF5B0);

INCLUDE_ASM(func_801EF914);
