#include "start_08.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801DA474(void) {
    s32          val0;
    s16          val1;
    s32          tmp0;
    s32          tmp1;
    s8           tmp2;
    s8           tmp3;
    s8           val2;
    s8           val3;
    u8*          val4;
    s32          input_bits;
    u8           tmp4;
    u8           tmp5;
    volatile u8* flag;

    val4 = &D_80144953;
    val4 = &D_80144953;
    Menu_DrawClutStrip(*val4);
    flag                                                   = &D_801485DC;
    *flag                                                  = 0;
    g_MenuPanelTasks[20].active                            = 0;
    tmp1                                                   = (D_80148658[0] * 8) + (D_80148659 * 0x10);
    D_801485E0                                             = FIELD(u16, &D_801EC548, tmp1);
    D_801485E2                                             = FIELD(u16, &D_801EC54A, tmp1);
    *flag                                                  = 1;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR_FRAME].unk_0B = 1;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR_FRAME].unk_0A = FIELD(s32, &D_801EC54C, tmp1);
    if ((s8)D_8014865D != 0x7F) {
        tmp0                        = ((s8)D_8014865A * 8) + ((s8)D_8014865D * 0x10);
        g_MenuPanelTasks[20].pos.x  = FIELD(u16, &D_801EC548, tmp0);
        g_MenuPanelTasks[20].active = 1;
        g_MenuPanelTasks[20].pos.y  = FIELD(u16, &D_801EC54A, tmp0);
        g_MenuPanelTasks[20].unk_0B = 0;
        g_MenuPanelTasks[20].unk_0A = FIELD(s32, &D_801EC54C, tmp0);
    }
    if (D_801ED69C == GAME_NONE) {
        val1 = 0x60;
    } else {
        Message_SetVariable(0U, 5U, (g_CharSlot[D_801ED69C] * 0xA4) + (&D_80144953 + 0x15));
        val1 = 0x61;
    }
    g_MenuPanelTasks[MENU_START_PANEL_DESCRIPTION].u.message.id = val1;
    input_bits                                                  = INPUT_GetRepeatedButtons(g_InputPressed & INPUT_DIRECTIONAL);
    tmp4                                                        = Party_CountOrder(PARTY_ORDER_FIELD);
    if ((input_bits & (PADLright | PADLleft)) && (g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].unk_0A != 0)) {
        D_80148658[0] = (u8)D_80148658[0] ^ 1;
    }
    if (D_80148658[0] == 0) {
        val2 = tmp4 - 1;
        if (((tmp4 & BYTE_MASK) - 1) < D_80148659) {
            goto block_12; /* retail branch */
        }
    } else {
        val2 = g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].unk_0A - 1;
        if ((g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].unk_0A - 1) < D_80148659) {
        block_12:
            D_80148659 = val2;
        }
    }
    if (input_bits & PADLup) {
        tmp2       = (u8)D_80148659 - 1;
        D_80148659 = tmp2;
        if (tmp2 & 0x80) {
            val3 = tmp4 - 1;
            if (D_80148658[0] != 0) {
                val3 = g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].unk_0A - 1;
            }
            D_80148659 = val3;
        }
    } else if (input_bits & PADLdown) {
        tmp3       = (u8)D_80148659 + 1;
        D_80148659 = tmp3;
        if (D_80148658[0] == 0) {
            if (((tmp4 & BYTE_MASK) - 1) < tmp3) {
                goto block_23; /* retail branch */
            }
        } else if ((g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].unk_0A - 1) < tmp3) {
        block_23:
            D_80148659 = 0;
        }
    }
    if (((u8)D_80148658[0] != (u8)D_80148658[0]) || ((u8)D_80148659 != (u8)D_80148659)) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
    }
    if (g_InputMasks[MENU_INPUT_CONFIRM] & g_InputPressed) {
        val4 = &D_8014865A;
        val4 = &D_8014865A;
        if ((s8)D_8014865A == 0x7F) {
            SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 3));
            D_8014865A = (u8)D_80148658[0];
            D_8014865D = (u8)D_80148659;
            return;
        }
        tmp5       = func_801DB04C();
        D_801ED69C = tmp5;
        val0       = 0x107;
        if ((tmp5 & BYTE_MASK) == GAME_NONE) {
            val0 = 0x103;
        }
        SND_PlayCue(val0);
        D_8014865A = 0x7F;
        D_8014865D = 0x7F;
        return;
    }
    if (g_InputMasks[MENU_INPUT_CANCEL] & g_InputPressed) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 6));
        if ((s8)D_8014865A != 0x7F) {
            D_8014865A = 0x7F;
            D_8014865D = 0x7F;
            return;
        }
        D_80148654                                        = 5;
        D_801485DC                                        = 0;
        g_MenuPanelTasks[20].active                       = 0;
        g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].state = 1;
        g_MenuStep.state += 1;
    }
}
#else
INCLUDE_ASM(func_801DA474);
#endif
