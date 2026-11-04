#include "game_00.h"

/* nonmatching unmeasured: tried 72.01%: u8 record copy base, pointer locals val13/val0 for D_80145FBC/D_1F800008;
 * remaining: record-copy loop biv form (retail lw 0..0xc from a2), D_80146111 compare against g_PartySize reg not const
 * 3, hoisted lui a0 base. */
#ifdef NON_MATCHING
NON_MATCHING void func_801B21E8(void) {
    s16*  val0;
    s32   cnt;
    s32   tmp0;
    s32   tmp1;
    s32   tmp2;
    s32   tmp3;
    s32   val1;
    s32   val2;
    s32   val3;
    s32   val4;
    s32   val5;
    s32   val6;
    s32   val7;
    s32   val8;
    s32   val9;
    s32   val10;
    u32*  tmp4;
    u32*  tmp5;
    u32*  tmp6;
    u32*  tmp7;
    u32*  tmp8;
    u32*  tmp9;
    u8*   val11;
    u8*   val12;
    u8*   val13;
    u8    tmp10;
    u8    val14;
    void* tmp11;
    /* FAKE: unused frame, 8 bytes. */
    STACK_PADS(u8, 8);

    val3  = 3;
    val14 = g_GameState->flags_12C.u8_value;
    if (D_80145FD1 == 3) {
        Party_SwapBattlerRows(0, 1, 1);
        if (g_PartySize == 3) {
            if (D_80146111 == 3) {
                Party_SwapBattlerRows(1, 2, 1);
            }
        }
    } else if (g_PartySize == 3) {
        if (D_80146111 == g_PartySize) {
            Party_SwapBattlerRows(0, 2, 1);
        }
    }
    val4 = 0;
    cnt  = g_PartySize;
    if (cnt > 0) {
        val13 = &D_80145FBC;
        val13 = &D_80145FBC;
        val0  = &D_1F800008;
        val0  = &D_1F800008;
        val6  = -2;
        val5  = 0;
        do {
            if (D_80145E91[val5] == 3) {
                tmp5        = (u8*)g_BattlePartyBattlers + val5;
                g_SpadWork  = tmp5;
                g_GameState = tmp5;
                func_801C1254(FIELD(u8, tmp5, 0x79u), val4 & BYTE_MASK);
                g_GameState->flags_12C.u8_value = val14;
                if (g_GameState->flags_12C.u8_value & 1) {
                    FIELD(s8, g_SpadWork, 0x29u) = 4;
                }
                val11 = (u8*)g_Characters;
                val12 = (u8*)g_GameState + 0x74;
                val11 += g_CharSlot[g_GameState->slot_index_79] * 0xA4;
                tmp11 = val11 + 0xA0;
                do {
                    FIELD(s32, val12, 0)    = FIELD(s32, val11, 0);
                    FIELD(s32, val12, 0x4u) = FIELD(s32, val11, 0x4u);
                    FIELD(s32, val12, 0x8u) = FIELD(s32, val11, 0x8u);
                    FIELD(s32, val12, 0xCu) = FIELD(s32, val11, 0xCu);
                    val11 += 0x10;
                    val12 += 0x10;
                } while (val11 != tmp11);
                *val12                = *val11;
                g_GameState->slot_13C = (u8)g_CharSlot[g_GameState->slot_index_79];
                D_80144F5A[val4]      = g_GameState->slot_index_79;
                if (val4 != 0) {
                    func_801C2438();
                    tmp6                                = g_SpadWork;
                    *(u8*)(tmp6)                        = (u8)(*(u8*)(tmp6) & 0xBF);
                    g_SpadWork->tint.signed_bytes.flags = 1;
                    g_SpadWork->direction_08            = (u8)(D_80145E98 ^ 4);
                }
                if (!(*val13 & 1) && (val4 != 0)) {
                    tmp4  = g_SpadWork;
                    tmp10 = FIELD(u8, tmp4, 0x8u);
                    tmp1  = val6 + (tmp10 * 4);
                    val3 =
                        func_801B1B2C(FIELD(s32, val13, -0xF8) + (*(s32*)(s_EntityPlacementOffsets + tmp1 * 4) << 0xF),
                                      FIELD(s32, val13, -0xF4) + (*(s32*)(D_801CD08D + tmp1 * 4) << 0xF), (s32)tmp10,
                                      FIELD(u8, tmp4, 0x70u));
                    val8 = val3 & BYTE_MASK;
                    val9 = 0;
                    if (val8 != 0) {
                        val9 = func_801B1C18(*(s32*)val0, FIELD(s32, val0, 0x4u), g_SpadWork->state_70.byte);
                        val8 = val3 & BYTE_MASK;
                    }
                    if ((val8 == 0) || !(val9 & BYTE_MASK)) {
                        val1 = D_80145EC4;
                        val2 = D_80145EC8;
                        goto block_26; /* retail branch */
                    }
                } else {
                    val1 = FIELD(s32, val13, -0xF8);
                    val2 = FIELD(s32, val13, -0xF4);
                block_26:
                    func_801B1B2C(val1, val2, g_SpadWork->direction_08, g_SpadWork->state_70.byte);
                }
                tmp7                    = g_SpadWork;
                FIELD(s32, tmp7, 0x34u) = (s32) * (s32*)(&D_1F800008);
                FIELD(s32, tmp7, 0x38u) = FIELD(s32, val0, 0x4u);
                tmp8                    = g_SpadWork;
                FIELD(s16, tmp8, 0x3Eu) = Area_ReadHeight(FIELD(s32, tmp7, 0x34u), FIELD(s32, val0, 0x4u));
                Actor_SelectScript(FIELD(u8, tmp8, 0x8u));
            }
            val6 += 2;
            val4 += 1;
            val5 += BATTLE_PARTY_STRIDE;
        } while (val4 < (s32)g_PartySize);
    }
    g_SpadWork       = (Actor*)g_BattlePartyBattlers;
    g_GameState      = (GameStateRecord*)g_BattlePartyBattlers;
    g_AreaCameraStep = 0x20;
    tmp3             = g_AreaScrollTargetX - D_80145EC4;
    val7             = tmp3;
    if (tmp3 < 0) {
        val7 = -val7;
    }
    tmp2  = g_AreaScrollTargetY - D_80145EC8;
    val10 = tmp2;
    if (tmp2 < 0) {
        val10 = -val10;
    }
    g_AreaScrollTargetX = D_80145EC4;
    g_AreaScrollTargetY = D_80145EC8;
    if (val7 < val10) {
        val7 = val10;
    }
    tmp0 = ((u32)val7 >> 0xD) & BYTE_MASK;
    if (tmp0 != 0) {
        g_AreaCameraHeightStep = (s16)((s16)((u16)D_80145ECE - g_AreaCameraHeight) / tmp0);
    } else {
        g_AreaCameraHeightStep = 0;
    }
    FIELD(s8, g_SpadWork, 0x9u) = 4;
    tmp9                        = g_SpadWork;
    FIELD(u8, tmp9, 0x2u)       = (u8)(FIELD(u8, tmp9, 0x2u) + 1);
}
#else
INCLUDE_ASM(func_801B21E8);
#endif
