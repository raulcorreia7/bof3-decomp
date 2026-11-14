#include "area030_04.h"

/* TODO */
MATCH void func_801D36F8(void) {
    FishingState* record;
    s8            slot;
    u8            area;

    record = FISHING_STATE;
    if (g_FishingPromptSets[record->cue_index_06][3] != 0) {
        slot = Actor_FindFreeSlot();
        if (slot != -1) {
            g_SpawnedActors[slot].header.flags = 1;
            g_SpawnedActors[slot].type         = 0xF;
            area                               = FISHING_STATE->cue_index_06;
            g_SpawnedActors[slot].unk_4A       = 0;
            g_SpawnedActors[slot].link         = 0;
            g_SpawnedActors[slot].header.mode  = 8;
            g_SpawnedActors[slot].unk_06       = area;
        }
        FISHING_STATE->handler_index_01 = 6;
    } else {
        record->row_4B                  = g_FishingPromptSets[record->cue_index_06][0];
        FISHING_STATE->handler_index_01 = FISHING_STATE->handler_index_01 + 1;
    }
    Fishing_DrawWindowFrame(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, 0);
}
