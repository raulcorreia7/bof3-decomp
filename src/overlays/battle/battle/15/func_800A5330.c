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
#ifdef NON_MATCHING
NON_MATCHING void func_800A5330(void) {
    u8  row;
    u8  col;
    u8  gene_row;
    u8* cell;
    u8  gene;
    s32 text_id;
    s32 buttons;

    row = g_Battle.cursor.gene.row;
    if (row != GAME_NONE) {
        col = g_Battle.cursor.gene.column;
        if (D_800B7070[row][col] != 0) {
            func_801DE60C(0, 1, 1, 0, GAME_NONE, UI_MessageGetText((u16)(col + (row * GENE_GRID_COLUMNS + GENE_NAME_TEXT))));
        } else {
            func_801DE60C(0, 1, 1, 0, GAME_NONE, UI_MessageGetText(BLANK_TEXT));
        }
    } else {
        func_801DE60C(0, 1, 1, 0, GAME_NONE, UI_MessageGetText(BLANK_TEXT));
    }

    if (g_PadStates[0].pressed & g_InputMasks[BATTLE_INPUT_CANCEL]) {
        if (g_Battle.gene_count != 0) {
            g_Battle.gene_count--;
            gene                                                           = g_Battle.genes[g_Battle.gene_count];
            D_800B7070[gene / GENE_GRID_COLUMNS][gene % GENE_GRID_COLUMNS] = 1;
            Battle_SetGeneCount();
        } else {
            D_80148597           = 1;
            g_BattleMessageState = 2;
            g_Battle.ui_step     = 2;
            g_Battle.ui_mode     = 0;
            g_Battle.selection &= 0x7F;
        }
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        return;
    }

    if (g_PadStates[0].pressed & g_InputMasks[BATTLE_INPUT_CONFIRM]) {
        if ((u8)g_Battle.cursor.gene.row != GAME_NONE) {
            cell = &D_800B7070[(u8)g_Battle.cursor.gene.row][0];
            cell += g_Battle.cursor.gene.column;
            if (*cell == 0) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
                return;
            }
            if (g_Battle.gene_count < GENE_PICK_MAX) {
                *cell                               = 0;
                g_Battle.genes[g_Battle.gene_count] = (u8)g_Battle.cursor.gene.row * GENE_GRID_COLUMNS + g_Battle.cursor.gene.column;
                g_Battle.gene_count++;
                Battle_SetGeneCount();
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
                if (g_Battle.gene_count == GENE_PICK_MAX) {
                    g_Battle.cursor.gene.row = -1;
                }
            } else {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
            }
        } else if (g_Battle.gene_count != 0 && BATTLE_ACTIVE_MEMBER->chr.ap >= D_801463B8[0]) {
            g_Battle.ui_mode += 1;
            return;
        } else {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 7));
        }
    }

    if (g_Battle.cursor.gene.row == -1) {
        if (g_Battle.gene_count != 0) {
            text_id = GENE_HELP_CONFIRM_TEXT;
        } else {
            text_id = GENE_HELP_PICK_TEXT;
        }
    } else {
        gene_row = g_Battle.cursor.gene.row;
        col      = g_Battle.cursor.gene.column;
        if (D_800B7070[gene_row][col] != 0) {
            text_id = gene_row * GENE_GRID_COLUMNS + GENE_HELP_TEXT;
            text_id += col;
        } else {
            text_id = BLANK_TEXT;
        }
    }
    g_BattleMessages[((D_801EC328 - 1) & 0xF)].text = UI_MessageGetText(text_id);

    buttons = INPUT_REPEATED(g_PadStates[0].pressed, INPUT_DIRECTIONAL);
    if ((buttons & PADLup) && g_Battle.cursor.gene.row >= 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        g_Battle.cursor.gene.row--;
    }
    if ((buttons & PADLdown) && g_Battle.cursor.gene.row < GENE_GRID_ROWS - 1) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
        g_Battle.cursor.gene.row++;
    }
    if (g_Battle.cursor.gene.row != -1) {
        if ((buttons & PADLright) && g_Battle.cursor.gene.column < GENE_GRID_COLUMNS - 1) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
            g_Battle.cursor.gene.column++;
        }
        if ((buttons & PADLleft) && g_Battle.cursor.gene.column != 0) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 1));
            g_Battle.cursor.gene.column--;
        }
    }
}
#else
INCLUDE_ASM(func_800A5330);
#endif
