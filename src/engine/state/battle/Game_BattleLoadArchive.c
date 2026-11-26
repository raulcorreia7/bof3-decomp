#include "engine/game/00/game_00.h"

MATCH void Game_BattleLoadArchive(void) {
    u16* state;
    u16  counter;
    u32  arg;
    u32  i;

    Party_BattlersBuild(PARTY_ORDER_BATTLE);
    Game_BattlePlaceMembers();
    Actor_RunInteractions();
    Area_RunLoadingFrame();
    if ((g_Battle.outcome.options & BATTLE_OPT_KEEP_BGM) == 0) {
        if (g_SndBGMId != GAME_NONE) {
            SsSepPause(g_SelectionEffectVoices[g_BGMTracks[g_SndBGMId].sep_slot], g_BGMTracks[g_SndBGMId].sequence);
            for (i = 0; i < 1376; i++) {
                D_8018E268[i] = D_80148A50[i];
            }
            SND_SeqStop(g_BGMTracks[g_SndBGMId].sep_slot, g_BGMTracks[g_SndBGMId].sequence);
        }
        g_EmiStreamFlags |= 0x40;
    }
    D_80146856 = 0;
    D_80146855 = 0;
    if (BATTLE_IS_SCRIPTED()) {
        arg = g_BossArchiveSlots[D_801CD78F[g_Battle.encounter * 4]];
    } else if (g_ScenarioState.scenario_id < 8) {
        arg = 6;
    } else {
        arg = 7;
    }
    EMI_ArchiveLoad(arg);
    UI_PanelResetTasks();
    state                        = &g_GameEntrySubstate;
    counter                      = *state;
    g_Battle.outcome.event_flags = 0;
    g_Battle.flags               = 0;
    g_Battle.phase.mode          = BATTLE_MODE_ENTRANCE;
    g_Battle.phase.step          = 0;
    g_Battle.phase.sub_step      = 0;
    g_Battle.ui_step             = 0;
    g_Battle.ui_mode             = 0;
    *state                       = counter + 1;
}
