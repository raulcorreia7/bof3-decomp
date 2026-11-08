#include "game_00.h"

MATCH void func_801BFF9C(u32 work_kind, u32 work_index, u32 work_mode) {
    Character* rec;
    u8         count;
    s32        i;
    s32        id;
    s32        off;
    MATCH_FAKE_PIN(u8*, work, "s1"); /* FAKE: work pointer stays in s1. */
    u8* base;
    u8* order;
    u8* dst;
    MATCH_FAKE_PIN(u8*, feed, "t1"); /* FAKE: record base reloads into t1. */
    u8* mask;
    MATCH_FAKE_PIN(u32, addr, "v0"); /* FAKE: work base staged in v0. */
    u8  kind;
    s32 koff; /* FAKE: retail scales the record index before the base add. */
    /* FAKE: retail holds the three arguments in s7/fp/s6. */
    s32 z;
    MATCH_FAKE_PIN(s32, c41, "v1"); /* FAKE: TO_COORD(65) materializes in v1. */
    s32 x;
    s32 y;

    x = work_kind;
    y = work_index;
    z = work_mode;
    g_GameFlags &= 0xEFFF;
    if (!(g_AreaWalkFlags & AREA_WALK_MAP_LOADING) &&
        (((LOBU(g_GameRequestFlags) & 9) != 0) || (LOHU(g_GameAreaId) == AREA_ID_DESERT_OF_DEATH_MAP) ||
         (LOHU(g_GameAreaId) == AREA_ID_ADULT_CAMP) ||
         (((LOBU(g_GameRequestFlags) & 0x40) != 0) && (SYS_TestFlag(g_SceneEventFlags, 0x77U) == 0)))) {
        count = Party_CountOrder(PARTY_ORDER_FIELD);
        for (i = 0; i < count; i++) {
            g_Characters[g_CharSlot[g_PartyFieldOrder[i]]].status &= ~STATUS_CONFUSED;
        }
        for (i = 0; i < count; i++) {
            if (g_Characters[g_CharSlot[g_PartyFieldOrder[i]]].status & STATUS_POISONED) {
                g_BattlePartyBattlers[0].u.turn.command.target = 0xA;
                break;
            }
        }
        TASK_SET(g_BattlePartyBattlers);
        g_PartySize                              = 1;
        g_BattlePartyBattlers[0].slot            = 0;
        g_BattlePartyBattlers[0].chr             = g_Characters[0];
        g_BattlePartyBattlers[0].character_index = 0;
        /* D_80145FBC stays an address symbol: VOL takes a plain lvalue and the member view changes the code. */
        VOL(u8, D_80145FBC) &= 0xFE;
        g_Task->unk_48 = 0;
        if (LOBU(g_GameRequestFlags) & 1) {
            if (g_Characters[CHAR_INDEX_RYU].character_id == CHAR_ID_RYU_YOUNG) {
                id = 0x52;
                goto set_mode; /* shared mode dispatch */
            }
            if (g_Characters[CHAR_INDEX_RYU].character_id == CHAR_ID_RYU_PAJAMAS) {
                id = 0xCB;
                goto set_mode; /* shared mode dispatch */
            }
            id = 0x27A;
            if (g_Characters[CHAR_INDEX_RYU].character_id == CHAR_ID_RYU_ADULT) {
            set_mode:
                Area_FindSceneRecord(id);
            }
            g_Task->active_flags = 0;
            g_GameFlags |= 0x1000;
        } else if (LOBU(g_GameRequestFlags) & 8) {
            id = 0x1FD;
            if (g_BattlePartyBattlers[0].chr.character_id == 0) {
                id = 0x47;
            }
            Area_FindSceneRecord(id);
            g_Task->unk_2A       = 0;
            g_Task->active_flags = 0;
        } else if (LOBU(g_GameRequestFlags) & 0x40) {
            func_801C1254(g_BattlePartyBattlers[0].chr.character_id, 0);
        } else if (LOHU(g_GameAreaId) == AREA_ID_DESERT_OF_DEATH_MAP) {
            g_BattlePartyBattlers[0].unk_2B = 0;
            *(s32*)&D_80145F00              = 0;
        }
    } else {
        g_PartySize = Party_CountOrder(PARTY_ORDER_FIELD);
        if (!(g_AreaWalkFlags & AREA_WALK_MAP_LOADING)) {
            Party_BuildBattlers(PARTY_ORDER_FIELD);
        } else {
            i = 0;
            if (i < g_PartySize) {
                addr  = g_BattlePartyBattlers;
                base  = (u8*)g_Characters;
                order = base + 0x5F2;        /* party order field follows the records */
                mask  = (u8*)(addr + 0x12C); /* row flag byte */
                work  = (u8*)addr;
                off   = 0;
                do {
                    TASK_SET(work);
                    *work |= 1;
                    *mask &= 0xFE;
                    g_Task->pos.x.fixed                              = 0;
                    g_Task->pos.y.fixed                              = 0;
                    g_Task->pos.z.fixed                              = 0;
                    kind                                             = g_CharSlot[*order];
                    feed                                             = D_80145F04;
                    dst                                              = feed + off;
                    koff                                             = (kind & BYTE_MASK) * PARTY_RECORD_STRIDE;
                    rec                                              = (Character*)(koff + (u32)base);
                    (&g_BattlePartyBattlers[0].character_index)[off] = kind;
                    *(Character*)dst                                 = *rec;
                    if (!(g_Task->active_flags & 1)) {
                        func_801C1254(*order, i & BYTE_MASK);
                        MATCH_FAKE_BARRIER(); /* FAKE: keeps order++ past the call. */
                        order++;
                    } else {
                        func_801C1254(*order, i & BYTE_MASK);
                        order++;
                        GFX_FreePaletteFadeTarget(g_Task);
                        g_Task->unk_27 = (g_Task->unk_05 + 0x78);
                        GFX_StagePalette((g_Task->unk_05 << 6) + GAME_PALETTE_STAGE, 0);
                    }
                    mask += BATTLE_PARTY_STRIDE;
                    work += BATTLE_PARTY_STRIDE;
                    off += BATTLE_PARTY_STRIDE;
                    i++;
                } while (i < g_PartySize);
            }
        }
    }
    if (!(g_GameRequestFlags & 8)) {
        if (z & 0x80) {
            g_AreaScrollTargetX = x;
            g_AreaScrollTargetY = y;
            return;
        }
        if (!(g_GameFlags & 0x800)) {
            func_801C0758(x, y, z & BYTE_MASK);
        } else {
            func_801C090C(x, y, z & BYTE_MASK);
        }
        g_AreaScrollTargetX = D_80145EC4;
        g_AreaScrollTargetY = D_80145EC8;
        return;
    }
    c41                 = TO_COORD(65);
    D_80145EC4          = TO_COORD(15);
    g_AreaScrollTargetX = TO_COORD(15);
    D_80145EC8          = c41;
    g_AreaScrollTargetY = TO_COORD(60);
}
