#include "game_00.h"

/* nonmatching unmeasured: tried 57.84%: s8 table reads, signed count; gcc folds 0xC0 into the 0x80035600 constant
 * (retail keeps s2=0x5600, 5 saved regs not 6); retail return blocks sit at function head. */
#ifdef NON_MATCHING
NON_MATCHING u8 func_801BF11C(void) {
    s16  tmp0;
    s32  tmp1;
    s32  cnt;
    s32  tmp2;
    s32  tmp3;
    s32  tmp4;
    s32  val0;
    s32  val1;
    s32  val2;
    s32  val3;
    s32  val6;
    s32  val7;
    s32  val8;
    s32  val9;
    u32* tmp5;
    u32* tmp6;
    u32* tmp7;
    u32* tmp8;
    u8   tmp9;

    if (g_BattleOptions & 4) {
        return 1U;
    }
    tmp1       = g_BattleScrollDir * 2;
    D_80143F24 = g_AreaScrollTargetX + (s_CameraScrollDeltas[tmp1] << 0x10);
    D_80143F28 = g_AreaScrollTargetY + (s_CameraScrollDeltas[tmp1 + 1] << 0x10);
    val2       = 0;
    cnt        = g_PartySize;
    if (cnt > 0) {
        val6 = 1;
        val3 = 0;
        do {
            tmp6        = val3 + (u8*)g_BattlePartyBattlers;
            g_GameState = tmp6;
            g_Task      = tmp6;
            tmp9        = FIELD(u8, tmp6, 0xBu);
            if (tmp9 == 0) {
                val0 = 0;
                if (func_801C29A0(8) & 0xFF) {
                    val7 = 0 & 0xFF;
                loop_8:
                    if (D_80144F5D[val7] != g_GameState->slot_index_79) {
                        val0 += 1;
                        val7 = val0 & 0xFF;
                        if ((u32)(val0 & 0xFF) < 3U) {
                            goto loop_8; /* retail branch */
                        }
                    }
                    g_GameState->flags_12C.u8_value = (u8)(g_GameState->flags_12C.u8_value & 0xFE);
                    g_Task->unk_29                  = (u8)g_AreaDrawMode;
                    tmp4                            = (val0 & 0xFF) * 8;
                    tmp5                            = g_Task;
                    FIELD(s32, tmp5, 0x34u)         = (s32) * (D_80143F2C + tmp4);
                    tmp2                            = *(D_80143F30 + tmp4);
                    FIELD(s32, tmp5, 0x38u)         = tmp2;
                    tmp0                            = Area_ReadHeight(FIELD(s32, tmp5, 0x34u), tmp2);
                    tmp7                            = g_Task;
                    FIELD(s8, tmp7, 0x48u)          = 0;
                    FIELD(s16, tmp7, 0x3Eu)         = tmp0;
                    FIELD(s8, g_Task, 0xBu)         = 1;
                }
            } else if (tmp9 == 1) {
                val1 = 0;
                if (func_801C2894(8) & 0xFF) {
                    val8 = 0 * 2;
                    do {
                        val1 += 1;
                        tmp3                                = g_Task->unk_05 << 6;
                        *(u16*)(val8 + (tmp3 + 0x80039600)) = FIELD(u16, (tmp3 + 0x80035600 + val8), 0xC0u);
                        val8                                = val1 * 2;
                    } while (val1 < 0x20);
                    tmp8                             = g_Task;
                    g_GfxPalettePending              = 1;
                    *(u8*)(tmp8)                     = (u8)(*(u8*)(tmp8) & 0xDF);
                    FIELD(s8, g_Task, 0xBu)          = 0;
                    g_Task->tint.signed_bytes.unk_5D = 0;
                    g_Task->tint.signed_bytes.unk_5E = 0;
                    g_Task->tint.signed_bytes.unk_5F = 0;
                    g_Task->tint.signed_bytes.flags  = 0;
                    FIELD(s8, g_Task, 0xBu)          = 2;
                }
            }
            val3 += BATTLE_PARTY_STRIDE;
            func_8014D978();
            val2 += 1;
        } while (val2 < (s32)g_PartySize);
    }
    val2 = 0;
    if ((s32)g_PartySize > 0) {
        val9 = 0;
    loop_19:
        val2 += 1;
        if ((&D_80145E9B)[val9] == 2) {
            val9 += BATTLE_PARTY_STRIDE;
            if (val2 >= (s32)g_PartySize) {
                goto block_21; /* retail branch */
            }
            goto loop_19; /* retail branch */
        }
        return 0U;
    }
block_21:
    return 1U;
}
#else
INCLUDE_ASM(func_801BF11C);
#endif
