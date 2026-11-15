#include "engine/slus/slus.h"

/* resolves the effect group's entry in the s8 table at g_SelectionEffectVoices
 * and forwards it, with the caller's effect id, to SsSepStop.
 */
MATCH void SND_StopSequence(s32 group, s16 sequence) {
    SsSepStop(g_SelectionEffectVoices[group & HALF_MASK], sequence);
}
