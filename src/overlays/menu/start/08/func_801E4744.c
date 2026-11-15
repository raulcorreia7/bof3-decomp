#include "start_08.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801E4744(void) {
    u8* val0;
    s32 tmp0;
    s32 tmp1;
    s32 tmp2;
    s32 tmp3;
    s32 tmp4;
    s32 val1;
    s32 val2;
    s32 val3;
    s32 val4;
    s32 val5;
    s32 val6;
    s8  tmp5;
    s8  tmp6;
    s8  tmp7;
    s8  val7;
    s8  val8;
    s8  val9;
    u32 tmp8;
    u8* val10;
    u8  tmp9;
    u8  tmp10;
    u8  tmp11;
    u8  tmp12;
    u8  tmp13;
    u8  tmp14;
    u8  tmp15;
    u8  tmp16;
    u8  val11;

    func_801E7000();
    val0  = D_801ECDBC;
    val0  = D_801ECDBC;
    val2  = INPUT_GetRepeatedButtons(g_InputPressed & (INPUT_DIRECTIONAL | PADL1 | PADL2 | PADR1 | PADR2));
    val10 = (D_801ED7E8 * 0x60) + (((s8)D_801ED7E4 * 0xC) + D_801ECDBC) + (s8)D_801ED7E0;
    if (val2 & PADLup) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
        do {
            tmp13      = D_801ED7E4 - 1;
            D_801ED7E4 = tmp13;
            if (tmp13 & 0x80) {
                D_801ED7E4 = 7;
            }
        } while (*(((s8)D_801ED7E4 * 0xC) + ((D_801ED7E8 * 0x60) + D_801ECDBC) + (s8)D_801ED7E0) == 0);
    } else if (val2 & PADLdown) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
        do {
            tmp14      = D_801ED7E4 + 1;
            D_801ED7E4 = tmp14;
            if ((s8)tmp14 >= 8) {
                D_801ED7E4 = 0;
            }
        } while (*(((s8)D_801ED7E4 * 0xC) + ((D_801ED7E8 * 0x60) + D_801ECDBC) + (s8)D_801ED7E0) == 0);
    } else if (val2 & PADLleft) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
        tmp9 = *val10;
        if ((tmp9 != 0) && (tmp9 < 6U)) {
            D_801ED7E0 = 9;
        } else {
            do {
                tmp10      = D_801ED7E0 - 1;
                D_801ED7E0 = tmp10;
                if (tmp10 & 0x80) {
                    D_801ED7E0 = 0xB;
                }
            } while (*(((s8)D_801ED7E4 * 0xC) + ((D_801ED7E8 * 0x60) + D_801ECDBC) + (s8)D_801ED7E0) == 0);
        }
    } else if (val2 & PADLright) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
        tmp11 = *val10;
        if ((tmp11 != 0) && (tmp11 < 6U)) {
            D_801ED7E0 = 0;
        } else {
            do {
                tmp12      = D_801ED7E0 + 1;
                D_801ED7E0 = tmp12;
                if ((s8)tmp12 >= 0xC) {
                    D_801ED7E0 = 0;
                }
            } while (*(((s8)D_801ED7E4 * 0xC) + ((D_801ED7E8 * 0x60) + D_801ECDBC) + (s8)D_801ED7E0) == 0);
        }
    }
    if (g_InputPressed & PADRdown) {
        val10 = (D_801ED7E8 * 0x60) + (((s8)D_801ED7E4 * 0xC) + D_801ECDBC) + (s8)D_801ED7E0;
        tmp15 = *val10;
        switch (tmp15) { /* irregular */
            case NAME_ENTRY_NEXT:
                if ((u8)D_801ED7DC < 4U) {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
                    val11 = D_801ED7DC + 1;
                block_45:
                    D_801ED7DC = val11;
                } else {
                block_41:
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 7));
                }
                break;
            case NAME_ENTRY_BACK:
                if (D_801ED7DC != 0) {
                    SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
                    val11 = D_801ED7DC - 1;
                    goto block_45; /* retail branch */
                }
                goto block_41; /* retail branch */
            case NAME_ENTRY_QUIT:
                SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
                g_MenuStartStep     = 0;
                g_GameEntrySubstate = 1;
                break;
            case NAME_ENTRY_START:
                g_InputPressed |= PADstart;
                break;
            default:
                D_801ED105 = 0;
                SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
                s_CampMenuState[D_801ED7DC] = *val10;
                val11                       = D_801ED7DC + 1;
                if ((u8)D_801ED7DC < 4U) {
                    goto block_45; /* retail branch */
                }
                break;
        }
    }
    if ((g_InputPressed & PADRright) || (val2 & (PADR1 | PADR2))) {
        if ((u8)D_801ED7DC < 4U) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
            D_801ED7DC += 1;
        }
    } else if ((g_InputPressed & PADRleft) || (val2 & PADL1) || (val2 & PADL2)) {
        if (D_801ED7DC != 0) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 1));
            D_801ED7DC -= 1;
        }
    } else {
        if (g_InputPressed & PADRup) {
            D_801ED105 = 0;
            tmp0       = D_801ED7DC & BYTE_MASK;
            if ((tmp0 != 0) && ((tmp16 = s_CampMenuState[tmp0], (tmp16 == 0xFF)) || (tmp16 == 0))) {
                D_801ED7DC -= 1;
            }
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
            s_CampMenuState[D_801ED7DC] = 0xFF;
            return;
        }
        if (g_InputPressed & PADstart) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 5));
            val6 = 5;
            val7 = 4;
        loop_63:
            tmp5 = val7 - 1;
            if (s_CampMenuState[val7] == 0xFF) {
                val7 = tmp5;
                val6 -= 1;
                if (!(tmp5 & 0x80)) {
                    goto loop_63; /* retail branch */
                }
            }
            tmp8 = val6 & HALF_MASK;
            if (tmp8 == 0) {
                val8 = 0;
                val3 = 0 << 0x18;
                do {
                    tmp1                  = val3 >> 0x18;
                    tmp6                  = val8 + 1;
                    val8                  = tmp6;
                    s_CampMenuState[tmp1] = g_Characters[0].name[tmp1];
                    val3                  = val8 << 0x18;
                } while (tmp6 < 5);
                val9 = 0;
            } else {
                val1 = 4;
                if (tmp8 < 5U) {
                    val4 = 4 << 0x18;
                loop_71:
                    tmp4 = val4 >> 0x18;
                    tmp2 = val1 - 1;
                    if (s_CampMenuState[tmp4] == 0xFF) {
                        s_CampMenuState[tmp4] = 0;
                        val1                  = tmp2;
                        val4                  = val1 << 0x18;
                        if (!(tmp2 & 0x80)) {
                            goto loop_71; /* retail branch */
                        }
                    }
                }
                val9 = 0;
            }
            val5 = 0 << 0x18;
            do {
                tmp3                       = val5 >> 0x18;
                tmp7                       = val9 + 1;
                val9                       = tmp7;
                g_Characters[0].name[tmp3] = s_CampMenuState[tmp3];
                val5                       = val9 << 0x18;
            } while (tmp7 < 5);
            UI_SetMode(UI_MODE_FADE_OUT);
            g_MenuStartStep += 1;
        }
    }
}
#else
INCLUDE_ASM(func_801E4744);
#endif
