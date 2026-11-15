#include "game_00.h"

MATCH void func_80197F48(void) {
    u8  changed;
    u8* flags; /* pointer form keeps the flags byte in s0 */
    u8* sel;
    u32 i;

    changed = 0;
    if (g_AreaCameraMoving == 0 && EMI_IsReady() != 0) {
        g_AreaDrawMode = 6;
        Party_BuildBattlers(PARTY_ORDER_FIELD);
        func_801BFB34();
        flags            = &g_Battle.outcome.options;
        g_EncounterSteps = 0;
        if ((*flags & 0x2) == 0) {
            Area_AdvanceScroll(Area_SampleHeight(g_AreaScrollTargetX, g_AreaScrollTargetY));
        }
        if ((*flags & 0x40) == 0 && (g_Battle.outcome.result & BATTLE_RESULT_NO_BGM) == 0 && g_SndBGMId != 0xFF) {
            for (i = 0; i < 1376; i++) {
                D_80148A50[i] = D_8018E268[i];
            }
            sel = &g_SndBGMId;
            /* NOTE: '<< 2' in place of '* 4' keeps cc1 from reserving 32 unused frame bytes. */
            SsSepReplay(g_SelectionEffectVoices[g_SelectionCues[*sel << 2]], g_SelectionSequences[*sel << 2]);
            SND_SetSequenceVolume((u16)(s8)(u8)g_SelectionEffectVoices[g_SelectionCues[*sel << 2]], g_SelectionSequences[*sel << 2], 0, 0);
            SND_FadeInSequence((u16)(s8)(u8)g_SelectionEffectVoices[g_SelectionCues[*sel << 2]], g_SelectionSequences[*sel << 2], 0x64, 8);
        }
        g_Battle.outcome.options = 0;
        g_Battle.encounter       = 0;
        Area_RollEncounterThreshold(0);
        func_801C2018();
        changed = 1;
    }
    func_801BFAC4();
    func_801A06D8();
    func_801992B8();
    if (changed != 0) {
        g_GameEntryState    = GAME_STATE_FIELD;
        g_GameEntrySubstate = 0;
        g_GameStateIndex    = GAME_REQUEST_IDLE;
    }
}
