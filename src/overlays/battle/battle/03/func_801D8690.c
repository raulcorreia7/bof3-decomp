#include "battle_03.h"

/* 69.64%; opcode/regalloc: prologue saves s3/s4 instead of s1/s0; later register and branch differences remain. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D8690(s32 x, s32 y, s32 slot) {
    s16 tex_u;
    s16 temp_a1_190;
    s16 temp_v0_217;
    s16 var_a0_154;
    s16 var_s3;
    s16 var_s5;
    s32 temp_v0_233;
    s32 var_fp;
    s32 var_s0;
    s32 var_s1;
    s32 var_s2;
    s32 var_s6;
    s32 var_s7;
    s32 var_v0_226;
    s32 var_v1_238;
    u16 temp_v0_57;
    u32 temp_v0_61;
    u8  temp_v1_139;
    u8  var_s4;

    var_s2 = x;
    var_s1 = y;
    var_s0 = slot;
    var_s4 = var_s0 - 3;
    GFX_AddDrawMode(GetTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y) & HALF_MASK);
    var_s0 = var_s2 + 4;
    var_s0 <<= 0x10;
    var_s0     = var_s0 >> 0x10;
    temp_v0_57 = *(u16*)((u8*)&D_80033A08 + ((g_WindowStyle << 6) | 0x20));
    temp_v0_61 = temp_v0_57 & HALF_MASK;
    var_s6     = (temp_v0_61 >> 2) & 0xF8;
    var_s5     = (temp_v0_61 >> 7) & 0xF8;
    tex_u      = (temp_v0_57 & 0x1F) * 8;
    Battle_DrawWindowTile((s16)var_s0, (s16)(var_s1 + 8), 8U, 1U);
    func_801D9AB4((s16)var_s0, (s16)(var_s1 + 6), 2, 1);
    func_801D9AB4((s16)var_s0, (s16)(var_s1 + 0x19), 3, 1);
    GFX_AddDrawMode(GetTPage(0, 1, FONT_TPAGE_X, FONT_TPAGE_Y) & HALF_MASK);
    var_s0 = var_s2 << 0x10;
    var_s0 = (s32)(s16)var_s2;
    Battle_DrawWindowTile((s16)var_s0, (s16)(var_s1 + 2), 8U, 0U);
    var_s3 = var_s2 + 6;
    func_801D9DBC(var_s3, (s16)(var_s1 + 0xB), 9, 0, 0U);
    func_801D9AB4((s16)var_s0, (s16)var_s1, 2, 0);
    func_801D9AB4((s16)var_s0, (s16)(var_s1 + 0x13), 3, 0);
    var_fp      = var_s2;
    temp_v1_139 = g_BattleEnemyBattlers[var_s4].unk_7F;
    var_s7      = var_s1;
    if (temp_v1_139 == 1) {
        func_801D9E9C(var_s3, (s16)(var_s1 + 0xA), (u16)g_MenuCurrentPanel->unk_0B, (u16)g_MenuCurrentPanel->flags, (s8)(s32)temp_v1_139);
        var_a0_154 = var_fp + 4;
    } else {
        func_801D94D4((s32)(s16)(var_s2 + 0x24), (u32)(s16)(var_s1 + 0xC), 0, 0xFFFF);
        var_a0_154 = var_fp + 4;
    }
    var_s1 = var_s7 + 3;
    var_s1 <<= 0x10;
    var_s1 = var_s1 >> 0x10;
    UI_DrawTextString(var_a0_154, (s16)var_s1, 0, 8U, g_BattleEnemyBattlers[var_s4].name);
    var_s0 = var_fp + 2;
    var_s0 <<= 0x10;
    var_s0      = var_s0 >> 0x10;
    temp_a1_190 = var_s7 + 2;
    var_s3      = var_s6 & BYTE_MASK;
    var_s4      = tex_u;
    var_s2      = var_s5 & BYTE_MASK;
    func_801DA5A8((s16)var_s0, temp_a1_190, (s16)(var_fp + 0x49), temp_a1_190, (u8)(s32)var_s4, (u8)(s32)var_s3, (u8)var_s2);
    func_801DA5A8((s16)var_s0, (s16)var_s1, (s16)var_s0, (s16)(var_s7 + 0x12), (u8)(s32)var_s4, (u8)(s32)var_s3, (u8)var_s2);
    var_s6 -= 0x10;
    temp_v0_217 = tex_u - 0x10;
    var_s5 -= 0x10;
    if (temp_v0_217 < 0) {
        tex_u = 0;
    } else if (temp_v0_217 >= 0x100) {
        tex_u = 0xFF;
    } else {
        tex_u = temp_v0_217;
    }
    var_v0_226  = var_s6 << 0x10;
    temp_v0_233 = var_v0_226 >> 0x10;
    if (temp_v0_233 >= 0) {
        var_v1_238 = var_s6;
        if (temp_v0_233 >= 0x100) {
            var_v1_238 = 0xFF;
        }
    } else {
        var_v1_238 = 0;
    }
    var_s6 = var_v1_238;
    if (var_s5 >= 0) {
        var_s2 = (s32)var_s5;
        if (var_s5 >= 0x100) {
            var_s2 = 0xFF;
        }
    } else {
        var_s2 = 0;
    }
    var_s0 = var_fp + 0x49;
    var_s0 <<= 0x10;
    var_s0 = var_s0 >> 0x10;
    var_s1 = var_s7 + 0x12;
    var_s1 <<= 0x10;
    var_s1 = var_s1 >> 0x10;
    var_s3 = var_s6 & BYTE_MASK;
    var_s4 = tex_u;
    var_s2 &= BYTE_MASK;
    Battle_DrawLine((s16)var_s0, (s16)(var_s7 + 2), (s16)var_s0, (s16)var_s1, (u8)(s32)var_s4, (u8)(s32)var_s3, (u8)var_s2);
    Battle_DrawLine((s16)(var_fp + 2), (s16)var_s1, (s16)var_s0, (s16)var_s1, (u8)(s32)var_s4, (u8)(s32)var_s3, (u8)var_s2);
}
#else
INCLUDE_ASM(func_801D8690);
#endif
