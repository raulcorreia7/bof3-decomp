#include "magic114_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

INCLUDE_ASM(func_801EEC44);

INCLUDE_ASM(func_801EEDA0);

MATCH void func_801EEE84(void) {
    u8 temp_v0;

    temp_v0       = g_Task->timer + 1;
    g_Task->timer = temp_v0;
    if ((temp_v0 & 0xFF) >= 0x21U) {
        g_Task->mode += 1;
        g_Task->unk_09 = 0;
    }
}

MATCH void func_801EEEE4(void) {
    u8 temp_v0;

    temp_v0        = g_Task->unk_09 + 1;
    g_Task->unk_09 = temp_v0;
    if ((temp_v0 & 0xFF) >= 0x21U) {
        g_Task->mode += 1;
        g_Task->unk_09 = 0;
    }
}

INCLUDE_ASM(func_801EEF44);

MATCH void func_801EEFFC(void) {
    u8 temp_v0;

    temp_v0        = g_Task->unk_09 - 1;
    g_Task->unk_09 = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_Task->mode += 1;
        return;
    }
    func_801F0FBC();
}

MATCH void func_801EF060(void) {
    u8 temp_v0;

    temp_v0       = g_Task->timer - 1;
    g_Task->timer = temp_v0;
    if (!(temp_v0 & 0xFF)) {
        g_Task->mode += 1;
        g_Task->unk_09 = 0x40;
    }
}

#include "overlays/bmagic/Effect_CountDownAndPlay.h"

INCLUDE_ASM(func_801EF128);

INCLUDE_ASM(func_801EF280);

MATCH void func_801EF6A8(void) {
    PartyBattler* src;
    SVECTOR       pos;
    SVECTOR       rot;
    MATRIX        matrix;
    long          flags;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = ((g_Task->timer & 0x1F) - 2) << 7;
    src    = (PartyBattler*)D_801EB4E0;
    pos.vx = (src->pos.x.fixed >> 9) - 0x4000;
    pos.vy = (src->pos.y.fixed >> 9) - 0x4000;
    pos.vz = -(COORD_INT(src->pos.z) + 0x200) / 2;
    RotTrans(&pos, &matrix.t, &flags);
    RotMatrix(&rot, &matrix);
    MulMatrix2((MATRIX*)g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}

MATCH void func_801EF774(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, TASK_BYTES[1]);
}

MATCH void func_801EF7B8(void) {
    SYS_DISPATCH_TASK((g_BMagicEffectFuncs + 3), 2, g_Task);
}

INCLUDE_ASM(func_801EF7FC);

INCLUDE_ASM(func_801EF8C0);

INCLUDE_ASM(func_801EFA80);

MATCH void func_801EFDD8(void) {
    SYS_DISPATCH_BYTE(D_801F1230, g_Task->step);
    if (g_Task->flags != 0 && g_Task->step != 0) {
        func_801F093C();
        func_801F04D4(g_Task->unk_0B);
        func_801F0004();
    }
}

/* Best 20 differences: bnez at 0x801EFE94; adjust work pointer reloads. */
/* blocker: work pointer lifetime; first diff: +0x34 lui v1 against lui a0. */
INCLUDE_ASM(func_801EFE70);

MATCH void func_801EFF1C(void) {
    s32 value;

    g_Task->unk_20 -= 5;
    if (g_Task->unk_14 == 0x30) {
        func_800A9610(g_BattleTargetSelector, 0x10U);
    }
    value          = g_Task->unk_14 + 2;
    g_Task->unk_14 = value;
    if (value == 0xC0) {
        g_Task->unk_0B = 1;
        g_Task->step += 1;
    }
}

MATCH void func_801EFFB0(void) {
    PartyBattler* work  = g_Task;
    u8            timer = work->unk_09 - 1;
    work->unk_09        = timer;
    work->unk_20 -= 5;
    work->unk_14 += 2;
    if (timer == 0) {
        func_801E5988();
    }
}

INCLUDE_ASM(func_801F0004);

INCLUDE_ASM(func_801F04D4);

INCLUDE_ASM(func_801F093C);

MATCH void func_801F0D08(void) {
    g_ScriptBank = 0x800C3800;
    SYS_DISPATCH_BYTE(D_801F1230 + 3, g_Task->step);
    g_ScriptBank = AREA_SCRIPT_BANK;
}

MATCH void func_801F0D6C(void) {
    PartyBattler* work;

    g_Task->unk_25    = 0x1D;
    g_Task->unk_26    = 0;
    g_Task->unk_27    = 0x1A;
    g_Task->unk_28    = 1;
    g_Task->unk_2A    = (g_Task->facing - 1) & 1;
    g_Task->unk_29    = 4;
    g_Task->unk_24    = 0;
    work              = g_Task;
    work->unk_2B      = 0;
    work->unk_2C.half = 0;
    g_Task->unk_09    = 0;
    g_Task->step += 1;
    Actor_SelectScript(0);
    func_8014D290();
}

MATCH void func_801F0E4C(void) {
    if (func_8014DAEC() & BYTE_MASK) {
        func_801E5988();
        return;
    }
    func_8014D290();
}

INCLUDE_ASM(func_801F0E90);

INCLUDE_ASM(func_801F0FBC);
