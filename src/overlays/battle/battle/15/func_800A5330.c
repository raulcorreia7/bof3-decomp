#include "battle_15.h"

#define CURSOR        (&LOBU(g_BattlePanelEntry))
#define CURSOR_ENTRY  0
#define CURSOR_COLUMN 1

/* The Accession gene picker: moves the cursor over the 3x6 gene grid, adds or removes up to three genes and confirms
 * when the party member has the AP. */
/* blocker: retail spills the g_BattleGeneCount address in the confirm branch (0x30 frame, absolute loads), the draft
 * keeps it in s0; first diff: addiu sp,sp,-48. */
#ifdef NON_MATCHING
NON_MATCHING void func_800A5330(void) {
    s32 row;
    s32 col;
    s32 entry;
    u8  gene_row;
    u8* cell;
    u8  gene;
    s32 text_id;
    s32 buttons;

    row = CURSOR[CURSOR_ENTRY];
    if (row != GAME_NONE) {
        col = CURSOR[CURSOR_COLUMN];
        if (D_800B7070[row][col] != 0) {
            func_801DE60C(0, 1, 1, 0, GAME_NONE, Resource_GetText((u16)(col + (row * 6 + 0x4172))));
        } else {
            func_801DE60C(0, 1, 1, 0, GAME_NONE, Resource_GetText(0x4000));
        }
    } else {
        func_801DE60C(0, 1, 1, 0, GAME_NONE, Resource_GetText(0x4000));
    }

    if (g_InputPressed & g_InputMasks[INPUT_SLOT_CANCEL]) {
        if (g_BattleGeneCount[0] != 0) {
            g_BattleGeneCount[0]--;
            gene                           = g_BattleGenes[g_BattleGeneCount[0]];
            D_800B7070[gene / 6][gene % 6] = 1;
            func_800A82F8();
        } else {
            D_80148597           = 1;
            g_BattleMessageState = 2;
            g_BattleUIStep       = 2;
            g_BattleUIState      = 0;
            g_BattleRowCursor &= 0x7F;
        }
        SND_PlayCue(EMI_CUE_ID(1, 6));
        return;
    }

    if (g_InputPressed & g_InputMasks[INPUT_SLOT_CONFIRM]) {
        if (CURSOR[CURSOR_ENTRY] != GAME_NONE) {
            cell = &D_800B7070[CURSOR[CURSOR_ENTRY]][CURSOR[CURSOR_COLUMN]];
            if (*cell == 0) {
                SND_PlayCue(EMI_CUE_ID(1, 7));
                return;
            }
            if (g_BattleGeneCount[0] < 3) {
                *cell                               = 0;
                g_BattleGenes[g_BattleGeneCount[0]] = CURSOR[CURSOR_ENTRY] * 6 + CURSOR[CURSOR_COLUMN];
                g_BattleGeneCount[0]++;
                func_800A82F8();
                SND_PlayCue(EMI_CUE_ID(1, 3));
                if (g_BattleGeneCount[0] == 3) {
                    CURSOR[CURSOR_ENTRY] = GAME_NONE;
                }
            } else {
                SND_PlayCue(EMI_CUE_ID(1, 6));
            }
        } else if (g_BattleGeneCount[0] != 0 && BATTLE_ACTIVE_ROW->chr.ap >= D_801463B8[0]) {
            g_BattleUIState += 1;
            return;
        } else {
            SND_PlayCue(EMI_CUE_ID(1, 7));
        }
    }

    entry = LOB(CURSOR[CURSOR_ENTRY]);
    if (entry == -1) {
        if (g_BattleGeneCount[0] != 0) {
            text_id = 0x57;
        } else {
            text_id = 0x58;
        }
    } else {
        gene_row = entry;
        col      = CURSOR[CURSOR_COLUMN];
        if (D_800B7070[gene_row][col] != 0) {
            text_id = col + (gene_row * 6 + 0x45);
        } else {
            text_id = 0x4000;
        }
    }
    D_801EB5B4[((D_801EC328 - 1) & 0xF) * 2] = Resource_GetText(text_id);

    buttons = INPUT_REPEATED(g_InputPressed, INPUT_DIRECTIONAL);
    if ((buttons & PADLup) && LOB(CURSOR[CURSOR_ENTRY]) >= 0) {
        SND_PlayCue(EMI_CUE_ID(1, 1));
        CURSOR[CURSOR_ENTRY]--;
    }
    if ((buttons & PADLdown) && LOB(CURSOR[CURSOR_ENTRY]) < 2) {
        SND_PlayCue(EMI_CUE_ID(1, 1));
        CURSOR[CURSOR_ENTRY]++;
    }
    if (LOB(CURSOR[CURSOR_ENTRY]) != -1) {
        if ((buttons & PADLright) && CURSOR[CURSOR_COLUMN] < 5) {
            SND_PlayCue(EMI_CUE_ID(1, 1));
            CURSOR[CURSOR_COLUMN]++;
        }
        if ((buttons & PADLleft) && CURSOR[CURSOR_COLUMN] != 0) {
            SND_PlayCue(EMI_CUE_ID(1, 1));
            CURSOR[CURSOR_COLUMN]--;
        }
    }
}
#else
INCLUDE_ASM(func_800A5330);
#endif
