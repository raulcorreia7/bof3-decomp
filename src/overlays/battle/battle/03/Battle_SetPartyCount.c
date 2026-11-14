#include "battle_03.h"

#ifdef NON_MATCHING
/* func_801D750C */
NON_MATCHING void Battle_SetPartyCount(s32 x, s32 y) {
    s32 u;
    s32 v_tex;
    s16 var_a0_255;
    s16 var_s0;
    s16 var_s7;
    s32 temp_v0_199;
    s32 var_a2_187;
    s32 var_a2_225;
    s32 var_a2_248;
    s32 var_fp;
    s32 var_s2;
    s32 var_s3;
    s32 var_s4;
    s32 var_s5;
    s32 var_s6;
    u16 temp_a3_277;
    u16 temp_v0_81;
    u16 temp_v1_181;
    u16 temp_v1_221;
    u16 temp_v1_245;
    u32 temp_v0_85;
    s32 var_s1;
    u8  temp_a2_160;
    u8  temp_v0_153;

    var_s2 = x;
    var_s3 = y;
    GFX_AddDrawMode(GetTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y) & HALF_MASK);
    var_s0 = var_s2 << 0x10;
    var_s0 = (s16)var_s2;
    func_801D9AB4(var_s0, (s16)var_s3, ((g_Battle.party_count * 2) + 0xA) & 0xFE, 1);
    func_801D9AB4(var_s0, (s16)(var_s3 + 0x18), ((g_Battle.party_count * 2) + 0xB) & BYTE_MASK, 1);
    Battle_DrawWindowTile(var_s0, (s16)(var_s3 + 2), (g_Battle.party_count + 0xD) & BYTE_MASK, 1U);
    var_s4     = var_s2;
    var_s5     = 0;
    temp_v0_81 = *(((g_WindowStyle << 6) | 0x20) + &D_80033A08);
    var_s6     = var_s3;
    temp_v0_85 = temp_v0_81 & HALF_MASK;
    if (g_Battle.party_count != 0) {
        var_s3 += 0xE;
        var_s7 = (s16)var_s3;
        var_fp = (temp_v0_85 >> 7) & 0xF8 & BYTE_MASK;
        u      = ((temp_v0_81 & 0x1F) * 8) & BYTE_MASK;
        v_tex  = (temp_v0_85 >> 2) & 0xF8 & BYTE_MASK;
        do {
            var_s3 = var_s4 + 0x14;
            var_s2 = (s32)(s16)var_s3;
            func_801D9DBC((s16)var_s2, var_s7, 9, 0, 0U);
            var_s0 = var_s5 & BYTE_MASK;
            var_s1 = (var_s0 + 0xD) * 0x24;
            func_801D9E9C((s16)var_s2, var_s7, (u16)((u8*)&D_8014833B)[var_s1], (u16)((u8*)&D_8014833D)[var_s1], 0);
            if (*(D_80145F22 + (var_s0 * BATTLE_PARTY_STRIDE)) != 0) {
                func_801DA5A8((s16)var_s2, var_s7, (s16)(var_s4 + (g_MenuPanelTasks[var_s0 + 0xD].unk_0C + 0x14)), var_s7, 0x64U, 0U, 0xC8U);
                temp_v0_153 = ((u8*)&D_8014833E)[var_s1];
                if (temp_v0_153 != 0) {
                    temp_a2_160 = g_MenuPanelTasks[var_s0 + 0xD].unk_0C;
                    func_801DA5A8((s16)(var_s4 + (temp_a2_160 + 0x14)), var_s7, (s16)(temp_v0_153 + (temp_a2_160 + var_s3)), var_s7, 0xC8U, 0U, 0U);
                }
            }
            temp_v1_181 = *(D_80145F10 + ((var_s5 & BYTE_MASK) * BATTLE_PARTY_STRIDE));
            if (temp_v1_181 & 0x4000) {
                var_a2_187 = 2;
            } else {
                var_a2_187 = (temp_v1_181 & 0xBFC) != 0;
            }
            temp_v0_199 = var_s5 & BYTE_MASK;
            var_s0      = temp_v0_199 * 4;
            var_s0      = temp_v0_199 * 5;
            var_s0      = temp_v0_199 * BATTLE_PARTY_STRIDE;
            UI_DrawTextString((s16)(var_s4 + 6), (s16)(var_s6 + 5), var_a2_187, 5U, var_s0 + D_80145F04);
            func_801DA078((var_s4 + 0x3A) & HALF_MASK, (var_s6 + 6) & HALF_MASK, 1);
            func_801DA078((var_s4 + 4) & HALF_MASK, (s16)var_s7, 0);
            temp_v1_221 = *(D_80145F10 + var_s0);
            var_a2_225  = 2;
            if (!(temp_v1_221 & 0x4000)) {
                var_a2_225 = (temp_v1_221 >> 0xB) & 4;
            }
            var_s0 = (var_s5 & BYTE_MASK) * BATTLE_PARTY_STRIDE;
            func_801D94D4((s32)(s16)(var_s4 + 0x48), (u32)(s16)(var_s6 + 0xF), var_a2_225, (s32) * (D_80145F18 + var_s0));
            temp_v1_245 = *(D_80145F1A + var_s0);
            var_a2_248  = 2;
            if (temp_v1_245 != 0) {
                var_a0_255 = var_s4 + 0x48;
                if (!(*(D_80145F10 + var_s0) & 0x4000)) {
                    var_a2_248 = (temp_v1_245 < (u32)((u16) * (D_80145F22 + var_s0) >> 2)) * 4;
                    goto block_13;
                }
            } else {
            block_13:
                var_a0_255 = var_s4 + 0x48;
            }
            temp_a3_277 = *(D_80145F1A + ((var_s5 & BYTE_MASK) * BATTLE_PARTY_STRIDE));
            var_s5 += 1;
            func_801D94D4((s32)var_a0_255, (u32)(s16)(var_s6 + 8), var_a2_248, (s32)temp_a3_277);
            var_s3 = var_s4 + 2;
            var_s3 <<= 0x10;
            var_s3 = var_s3 >> 0x10;
            var_s1 = (s16)(var_s6 + 2);
            var_s2 = var_s4 + 0x5D;
            var_s2 <<= 0x10;
            var_s2 = var_s2 >> 0x10;
            func_801DA5A8((s16)var_s3, (s16)var_s1, (s16)var_s2, (s16)var_s1, (u8)u, (u8)v_tex, (u8)var_fp);
            var_s0 = var_s6 + 0x17;
            var_s0 <<= 0x10;
            var_s0 = (s16)(var_s0 >> 0x10);
            func_801DA5A8((s16)var_s3, (s16)(var_s6 + 3), (s16)var_s3, var_s0, (u8)u, (u8)v_tex, (u8)var_fp);
            func_801DA4B4((s16)var_s2, (s16)var_s1, (s16)var_s2, var_s0, (u8)u, (u8)v_tex, (u8)var_fp);
            func_801DA4B4((s16)var_s3, var_s0, (s16)var_s2, var_s0, (u8)u, (u8)v_tex, (u8)var_fp);
            var_s4 += 0x5E;
        } while ((u32)(var_s5 & BYTE_MASK) < (u8)g_Battle.party_count);
    }
}
#else
INCLUDE_ASM(Battle_SetPartyCount);
#endif
