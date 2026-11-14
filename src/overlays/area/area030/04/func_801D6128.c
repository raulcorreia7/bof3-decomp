#include "area030_04.h"

/* Work-row fields behind the area-030 scratchpad pointer. */
#define BANNER_TIMER (FISHING_STATE->step_timer_09)
#define BANNER_INDEX (FISHING_STATE->step_index_0A)
#define BANNER_FRAME (FISHING_STATE->cue_index_06)

/* Advances the area-030 title banner: walks the 3-byte frame table, queues the shop record when the frame
 * asks for it, clamps the scroll frame, and draws the banner panels. */
MATCH void func_801D6128(void) {
    s8            delta;
    s32           prev;
    s32           last;
    FishingState* work;
    s8            frame;
    s8            frame_value;
    s32           entry_offset;
    s32           entry;
    u8            count;

    count = BANNER_TIMER;
    if (count == 0) {
        entry_offset = BANNER_INDEX * 3;
        if (D_801E2024[entry_offset] == 0) {
            BANNER_INDEX = D_801E2025[entry_offset];
            BANNER_FRAME = 0;
        }
        Actor_SelectScript(D_801E2024[BANNER_INDEX * 3]);
        BANNER_TIMER = D_801E2025[BANNER_INDEX * 3];
        if (D_801E2026[BANNER_INDEX * 3] == 0x50) {
            entry                               = Actor_FindFreeSlot() & BYTE_MASK;
            g_SpawnedActors[entry].header.flags = 1;
            g_SpawnedActors[entry].type         = 0x1A;
            g_SpawnedActors[entry].header.mode  = 0x10;
            g_SpawnedActors[entry].header.step  = 2;
            g_SpawnedActors[entry].unk_03       = 2;
            g_SpawnedActors[entry].unk_2E       = 0xF0;
            g_SpawnedActors[entry].unk_30       = 0xA6;
        }
        BANNER_INDEX += 1;
    } else {
        BANNER_TIMER = count - 1;
        Actor_StepAnimLoop();
    }
    Area_AddActor();
    prev = BANNER_INDEX;
    prev -= 1;
    delta = D_801E2026[prev * 3];
    if (delta != 0x50 && !(g_FrameCount & 0x3)) {
        BANNER_FRAME += delta;
        work  = FISHING_STATE;
        frame = work->cue_index_06;
        if (frame >= 0) {
            if (frame < 25) {
                frame_value = frame;
            } else {
                frame_value = 0x18;
            }
        } else {
            frame_value = 0;
        }
        work->cue_index_06 = frame_value;
    }
    func_801D1744(236, 112, 1);
    func_801D1818(236, 128, 1);
    Fishing_SetDrawMode(0, 1);
    Fishing_DrawSprite(20, 1, 228, 104);
    last = BANNER_INDEX;
    last -= 1;
    if (D_801E2026[last * 3] != 0) {
        Fishing_DrawIcon(252, BANNER_FRAME + 112, 1);
    }
}
