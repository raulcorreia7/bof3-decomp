#include "area030_04.h"

/* A three-row menu: left and right move the row, cancel and confirm set the menu state; at step 2 the row message and cursor. */
MATCH void func_801DC93C(void) {
    s32 pad;
    u8  mode;

    pad = INPUT_REPEATED(g_PadStates[0].pressed, (PADLright | PADLleft));
    if (pad & PADLleft) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        if ((s8)--g_SpawnedActors[6].unk_06 < 0) {
            g_SpawnedActors[6].unk_06 = 2;
        }
    } else if (pad & PADLright) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 0));
        if (++g_SpawnedActors[6].unk_06 >= 3) {
            g_SpawnedActors[6].unk_06 = 0;
        }
    } else if (g_PadStates[0].pressed & g_InputMasks[FISHING_INPUT_CANCEL]) {
        SND_SeqFadeIn(0, 0, 0x14, 0x10);
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        mode = g_SpawnedActors[6].header.mode;
        if (mode == 3 || mode == 4) {
            g_SpawnedActors[6].header.mode = 5;
        } else if (mode == 8) {
            g_SpawnedActors[6].header.mode = 0xB;
        } else if (mode == 0xE) {
            g_SpawnedActors[6].header.mode = 0xF;
        }
        g_SpawnedActors[6].link = 0;
        SELF(Actor)->unk_03     = 4;
    } else if (g_PadStates[0].pressed & g_InputMasks[FISHING_INPUT_CAST]) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 3));
        if (g_SpawnedActors[6].unk_06 == 0) {
            if (g_SpawnedActors[6].header.mode == 8) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
                g_SpawnedActors[6].header.mode = 0xB;
            } else if (g_SpawnedActors[6].header.mode == 0xE) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
                g_SpawnedActors[6].header.mode = 0xF;
            }
        } else if (g_SpawnedActors[6].unk_06 == 1) {
            if (g_SpawnedActors[6].header.mode == 3 || g_SpawnedActors[6].header.mode == 4) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
                g_SpawnedActors[6].header.mode = 5;
            } else if (g_SpawnedActors[6].header.mode == 0xE) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
                g_SpawnedActors[6].header.mode = 0xF;
            }
        } else {
            if (g_SpawnedActors[6].header.mode == 3 || g_SpawnedActors[6].header.mode == 4) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
                g_SpawnedActors[6].header.mode = 5;
            } else if (g_SpawnedActors[6].header.mode == 8) {
                SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
                g_SpawnedActors[6].header.mode = 0xB;
            }
        }
        SELF(Actor)->unk_03++;
    }
    if (SELF(Actor)->unk_03 == 2) {
        switch (g_SpawnedActors[6].unk_06 & 3) {
            case 0:
                UI_TextDraw(29, 20, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_MESSAGE_EQUIP_ROD_LURE));
                break;
            case 1:
                UI_TextDraw(29, 20, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_MSG_DATA_TITLE));
                break;
            case 2:
                UI_TextDraw(29, 20, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_MESSAGE_HOW_TO_FISH));
                break;
        }
        UI_CursorDraw((g_SpawnedActors[6].unk_06 * 48) + 88, 46U, 0);
    }
}
