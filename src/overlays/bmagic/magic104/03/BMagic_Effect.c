#include "magic104_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC14.h"

INCLUDE_ASM(func_801EEC80);

MATCH void func_801EEE7C(void) {
    if (g_Task->unk_0B == 7) {
        g_Task->unk_09 = 8;
        g_Task->mode += 1;
    }
}

INCLUDE_ASM(func_801EEEC0);

MATCH void func_801EF03C(void) {
    if (g_Task->unk_0B == 7) {
        func_800A9820(g_BattleTargetSelector);
        g_BattleState |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}

MATCH void func_801EF09C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, g_Task->mode);
}

MATCH void func_801EF0E0(void) {
    SYS_DISPATCH_BYTE(D_801F08F0, g_Task->step);
    if (g_Task->flags != 0 && g_Task->step != 0) {
        func_801EFA54();
        func_801EFE34();
        func_801EFB2C();
        func_801EF370();
        PopMatrix();
    }
}

MATCH void func_801EF178(void) {
    s32 var_a0;
    u8  temp_v0;

    temp_v0       = g_Task->timer - 1;
    g_Task->timer = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        var_a0 = 0x100;
        if (g_Task->unk_0B & 1) {
            var_a0 = 0x101;
        }
        SND_QueueSelectionFx(var_a0);
        g_Task->unk_09 = 0;
        g_Task->timer  = 0;
        g_Task->step += 1;
    }
}

MATCH void func_801EF21C(void) {
    u8 temp_v1;

    temp_v1        = g_Task->unk_09 + 1;
    g_Task->unk_09 = temp_v1;
    if ((temp_v1 & 0xFF) == 8) {
        g_Task->timer = 0;
        g_Task->step += 1;
    }
}

/* Template: bmagic/magic040 func_801EF114; size 0x6C against retail 0x7C, first difference lbu v0,9(v1) at +0x0C. */
MATCH void func_801EF27C(void) {
    u8 temp_v0;

    g_Task->timer += 1;
    temp_v0        = g_Task->unk_09 + 1;
    g_Task->unk_09 = temp_v0;
    if ((temp_v0 & 0xFF) == 0x10) {
        g_Task->timer = 0;
        g_Task->step += 1;
    }
}

MATCH void func_801EF2F8(void) {
    PartyBattler* work;
    PartyBattler* active;

    work         = g_Task;
    work->timer  = work->timer + 1;
    work         = g_Task;
    work->unk_09 = work->unk_09 + 1;
    if (work->unk_09 == 0x18) {
        active         = BATTLE_ACTIVE_WORK;
        active->unk_0B = g_Task->unk_0B;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF370);

MATCH void func_801EFA54(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = 0;
    if (g_Task->slot == 0xC) {
        rot.vz = (g_FrameCount & 0xF) << 8;
    }
    BMAGIC_PROJECT_ACTOR_MATRIX(g_Task);
}

INCLUDE_ASM(func_801EFB2C);

INCLUDE_ASM(func_801EFE34);

MATCH void func_801F020C(void) {
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetGraphType() != 1 ? (GetGraphType() == 2 ? 0xA5 : 0x35) : 0xA5, 0);
    GFX_AddPrim(4, 0xC);
    SYS_DISPATCH_BYTE(D_801F0900, g_Task->step);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetGraphType() != 1 ? (GetGraphType() == 2 ? 0xA5 : 0x35) : 0xA5, 0);
    GFX_AddPrim(4, 0xC);
}

MATCH void func_801F02F4(void) {
    PartyBattler* work;

    work = g_Task;
    if (work->timer == 0) {
        work->unk_09             = 8;
        work->pos.z.part.integer = work->pos.z.part.integer + 0x200;
        Bmagic_NextStep();
    } else {
        work->timer = work->timer - 1;
    }
}

#ifdef NON_MATCHING
MATCH void func_801F034C(void) {
    u8  next;
    u16 span;

    func_801EFA54();
    func_801F03C4();
    PopMatrix();
    next                  = g_Task->unk_09 - 1;
    span                  = (u16)(g_Task->pos.z.half.hi - 0x40);
    g_Task->unk_09        = next;
    g_Task->pos.z.half.hi = span;
    if (!(next & 0xFF)) {
        D_801EB4E0->unk_0B = g_Task->unk_0B;
        func_801E5988();
    }
}
#else
INCLUDE_ASM(func_801F034C);
#endif

INCLUDE_ASM(func_801F03C4);
