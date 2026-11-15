#include "game_00.h"

MATCH void Battle_LoadBattleArchive(void) {
    u16* state;
    u16  counter;
    u32  arg;
    u32  i;

    Party_BuildBattlers(PARTY_ORDER_BATTLE);
    Battle_PlaceMembers();
    func_801A06D8();
    func_801992B8();
    if ((g_Battle.outcome.options & BATTLE_OPT_KEEP_BGM) == 0) {
        if (g_SndBGMId != GAME_NONE) {
            SsSepPause(g_SelectionEffectVoices[g_SelectionCues[g_SndBGMId * 4]], g_SelectionSequences[g_SndBGMId * 4]);
            for (i = 0; i < 1376; i++) {
                D_8018E268[i] = D_80148A50[i];
            }
            SND_StopSequence(g_SelectionCues[g_SndBGMId * 4], g_SelectionSequences[g_SndBGMId * 4]);
        }
        g_EmiStreamFlags |= 0x40;
    }
    D_80146856 = 0;
    D_80146855 = 0;
    if (BATTLE_IS_SCRIPTED()) {
        arg = g_BossArchiveSlots[D_801CD78F[g_Battle.encounter * 4]];
    } else if (g_SceneState.scenario_id < 8) {
        arg = 6;
    } else {
        arg = 7;
    }
    EMI_LoadArchive(arg);
    Menu_ResetPanelTasks();
    state                        = &g_GameEntrySubstate;
    counter                      = *state;
    g_Battle.outcome.event_flags = 0;
    g_Battle.state               = 0;
    g_Battle.phase.mode          = BATTLE_MODE_ENTRANCE;
    g_Battle.phase.step          = 0;
    g_Battle.phase.sub_step      = 0;
    g_Battle.ui_step             = 0;
    g_Battle.ui_state            = 0;
    *state                       = counter + 1;
}
