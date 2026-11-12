#include "area030_04.h"

/* Panel page fields of the scratchpad work record. */
#define FISHING_PAGE_STEP     (FISHING_STATE->step_timer_09)
#define FISHING_PAGE_CATEGORY (FISHING_STATE->saved_index_0B)
#define FISHING_PAGE_FLAG     (FISHING_STATE->cue_index_06)
#define FISHING_SLOT_HANDLER  (FISHING_STATE->mode_index_02)
#define FISHING_PAGE_HANDLER  (FISHING_STATE->sub_index_03)

/* Advances the AREA030 selection page: slides the page counter,
 * draws the page/selection rows for the current category entry, and on the
 * fourth step resets the counter, registers the chosen entry with the page
 * flags, and queues the 0x203 cue before the world step passes. */
MATCH void func_801DC248(void) {
    s32 offset;
    u8* counter;

    FISHING_PAGE_STEP += 1;
    Fishing_DrawCatchBar((-(FISHING_PAGE_STEP * TO_COORD(80)) >> 16), FISHING_CATCH_BAR_Y);
    Fishing_DrawCatchIcon((FISHING_PAGE_STEP * FISHING_CATCH_ICON_STEP) + FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, D_8014688E[g_FishingHookedFish * 0x98]);

    offset = g_FishingHookedFish * 0x98;
    func_801E1004(D_8014688E[offset], D_80146918[offset], FISHING_PAGE_STEP);
    Fishing_DrawRank(FISHING_CATCH_RANK_X, (FISHING_PAGE_STEP * FISHING_CATCH_ROW_STEP) + FISHING_CATCH_RANK_Y);

    if (FISHING_PAGE_CATEGORY == 1) {
        Fishing_DrawIconRow(8, (FISHING_PAGE_STEP * FISHING_CATCH_ROW_STEP) + FISHING_CATCH_ROW_Y, 68);
    } else if (FISHING_PAGE_CATEGORY == 2) {
        Fishing_DrawIconRow(8, (FISHING_PAGE_STEP * FISHING_CATCH_ROW_STEP) + FISHING_CATCH_ROW_Y, 66);
    }

    if (FISHING_PAGE_STEP == 4) {
        FISHING_PAGE_STEP = 0;
        if (FISHING_PAGE_CATEGORY == 1 && FISHING_PAGE_FLAG == 0) {
            FISHING_SLOT_HANDLER = 0xB;
            FISHING_PAGE_HANDLER = 0;
        } else {
            FISHING_SLOT_HANDLER = 1;
            counter              = &D_8014403D;
            FISHING_PAGE_HANDLER = 0;
            *counter += 1;
        }
        SND_StopSequence(0, 1);
        SND_PlayBGM(0x28, 0x64, 8);
        SND_PlayCue(EMI_CUE_ID(SND_BANK_AREA, 3));
    }
    Actor_StepAnimLoop();
}
