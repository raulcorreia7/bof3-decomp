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
                scaled = D_8018B39C * (g_SndSeUseVolume - D_8018B3A4);
                if (scaled < 0) {
                    scaled += 0x7F;
                }
                next       = D_8018B3A0 * D_8018B3A4;
                D_8018B39C = scaled >> 7;
                if (next < 0) {
                    next += 0x7F;
                }
                D_8018B3A0 = next >> 7;
                /* fall through */
            case 2:
                scaled = D_8018B374 * (0x80 - D_8018B37C);
                if (scaled < 0) {
                    scaled += 0x7F;
                }
                next       = D_8018B378 * D_8018B37C;
                D_8018B374 = scaled >> 7;
                if (next < 0) {
                    next += 0x7F;
                }
                D_8018B378 = next >> 7;
                /* fall through */
            case 1:
                scaled = D_8018B34C * (0x80 - D_8018B354);
                if (scaled < 0) {
                    scaled += 0x7F;
                }
                next       = D_8018B350 * D_8018B354;
                D_8018B34C = scaled >> 7;
                if (next < 0) {
                    next += 0x7F;
                }
                D_8018B350 = next >> 7;
                /* fall through */
            case 0:
                scaled = D_8018B324 * (0x80 - D_8018B32C);
                if (scaled < 0) {
                    scaled += 0x7F;
                }
                next       = D_8018B328 * D_8018B32C;
                D_8018B324 = scaled >> 7;
                if (next < 0) {
                    next += 0x7F;
                }
                D_8018B328 = next >> 7;
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
        D_8018B394 = SsUtKeyOnV(D_8018B390, D_8018B30C, D_8018B380, D_8018B388, D_8018B38C, D_8018B398, D_8018B39C, D_8018B3A0);
        if (g_SndSeUseVolume == 0x80) {
            SsUtSetDetVVol(D_8018B394, g_SndSeVolumeL, g_SndSeVolumeR);
        }
    initial_mode2:
        D_8018B36C = SsUtKeyOnV(D_8018B368, D_8018B30C, D_8018B358, D_8018B360, D_8018B364, D_8018B370, D_8018B374, D_8018B378);
        if (g_SndSeUseVolume == 0x80) {
            SsUtSetDetVVol(D_8018B36C, g_SndSeVolumeL, g_SndSeVolumeR);
        }
    initial_mode1:
        D_8018B344 = SsUtKeyOnV(D_8018B340, D_8018B30C, D_8018B330, D_8018B338, D_8018B33C, D_8018B348, D_8018B34C, D_8018B350);
        if (g_SndSeUseVolume == 0x80) {
            SsUtSetDetVVol(D_8018B344, g_SndSeVolumeL, g_SndSeVolumeR);
        }
    initial_mode0:
        D_8018B31C = SsUtKeyOnV(D_8018B318, D_8018B30C, D_8018B308, D_8018B310, D_8018B314, D_8018B320, D_8018B324, D_8018B328);
        if (g_SndSeUseVolume == 0x80) {
            SsUtSetDetVVol(D_8018B31C, g_SndSeVolumeL, g_SndSeVolumeR);
        }
    initial_done:
        D_8018232A           = -1;
        g_SndSeLastVoice     = D_8018B318;
        g_SndSeLastRetrigger = g_SndSeRetrigger;
        goto queue_done;
    } else {
        if (g_SndSeLastVoice != D_8018B318) {
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
    D_8018B394 = SsUtKeyOnV(D_8018B390, D_8018B30C, D_8018B380, D_8018B388, D_8018B38C, D_8018B398, D_8018B39C, D_8018B3A0);
    if (g_SndSeUseVolume == 0x80) {
        SsUtSetDetVVol(D_8018B394, g_SndSeVolumeL, g_SndSeVolumeR);
    }
queue_special2:
    D_8018B36C = SsUtKeyOnV(D_8018B368, D_8018B30C, D_8018B358, D_8018B360, D_8018B364, D_8018B370, D_8018B374, D_8018B378);
    if (g_SndSeUseVolume == 0x80) {
        SsUtSetDetVVol(D_8018B36C, g_SndSeVolumeL, g_SndSeVolumeR);
    }
queue_special1:
    D_8018B344 = SsUtKeyOnV(D_8018B340, D_8018B30C, D_8018B330, D_8018B338, D_8018B33C, D_8018B348, D_8018B34C, D_8018B350);
    if (g_SndSeUseVolume == 0x80) {
        SsUtSetDetVVol(D_8018B344, g_SndSeVolumeL, g_SndSeVolumeR);
    }
queue_special0:
    D_8018B31C = SsUtKeyOnV(D_8018B318, D_8018B30C, D_8018B308, D_8018B310, D_8018B314, D_8018B320, D_8018B324, D_8018B328);
    if (g_SndSeUseVolume == 0x80) {
        SsUtSetDetVVol(D_8018B31C, g_SndSeVolumeR, g_SndSeVolumeR);
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
    D_8018B394 = SsUtKeyOnV(D_8018B390, D_8018B30C, D_8018B380, D_8018B388, D_8018B38C, D_8018B398, D_8018B39C, D_8018B3A0);
    if (g_SndSeUseVolume == 0x80) {
        SsUtSetDetVVol(D_8018B394, g_SndSeVolumeL, g_SndSeVolumeR);
    }
queue_standard2:
    D_8018B36C = SsUtKeyOnV(D_8018B368, D_8018B30C, D_8018B358, D_8018B360, D_8018B364, D_8018B370, D_8018B374, D_8018B378);
    if (g_SndSeUseVolume == 0x80) {
        SsUtSetDetVVol(D_8018B36C, g_SndSeVolumeL, g_SndSeVolumeR);
    }
queue_standard1:
    D_8018B344 = SsUtKeyOnV(D_8018B340, D_8018B30C, D_8018B330, D_8018B338, D_8018B33C, D_8018B348, D_8018B34C, D_8018B350);
    if (g_SndSeUseVolume == 0x80) {
        SsUtSetDetVVol(D_8018B344, g_SndSeVolumeL, g_SndSeVolumeR);
    }
queue_standard0:
    D_8018B31C = SsUtKeyOnV(D_8018B318, D_8018B30C, D_8018B308, D_8018B310, D_8018B314, D_8018B320, D_8018B324, D_8018B328);
    if (g_SndSeUseVolume == 0x80) {
        SsUtSetDetVVol(D_8018B31C, g_SndSeVolumeL, g_SndSeVolumeR);
    }
queue_update:
    g_SndSeLastVoice     = D_8018B318;
    g_SndSeLastRetrigger = g_SndSeRetrigger;
queue_done:;
}
