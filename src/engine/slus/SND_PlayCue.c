#include "engine/slus/slus.h"

/* dispatches a cue's bank and record, updates interpolated channel
 * values, and keys the requested SPU voices.
 */
MATCH void SND_PlayCue(u16 cue_id) {
    s32 scaled;
    s32 next;

    D_8018B408 = (cue_id & EMI_CUE_ID_BANK_MASK) >> 8;
    D_8018B404 = cue_id & EMI_CUE_ID_INDEX_MASK;
    ((void (*)(void))g_SndCueReaders[(cue_id & EMI_CUE_ID_BANK_MASK) >> 8])();

    if (D_8018B3F4 == 0x80) {
        switch (D_8018B3E4) {
            case 3:
                scaled = D_8018B39C * (D_8018B3F4 - D_8018B3A4);
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

        if ((cue_id & 0xF000) == 0) {
            D_8018B3D8 = 0x17FF;
            D_8018B3DC = 0x17FF;
        }
    }

    if (D_8018232A == 0) {
        if (D_8018B3E4 == 1) {
            goto initial_mode1; /* key modes 1..0 */
        } else if (D_8018B3E4 < 2) {
            if (D_8018B3E4 == 0) {
                goto initial_mode0; /* key mode 0 */
            }
            return;
        } else if (D_8018B3E4 == 2) {
            goto initial_mode2; /* key modes 2..0 */
        } else if (D_8018B3E4 != 3) {
            return;
        }
    initial_mode3:
        D_8018B394 =
            SsUtKeyOnV(D_8018B390, D_8018B30C, D_8018B380, D_8018B388, D_8018B38C, D_8018B398, D_8018B39C, D_8018B3A0);
        if (D_8018B3F4 == 0x80) {
            SsUtSetDetVVol(D_8018B394, D_8018B3D8, D_8018B3DC);
        }
    initial_mode2:
        D_8018B36C =
            SsUtKeyOnV(D_8018B368, D_8018B30C, D_8018B358, D_8018B360, D_8018B364, D_8018B370, D_8018B374, D_8018B378);
        if (D_8018B3F4 == 0x80) {
            SsUtSetDetVVol(D_8018B36C, D_8018B3D8, D_8018B3DC);
        }
    initial_mode1:
        D_8018B344 =
            SsUtKeyOnV(D_8018B340, D_8018B30C, D_8018B330, D_8018B338, D_8018B33C, D_8018B348, D_8018B34C, D_8018B350);
        if (D_8018B3F4 == 0x80) {
            SsUtSetDetVVol(D_8018B344, D_8018B3D8, D_8018B3DC);
        }
    initial_mode0:
        D_8018B31C =
            SsUtKeyOnV(D_8018B318, D_8018B30C, D_8018B308, D_8018B310, D_8018B314, D_8018B320, D_8018B324, D_8018B328);
        if (D_8018B3F4 == 0x80) {
            SsUtSetDetVVol(D_8018B31C, D_8018B3D8, D_8018B3DC);
        }
    initial_done:
        D_8018232A = -1;
        D_8018B3F0 = D_8018B318;
        D_8018B3EC = D_8018B3E8;
        goto queue_done; /* shared return */
    } else {
        if (D_8018B3F0 != D_8018B318) {
            if (D_8018B3E4 == 1) {
                goto queue_standard1; /* key modes 1..0 */
            }
            if (D_8018B3E4 < 2) {
                goto queue_standard_low; /* key mode 0 */
            }
            goto queue_standard23; /* key modes 2..3 */
        }
        if (D_8018B3EC > D_8018B3E8) {
            goto queue_array_guard; /* once per active cue */
        }
        switch (D_8018B3E4) {
            case 3:
                goto queue_special3; /* key mode 3 */
            case 2:
                goto queue_special2; /* key modes 2..0 */
            case 1:
                goto queue_special1; /* key modes 1..0 */
            case 0:
                goto queue_special0; /* key mode 0 */
            default:
                return;
        }
    }

queue_special3:
    D_8018B394 =
        SsUtKeyOnV(D_8018B390, D_8018B30C, D_8018B380, D_8018B388, D_8018B38C, D_8018B398, D_8018B39C, D_8018B3A0);
    if (D_8018B3F4 == 0x80) {
        SsUtSetDetVVol(D_8018B394, D_8018B3D8, D_8018B3DC);
    }
queue_special2:
    D_8018B36C =
        SsUtKeyOnV(D_8018B368, D_8018B30C, D_8018B358, D_8018B360, D_8018B364, D_8018B370, D_8018B374, D_8018B378);
    if (D_8018B3F4 == 0x80) {
        SsUtSetDetVVol(D_8018B36C, D_8018B3D8, D_8018B3DC);
    }
queue_special1:
    D_8018B344 =
        SsUtKeyOnV(D_8018B340, D_8018B30C, D_8018B330, D_8018B338, D_8018B33C, D_8018B348, D_8018B34C, D_8018B350);
    if (D_8018B3F4 == 0x80) {
        SsUtSetDetVVol(D_8018B344, D_8018B3D8, D_8018B3DC);
    }
queue_special0:
    D_8018B31C =
        SsUtKeyOnV(D_8018B318, D_8018B30C, D_8018B308, D_8018B310, D_8018B314, D_8018B320, D_8018B324, D_8018B328);
    if (D_8018B3F4 == 0x80) {
        SsUtSetDetVVol(D_8018B31C, D_8018B3DC, D_8018B3DC);
    }
    goto queue_update; /* shared active-cue update */

queue_array_guard:
    if (D_8018E140[D_8018B3F0] != 0) {
        return;
    }
    if (D_8018B3E4 == 1) {
        goto queue_standard1; /* key modes 1..0 */
    }
    if (D_8018B3E4 >= 2) {
        goto queue_standard23; /* key modes 2..3 */
    }
    if (D_8018B3E4 == 0) {
        goto queue_standard0; /* key mode 0 */
    }
    return;

/* NOTE: duplicate of the array-guard mode-0 tail above. GCC merges the two
 * blocks and keeps the array-guard copy; deleting it moves the shared tail and
 * breaks the byte match.
 */
queue_standard_low:
    if (D_8018B3E4 == 0) {
        goto queue_standard0; /* key mode 0 */
    }
    return;

queue_standard23:
    if (D_8018B3E4 == 2) {
        goto queue_standard2; /* key modes 2..0 */
    }
    if (D_8018B3E4 != 3) {
        return;
    }
queue_standard3:
    D_8018B394 =
        SsUtKeyOnV(D_8018B390, D_8018B30C, D_8018B380, D_8018B388, D_8018B38C, D_8018B398, D_8018B39C, D_8018B3A0);
    if (D_8018B3F4 == 0x80) {
        SsUtSetDetVVol(D_8018B394, D_8018B3D8, D_8018B3DC);
    }
queue_standard2:
    D_8018B36C =
        SsUtKeyOnV(D_8018B368, D_8018B30C, D_8018B358, D_8018B360, D_8018B364, D_8018B370, D_8018B374, D_8018B378);
    if (D_8018B3F4 == 0x80) {
        SsUtSetDetVVol(D_8018B36C, D_8018B3D8, D_8018B3DC);
    }
queue_standard1:
    D_8018B344 =
        SsUtKeyOnV(D_8018B340, D_8018B30C, D_8018B330, D_8018B338, D_8018B33C, D_8018B348, D_8018B34C, D_8018B350);
    if (D_8018B3F4 == 0x80) {
        SsUtSetDetVVol(D_8018B344, D_8018B3D8, D_8018B3DC);
    }
queue_standard0:
    D_8018B31C =
        SsUtKeyOnV(D_8018B318, D_8018B30C, D_8018B308, D_8018B310, D_8018B314, D_8018B320, D_8018B324, D_8018B328);
    if (D_8018B3F4 == 0x80) {
        SsUtSetDetVVol(D_8018B31C, D_8018B3D8, D_8018B3DC);
    }
queue_update:
    D_8018B3F0 = D_8018B318;
    D_8018B3EC = D_8018B3E8;
queue_done:;
}
