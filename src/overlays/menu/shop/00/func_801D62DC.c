#include "shop_00.h"
#include "area/map.h"

/* UI-owner row field behind the scratchpad row pointer. */
#define SPAD_ROW(type, offset) FIELD(type, g_Self, offset)

MATCH void func_801D62DC(void) {
    s32 offset;
    s32 base;
    u8  selection;
    u8  i;
    u8  track;
    u8* selection_ptr;

    if (WINDOW_EFFECT_BUSY()) {
        return;
    }
    func_801D6E94();
    if (g_GameAreaId == AREA_ID_ADULT_CAMP || g_GameAreaId == AREA_ID_DESERT_ENTRANCE_CAMP ||
        (g_GameAreaId == AREA_ID_DESERT_CAMP_FIRST && g_ScenarioState.scenario_id == 0xE && SYS_TestFlag(g_SceneFlags[0], 5) != 0)) {
        for (track = 0; track < 4; track++) {
            if (D_801E6100[track] != 0) {
                SsSepReplay(0, track);
            }
        }
    } else {
        selection_ptr  = &g_SndBGMId;
        *selection_ptr = 0xFF;
        selection      = 0;
        if (g_GameAreaId == AREA_ID_BOAT_AFTER_BLACK_SHIP) {
            SYS_ClearFlag(selection_ptr - 0x101, 119);
            selection = 1;
        }
        if (g_GameAreaId == AREA_ID_DESERT_CAMP_FIRST) {
            selection = 2;
        }
        g_AreaWalkFlags &= ~AREA_WALK_BUSY_ALL;
        g_PartySize = Party_CountOrder(PARTY_ORDER_FIELD);
        Party_BattlersBuild(PARTY_ORDER_FIELD);
        i = 0;
        if (g_Game.party_size != 0) {
            base = selection * 0x30;
            do {
                SELF_SET(((u8*)g_Game.members + i * BATTLE_PARTY_STRIDE));
                Party_MemberLoadSprite(g_Game.members[i].chr.character_id, i);
                Script_Select(SELF(Actor)->direction);
                offset                      = i * 0x10 + base;
                SELF(ShopSelection)->unk_34 = FIELD(s32, &D_801E537C, offset);
                SELF(ShopSelection)->unk_38 = FIELD(s32, &D_801E5380, offset);
                SELF(ShopSelection)->unk_3C = FIELD(s32, &D_801E5384, offset);
                SPAD_ROW(u8, 0x1u)          = 0;
                SPAD_ROW(u8, 0x2u)          = 0;
                SPAD_ROW(u8, 0x3u)          = 0;
                SPAD_ROW(u8, 0x4u)          = 0;
                i++;
            } while (i < g_PartySize);
        }
        g_AreaScrollTargetX = g_Game.members[0].pos.x.fixed;
        g_AreaScrollTargetY = g_Game.members[0].pos.y.fixed;
        Area_InitMapRenderer();
        Area_RunSetupStream(*g_AreaLoads[g_GameAreaId]);
    }
    (*(s8*)&g_MenuStep.sub_step)++;
}
