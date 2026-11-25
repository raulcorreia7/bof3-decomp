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
                scaled = g_SndSeVoice3VolumeL * (g_SndSeUseVolume - g_SndSeVoice3Pan);
                if (scaled < 0) {
                    scaled += 0x7F;
                }
                next                 = g_SndSeVoice3VolumeR * g_SndSeVoice3Pan;
                g_SndSeVoice3VolumeL = scaled >> 7;
                if (next < 0) {
                    next += 0x7F;
                }
                g_SndSeVoice3VolumeR = next >> 7;
                /* fall through */
            case 2:
                scaled = g_SndSeVoice2VolumeL * (0x80 - g_SndSeVoice2Pan);
                if (scaled < 0) {
                    scaled += 0x7F;
                }
                next                 = g_SndSeVoice2VolumeR * g_SndSeVoice2Pan;
                g_SndSeVoice2VolumeL = scaled >> 7;
                if (next < 0) {
                    next += 0x7F;
                }
                g_SndSeVoice2VolumeR = next >> 7;
                /* fall through */
            case 1:
                scaled = g_SndSeVoice1VolumeL * (0x80 - g_SndSeVoice1Pan);
                if (scaled < 0) {
                    scaled += 0x7F;
                }
                next                 = g_SndSeVoice1VolumeR * g_SndSeVoice1Pan;
                g_SndSeVoice1VolumeL = scaled >> 7;
                if (next < 0) {
                    next += 0x7F;
                }
                g_SndSeVoice1VolumeR = next >> 7;
                /* fall through */
            case 0:
                scaled = g_SndSeVoice0VolumeL * (0x80 - g_SndSeVoice0Pan);
                if (scaled < 0) {
                    scaled += 0x7F;
                }
                next                 = g_SndSeVoice0VolumeR * g_SndSeVoice0Pan;
                g_SndSeVoice0VolumeL = scaled >> 7;
                if (next < 0) {
                    next += 0x7F;
                }
                g_SndSeVoice0VolumeR = next >> 7;
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
        g_SndSeVoice3KeyedVoice =
            SsUtKeyOnV(g_SndSeVoice3SpuVoice, g_SndSeVabId, g_SndSeVoice3Program, g_SndSeVoice3Tone, g_SndSeVoice3Note, g_SndSeVoice3Fine, g_SndSeVoice3VolumeL, g_SndSeVoice3VolumeR);
        if (g_SndSeUseVolume == 0x80) {
            SsUtSetDetVVol(g_SndSeVoice3KeyedVoice, g_SndSeVolumeL, g_SndSeVolumeR);
        }
    initial_mode2:
        g_SndSeVoice2KeyedVoice =
            SsUtKeyOnV(g_SndSeVoice2SpuVoice, g_SndSeVabId, g_SndSeVoice2Program, g_SndSeVoice2Tone, g_SndSeVoice2Note, g_SndSeVoice2Fine, g_SndSeVoice2VolumeL, g_SndSeVoice2VolumeR);
        if (g_SndSeUseVolume == 0x80) {
            SsUtSetDetVVol(g_SndSeVoice2KeyedVoice, g_SndSeVolumeL, g_SndSeVolumeR);
        }
    initial_mode1:
        g_SndSeVoice1KeyedVoice =
            SsUtKeyOnV(g_SndSeVoice1SpuVoice, g_SndSeVabId, g_SndSeVoice1Program, g_SndSeVoice1Tone, g_SndSeVoice1Note, g_SndSeVoice1Fine, g_SndSeVoice1VolumeL, g_SndSeVoice1VolumeR);
        if (g_SndSeUseVolume == 0x80) {
            SsUtSetDetVVol(g_SndSeVoice1KeyedVoice, g_SndSeVolumeL, g_SndSeVolumeR);
        }
    initial_mode0:
        g_SndSeVoice0KeyedVoice =
            SsUtKeyOnV(g_SndSeVoice0SpuVoice, g_SndSeVabId, g_SndSeVoice0Program, g_SndSeVoice0Tone, g_SndSeVoice0Note, g_SndSeVoice0Fine, g_SndSeVoice0VolumeL, g_SndSeVoice0VolumeR);
        if (g_SndSeUseVolume == 0x80) {
            SsUtSetDetVVol(g_SndSeVoice0KeyedVoice, g_SndSeVolumeL, g_SndSeVolumeR);
        }
    initial_done:
        D_8018232A           = -1;
        g_SndSeLastVoice     = g_SndSeVoice0SpuVoice;
        g_SndSeLastRetrigger = g_SndSeRetrigger;
        goto queue_done;
    } else {
        if (g_SndSeLastVoice != g_SndSeVoice0SpuVoice) {
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
    g_SndSeVoice3KeyedVoice =
        SsUtKeyOnV(g_SndSeVoice3SpuVoice, g_SndSeVabId, g_SndSeVoice3Program, g_SndSeVoice3Tone, g_SndSeVoice3Note, g_SndSeVoice3Fine, g_SndSeVoice3VolumeL, g_SndSeVoice3VolumeR);
    if (g_SndSeUseVolume == 0x80) {
        SsUtSetDetVVol(g_SndSeVoice3KeyedVoice, g_SndSeVolumeL, g_SndSeVolumeR);
    }
queue_special2:
    g_SndSeVoice2KeyedVoice =
        SsUtKeyOnV(g_SndSeVoice2SpuVoice, g_SndSeVabId, g_SndSeVoice2Program, g_SndSeVoice2Tone, g_SndSeVoice2Note, g_SndSeVoice2Fine, g_SndSeVoice2VolumeL, g_SndSeVoice2VolumeR);
    if (g_SndSeUseVolume == 0x80) {
        SsUtSetDetVVol(g_SndSeVoice2KeyedVoice, g_SndSeVolumeL, g_SndSeVolumeR);
    }
queue_special1:
    g_SndSeVoice1KeyedVoice =
        SsUtKeyOnV(g_SndSeVoice1SpuVoice, g_SndSeVabId, g_SndSeVoice1Program, g_SndSeVoice1Tone, g_SndSeVoice1Note, g_SndSeVoice1Fine, g_SndSeVoice1VolumeL, g_SndSeVoice1VolumeR);
    if (g_SndSeUseVolume == 0x80) {
        SsUtSetDetVVol(g_SndSeVoice1KeyedVoice, g_SndSeVolumeL, g_SndSeVolumeR);
    }
queue_special0:
    g_SndSeVoice0KeyedVoice =
        SsUtKeyOnV(g_SndSeVoice0SpuVoice, g_SndSeVabId, g_SndSeVoice0Program, g_SndSeVoice0Tone, g_SndSeVoice0Note, g_SndSeVoice0Fine, g_SndSeVoice0VolumeL, g_SndSeVoice0VolumeR);
    if (g_SndSeUseVolume == 0x80) {
        SsUtSetDetVVol(g_SndSeVoice0KeyedVoice, g_SndSeVolumeR, g_SndSeVolumeR);
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
    g_SndSeVoice3KeyedVoice =
        SsUtKeyOnV(g_SndSeVoice3SpuVoice, g_SndSeVabId, g_SndSeVoice3Program, g_SndSeVoice3Tone, g_SndSeVoice3Note, g_SndSeVoice3Fine, g_SndSeVoice3VolumeL, g_SndSeVoice3VolumeR);
    if (g_SndSeUseVolume == 0x80) {
        SsUtSetDetVVol(g_SndSeVoice3KeyedVoice, g_SndSeVolumeL, g_SndSeVolumeR);
    }
queue_standard2:
    g_SndSeVoice2KeyedVoice =
        SsUtKeyOnV(g_SndSeVoice2SpuVoice, g_SndSeVabId, g_SndSeVoice2Program, g_SndSeVoice2Tone, g_SndSeVoice2Note, g_SndSeVoice2Fine, g_SndSeVoice2VolumeL, g_SndSeVoice2VolumeR);
    if (g_SndSeUseVolume == 0x80) {
        SsUtSetDetVVol(g_SndSeVoice2KeyedVoice, g_SndSeVolumeL, g_SndSeVolumeR);
    }
queue_standard1:
    g_SndSeVoice1KeyedVoice =
        SsUtKeyOnV(g_SndSeVoice1SpuVoice, g_SndSeVabId, g_SndSeVoice1Program, g_SndSeVoice1Tone, g_SndSeVoice1Note, g_SndSeVoice1Fine, g_SndSeVoice1VolumeL, g_SndSeVoice1VolumeR);
    if (g_SndSeUseVolume == 0x80) {
        SsUtSetDetVVol(g_SndSeVoice1KeyedVoice, g_SndSeVolumeL, g_SndSeVolumeR);
    }
queue_standard0:
    g_SndSeVoice0KeyedVoice =
        SsUtKeyOnV(g_SndSeVoice0SpuVoice, g_SndSeVabId, g_SndSeVoice0Program, g_SndSeVoice0Tone, g_SndSeVoice0Note, g_SndSeVoice0Fine, g_SndSeVoice0VolumeL, g_SndSeVoice0VolumeR);
    if (g_SndSeUseVolume == 0x80) {
        SsUtSetDetVVol(g_SndSeVoice0KeyedVoice, g_SndSeVolumeL, g_SndSeVolumeR);
    }
queue_update:
    g_SndSeLastVoice     = g_SndSeVoice0SpuVoice;
    g_SndSeLastRetrigger = g_SndSeRetrigger;
queue_done:;
}
