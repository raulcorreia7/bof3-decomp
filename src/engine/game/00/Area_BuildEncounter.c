#include "game_00.h"

MATCH s32 Area_BuildEncounter(u8 work_mode, s32 work_index) {
    s32 result;
    /* FAKE: both loops' counter; retail keeps it in s2 while the record
     * pointers take s1/s0 (allocation only, no source shape reached it). */
    FAKE_REG(u8, i, "s2");
    s32             x;
    s32             y;
    s32             reach;
    u8              kind;
    u8              slot;
    s32             off;
    EncounterEnemy* entry;
    u8*             fields;

    result = 1;
    TASK_SET(D_801CD8D0);
    if ((work_mode & BYTE_MASK) >= 4U) {
        D_801CD8C8 = (D_801CD8C8 + 1) & 0x3;
    } else {
        D_801CD8C8 = work_mode;
    }
    if ((work_index & BYTE_MASK) == 0) {
        g_EncounterOriginX = g_AreaScrollTargetX & 0xFFFF8000;
        g_EncounterOriginY = g_AreaScrollTargetY & 0xFFFF8000;
    }
    D_801CD8CC = ((Area_PickEncounter() & BYTE_MASK) * 9) + ENCOUNTER_TABLE_BASE;
    D_801CD8C0 = Area_RollEncounterEnemies(D_801CD8CC);
    if (!(D_801CD8C0 & BYTE_MASK)) {
        return 0;
    }
    g_Battle.scroll_dir = D_801CD8C8;
    if (result & BYTE_MASK) {
        if (!(Area_PlaceEncounterParty() & BYTE_MASK)) {
            result = 0;
        }
    }
    if (result & BYTE_MASK) {
        if ((Area_PlaceEncounterEnemies() << 0x18) == 0) {
            result = 0;
        }
    }
    if (result & BYTE_MASK) {
        if (!(func_801C6DCC() & BYTE_MASK)) {
            result = 0;
        }
    }
    PushMatrix();
    Area_SetEncounterCamera(D_801CD8C8);
    i = 0;
loop_16:
    if ((i & BYTE_MASK) < (Party_CountOrder(PARTY_ORDER_BATTLE) & BYTE_MASK)) {
        kind = g_PartyBattleOrder[i & BYTE_MASK];
        x    = g_EncounterParty[i & BYTE_MASK].x.fixed;
        y    = g_EncounterParty[i & BYTE_MASK].y.fixed;
        if ((kind == 2) || (kind == 6)) {
            reach = 1;
        } else {
            reach = 0;
        }
        if (!(func_801C7064(x, y, reach, 32) & BYTE_MASK)) {
            goto block_29; /* the scan found its entry */
        }
        i += 1;
        goto loop_16; /* keep scanning the remaining entries */
    }
    entry  = D_801463DC;
    i      = 0;
    fields = (u8*)D_801463DC + 8;
loop_18:
    slot = fields[-7];
    off  = slot * ENEMY_STRIDE;
    if (entry->active != 0) {
        if (!(func_801C7064(*(s32*)(fields - 4), *(s32*)(fields), ENCOUNTER_ENEMY_AT(off)->reach, ENCOUNTER_ENEMY_AT(off)->height) & BYTE_MASK)) {
            entry->active = 0;
            D_801CD8C4 -= 1;
        }
        fields += 0xC;
        goto block_2; /* the scan reached its end */
    }
    fields += 0xC;
block_2:
    i += 1;
    entry++;
    if ((u32)(i & BYTE_MASK) < 8U) {
        goto loop_18; /* the scan reached its end */
    }
    if (D_801CD8C4 != 0) {
        PopMatrix();
        return result;
    }
block_29:
    PopMatrix();
    return 0;
}
