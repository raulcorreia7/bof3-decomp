#include "start_08.h"

typedef struct Start08Rotation {
    u16 unk_00;
    u16 unk_02;
    s32 unk_04;
} Start08Rotation;

extern Start08Rotation D_801EC4D0[];
extern u8              D_801ED66C;

/* nonmatching unmeasured: tried the first draft cleaned to compiling C; best score 82.70%. resume: a lever or header fix that
 * closes the first mismatch. */
#ifdef NON_MATCHING
NON_MATCHING void func_801D9BDC(void) {
    s16   val0;
    s32   tmp0;
    s32   tmp1;
    s32   tmp2;
    s32   tmp3;
    s32   val1;
    s32   val2;
    s32   val3;
    s32   val4;
    s32   val5;
    u8    val6;
    s8    tmp4;
    s8    tmp5;
    s8    val7;
    s8    val8;
    s8    val9;
    s8    val10;
    u8    val11;
    u8    tmp6;
    void* tmp7;

    val2 = 0;
    val1 = 0;
    val6 = 0;
    Menu_DrawClutStrip(D_80144953);
    *(u8*)(&D_801485DC) = 0;
    if (D_801ED678 != 0x7F) {
        tmp2                = (D_801ED67C * 3) + D_801ED678;
        D_801485E0          = D_801EC4D0[tmp2].unk_00;
        *(u8*)(&D_801485DC) = 1;
        D_801485E2          = D_801EC4D0[tmp2].unk_02;
        D_801485E7          = 0;
        D_801485E6          = D_801EC4D0[tmp2].unk_04 + 1;
    }
    tmp3                            = ((s8)D_801ED66C * 3) + D_801ED668;
    D_80148604                      = D_801EC4D0[tmp3].unk_00;
    FIELD(s8, (&D_801485DC), 0x24u) = 1;
    D_80148606                      = D_801EC4D0[tmp3].unk_02;
    val8                            = 0;
    D_8014860B                      = 1;
    D_8014860A                      = D_801EC4D0[tmp3].unk_04 + 1;
    val5                            = 0 << 0x18;
    do {
        D_8014833C[(val5 >> 0x18) + 0xC][0] = 0;
        tmp4                                = val8 + 1;
        val8                                = tmp4;
        val5                                = val8 << 0x18;
    } while (tmp4 < 6);
    if (D_801ED668 == 0) {
        val9 = 1 << (s8)D_801ED66C;
    } else {
        val9 = 7;
    }
    D_8014833C[(D_801ED674 * 2) + (D_801ED670 + 0xB)][0] = val9;
    if (D_801ED668 != 0) {
        val0 = ((s32)(D_801ED66C << 0x18) >> 0x17) + (D_801ED668 + 0x76);
    } else {
        val0 = 0x3B;
    }
    D_801484CC = val0;
    if (D_80145AC2 & g_InputPressed) {
        *(u8*)(&D_801485DC) = 0;
        if (D_801ED668 != 0) {
            SND_PlayCue(EMI_CUE_ID(1, 4));
            D_801ED678 = 0x7F;
            D_801ED67C = 0x7F;
            D_801ED670 = (s8)(u8)D_801ED668;
            D_801ED674 = (s8)D_801ED66C;
            D_801ED660 = (u8)D_801ED668;
            D_801ED664 = D_801ED66C;
        } else if (D_801ED678 == 0x7F) {
            SND_PlayCue(EMI_CUE_ID(1, 3));
            D_801ED678 = (s8)(u8)D_801ED668;
            D_801ED67C = (s8)D_801ED66C;
        } else {
            SND_PlayCue(EMI_CUE_ID(1, 4));
            Menu_SwapBytes_801DAC08(&D_80144F5D[(s8)D_801ED66C], &D_80144F5D[D_801ED67C]);
            if ((s8)D_801ED66C != D_801ED67C) {
                D_801ED660 = (u8)(s8)D_801ED66C;
                D_801ED664 = (u8)D_801ED67C;
            }
            goto block_20; /* retail branch */
        }
    } else if (D_80145AC4 & g_InputPressed) {
        SND_PlayCue(EMI_CUE_ID(1, 6));
        *(u8*)(&D_801485DC) = 0;
        D_80148600          = 0;
        if (D_801ED678 != 0x7F) {
        block_20:
            D_801ED678 = 0x7F;
            D_801ED67C = 0x7F;
        } else if (D_80148660 != 1) {
            D_80148654       = 0;
            g_PartyFormation = ((u8)D_801ED674 * 2) + ((u8)D_801ED670 - 1);
            SND_PlayCue(EMI_CUE_ID(1, 2));
            val7 = 0;
            val3 = 0 << 0x18;
            do {
                tmp7  = ((val3 >> 0x18) * 0x24) + (&D_801485DC - 0xFC);
                val10 = val7 + 1;
                if (*(u8*)(tmp7) != 0) {
                    val10 = val7 + 1;
                    if (FIELD(u8, tmp7, 0x2u) == 0xB) {
                        FIELD(s8, tmp7, 0x3u) = 1;
                    }
                }
                val7 = val10;
                val3 = val7 << 0x18;
            } while (val10 < 6);
            D_80148654 = 5;
            D_80148652 += 1;
        } else {
            D_80148651 = 6;
            D_80148652 = 0;
            D_80148660 = 0;
            g_GameEntrySubstate += 1;
        }
    }
    tmp0 = INPUT_GetRepeatedButtons(g_InputPressed & (PADLup | PADLdown));
    if (tmp0 & PADLup) {
        val1 = -1;
    }
    if (tmp0 & PADLdown) {
        val1 = 1;
    }
    val11 = D_801ED66C;
    do {
        tmp6       = D_801ED66C + val1;
        D_801ED66C = tmp6;
        if (tmp6 & 0x80) {
            D_801ED66C = 2;
        }
        if ((s8)D_801ED66C >= 3) {
            D_801ED66C = 0;
        }
    } while (*(((s8)D_801ED66C * 3) + D_801ED680 + D_801ED668) == 0);
    val4 = 0 << 0x18;
    if (D_801ED678 != 0) {
        tmp1 = INPUT_GetRepeatedButtons(g_InputPressed & (PADLright | PADLleft));
        if (tmp1 & PADLleft) {
            val2 = -1;
        }
        if (tmp1 & PADLright) {
            val2 = 1;
        }
        val6 = D_801ED668;
        do {
            tmp5       = (u8)D_801ED668 + val2;
            D_801ED668 = tmp5;
            if (tmp5 & 0x80) {
                D_801ED668 = 2;
            }
            if (D_801ED668 >= 3) {
                D_801ED668 = 0;
            }
            val4 = (s32)val6 << 0x18;
        } while (*(((s8)D_801ED66C * 3) + D_801ED680 + D_801ED668) == 0);
    }
    if (((val4 >> 0x18) != D_801ED668) || ((s8)val11 != (s8)D_801ED66C)) {
        SND_PlayCue(EMI_CUE_ID(1, 1));
    }
    g_PartyFormation = ((u8)D_801ED670 + ((u8)D_801ED674 * 2)) - 1;
}
#else
INCLUDE_ASM(func_801D9BDC);
#endif
