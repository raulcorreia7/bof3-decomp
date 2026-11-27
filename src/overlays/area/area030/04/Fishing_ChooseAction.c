#include "area030_04.h"

/* Translates the frame's pad state into the panel mode: the 0x10
 *           case advances the step counter, 0x80/0x4 select the next panel
 *           step, and 0x40 either arms or clears the fishing prompt depending
 *           on the lure/rod and the area query. */
/* func_801D9E40 */
MATCH void Fishing_ChooseAction(void) {
    switch (g_PadStates[0].pressed & (PADRup | PADRdown | PADRleft | PADL1)) {
        case PADRup:
            g_SpawnedActors[3].header.mode = 7;
            g_SpawnedActors[1].header.mode = 4;
            SELF(FishingState)->sub_index++;
            break;
        case PADRleft:
            g_SpawnedActors[3].header.mode = 7;
            g_SpawnedActors[1].header.mode = 4;
            SELF(FishingState)->mode_index = 9;
            SELF(FishingState)->sub_index  = 0;
            break;
        case PADRdown:
            g_SpawnedActors[3].header.mode = 7;
            if (g_FishingEquipment.lure_id == 0 || g_FishingEquipment.rod_id == 0) {
                g_SpawnedActors[1].header.mode = 4;
                SELF(FishingState)->mode_index = 9;
                SELF(FishingState)->sub_index  = 0;
                break;
            }
            if (Fishing_FishStacksFull() & BYTE_MASK) {
                if (g_FishingFullNoticeShown == 0) {
                    g_FishingFullNoticeShown       = 1;
                    g_SpawnedActors[1].header.mode = 4;
                    SELF(FishingState)->sub_index  = 7;
                    break;
                }
            } else {
                g_FishingFullNoticeShown = 0;
            }
            SELF(FishingState)->mode_index = 2;
            /* FAKE: the order lock steers regalloc */
            FAKE_ORDER_LOCK_BEGIN
                SELF(FishingState)->sub_index = 0;
            FAKE_ORDER_LOCK_END;
            break;
        case PADL1:
            g_SpawnedActors[3].header.mode = 7;
            g_SpawnedActors[1].header.mode = 4;
            SELF(FishingState)->mode_index = 0xA;
            SELF(FishingState)->sub_index  = 0;
            break;
    }
}
