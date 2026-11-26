#include "engine/game/00/game_00.h"

/* func_801985C8 */
MATCH void Game_FishingReturn(void) {
    u8 selection;

    g_EmiStreamFlags = 0x20;
    g_AreaWalkFlags |= AREA_WALK_ENTRY_PENDING;
    EMI_ArchiveLoadFamily(g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK, EMI_FAMILY_PL);
    while (EMI_IsReady() == 0) {
        func_801E0C40();
        SYS_ThreadWait(1);
    }
    selection = g_SndBGMId;
    if (selection != GAME_NONE && g_GamePrevSelection != selection) {
        SND_StartDecrescendo(g_BGMTracks[selection].sep_slot, g_BGMTracks[selection].sequence, 100, 16);
    }
    UI_ModeSet(0);
    while (WINDOW_EFFECT_BUSY()) {
        func_801E0C40();
        SYS_ThreadWait(1);
    }
    Game_RequestAreaChange(*(u16*)&g_GameLastAreaId, *(u32*)&g_GameLastX, *(u32*)&g_GameLastY, FACING_DOWN_RIGHT);
    selection = g_SndBGMId;
    if (selection != GAME_NONE && g_GamePrevSelection != selection) {
        SND_SeqStop(g_BGMTracks[selection].sep_slot, g_BGMTracks[selection].sequence);
    }
    g_GameEntryState    = GAME_MODE_AREA_LOAD;
    g_GameEntrySubstate = 0;
}
