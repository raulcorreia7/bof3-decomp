#include "commu00_00.h"

/* The 60 active-record slots are FairyJob rows; this pass
 * folds the 9-byte rows of D_801F2705 for the slots of one kind. */

MATCH void func_801EF110(s32 battle_count) {
    u32 dec;
    s32 total;
    s32 i;
    s32 j;
    s32 arg_step;
    s32 kind;
    s32 term;
    s32 value;
    s32 result;

    dec = (g_BattleCount - D_801455B4) / 5u;
    if ((u16)dec != 0u) {
        arg_step = (battle_count & BYTE_MASK) * 2;
        total    = 0;
        /* FAKE: the local copy of the compared kind is required; the bare
         * literal measures 98.46. */
        kind     = FAIRY_JOB_HUNT;
        j        = 0;
        i        = 0;
        do {
            if ((g_FairyJobs[i].active != 0) && (g_FairyJobs[i].type == kind)) {
                term = *(g_Fairies[0] + 5 + j) + 3;
                total += term;
            }
            i += 1;
            j += 9;
        } while (i < 60);

        value = D_801455C2 + ((s16)total - arg_step) * (u16)dec;
        if (value >= 0) {
            result = 99;
            if (value < 100) {
                result = value;
            }
        } else {
            result = 0;
        }
        D_801455C2 = result;
        D_801455B4 = g_BattleCount;
    }
}
