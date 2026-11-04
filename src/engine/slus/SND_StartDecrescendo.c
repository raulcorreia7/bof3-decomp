#include "engine/slus/slus.h"

/* starts the effect group's decrescendo: while D_80144954 is clear it
 * pins the SsSepVol pair to 0x3FF and forwards the group's s8 separator id with
 * the caller's cue arguments to SsSepSetDecrescendo.
 */
MATCH void SND_StartDecrescendo(s32 group, s16 sequence, s16 volume, s32 time) {
    if (D_80144954 != 0) {
        return;
    }
    D_8018B418 = 0x3FF;
    D_8018B41A = 0x3FF;
    SsSepSetDecrescendo(g_SelectionFxVoices[group & HALF_MASK], sequence, volume, time);
}
