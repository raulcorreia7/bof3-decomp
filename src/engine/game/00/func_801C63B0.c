#include "game_00.h"

MATCH s32 func_801C63B0(void) {
    u8         mode;
    u8         count;
    u8         i;
    u8         j;
    u8         swapped;
    PartySlot* slot;
    u8         a;
    u8         b;
    s32        x;
    s32        y;
    /* FAKE: retail frame reserves 8 bytes no statement uses. */
    STACK_PADS(u8, 8);

    mode  = g_PartyFormation;
    count = Party_CountOrder(PARTY_ORDER_BATTLE);
    slot  = D_801CD944;
    i     = 0;
    for (; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
        s_PartySlotOrder[i] = i;
        slot->active        = 0;
        if ((g_CharSlot[g_PartyBattleOrder[i]] == 2) || (g_CharSlot[g_PartyBattleOrder[i]] == 6)) {
            slot->key = 1;
        } else {
            slot->key = 0;
        }
        slot++;
    }
    swapped = 0;
    for (i = 0; i < count; i++) {
        for (j = 0; j < count - i - 1; j++) {
            a = s_PartySlotOrder[j];
            b = s_PartySlotOrder[j + 1];
            if (D_801CD944[a].key < D_801CD944[b].key) {
                swapped                 = 1;
                s_PartySlotOrder[j]     = b;
                s_PartySlotOrder[j + 1] = a;
            }
        }
    }
    if (swapped) {
        for (i = 0; i < ARRAY_COUNT(s_EncounterOriginNudges); i++) {
            x = g_EncounterOriginX + s_EncounterOriginNudges[i].x;
            y = g_EncounterOriginY + s_EncounterOriginNudges[i].y;
            if (((func_801C7518(x, y, 1) & BYTE_MASK) != 0) &&
                ((func_801C7824(D_80143F2A, D_80143F2A, x >> 16, y >> 16) & BYTE_MASK) != 0)) {
                break;
            }
        }
        g_EncounterOriginX = x;
        g_EncounterOriginY = y;
    }
    for (i = 0; i < count; i++) {
        if ((func_801C6658(mode, s_PartySlotOrder[i], (u8)(count - 1), D_801CD8C8) & BYTE_MASK) == 0) {
            return 0;
        }
    }
    return 1;
}
