#include "battle_15.h"

/* The Accession gene grid and the most genes one transformation combines. */
#define GENE_GRID_ROWS         3
#define GENE_GRID_COLUMNS      6
#define GENE_PICK_MAX          3

/* Text ids: gene names, gene help lines, the confirm row's help lines and the blank text. */
#define GENE_NAME_TEXT         0x4172
#define GENE_HELP_TEXT         0x45
#define GENE_HELP_CONFIRM_TEXT 0x57
#define GENE_HELP_PICK_TEXT    0x58
#define BLANK_TEXT             0x4000

/* The Accession gene picker: moves the cursor over the gene grid, adds or removes up to GENE_PICK_MAX genes and
 * confirms when the party member has the AP. */
/* blocker: retail spills the function-wide g_BattleGeneCount address (unused 8-byte slot, absolute loads in the
 * confirm branch); the draft keeps it in s0. First diff: addiu sp,sp,-48. Tried: a local count pointer. */
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

    row = g_GeneCursor.row;
    if (row != -1) {
        col = g_GeneCursor.column;
        if (D_800B7070[row][col] != 0) {
            func_801DE60C(0, 1, 1, 0, GAME_NONE,
                          Resource_GetText((u16)(col + (row * GENE_GRID_COLUMNS + GENE_NAME_TEXT))));
        } else {
            func_801DE60C(0, 1, 1, 0, GAME_NONE, Resource_GetText(BLANK_TEXT));
        }
    } else {
        func_801DE60C(0, 1, 1, 0, GAME_NONE, Resource_GetText(BLANK_TEXT));
    }

    if (g_InputPressed & g_InputMasks[BATTLE_INPUT_CANCEL]) {
        if (g_BattleGeneCount[0] != 0) {
            g_BattleGeneCount[0]--;
            gene                                                           = g_BattleGenes[g_BattleGeneCount[0]];
            D_800B7070[gene / GENE_GRID_COLUMNS][gene % GENE_GRID_COLUMNS] = 1;
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

    if (g_InputPressed & g_InputMasks[BATTLE_INPUT_CONFIRM]) {
        if (g_GeneCursor.row != -1) {
            cell = &D_800B7070[g_GeneCursor.row][g_GeneCursor.column];
            if (*cell == 0) {
                SND_PlayCue(EMI_CUE_ID(1, 7));
                return;
            }
            if (g_BattleGeneCount[0] < GENE_PICK_MAX) {
                *cell                               = 0;
                g_BattleGenes[g_BattleGeneCount[0]] = g_GeneCursor.row * GENE_GRID_COLUMNS + g_GeneCursor.column;
                g_BattleGeneCount[0]++;
                func_800A82F8();
                SND_PlayCue(EMI_CUE_ID(1, 3));
                if (g_BattleGeneCount[0] == GENE_PICK_MAX) {
                    g_GeneCursor.row = -1;
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

    entry = g_GeneCursor.row;
    if (entry == -1) {
        if (g_BattleGeneCount[0] != 0) {
            text_id = GENE_HELP_CONFIRM_TEXT;
        } else {
            text_id = GENE_HELP_PICK_TEXT;
        }
    } else {
        gene_row = entry;
        col      = g_GeneCursor.column;
        if (D_800B7070[gene_row][col] != 0) {
            text_id = col + (gene_row * GENE_GRID_COLUMNS + GENE_HELP_TEXT);
        } else {
            text_id = BLANK_TEXT;
        }
    }
    D_801EB5B4[((D_801EC328 - 1) & 0xF) * 2] = Resource_GetText(text_id);

    buttons = INPUT_REPEATED(g_InputPressed, INPUT_DIRECTIONAL);
    if ((buttons & PADLup) && g_GeneCursor.row >= 0) {
        SND_PlayCue(EMI_CUE_ID(1, 1));
        g_GeneCursor.row--;
    }
    if ((buttons & PADLdown) && g_GeneCursor.row < GENE_GRID_ROWS - 1) {
        SND_PlayCue(EMI_CUE_ID(1, 1));
        g_GeneCursor.row++;
    }
    if (g_GeneCursor.row != -1) {
        if ((buttons & PADLright) && g_GeneCursor.column < GENE_GRID_COLUMNS - 1) {
            SND_PlayCue(EMI_CUE_ID(1, 1));
            g_GeneCursor.column++;
        }
        if ((buttons & PADLleft) && g_GeneCursor.column != 0) {
            SND_PlayCue(EMI_CUE_ID(1, 1));
            g_GeneCursor.column--;
        }
    }
}
#else
INCLUDE_ASM(func_800A5330);
#endif
