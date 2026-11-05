#include "commu00_00.h"

/* 4-byte weighted-roll entry: a value followed by three weight bytes. */

MATCH void Fairy_RollExploreReward(void) {
    FairyRewardRoll buf[3];
    u8*             edp;
    u8*             edp_tail;
    u8*             src;
    u32             roll;
    u8              state;
    s32             i;
    s32             offset;
    u8              high;
    u8              low;

    memcpy(buf, D_801EEC98, 12);
    edp   = &D_801448ED;
    state = g_FairyJobs[*edp].record_state;
    if (state == 3) {
        Message_StartAreaMessage(0x52);
        g_FairyJobs[*edp].progress_anchor = g_BattleCount;
        /* FAKE: retail keeps this arm's anchor stamp in place; the barrier
         * stops the cross-jump that merges it into the state-2 tail. */
        MATCH_BARRIER();
        g_FairyJobs[*edp].record_state            = 0;
        ((Actor*)FAIRY_VILLAGE_ACTIVE_UI)->unk_7C = 0x51;
    } else if (state == 2) {
        roll = RANDOM_MASK(0x7F);
        if (roll >= 101) {
            roll = 0x64;
        }
        offset = g_FairyJobs[*edp].type - 1;
        if ((u8)roll < buf[D_801457A9[offset * 8]].value) {
            roll = 0;
        } else {
            roll -= buf[D_801457A9[offset * 8]].value;
        }
        offset = g_FairyJobs[D_801448ED].type - 1;
        for (i = 1; i < 3; i++) {
            if (buf[D_801457A9[offset * 8]].weights[i - 1] >= (u8)roll) {
                break;
            }
            roll -= buf[D_801457A9[offset * 8]].weights[i - 1];
        }
        i      = (i - 1) * 16;
        offset = (i + (RANDOM_MASK(0xF))) * 2;
        high   = D_801F2619[offset];
        low    = g_FairyExploreRewards[offset];
        if (!(Party_AddItem(high, low, 1, 0) & BYTE_MASK)) {
            Message_StartAreaMessage(0x50);
            /* The item pair was rejected: skip the refresh tail. */
            goto done;
        }
        src = Item_GetRecord(high, low);
        for (i = 0; i < 12; i++) {
            g_TextVariables[0][i] = src[i];
        }
        D_801490E4[0] = 0;
        Message_StartAreaMessage(0x4F);
        edp_tail                                                    = &D_801448ED;
        g_FairyJobs[*edp_tail].progress_anchor                      = g_BattleCount;
        /* FAKE: retail reloads the index through the materialized pointer. */
        g_FairyJobs[*MATCH_VOLATILE_PTR(u8, edp_tail)].record_state = 0;
        ((Actor*)FAIRY_VILLAGE_ACTIVE_UI)->unk_7C                   = 0x51;
    } else {
        /* No live state: leave the record untouched. */
        goto done;
    }
done:
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    FAIRY_EVENT_STEP = FAIRY_EVENT_STEP + 1;
}
