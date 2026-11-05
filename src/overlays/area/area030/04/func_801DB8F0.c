#include "area030_04.h"

/* Declared file-locally: this module's shared header omits the callee. */

/* Drives the AREA030 prompt row cursor from the pad pair and, when it
 * reaches the slot's row limit, queues the confirm cue and advances the panel
 * step. */
MATCH void func_801DB8F0(void) {
    s32 offset;

    if ((g_InputPressed & PADRdown) != 0) {
        FISHING_STATE->step_timer_09 = (u8)g_Actors[D_801E3208].roll_90;
    } else {
        FISHING_STATE->step_timer_09 = (u8)(FISHING_STATE->step_timer_09 + 1);
    }

    func_801E0ED0(0, 0x4E);
    func_801E0F4C(0x80, 0x5B, D_8014688E[D_801E3208 * 0x98]);

    offset = D_801E3208 * 0x98;
    func_801E1004(D_8014688E[offset], FISHING_STATE->step_timer_09, 0);

    if (FISHING_STATE->step_timer_09 == g_Actors[D_801E3208].roll_90) {
        if (D_801E3214 != 0) {
            SND_PlayCue(EMI_CUE_ID(2, 13));
        }
        SND_PlayCue(EMI_CUE_ID(1, 2));
        FISHING_STATE->step_timer_09 = 4;
        FISHING_STATE->sub_index_03  = (u8)(FISHING_STATE->sub_index_03 + 1);
    }
    func_8014D978();
    func_801E16DC();
}
