#include "magic094_03.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    Callback table[2] = {func_801EEC5C, func_801EED60};

    table[SP_REF(u8*, 0x44)[1]]();
}

INCLUDE_ASM(func_801EEC5C);

/* Copies unk_2E and unk_30 - 0x10 from g_BattleSelectedActor; at unk_0B 0xFF frees the palette
 * fade of the target (party row below 3, else g_BattleEnemies + selector * 0x118) with
 * GFX_FreePaletteFadeTarget, then func_800AF814(selector), func_800A9820(selector),
 * BATTLE_RAISE_STATE and func_801E5988. Tried the selector read directly, through a volatile u8
 * pointer local and through a u8 slot local: first differing instruction sw ra,20(sp) retail
 * against sw ra,16(sp) (retail keeps the selector address in s0, frame 0x18 with s0 saved;
 * candidate saves no s0 and is 8 bytes shorter). Needs a g_BattleEnemies row in the magic094 table
 * and a func_800AF814(u32) prototype. */
INCLUDE_ASM(func_801EED60);

INCLUDE_ASM(func_801EEE4C);

MATCH void func_801EEF1C(void) {
    func_800A9610(g_BattleTargetSelector, 32);
    g_SpadWork->unk_09 = 0;
    g_SpadWork->unk_0A = 0;
    g_SpadWork->step_01++;
}

INCLUDE_ASM(func_801EEF7C);

INCLUDE_ASM(func_801EF078);

INCLUDE_ASM(func_801EF0FC);

INCLUDE_ASM(func_801EF14C);

MATCH void func_801EF654(void) {
    SVECTOR pos;
    SVECTOR rot;
    MATRIX  matrix;
    long    flags;

    PushMatrix();
    rot.vx = 0;
    rot.vy = 0;
    rot.vz = g_SpadWork->unk_0A << 4;
    pos.vx = (g_SpadWork->coord_x_34.raw >> 9) - 0x4000;
    pos.vy = (g_SpadWork->coord_y_38.raw >> 9) - 0x4000;
    pos.vz = -g_SpadWork->word_3C.half.span_3E / 2;
    RotTrans(&pos, &matrix.t, &flags);
    RotMatrix(&rot, &matrix);
    MulMatrix2((MATRIX*)g_CameraMatrix, &matrix);
    SetRotMatrix(&matrix);
    SetTransMatrix(&matrix);
}

INCLUDE_ASM(func_801EF710);
