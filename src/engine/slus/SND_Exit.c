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
    if (g_SelectionFxVoices[0] != -1) {
        SsSepClose(g_SelectionFxVoices[0]);
    }
    if (g_SelectionFxVoices[1] != -1) {
        SsSepClose(g_SelectionFxVoices[1]);
    }
    if (g_SelectionFxVoices[2] != -1) {
        SsSepClose(g_SelectionFxVoices[2]);
    }
    if (g_SelectionFxVoices[3] != -1) {
        SsSepClose(g_SelectionFxVoices[3]);
    }
    if (g_SelectionFxVoices[4] != -1) {
        SsSepClose(g_SelectionFxVoices[4]);
    }
    if (g_SelectionFxVoices[5] != -1) {
        SsSepClose(g_SelectionFxVoices[5]);
    }
    if (g_SelectionFxVoices[6] != -1) {
        SsSepClose(g_SelectionFxVoices[6]);
    }
    SsUtReverbOff();
    SsUtSetReverbType(SS_REV_TYPE_OFF);
    SsUtSetReverbDepth(0, 0);
    SsEnd();
    func_8016BA04();
}
