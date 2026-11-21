#include "start_08.h"

/* func_801D9BDC */
#ifdef NON_MATCHING
NON_MATCHING void Menu_UpdateFormation(void) {
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
    if (g_FormationPickColumn != 0x7F) {
        tmp2                                                   = (g_FormationPickRow * 3) + g_FormationPickColumn;
        D_801485E0                                             = D_801EC4D0[tmp2].unk_00;
        *(u8*)(&D_801485DC)                                    = 1;
        D_801485E2                                             = D_801EC4D0[tmp2].unk_02;
        g_MenuPanelTasks[MENU_START_PANEL_CURSOR_FRAME].unk_0B = 0;
        g_MenuPanelTasks[MENU_START_PANEL_CURSOR_FRAME].unk_0A = D_801EC4D0[tmp2].unk_04 + 1;
    }
    tmp3                            = ((s8)g_FormationCursorRow * 3) + g_FormationCursorColumn;
    g_MenuPanelTasks[20].pos.x      = D_801EC4D0[tmp3].unk_00;
    FIELD(s8, (&D_801485DC), 0x24u) = 1;
    g_MenuPanelTasks[20].pos.y      = D_801EC4D0[tmp3].unk_02;
    val8                            = 0;
    g_MenuPanelTasks[20].unk_0B     = 1;
    g_MenuPanelTasks[20].unk_0A     = D_801EC4D0[tmp3].unk_04 + 1;
    val5                            = 0 << 0x18;
    do {
        g_MenuPanelTasks[(val5 >> 0x18) + 0xC].unk_0C = 0;
        tmp4                                          = val8 + 1;
        val8                                          = tmp4;
        val5                                          = val8 << 0x18;
    } while (tmp4 < 6);
    if (g_FormationCursorColumn == 0) {
        val9 = 1 << (s8)g_FormationCursorRow;
    } else {
        val9 = 7;
    }
    g_MenuPanelTasks[(g_FormationRow * 2) + (g_FormationColumn + 0xB)].unk_0C = val9;
    if (g_FormationCursorColumn != 0) {
        val0 = ((s32)(g_FormationCursorRow << 0x18) >> 0x17) + (g_FormationCursorColumn + 0x76);
    } else {
        val0 = 0x3B;
    }
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = val0;
    if (g_InputMasks[MENU_INPUT_CONFIRM] & g_InputPressed) {
        *(u8*)(&D_801485DC) = 0;
        if (g_FormationCursorColumn != 0) {
            SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 4));
            g_FormationPickColumn = 0x7F;
            g_FormationPickRow    = 0x7F;
            g_FormationColumn     = (s8)(u8)g_FormationCursorColumn;
            g_FormationRow        = (s8)g_FormationCursorRow;
            D_801ED660            = (u8)g_FormationCursorColumn;
            D_801ED664            = g_FormationCursorRow;
        } else if (g_FormationPickColumn == 0x7F) {
            SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 3));
            g_FormationPickColumn = (s8)(u8)g_FormationCursorColumn;
            g_FormationPickRow    = (s8)g_FormationCursorRow;
        } else {
            SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 4));
            Menu_SwapBytes4(&g_PartyBattleOrder[(s8)g_FormationCursorRow], &g_PartyBattleOrder[g_FormationPickRow]);
            if ((s8)g_FormationCursorRow != g_FormationPickRow) {
                D_801ED660 = (u8)(s8)g_FormationCursorRow;
                D_801ED664 = (u8)g_FormationPickRow;
            }
            goto block_20; /* retail branch */
        }
    } else if (g_InputMasks[MENU_INPUT_CANCEL] & g_InputPressed) {
        SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 6));
        *(u8*)(&D_801485DC)         = 0;
        g_MenuPanelTasks[20].active = 0;
        if (g_FormationPickColumn != 0x7F) {
        block_20:
            g_FormationPickColumn = 0x7F;
            g_FormationPickRow    = 0x7F;
        } else if (D_80148660 != 1) {
            D_80148654       = 0;
            g_PartyFormation = ((u8)g_FormationRow * 2) + ((u8)g_FormationColumn - 1);
            SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 2));
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
            g_MenuStep.state += 1;
        } else {
            g_MenuStep.sub_step = 6;
            g_MenuStep.state    = 0;
            D_80148660          = 0;
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
    val11 = g_FormationCursorRow;
    do {
        tmp6                 = g_FormationCursorRow + val1;
        g_FormationCursorRow = tmp6;
        if (tmp6 & 0x80) {
            g_FormationCursorRow = 2;
        }
        if ((s8)g_FormationCursorRow >= 3) {
            g_FormationCursorRow = 0;
        }
    } while (*(((s8)g_FormationCursorRow * 3) + g_FormationCells + g_FormationCursorColumn) == 0);
    val4 = 0 << 0x18;
    if (g_FormationPickColumn != 0) {
        tmp1 = INPUT_GetRepeatedButtons(g_InputPressed & (PADLright | PADLleft));
        if (tmp1 & PADLleft) {
            val2 = -1;
        }
        if (tmp1 & PADLright) {
            val2 = 1;
        }
        val6 = g_FormationCursorColumn;
        do {
            tmp5                    = (u8)g_FormationCursorColumn + val2;
            g_FormationCursorColumn = tmp5;
            if (tmp5 & 0x80) {
                g_FormationCursorColumn = 2;
            }
            if (g_FormationCursorColumn >= 3) {
                g_FormationCursorColumn = 0;
            }
            val4 = (s32)val6 << 0x18;
        } while (*(((s8)g_FormationCursorRow * 3) + g_FormationCells + g_FormationCursorColumn) == 0);
    }
    if (((val4 >> 0x18) != g_FormationCursorColumn) || ((s8)val11 != (s8)g_FormationCursorRow)) {
        SND_PlaySE(EMI_SE_ID(SND_BANK_COMMON, 1));
    }
    g_PartyFormation = ((u8)g_FormationColumn + ((u8)g_FormationRow * 2)) - 1;
}
#else
INCLUDE_ASM(Menu_UpdateFormation);
#endif
