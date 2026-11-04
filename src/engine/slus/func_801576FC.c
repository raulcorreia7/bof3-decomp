#include "engine/slus/slus.h"

/* lifted draft, best score 48.52%; semantics unverified
 */
/* nonmatching unmeasured: tried the first draft cleaned to compiling C; best score 48.52%. resume: a lever or header fix that
 * closes the first mismatch. */
#ifdef NON_MATCHING
NON_MATCHING void func_801576FC(u8* record) {
    s32   tmp0;
    s32   tmp1;
    s32   tmp2;
    s32   val0;
    s32   val1;
    s32   val2;
    s32   val3;
    s32   val4;
    s8    tmp3;
    s32   val5;
    u16   val6;
    u16   val7;
    u32   tmp4;
    u32   tmp5;
    u8*   val8;
    u8*   val9;
    u8*   val10;
    u8*   val11;
    u8    tmp6;
    u8    tmp7;
    void* val12;
    /* FAKE: unused frame, 16 bytes. */
    STACK_PADS(u8, 16);

    val11 = record;
    val1  = 0;
    tmp3  = Area_TestCondition((s32) * (s16*)(val11));
    val6  = FIELD(u16, val11, 0x2u);
    val11 += 4;
    if (val6 != 0) {
        val5  = tmp3;
        val10 = MEM_PTR(u8, 0x80100000);
        val10 = MEM_PTR(u8, (MAP_BUNDLE_BASE + 0x00));
        val2  = val5 * 4;
        val8  = (u8*)g_AreaCellPrims;
        val8  = (u8*)g_AreaCellPrims;
        val3  = 0 * 4;
        do {
            val9 = &val11[val3];
            tmp4 = *(u32*)(val9);
            tmp6 = FIELD(u8, val9, 0x1u);
            tmp5 = tmp4 >> 0x18;
            tmp1 = tmp4 & BYTE_MASK;
            switch (tmp5) { /* switch 1; irregular */
                case 0:     /* switch 1 */
                    tmp7 = *val10;
                    val1 += 1;
                    tmp0                                   = g_AreaMapBundle.grid_off4_02 * 4;
                    FIELD(u32, val10,
                          tmp0 + ((((s32)((tmp7 * g_AreaMapBundle.height_01) + 1) >> 1) * 4) +
                                  (FIELD(u16, val10, (tmp1 * tmp7 * 2) + tmp0 + (tmp6 * 2)) * 4) +
                                  ((tmp4 >> 0xE) & 0x3C))) = FIELD(s32, (val2 + val9), 0x4u);
                    goto block_13; /* retail branch */
                default:           /* switch 1 */
                    val1 += 2;
                    FIELD(u8, (u8*)g_AreaCellCodes, tmp6 + (tmp1 * LOBU(g_AreaMapBundle.width_00))) =
                        (s8)(FIELD(u32, val9, 0x4u) >> (val5 * 0x10));
                    break;
                case 1: /* switch 1 */
                block_13:
                    val0 = ((u32) * (u32*)(val9) >> 0x14) & 0xF;
                    tmp2 = Area_ProbeCellId((s32)tmp6, tmp1);
                    if (tmp2 != 0) {
                        switch (val0) { /* switch 2; irregular */
                            case 0:     /* switch 2 */
                                val12 = (void*)(tmp2 * 0x50);
                                val4  = (s32)((g_FrameBufferIndex * 0x28) + val8);
                                break;
                            case 1: /* switch 2 */
                                val7 = FIELD(u16, ((u8*)g_AreaCellPrims + 0x4E), tmp2 * 0x50);
                            block_14:
                                val4  = val7 * 0x50;
                                val12 = (g_FrameBufferIndex * 0x28) + val8;
                                break;
                            default: /* switch 2 */
                                val7 = FIELD(u16, ((u8*)g_AreaCellPrims + 0x46), tmp2 * 0x50);
                                goto block_14; /* retail branch */
                        }
                        func_80155560(FIELD(u32, (val2 + val9), 0x4u), val4 + val12, 1);
                    }
                    val1 += 2;
                    break;
                case 2: /* switch 1 */
                    FIELD(u32, val10, 0x30 + (tmp6 * 4) + (tmp1 * LOBU(g_AreaMapBundle.width_00) * 4)) =
                        FIELD(s32, (val2 + val9), 0x4u);
                    g_AreaCameraRefreshCount = 2;
                    val1 += 3;
                    break;
            }
            val3 = val1 * 4;
        } while (val1 < (s32)val6);
    }
}
#else
INCLUDE_ASM(func_801576FC);
#endif
