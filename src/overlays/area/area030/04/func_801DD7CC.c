#include "area030_04.h"

/* Draws the AREA030 panel row, then moves the panel state when the
 * prompt page and frame state allow it: the accept cue steps the caret back,
 * right/left step the selected index with wraparound. */
MATCH void func_801DD7CC(void) {
    UI_TextDraw(29, 20, 0, TEXT_LENGTH_MAX, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_MESSAGE_HOW_TO_PAGE_HINT));
    if ((g_SpawnedActors[6].header.mode == 0xE) && (g_SpawnedActors[6].unk_08 == 0)) {
        if (g_PadStates[0].pressed & g_InputMasks[FISHING_INPUT_CANCEL]) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_COMMON, 6));
            SELF(FishingState)->flag_04   = 0;
            SELF(FishingState)->sub_index = (SELF(FishingState)->sub_index - 1);
            return;
        }
        if (g_PadStates[0].pressed & PADLdown) {
            g_SpawnedActors[6].unk_08              = 0xFF;
            g_SpawnedActors[6].pos.z.part.fraction = g_SpawnedActors[6].pos.z.part.fraction + 1;
            if ((g_SpawnedActors[6].pos.z.part.fraction & HALF_MASK) >= 6U) {
                g_SpawnedActors[6].pos.z.part.fraction = 0;
            }
        } else if (g_PadStates[0].pressed & PADLup) {
            g_SpawnedActors[6].unk_08              = 1;
            g_SpawnedActors[6].pos.z.part.fraction = g_SpawnedActors[6].pos.z.part.fraction - 1;
            if ((s16)g_SpawnedActors[6].pos.z.part.fraction < 0) {
                g_SpawnedActors[6].pos.z.part.fraction = 5;
            }
        }
    }
}
