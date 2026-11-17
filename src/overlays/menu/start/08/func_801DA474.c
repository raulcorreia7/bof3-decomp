#include "start_08.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801DA474(void) {
    u8*          panel_data;
    s32          input;
    s32          index;
    u8           count;
    u8           old_side;
    u8           old_row;
    u8           result;
    s16          id;
    volatile u8* flag;

    panel_data = &D_80144953;
    Menu_DrawClutStrip(*panel_data);
    flag                                                   = &D_801485DC;
    *flag                                                  = 0;
    index                                                  = D_80148658[0] * 8 + D_80148659 * 0x10;
    D_80148600                                             = 0;
    D_801485E0                                             = FIELD(u16, &D_801EC548, index);
    *flag                                                  = 1;
    D_801485E2                                             = FIELD(u16, &D_801EC54A, index);
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR_FRAME].unk_0B = 1;
    g_MenuPanelTasks[MENU_START_PANEL_CURSOR_FRAME].unk_0A = FIELD(s32, &D_801EC54C, index);
    if ((s8)D_8014865D != 0x7F) {
        index      = (s8)D_8014865A * 8 + (s8)D_8014865D * 0x10;
        D_80148604 = FIELD(u16, &D_801EC548, index);
        D_80148600 = 1;
        D_80148606 = FIELD(u16, &D_801EC54A, index);
        D_8014860B = 0;
        D_8014860A = FIELD(s32, &D_801EC54C, index);
    }
    if (D_801ED69C == GAME_NONE) {
        id = 0x60;
    } else {
        Message_SetVariable(0U, 5U, g_CharSlot[D_801ED69C] * 0xA4 + (panel_data + 0x15));
        id = 0x61;
    }
    D_801484CC = id;
    input      = INPUT_REPEATED(g_InputPressed, INPUT_DIRECTIONAL);
    count      = Party_CountOrder(PARTY_ORDER_FIELD);
    old_side   = *(u8*)D_80148658;
    old_row    = *(u8*)&D_80148659;
    if ((input & (PADLright | PADLleft)) && (g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].unk_0A != 0)) {
        *(u8*)D_80148658 = old_side ^ 1;
    }
    if (D_80148658[0] == 0) {
        if (count - 1 < D_80148659) {
            *(u8*)&D_80148659 = count - 1;
        }
    } else {
        if (g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].unk_0A - 1 < D_80148659) {
            *(u8*)&D_80148659 = g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].unk_0A - 1;
        }
    }
    if (input & PADLup) {
        *(u8*)&D_80148659 -= 1;
        if ((s8) * (u8*)&D_80148659 < 0) {
            *(u8*)&D_80148659 = D_80148658[0] != 0 ? g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].unk_0A - 1 : count - 1;
        }
    } else if (input & PADLdown) {
        *(u8*)&D_80148659 += 1;
        if (D_80148658[0] == 0) {
            if (count - 1 < (s8) * (u8*)&D_80148659) {
                *(u8*)&D_80148659 = 0;
            }
        } else if (g_MenuPanelTasks[MENU_START_PANEL_COMMANDS].unk_0A - 1 < (s8) * (u8*)&D_80148659) {
            *(u8*)&D_80148659 = 0;
        }
    }
    if (old_side != *(u8*)D_80148658 || old_row != *(u8*)&D_80148659) {
        SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 0));
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CONFIRM]) {
        s8* face = (s8*)&D_8014865A;

        if (*face == 0x7F) {
            SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 3));
            *face      = *(u8*)D_80148658;
            D_8014865D = *(u8*)&D_80148659;
            return;
        }
        result     = func_801DB04C();
        D_801ED69C = result;
        SND_PlaySE(result == GAME_NONE ? EMI_CUE_ID(SND_BANK_COMMON, 3) : EMI_CUE_ID(SND_BANK_COMMON, 7));
        D_8014865A = 0x7F;
        D_8014865D = 0x7F;
        return;
    }
    if (g_InputPressed & g_InputMasks[MENU_INPUT_CANCEL]) {
        s8* face;

        SND_PlaySE(EMI_CUE_ID(SND_BANK_COMMON, 6));
        face = (s8*)&D_8014865A;
        if (*face != 0x7F) {
            *face      = 0x7F;
            D_8014865D = 0x7F;
            return;
        }
        D_80148654 = 5;
        D_801485DC = 0;
        D_80148600 = 0;
        D_801484E3 = 1;
        D_80148652 += 1;
    }
}
#else
INCLUDE_ASM(func_801DA474);
#endif
