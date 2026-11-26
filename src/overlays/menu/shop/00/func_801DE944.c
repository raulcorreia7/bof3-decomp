#include "shop_00.h"
#include "area/map.h"

/* Refreshes the status-panel rows and the field-camera scroll: fills the row
 * buffer from the party records, then on scene 0x85 copies the per-row scroll
 * table and on scene 0x5C seeds a fixed scroll and its angle, priming
 * g_AreaScrollTargetX/0C unless the camera flag g_ScenarioState.flags_01 bit 6 is set.
 */
MATCH void func_801DE944(void) {
    u8*  party;
    u8*  actor;
    u8   mode;
    s32  i;
    u8*  step;
    s32  row;
    s32* scroll;
    s32  scroll_x;
    s32  scroll_y;
    s32  count;
    /* FAKE: the member reads need no spill slots; retail reserves 8 bytes. */
    FAKE_STACK_PADS(u8, 8);

    func_801DF90C();
    party = g_SaveData.party.order[0];
    actor = &g_Game.members[0].chr.character_id;
    mode  = actor[0];
    EMI_PartyLoadArchives(party[0], g_PartyFieldOrder[1], g_PartyFieldOrder[2], 0);
    if (g_SaveData.return_point.pending == 0 || (SYS_TestFlag(g_SaveData.scene_event_flags, 119) != 0 && g_GameAreaId != AREA_ID_ADULT_CAMP) || g_GameAreaId == AREA_ID_BOAT_AFTER_BLACK_SHIP) {
        g_PartySize = Party_CountOrder(PARTY_ORDER_FIELD);
        Party_BattlersBuild(PARTY_ORDER_FIELD);
        i = 0;
        if (i < g_Game.party_size) {
            row = 0;
            do {
                TASK_SET(((u8*)g_Game.members + row));
                Party_MemberLoadSprite(((PartyMember*)((u8*)&g_Game.members[0] + row))->chr.character_id, (u8)i);
                Script_Select(TASK(Actor)->direction);
                if (g_SaveData.return_point.pending != 0) {
                    ACTOR_SET_MODE(0);
                    TASK(Actor)->header.step = 0;
                    TASK(Actor)->unk_03      = 0;
                    TASK(Actor)->unk_04      = 0;
                }
                row += BATTLE_PARTY_STRIDE;
                i++;
            } while (i < g_PartySize);
        }
        if (mode != CHAR_ID_GARR && g_Game.members[0].chr.character_id == CHAR_ID_GARR) {
            g_Game.members[0].pos.x.fixed += g_ShopFacingSteps[g_Game.members[0].facing].vx << 15;
            g_Game.members[0].pos.y.fixed += g_ShopFacingSteps[g_Game.members[0].facing].vy << 15;
        }
        if (!(g_ScenarioState.flags_01 & SCENARIO_STATE_SCRIPT_ACTIVE)) {
            g_AreaScrollTargetX = g_Game.members[0].pos.x.fixed;
            g_AreaScrollTargetY = g_Game.members[0].pos.y.fixed;
            Area_InitMapRenderer();
        }
    } else {
        TASK_SET((actor - 0x79));
        g_Game.party_size        = 1;
        g_Game.members[0].slot   = 0;
        *(Character*)(actor - 5) = g_SaveData.characters[0];
        TASK(Actor)->unk_48      = 0;
        Party_MemberLoadSprite(g_Game.members[0].chr.character_id, 0);
        Script_Select(TASK(Actor)->direction);
        ACTOR_SET_MODE(0);
        TASK(Actor)->header.step = 0;
        TASK(Actor)->unk_03      = 0;
        TASK(Actor)->unk_04      = 0;
    }
    if (g_GameAreaId == AREA_ID_BOAT_AFTER_BLACK_SHIP) {
        i = 0;
        if (i < g_PartySize) {
            count = g_PartySize;
            for (; i < count; i++) {
                g_Game.members[i].pos.x.fixed = g_ShopBoatPartyPositions[i].vx;
                g_Game.members[i].pos.y.fixed = g_ShopBoatPartyPositions[i].vy;
                g_Game.members[i].pos.z.fixed = g_ShopBoatPartyPositions[i].vz;
            }
        }
        if (!(g_ScenarioState.flags_01 & SCENARIO_STATE_SCRIPT_ACTIVE)) {
            g_AreaScrollTargetX = g_Game.members[0].pos.x.fixed;
            g_AreaScrollTargetY = g_Game.members[0].pos.y.fixed;
            Area_InitMapRenderer();
        }
    }
    if (g_GameAreaId == AREA_ID_BEYD_TRAINING) {
        if ((i = 0) < g_Game.party_size) {
            scroll_x = 25 << 16;
            scroll_y = 60 << 16;
            scroll   = &D_80145EC4;
            do {
                g_Game.members[i].pos.x.fixed = scroll_x;
                g_Game.members[i].pos.y.fixed = scroll_y;
                g_Game.members[i].pos.z.fixed = Area_HeightSample(scroll[0], scroll[1]) << 16;
                i++;
            } while (i < g_Game.party_size);
        }
        g_AreaScrollTargetX = g_Game.members[0].pos.x.fixed;
        g_AreaScrollTargetY = g_Game.members[0].pos.y.fixed;
        Area_InitMapRenderer();
    }
    UI_ModeSet(UI_MODE_FAST_FADE_IN);
    step = &g_MenuStep.state;
    (*step)++;
}
