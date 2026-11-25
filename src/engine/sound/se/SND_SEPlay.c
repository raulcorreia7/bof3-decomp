#include "engine/slus/slus.h"

/* dispatches an SE's bank and record, updates interpolated channel
 * values, and keys the requested SPU voices.
 */
MATCH void SND_SEPlay(u16 se_id) {
    s32 scaled;
    s32 next;

    g_SndSeBank   = EMI_SE_ID_BANK(se_id);
    g_SndSeRecord = EMI_SE_ID_INDEX(se_id);
    ((void (*)(void))g_SndSeReaders[EMI_SE_ID_BANK(se_id)])();

    if (g_SndSeUseVolume == 0x80) {
        switch (g_SndSeLayers) {
            case 3:
                scaled = g_SndSeLayer3VolumeL * (g_SndSeUseVolume - g_SndSeLayer3Pan);
                if (scaled < 0) {
                    scaled += 0x7F;
                }
                next                 = g_SndSeLayer3VolumeR * g_SndSeLayer3Pan;
                g_SndSeLayer3VolumeL = scaled >> 7;
                if (next < 0) {
                    next += 0x7F;
                }
                g_SndSeLayer3VolumeR = next >> 7;
                /* fall through */
            case 2:
                scaled = g_SndSeLayer2VolumeL * (0x80 - g_SndSeLayer2Pan);
                if (scaled < 0) {
                    scaled += 0x7F;
                }
                next                 = g_SndSeLayer2VolumeR * g_SndSeLayer2Pan;
                g_SndSeLayer2VolumeL = scaled >> 7;
                if (next < 0) {
                    next += 0x7F;
                }
                g_SndSeLayer2VolumeR = next >> 7;
                /* fall through */
            case 1:
                scaled = g_SndSeLayer1VolumeL * (0x80 - g_SndSeLayer1Pan);
                if (scaled < 0) {
                    scaled += 0x7F;
                }
                next                 = g_SndSeLayer1VolumeR * g_SndSeLayer1Pan;
                g_SndSeLayer1VolumeL = scaled >> 7;
                if (next < 0) {
                    next += 0x7F;
                }
                g_SndSeLayer1VolumeR = next >> 7;
                /* fall through */
            case 0:
                scaled = g_SndSeLayer0VolumeL * (0x80 - g_SndSeLayer0Pan);
                if (scaled < 0) {
                    scaled += 0x7F;
                }
                next                 = g_SndSeLayer0VolumeR * g_SndSeLayer0Pan;
                g_SndSeLayer0VolumeL = scaled >> 7;
                if (next < 0) {
                    next += 0x7F;
                }
                g_SndSeLayer0VolumeR = next >> 7;
                break;
        }

        if ((se_id & 0xF000) == 0) {
            g_SndSeVolumeL = 0x17FF;
            g_SndSeVolumeR = 0x17FF;
        }
    }

    if (D_8018232A == 0) {
        if (g_SndSeLayers == 1) {
            goto initial_mode1;
        } else if (g_SndSeLayers < 2) {
            if (g_SndSeLayers == 0) {
                goto initial_mode0;
            }
            return;
        } else if (g_SndSeLayers == 2) {
            goto initial_mode2;
        } else if (g_SndSeLayers != 3) {
            return;
        }
    initial_mode3:
        g_SndSeLayer3KeyedVoice =
            SsUtKeyOnV(g_SndSeLayer3SpuVoice, g_SndSeVabId, g_SndSeLayer3Program, g_SndSeLayer3Tone, g_SndSeLayer3Note, g_SndSeLayer3Fine, g_SndSeLayer3VolumeL, g_SndSeLayer3VolumeR);
        if (g_SndSeUseVolume == 0x80) {
            SsUtSetDetVVol(g_SndSeLayer3KeyedVoice, g_SndSeVolumeL, g_SndSeVolumeR);
        }
    initial_mode2:
        g_SndSeLayer2KeyedVoice =
            SsUtKeyOnV(g_SndSeLayer2SpuVoice, g_SndSeVabId, g_SndSeLayer2Program, g_SndSeLayer2Tone, g_SndSeLayer2Note, g_SndSeLayer2Fine, g_SndSeLayer2VolumeL, g_SndSeLayer2VolumeR);
        if (g_SndSeUseVolume == 0x80) {
            SsUtSetDetVVol(g_SndSeLayer2KeyedVoice, g_SndSeVolumeL, g_SndSeVolumeR);
        }
    initial_mode1:
        g_SndSeLayer1KeyedVoice =
            SsUtKeyOnV(g_SndSeLayer1SpuVoice, g_SndSeVabId, g_SndSeLayer1Program, g_SndSeLayer1Tone, g_SndSeLayer1Note, g_SndSeLayer1Fine, g_SndSeLayer1VolumeL, g_SndSeLayer1VolumeR);
        if (g_SndSeUseVolume == 0x80) {
            SsUtSetDetVVol(g_SndSeLayer1KeyedVoice, g_SndSeVolumeL, g_SndSeVolumeR);
        }
    initial_mode0:
        g_SndSeLayer0KeyedVoice =
            SsUtKeyOnV(g_SndSeLayer0SpuVoice, g_SndSeVabId, g_SndSeLayer0Program, g_SndSeLayer0Tone, g_SndSeLayer0Note, g_SndSeLayer0Fine, g_SndSeLayer0VolumeL, g_SndSeLayer0VolumeR);
        if (g_SndSeUseVolume == 0x80) {
            SsUtSetDetVVol(g_SndSeLayer0KeyedVoice, g_SndSeVolumeL, g_SndSeVolumeR);
        }
    initial_done:
        D_8018232A           = -1;
        g_SndSeLastVoice     = g_SndSeLayer0SpuVoice;
        g_SndSeLastRetrigger = g_SndSeRetrigger;
        goto queue_done;
    } else {
        if (g_SndSeLastVoice != g_SndSeLayer0SpuVoice) {
            if (g_SndSeLayers == 1) {
                goto queue_standard1;
            }
            if (g_SndSeLayers < 2) {
                goto queue_standard_low;
            }
            goto queue_standard23;
        }
        if (g_SndSeLastRetrigger > g_SndSeRetrigger) {
            goto queue_array_guard; /* once per active SE */
        }
        switch (g_SndSeLayers) {
            case 3:
                goto queue_special3;
            case 2:
                goto queue_special2;
            case 1:
                goto queue_special1;
            case 0:
                goto queue_special0;
            default:
                return;
        }
    }

queue_special3:
    g_SndSeLayer3KeyedVoice =
        SsUtKeyOnV(g_SndSeLayer3SpuVoice, g_SndSeVabId, g_SndSeLayer3Program, g_SndSeLayer3Tone, g_SndSeLayer3Note, g_SndSeLayer3Fine, g_SndSeLayer3VolumeL, g_SndSeLayer3VolumeR);
    if (g_SndSeUseVolume == 0x80) {
        SsUtSetDetVVol(g_SndSeLayer3KeyedVoice, g_SndSeVolumeL, g_SndSeVolumeR);
    }
queue_special2:
    g_SndSeLayer2KeyedVoice =
        SsUtKeyOnV(g_SndSeLayer2SpuVoice, g_SndSeVabId, g_SndSeLayer2Program, g_SndSeLayer2Tone, g_SndSeLayer2Note, g_SndSeLayer2Fine, g_SndSeLayer2VolumeL, g_SndSeLayer2VolumeR);
    if (g_SndSeUseVolume == 0x80) {
        SsUtSetDetVVol(g_SndSeLayer2KeyedVoice, g_SndSeVolumeL, g_SndSeVolumeR);
    }
queue_special1:
    g_SndSeLayer1KeyedVoice =
        SsUtKeyOnV(g_SndSeLayer1SpuVoice, g_SndSeVabId, g_SndSeLayer1Program, g_SndSeLayer1Tone, g_SndSeLayer1Note, g_SndSeLayer1Fine, g_SndSeLayer1VolumeL, g_SndSeLayer1VolumeR);
    if (g_SndSeUseVolume == 0x80) {
        SsUtSetDetVVol(g_SndSeLayer1KeyedVoice, g_SndSeVolumeL, g_SndSeVolumeR);
    }
queue_special0:
    g_SndSeLayer0KeyedVoice =
        SsUtKeyOnV(g_SndSeLayer0SpuVoice, g_SndSeVabId, g_SndSeLayer0Program, g_SndSeLayer0Tone, g_SndSeLayer0Note, g_SndSeLayer0Fine, g_SndSeLayer0VolumeL, g_SndSeLayer0VolumeR);
    if (g_SndSeUseVolume == 0x80) {
        SsUtSetDetVVol(g_SndSeLayer0KeyedVoice, g_SndSeVolumeR, g_SndSeVolumeR);
    }
    goto queue_update; /* shared active-SE update */

queue_array_guard:
    if (g_SndVoiceStatus[g_SndSeLastVoice] != 0) {
        return;
    }
    if (g_SndSeLayers == 1) {
        goto queue_standard1;
    }
    if (g_SndSeLayers >= 2) {
        goto queue_standard23;
    }
    if (g_SndSeLayers == 0) {
        goto queue_standard0;
    }
    return;

/* A duplicate of the array-guard mode-0 tail: deleting it moves the shared tail and breaks the match. */
queue_standard_low:
    if (g_SndSeLayers == 0) {
        goto queue_standard0;
    }
    return;

queue_standard23:
    if (g_SndSeLayers == 2) {
        goto queue_standard2;
    }
    if (g_SndSeLayers != 3) {
        return;
    }
queue_standard3:
    g_SndSeLayer3KeyedVoice =
        SsUtKeyOnV(g_SndSeLayer3SpuVoice, g_SndSeVabId, g_SndSeLayer3Program, g_SndSeLayer3Tone, g_SndSeLayer3Note, g_SndSeLayer3Fine, g_SndSeLayer3VolumeL, g_SndSeLayer3VolumeR);
    if (g_SndSeUseVolume == 0x80) {
        SsUtSetDetVVol(g_SndSeLayer3KeyedVoice, g_SndSeVolumeL, g_SndSeVolumeR);
    }
queue_standard2:
    g_SndSeLayer2KeyedVoice =
        SsUtKeyOnV(g_SndSeLayer2SpuVoice, g_SndSeVabId, g_SndSeLayer2Program, g_SndSeLayer2Tone, g_SndSeLayer2Note, g_SndSeLayer2Fine, g_SndSeLayer2VolumeL, g_SndSeLayer2VolumeR);
    if (g_SndSeUseVolume == 0x80) {
        SsUtSetDetVVol(g_SndSeLayer2KeyedVoice, g_SndSeVolumeL, g_SndSeVolumeR);
    }
queue_standard1:
    g_SndSeLayer1KeyedVoice =
        SsUtKeyOnV(g_SndSeLayer1SpuVoice, g_SndSeVabId, g_SndSeLayer1Program, g_SndSeLayer1Tone, g_SndSeLayer1Note, g_SndSeLayer1Fine, g_SndSeLayer1VolumeL, g_SndSeLayer1VolumeR);
    if (g_SndSeUseVolume == 0x80) {
        SsUtSetDetVVol(g_SndSeLayer1KeyedVoice, g_SndSeVolumeL, g_SndSeVolumeR);
    }
queue_standard0:
    g_SndSeLayer0KeyedVoice =
        SsUtKeyOnV(g_SndSeLayer0SpuVoice, g_SndSeVabId, g_SndSeLayer0Program, g_SndSeLayer0Tone, g_SndSeLayer0Note, g_SndSeLayer0Fine, g_SndSeLayer0VolumeL, g_SndSeLayer0VolumeR);
    if (g_SndSeUseVolume == 0x80) {
        SsUtSetDetVVol(g_SndSeLayer0KeyedVoice, g_SndSeVolumeL, g_SndSeVolumeR);
    }
queue_update:
    g_SndSeLastVoice     = g_SndSeLayer0SpuVoice;
    g_SndSeLastRetrigger = g_SndSeRetrigger;
queue_done:;
}
