#include "shop_00.h"
#include "area/map.h"

/* Refreshes the status-panel rows and the field-camera scroll: fills the row
 * buffer from the party records, then on scene 0x85 copies the per-row scroll
 * table and on scene 0x5C seeds a fixed scroll and its angle, priming
 * g_AreaScrollTargetX/0C unless the camera flag g_SceneState.flags_01 bit 6 is set.
 */
MATCH void func_801DE944(void) {
    u8*  party;
    u8*  actor;
    u8   mode;
    s32  i;
    u8*  step;
    s32  src;
    s32  dst;
    s32  row;
    s32* scroll;
    s32  scroll_x;
    s32  scroll_y;
    s32  count;

    func_801DF90C();
    party = g_PartyFieldOrder;
    actor = &g_Game.members[0].chr.character_id;
    mode  = actor[0];
    EMI_LoadPartyArchives(party[0], g_PartyFieldOrder[1], g_PartyFieldOrder[2], 0);
    if (D_8014504A == 0 || (SYS_TestFlag(party - 0x32, 0x77) != 0 && g_GameAreaId != AREA_ID_ADULT_CAMP) ||
        g_GameAreaId == AREA_ID_BOAT_AFTER_BLACK_SHIP) {
        g_PartySize = Party_CountOrder(PARTY_ORDER_FIELD);
        Party_BuildBattlers(PARTY_ORDER_FIELD);
        i = 0;
        if (i < g_Game.party_size) {
            row = 0;
            do {
                TASK_SET(((u8*)g_Game.members + row));
                func_801C1254(FIELD(u8, &g_Game.members[0].chr.character_id, row), i);
                Actor_SelectScript(TASK_BYTES[8]);
                if (D_8014504A != 0) {
                    ACTOR_SET_MODE(0);
                    TASK_BYTES[2] = 0;
                    TASK_BYTES[3] = 0;
                    TASK_BYTES[4] = 0;
                }
                row += BATTLE_PARTY_STRIDE;
                i++;
            } while (i < g_PartySize);
        }
        if (mode != 2 && g_Game.members[0].chr.character_id == 2) {
            D_80145EC4 += FIELD(s16, g_ShopFacingSteps, g_Game.members[0].facing * 4) << 15;
            D_80145EC8 += FIELD(s16, g_ShopFacingSteps, g_Game.members[0].facing * 4 + 2) << 15;
        }
        if (!(g_SceneState.flags_01 & SCENE_STATE_SCRIPT_ACTIVE)) {
            g_AreaScrollTargetX = D_80145EC4;
            g_AreaScrollTargetY = D_80145EC8;
            func_80153DE8();
        }
    } else {
        TASK_SET((actor - 0x79));
        g_Game.party_size        = 1;
        g_Game.members[0].slot   = 0;
        *(Character*)(actor - 5) = *(Character*)(party - 0x5F2);
        TASK_BYTES[0x48]         = 0;
        func_801C1254(g_Game.members[0].chr.character_id, 0);
        Actor_SelectScript(TASK_BYTES[8]);
        ACTOR_SET_MODE(0);
        TASK_BYTES[2] = 0;
        TASK_BYTES[3] = 0;
        TASK_BYTES[4] = 0;
    }
    if (g_GameAreaId == AREA_ID_BOAT_AFTER_BLACK_SHIP) {
        i = 0;
        if (i < g_PartySize) {
            count = g_PartySize;
            src   = 0;
            dst   = 0;
            for (; i < count; i++) {
                FIELD(s32, &D_80145EC4, dst) = FIELD(s32, &g_ShopBoatPartyPositions[0].x, src);
                FIELD(s32, &D_80145EC8, dst) = FIELD(s32, &g_ShopBoatPartyPositions[0].y, src);
                FIELD(s32, &D_80145ECC, dst) = FIELD(s32, &g_ShopBoatPartyPositions[0].z, src);
                src += 0x10;
                dst += BATTLE_PARTY_STRIDE;
            }
        }
        if (!(g_SceneState.flags_01 & SCENE_STATE_SCRIPT_ACTIVE)) {
            g_AreaScrollTargetX = D_80145EC4;
            g_AreaScrollTargetY = D_80145EC8;
            func_80153DE8();
        }
    }
    if (g_GameAreaId == AREA_ID_BEYD_TRAINING) {
        if ((i = 0) < g_Game.party_size) {
            scroll_x = 25 << 16;
            scroll_y = 60 << 16;
            scroll   = &D_80145EC4;
            row      = 0;
            do {
                dst                          = row;
                FIELD(s32, &D_80145EC4, dst) = scroll_x;
                FIELD(s32, &D_80145EC8, dst) = scroll_y;
                FIELD(s32, &D_80145ECC, dst) = Area_SampleHeight(scroll[0], scroll[1]) << 16;
                i++;
                row += BATTLE_PARTY_STRIDE;
            } while (i < g_Game.party_size);
        }
        g_AreaScrollTargetX = D_80145EC4;
        g_AreaScrollTargetY = D_80145EC8;
        func_80153DE8();
    }
    UI_SetMode(UI_MODE_FAST_FADE_IN);
    step = &D_80148652;
    (*step)++;
}
