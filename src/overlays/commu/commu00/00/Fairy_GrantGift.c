#include "commu00_00.h"

/* 4-byte gift-shop row: the battle count, the item index and the item type; the handlers take the type first. */

MATCH void Fairy_GrantGift(void) {
    FairyGift buf[20];
    u8*       src;
    s32       i;
    s32       j;
    u32       elapsed;

    memcpy(buf, g_FairyGifts, 0x50);
    elapsed = g_BattleCount - g_FairyJobs[g_SceneEventSelection].progress_anchor;
    for (i = 0; i < 20; i++) {
        if (elapsed < buf[i].num_battles) {
            break;
        }
    }
    i -= 1;
    if (i < 0) {
        Message_StartAreaMessage(FAIRY_MESSAGE_NO_GIFT_YET);
    } else {
        src = Item_GetRecord(buf[i].item_type, buf[i].item_index);
        for (j = 0; j < 12; j++) {
            g_TextVariables[0][j] = src[j];
        }
        D_801490E4[0] = 0;
        Message_StartAreaMessage(FAIRY_MESSAGE_GIFT_RECEIVED);
        if (!(Item_Add(buf[i].item_type, buf[i].item_index, 1, 0) & BYTE_MASK)) {
            FAIRY_EVENT_STEP = FAIRY_EVENT_STEP + 1;
        } else {
            g_FairyJobs[g_SceneEventSelection].progress_anchor = g_BattleCount;
        }
    }
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    FAIRY_EVENT_STEP = FAIRY_EVENT_STEP + 1;
}
