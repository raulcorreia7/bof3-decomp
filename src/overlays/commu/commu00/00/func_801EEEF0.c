#include "commu00_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801EEEF0(u32 row_index) {
    s32 tmp0;
    s32 tmp1;
    s32 val0;
    s32 val1;
    s32 val2;
    s32 val3;
    s32 val4;
    s32 val5;
    u32 tmp2;
    u32 val6;
    u32 val7;
    u32 val8;
    /* FAKE: unused frame, 16 bytes. */
    FAKE_STACK_PADS(u32, 4);

    tmp2 = row_index & BYTE_MASK;
    tmp0 = tmp2 * 4;
    if (tmp0 < D_801455C2) {
        val4 = tmp2 < 0x14U;
        if ((u32)(g_BattleCount - D_801455B0) >= 0x15U) {
            D_801455B0 = g_BattleCount - 0x14;
            val4       = tmp2 < 0x14U;
        }
        if (val4 != 0) {
            tmp1 = ((s32)(D_801455C2 - tmp0) >> 2) + 1;
            val1 = (g_BattleCount - D_801455AC) / 10;
            if (tmp1 < val1) {
                val1 = tmp1;
            }
            if (val1 != 0) {
                val0 = 0;
                if (val1 > 0) {
                    val6 = tmp2;
                    val2 = 0x14;
                    val8 = val6;
                loop_9:
                    if (val8 != val2) {
                        val0 += 1;
                        Fairy_JoinVillage();
                        val8 = val6 + val0;
                        if (val0 < val1) {
                            goto loop_9; /* retail branch */
                        }
                    }
                }
                D_801455AC = g_BattleCount;
            }
        }
    } else if (D_801455C2 == 0) {
        val5 = tmp2 < 2U;
        if ((u32)(g_BattleCount - D_801455AC) >= 0xBU) {
            D_801455AC = g_BattleCount - 0xA;
            val5       = tmp2 < 2U;
        }
        if (val5 == 0) {
            val1 = (g_BattleCount - D_801455B0) / 20;
            if (val1 != 0) {
                val0 = 0;
                if (val1 != 0) {
                    val6 = tmp2;
                    val2 = 1;
                    val3 = val6 - 0;
                loop_19:
                    if (val3 != val2) {
                        val0 += 1;
                        func_801F01F4();
                        val3 = val6 - val0;
                        if (val0 < val1) {
                            goto loop_19; /* retail branch */
                        }
                    }
                }
                val7 = g_BattleCount;
                goto block_25; /* retail branch */
            }
        }
    } else {
        if ((u32)(g_BattleCount - D_801455AC) >= 0xBU) {
            D_801455AC = g_BattleCount - 0xA;
        }
        val7 = g_BattleCount - 0x14;
        if ((u32)(g_BattleCount - D_801455B0) >= 0x15U) {
        block_25:
            D_801455B0 = val7;
        }
    }
}
#else
INCLUDE_ASM(func_801EEEF0);
#endif
