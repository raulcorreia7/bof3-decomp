#include "start_08.h"

/* The name entry cursor: the page, row and column of the cell it sits on, and the
 * command cells the grid carries in its label column. */
MATCH void func_801E4744(void) {
    u8  cell_index;
    u8  col;
    u8  row;
    u8* cell;
    s8  slot;
    u16 count;
    s32 input;

    func_801E7000();
    input = INPUT_REPEATED(g_PadStates[0].pressed, (INPUT_DIRECTIONAL | PADL1 | PADL2 | PADR1 | PADR2));
    cell  = &D_801ECDBC[D_801ED7E8][(s8)D_801ED7E4][(s8)D_801ED7E0];
    if (input & PADLup) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        do {
            row        = D_801ED7E4 - 1;
            D_801ED7E4 = row;
            if ((s8)row < 0) {
                D_801ED7E4 = 7;
            }
        } while (D_801ECDBC[D_801ED7E8][(s8)D_801ED7E4][(s8)D_801ED7E0] == 0);
    } else if (input & PADLdown) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        do {
            row        = D_801ED7E4 + 1;
            D_801ED7E4 = row;
            if ((s8)row >= 8) {
                D_801ED7E4 = 0;
            }
        } while (D_801ECDBC[D_801ED7E8][(s8)D_801ED7E4][(s8)D_801ED7E0] == 0);
    } else if (input & PADLleft) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        if (*cell != 0 && *cell < 6) {
            D_801ED7E0 = 9;
        } else {
            do {
                col        = D_801ED7E0 - 1;
                D_801ED7E0 = col;
                if ((s8)col < 0) {
                    D_801ED7E0 = 0xB;
                }
            } while (D_801ECDBC[D_801ED7E8][(s8)D_801ED7E4][(s8)D_801ED7E0] == 0);
        }
    } else if (input & PADLright) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        if (*cell != 0 && *cell < 6) {
            D_801ED7E0 = 0;
        } else {
            do {
                col        = D_801ED7E0 + 1;
                D_801ED7E0 = col;
                if ((s8)col >= 0xC) {
                    D_801ED7E0 = 0;
                }
            } while (D_801ECDBC[D_801ED7E8][(s8)D_801ED7E4][(s8)D_801ED7E0] == 0);
        }
    }
    if (g_PadStates[0].pressed & PADRdown) {
        cell = &D_801ECDBC[D_801ED7E8][(s8)D_801ED7E4][(s8)D_801ED7E0];
        switch (*cell) {
            case NAME_ENTRY_NEXT:
                if (D_801ED7DC < 4) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
                    D_801ED7DC += 1;
                } else {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
                }
                break;
            case NAME_ENTRY_BACK:
                if (D_801ED7DC != 0) {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
                    D_801ED7DC -= 1;
                } else {
                    SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
                }
                break;
            case NAME_ENTRY_QUIT:
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
                g_MenuCampStep      = 0;
                g_GameEntrySubstate = 1;
                break;
            case NAME_ENTRY_START:
                g_PadStates[0].pressed |= PADstart;
                break;
            default:
                D_801ED105 = 0;
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
                s_CampMenuState[D_801ED7DC] = *cell;
                if (D_801ED7DC < 4) {
                    D_801ED7DC += 1;
                }
                break;
        }
    }
    if ((g_PadStates[0].pressed & PADRright) || (input & (PADR1 | PADR2))) {
        if (D_801ED7DC < 4) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
            D_801ED7DC += 1;
        }
    } else if (g_PadStates[0].pressed & PADRleft) {
        if (D_801ED7DC != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
            D_801ED7DC -= 1;
        }
    } else if (input & PADL1) {
        if (D_801ED7DC != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
            D_801ED7DC -= 1;
        }
    } else if (input & PADL2) {
        if (D_801ED7DC != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
            D_801ED7DC -= 1;
        }
    } else {
        if (g_PadStates[0].pressed & PADRup) {
            D_801ED105 = 0;
            cell_index = D_801ED7DC & BYTE_MASK;
            if (cell_index != 0 && (s_CampMenuState[cell_index] == 0xFF || s_CampMenuState[cell_index] == 0)) {
                D_801ED7DC -= 1;
            }
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
            s_CampMenuState[D_801ED7DC] = 0xFF;
            return;
        }
        if (g_PadStates[0].pressed & PADstart) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 5));
            count = 5;
            for (slot = 4; slot >= 0; slot--) {
                if (s_CampMenuState[slot] != 0xFF) {
                    break;
                }
                count--;
            }
            if (count == 0) {
                for (slot = 0; slot < 5; slot++) {
                    s_CampMenuState[slot] = g_Characters[0].name[slot];
                }
            } else if (count < 5) {
                for (slot = 4; slot >= 0; slot--) {
                    if (s_CampMenuState[slot] != 0xFF) {
                        break;
                    }
                    s_CampMenuState[slot] = 0;
                }
            }
            for (slot = 0; slot < 5; slot++) {
                g_Characters[0].name[slot] = s_CampMenuState[slot];
            }
            UI_ModeSet(UI_MODE_FADE_OUT);
            g_MenuCampStep += 1;
        }
    }
}
