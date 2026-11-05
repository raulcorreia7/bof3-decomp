#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callees. */

/* Draws the AREA030 prompt rows for the current slot, queues the cue
 * the pad pair selects, toggles the caret and advances the panel step, then
 * places the caret row and runs the shared per-frame tails. */
MATCH void func_801DC0CC(void) {
    FishingState* work;
    s32           offset;
    u16           cue;

    func_801E0ED0(0, 0x4E);
    func_801E0F4C(0x80, 0x5B, D_8014688E[D_801E3208 * 0x98]);

    offset = D_801E3208 * 0x98;
    func_801E1004(D_8014688E[offset], D_80146918[offset], 0);
    func_801E1320(0xB0, 0x9C);
    func_801E162C(8, 0x94, 0x44);

    if ((g_InputPressed & (PADLup | PADLdown)) != 0) {
        SND_PlayCue(EMI_CUE_ID(1, 0));
        work               = FISHING_STATE;
        work->cue_index_06 = (work->cue_index_06 ^ 1);
    } else if ((g_InputPressed & PADRdown) != 0) {
        cue = 0x103;
        SND_PlayCue(cue);
        SND_PlayCue(EMI_CUE_ID(1, 2));
        work               = FISHING_STATE;
        work->sub_index_03 = (work->sub_index_03 + 1);
    } else if ((g_InputPressed & PADRup) != 0) {
        cue                = 0x106;
        work               = FISHING_STATE;
        work->cue_index_06 = 1;
        SND_PlayCue(cue);
        SND_PlayCue(EMI_CUE_ID(1, 2));
        work               = FISHING_STATE;
        work->sub_index_03 = (work->sub_index_03 + 1);
    }
    Menu_DrawCursorSprite(0x20, FISHING_STATE->cue_index_06 * 0xC + 0xB6, 0);
    func_8014D978();
    func_801E16DC();
}
