#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callees. */

/* Draws the AREA030 prompt rows for the current slot, queues the cue the pad pair selects, toggles the caret and advances the panel step. */
MATCH void func_801DC0CC(void) {
    FishingState* work;
    s32           offset;
    u16           cue;

    func_801E0ED0(0, FISHING_CATCH_BAR_Y);
    func_801E0F4C(FISHING_CATCH_ICON_X, FISHING_CATCH_ICON_Y, D_8014688E[g_FishingHookedFish * 0x98]);

    offset = g_FishingHookedFish * 0x98;
    func_801E1004(D_8014688E[offset], D_80146918[offset], 0);
    Fishing_DrawRank(FISHING_CATCH_RANK_X, FISHING_CATCH_RANK_Y);
    Fishing_DrawIconRow(8, FISHING_CATCH_ROW_Y, 0x44);

    if ((g_InputPressed & (PADLup | PADLdown)) != 0) {
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 0));
        work               = FISHING_STATE;
        work->cue_index_06 = (work->cue_index_06 ^ 1);
    } else if ((g_InputPressed & PADRdown) != 0) {
        cue = 0x103;
        SND_PlayCue(cue);
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
        work               = FISHING_STATE;
        work->sub_index_03 = (work->sub_index_03 + 1);
    } else if ((g_InputPressed & PADRup) != 0) {
        cue                = 0x106;
        work               = FISHING_STATE;
        work->cue_index_06 = 1;
        SND_PlayCue(cue);
        SND_PlayCue(EMI_CUE_ID(SND_BANK_COMMON, 2));
        work               = FISHING_STATE;
        work->sub_index_03 = (work->sub_index_03 + 1);
    }
    Menu_DrawCursorSprite(32, FISHING_STATE->cue_index_06 * 12 + 182, 0);
    Actor_StepAnimLoop();
    func_801E16DC();
}
