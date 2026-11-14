#include "engine/slus/slus.h"

/* releases the sound system: stops all keys, closes the seven VAB
 * banks and the seven SEP owners, then shuts down the reverb and the SPU.
 */
MATCH void SND_Exit(void) {
    SsUtAllKeyOff(0);
    SsVabClose(g_SndVabIds[0]);
    SsVabClose(g_SndVabIds[1]);
    SsVabClose(g_SndVabIds[2]);
    SsVabClose(g_SndVabIds[3]);
    SsVabClose(g_SndVabIds[4]);
    SsVabClose(g_SndVabIds[5]);
    SsVabClose(g_SndVabIds[6]);
    if (g_SelectionEffectVoices[0] != -1) {
        SsSepClose(g_SelectionEffectVoices[0]);
    }
    if (g_SelectionEffectVoices[1] != -1) {
        SsSepClose(g_SelectionEffectVoices[1]);
    }
    if (g_SelectionEffectVoices[2] != -1) {
        SsSepClose(g_SelectionEffectVoices[2]);
    }
    if (g_SelectionEffectVoices[3] != -1) {
        SsSepClose(g_SelectionEffectVoices[3]);
    }
    if (g_SelectionEffectVoices[4] != -1) {
        SsSepClose(g_SelectionEffectVoices[4]);
    }
    if (g_SelectionEffectVoices[5] != -1) {
        SsSepClose(g_SelectionEffectVoices[5]);
    }
    if (g_SelectionEffectVoices[6] != -1) {
        SsSepClose(g_SelectionEffectVoices[6]);
    }
    SsUtReverbOff();
    SsUtSetReverbType(SS_REV_TYPE_OFF);
    SsUtSetReverbDepth(0, 0);
    SsEnd();
    SND_QuitSpu();
}
