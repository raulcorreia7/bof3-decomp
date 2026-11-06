#include "game_00.h"

MATCH void func_80197C94(void) {
    u16* state;
    u16  counter;
    u32  arg;
    u32  i;

    Party_BuildBattlers(1);
    func_801BF448();
    func_801A06D8();
    func_801992B8();
    if ((g_BattleOptions & BATTLE_OPT_KEEP_BGM) == 0) {
        if (g_SaveData.snd_bgm_id != GAME_NONE) {
            SsSepPause(g_SelectionFxVoices[g_SelectionCues[g_SaveData.snd_bgm_id * 4]],
                       D_80181EBB[g_SaveData.snd_bgm_id * 4]);
            for (i = 0; i < 1376; i++) {
                D_8018E268[i] = D_80148A50[i];
            }
            SND_StopSequence(g_SelectionCues[g_SaveData.snd_bgm_id * 4], D_80181EBB[g_SaveData.snd_bgm_id * 4]);
        }
        g_EmiStreamFlags |= 0x40;
    }
    D_80146856 = 0;
    D_80146855 = 0;
    if (g_BattleEncounter != 0) {
        arg = D_801CD86C[D_801CD78F[g_BattleEncounter * 4]];
    } else if (g_SceneState.scenario_id < 8) {
        arg = 6;
    } else {
        arg = 7;
    }
    EMI_LoaderStreamInitSlot(arg);
    Menu_ResetPanelTasks();
    state              = &g_GameEntrySubstate;
    counter            = *state;
    g_BattleEventFlags = 0;
    g_BattleState      = 0;
    g_BattleMode       = 0;
    g_BattleStep       = 0;
    g_BattleSubStep    = 0;
    g_BattleUIStep     = 0;
    g_BattleUIState    = 0;
    *state             = counter + 1;
}
