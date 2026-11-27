#include "area030_04.h"

/* TODO */
MATCH void func_801D36F8(void) {
    FishingState* record;
    s8            slot;
    u8            area;

    record = SELF(FishingState);
    if (g_FishingPromptSets[record->cue_index][3] != 0) {
        slot = Actor_FindFreeSpawned();
        if (slot != -1) {
            g_SpawnedActors[slot].header.flags = 1;
            g_SpawnedActors[slot].type         = 0xF;
            area                               = SELF(FishingState)->cue_index;
            g_SpawnedActors[slot].unk_4A       = 0;
            g_SpawnedActors[slot].link         = 0;
            g_SpawnedActors[slot].header.mode  = 8;
            g_SpawnedActors[slot].unk_06       = area;
        }
        SELF(FishingState)->handler_index = 6;
    } else {
        record->row_4B                    = g_FishingPromptSets[record->cue_index][0];
        SELF(FishingState)->handler_index = SELF(FishingState)->handler_index + 1;
    }
    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
}
