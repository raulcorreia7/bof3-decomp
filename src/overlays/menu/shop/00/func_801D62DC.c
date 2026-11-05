#include "shop_00.h"

/* UI-owner row field behind the scratchpad row pointer. */
#define SPAD_ROW(type, offset) FIELD(type, g_Task, offset)

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
    if (g_GameAreaId == 187 || g_GameAreaId == 193 ||
        (g_GameAreaId == 191 && g_SceneState.scenario_id == 0xE && SYS_TestFlag(g_SceneFlags[0], 5) != 0)) {
        for (track = 0; track < 4; track++) {
            if (D_801E6100[track] != 0) {
                SsSepReplay(0, (s16)track);
            }
        }
    } else {
        selection_ptr  = &g_SndBgmId;
        *selection_ptr = 0xFF;
        selection      = 0;
        if (g_GameAreaId == 133) {
            SYS_ClearFlag(selection_ptr - 0x101, 0x77);
            selection = 1;
        }
        if (g_GameAreaId == 191) {
            selection = 2;
        }
        g_AreaWalkFlags &= ~AREA_WALK_BUSY_ALL;
        /* FAKE: keeps the Party_CountOrder argument out of the load delay slot (pure C 96.05). */
        MATCH_FAKE_BARRIER();
        g_PartySize = Party_CountOrder(0);
        Party_BuildBattlers(0);
        i = 0;
        if (g_PartySize != 0) {
            base = selection * 0x30;
            do {
                TASK_SET(((u8*)g_BattlePartyBattlers + i * BATTLE_PARTY_STRIDE));
                func_801C1254(D_80145F09[i * BATTLE_PARTY_STRIDE], i);
                Actor_SelectScript(TASK_BYTES[8]);
                offset                           = i * 0x10 + base;
                ((ShopSelection*)g_Task)->unk_34 = FIELD(s32, &D_801E537C, offset);
                ((ShopSelection*)g_Task)->unk_38 = FIELD(s32, &D_801E5380, offset);
                ((ShopSelection*)g_Task)->unk_3C = FIELD(s32, &D_801E5384, offset);
                SPAD_ROW(u8, 0x1u)               = 0;
                SPAD_ROW(u8, 0x2u)               = 0;
                SPAD_ROW(u8, 0x3u)               = 0;
                SPAD_ROW(u8, 0x4u)               = 0;
                i++;
            } while (i < g_PartySize);
        }
        g_AreaScrollTargetX = D_80145EC4;
        g_AreaScrollTargetY = D_80145EC8;
        func_80153DE8();
        Area_RunSetupStream(*g_AreaLoads[g_GameAreaId]);
    }
    (*(s8*)&D_80148651)++;
}
