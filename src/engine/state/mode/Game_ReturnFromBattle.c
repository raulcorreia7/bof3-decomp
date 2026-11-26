#include "engine/game/00/game_00.h"

/* func_80197F48 */
MATCH void Game_ReturnFromBattle(void) {
    u8  changed;
    u8* flags;
    u8* sel;
    u32 i;

    changed = 0;
    if (g_AreaCameraMoving == 0 && EMI_IsReady() != 0) {
        g_AreaDrawMode = GFX_LAYER_FIELD_SCENE;
        Party_BattlersBuild(PARTY_ORDER_FIELD);
        Game_BattlePlaceFieldMembers();
        flags            = &g_Battle.outcome.options;
        g_EncounterSteps = 0;
        if ((*flags & 0x2) == 0) {
            Area_ScrollAdvance(Area_HeightSample(g_AreaCamera.scroll_x.fixed, g_AreaCamera.scroll_y.fixed));
        }
        if ((*flags & 0x40) == 0 && (g_Battle.outcome.result & BATTLE_RESULT_NO_BGM) == 0 && g_SndBGMId != 0xFF) {
            for (i = 0; i < 1376; i++) {
                D_80148A50[i] = D_8018E268[i];
            }
            sel = &g_SndBGMId;
            SsSepReplay(g_SelectionEffectVoices[g_BGMTracks[*sel].sep_slot], g_BGMTracks[*sel].sequence);
            SND_SeqSetVolume((u16)(s8)(u8)g_SelectionEffectVoices[g_BGMTracks[*sel].sep_slot], g_BGMTracks[*sel].sequence, 0, 0);
            SND_SeqFadeIn((u16)(s8)(u8)g_SelectionEffectVoices[g_BGMTracks[*sel].sep_slot], g_BGMTracks[*sel].sequence, 0x64, 8);
        }
        g_Battle.outcome.options = 0;
        g_Battle.encounter       = 0;
        Area_EncounterRollThreshold(0);
        func_801C2018();
        changed = 1;
    }
    Game_BattleRunPartyAnims();
    Actor_RunInteractions();
    Area_RunLoadingFrame();
    if (changed != 0) {
        g_GameEntryState    = GAME_MODE_FIELD;
        g_GameEntrySubstate = 0;
        g_GameStateIndex    = GAME_REQUEST_IDLE;
    }
}
