#include "area030_04.h"

/* Draws the AREA030 prompt row, then steps the panel cursor from the
 * pad pair: right/left wrap the entry index and move the caret, confirm queues
 * the accept cue and steps the panel state back. */
MATCH void func_801DD664(void) {
    u8* panel;
    u16 index;

    UI_TextDraw(29, 20, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_MSG_DATA_PAGE_HINT));

    panel = &g_SpawnedActors[6].header.mode;
    if (*panel != 8) {
        return;
    }

    if ((g_PadStates[0].pressed & PADLright) != 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
        index                                  = D_801442BE + 1;
        g_SpawnedActors[6].pos.z.part.fraction = index;
        if ((index & HALF_MASK) >= 0x17) {
            g_SpawnedActors[6].pos.z.part.fraction = 0;
        }
        g_SpawnedActors[6].unk_08 = 0;
        *panel                    = (*panel + 1);
        return;
    }

    if ((g_PadStates[0].pressed & PADLleft) != 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 2));
        index                                  = D_801442BE - 1;
        g_SpawnedActors[6].pos.z.part.fraction = index;
        if ((s16)index < 0) {
            g_SpawnedActors[6].pos.z.part.fraction = 0x16;
        }
        g_SpawnedActors[6].unk_08 = 1;
        *panel                    = (*panel + 1);
        return;
    }

    if ((g_PadStates[0].pressed & g_InputMasks[FISHING_INPUT_CANCEL]) != 0) {
        SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
        SELF(FishingState)->flag_04   = 0;
        SELF(FishingState)->sub_index = (SELF(FishingState)->sub_index - 1);
    }
}
