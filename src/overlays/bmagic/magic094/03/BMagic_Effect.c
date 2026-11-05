#include "magic094_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback table[2] = {func_801EEC5C, func_801EED60};

    table[TASK_BYTES[1]]();
}

INCLUDE_ASM(func_801EEC5C);

/* Copies the selected actor's unk_2E and unk_30 - 0x10; at unk_0B 0xFF releases the target and plays. */
MATCH void func_801EED60(void) {
    u32           slot;
    u8*           selector;
    PartyBattler* battler;

    g_Task->unk_2E.half = g_BattleSelectedActor->unk_2E.half;
    g_Task->unk_30.half = g_BattleSelectedActor->unk_30.half - 0x10;
    if (g_Task->unk_0B == 0xFF) {
        BMAGIC_RELEASE_TARGET_AND_PLAY();
    }
}

INCLUDE_ASM(func_801EEE4C);

MATCH void func_801EEF1C(void) {
    func_800A9610(g_BattleTargetSelector, 32);
    g_Task->unk_09 = 0;
    g_Task->timer  = 0;
    g_Task->mode++;
}

INCLUDE_ASM(func_801EEF7C);

MATCH void func_801EF078(void) {
    u8 temp_v1;
    u8 temp_v1_2;

    temp_v1 = g_Task->timer;
    if (temp_v1 < 0x10U) {
        g_Task->timer = temp_v1 + 1;
    }
    temp_v1_2      = g_Task->unk_09 + 1;
    g_Task->unk_09 = temp_v1_2;
    if ((temp_v1_2 & 0xFF) == 0x10) {
        g_Task->unk_09 = 0;
        g_Task->mode += 1;
    }
}

MATCH void func_801EF0FC(void) {
    u8 temp_v1;

    temp_v1        = g_Task->unk_09 + 1;
    g_Task->unk_09 = temp_v1;
    if ((temp_v1 & 0xFF) == 0x20) {
        D_801EB4E0->unk_0B = 0xFF;
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EF14C);

MATCH void func_801EF654(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = g_Task->timer << 4;
    pos.vx = (g_Task->pos.x.fixed >> 9) - 0x4000;
    pos.vy = (g_Task->pos.y.fixed >> 9) - 0x4000;
    pos.vz = -COORD_INT(g_Task->pos.z) / 2;
    RotTrans(&pos, &matrix.t, &flags);
    RotMatrix(&rot, &matrix);
    MulMatrix2((MATRIX*)g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}

INCLUDE_ASM(func_801EF710);
