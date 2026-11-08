#include "game_00.h"

/* nonmatching unmeasured: tried 63.54%: stride-1 spad, loaded counts; retail keeps count in a0 across loop and spad
 * base in a3 (pointer local), first-loop count copy move a1,v0. */
#ifdef NON_MATCHING
NON_MATCHING void func_801BFB34(void) {
    s32* val0;
    s32* val1;
    s32* val2;
    s32  tmp0;
    s32  tmp1;
    s32  tmp2;
    s32  tmp3;
    s32  tmp4;
    s32  val3;
    s32  val4;
    s32  val5;
    s32  val6;
    s32  val7;
    s32  val8;
    s32  val9;
    s32  val10;
    s32  val11;
    u32* tmp5;
    u32* tmp6;
    u8   tmp7;
    s32  cnt_a;
    s32  cnt_b;
    /* FAKE: unused frame, 56 bytes. */
    STACK_PADS(u8, 56);

    val4  = 0;
    cnt_a = g_PartySize;
    if (cnt_a > 0) {
        val0 = (s32*)&D_1F800000;
        val9 = 0;
        do {
            tmp2 = FIELD(s32, &D_80145EC4, val9);
            val9 += BATTLE_PARTY_STRIDE;
            val4 += 1;
            *val0 = tmp2;
            val0 += 1;
        } while (val4 < cnt_a);
    }
    val4  = 0;
    cnt_a = g_PartySize;
    if (cnt_a != 0) {
        val3 = 0;
        do {
            tmp3  = cnt_a & BYTE_MASK;
            val10 = 0;
            if (tmp3 > 0) {
            loop_7:
                val7 = val10 * 4;
                if (FIELD(u8, &g_BattlePartyBattlers[0].chr.character_id, val3) != g_PartyBattleOrder[val10]) {
                    val10 += 1;
                    if (val10 >= tmp3) {
                        goto block_9; /* retail branch */
                    }
                    goto loop_7; /* retail branch */
                }
            } else {
            block_9:
                val7 = val10 * 4;
            }
            val4 += 1;
            FIELD(s32, &D_80145EC4, val3) = FIELD(s32, &D_1F800000, val7);
            val3 += BATTLE_PARTY_STRIDE;
            cnt_a = g_PartySize;
        } while (val4 < cnt_a);
    }
    val4  = 0;
    cnt_b = g_PartySize;
    if (cnt_b > 0) {
        val1  = (s32*)&D_1F800000;
        val11 = 0;
        do {
            tmp4 = FIELD(s32, &D_80145EC8, val11);
            val11 += BATTLE_PARTY_STRIDE;
            val4 += 1;
            *val1 = tmp4;
            val1 += 1;
        } while (val4 < cnt_b);
    }
    tmp7 = g_PartySize;
    val4 = 0;
    if (tmp7 != 0) {
        val2 = &D_1F800000;
        val2 = &D_1F800000;
        val5 = 0;
        do {
            tmp1 = tmp7 & BYTE_MASK;
            val8 = 0;
            if (tmp1 > 0) {
            loop_18:
                val6 = val8 * 4;
                if (FIELD(u8, &g_BattlePartyBattlers[0].chr.character_id, val5) != g_PartyBattleOrder[val8]) {
                    val8 += 1;
                    if (val8 >= tmp1) {
                        goto block_20; /* retail branch */
                    }
                    goto loop_18; /* retail branch */
                }
            } else {
            block_20:
                val6 = val8 * 4;
            }
            tmp0                          = FIELD(s32, &D_1F800000, val6);
            FIELD(s32, &D_80145EC8, val5) = tmp0;
            val4 += 1;
            FIELD(s16, &D_80145ECE, val5) = Area_ReadHeight(FIELD(s32, &D_80145EC4, val5), tmp0);
            val5 += BATTLE_PARTY_STRIDE;
        } while (val4 < (s32)g_PartySize);
    }
    if (!(g_BattleOutcome.options & 0x80)) {
        val4 = 0;
        if ((s32)g_PartySize > 0) {
            val5 = 0;
        loop_25:
            tmp5                     = (u8*)g_BattlePartyBattlers + val5;
            g_GameState              = tmp5;
            g_Task                   = tmp5;
            FIELD(u8, tmp5, 0x8u)    = (u8)s_RouteIndexByMode[g_BattleScrollDir];
            FIELD(s8, g_Task, 0x29u) = 6;
            if (val4 != 0) {
                FIELD(s8, g_Task, 0x7u) = 0;
                tmp6                    = g_Task;
                FIELD(s8, tmp6, 0x6u)   = (s8)(FIELD(u8, tmp6, 0x5u) - 1);
            }
            val5 += BATTLE_PARTY_STRIDE;
            func_801C3204();
            val4 += 1;
            Actor_SelectScript(g_Task->direction_08);
            if (val4 < (s32)g_PartySize) {
                goto loop_25; /* retail branch */
            }
        }
    } else {
        func_801BE1B0((u32)g_BattlePartyOrder);
        func_80199440();
    }
}
#else
INCLUDE_ASM(func_801BFB34);
#endif
