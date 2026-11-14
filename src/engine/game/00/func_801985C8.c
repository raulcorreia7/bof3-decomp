#include "game_00.h"

MATCH void func_801985C8(void) {
    u8 selection;

    g_EmiStreamFlags = 0x20;
    g_AreaWalkFlags |= AREA_WALK_ENTRY_PENDING;
    EMI_GetArchiveId(g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK, EMI_FAMILY_PL);
    while (EMI_IsReady() == 0) {
        func_801E0C40();
        SYS_ThreadWait(1);
    }
    selection = g_SndBGMId;
    if (selection != GAME_NONE && g_GamePrevSelection != selection) {
        SND_StartDecrescendo(g_SelectionCues[selection * 4], g_SelectionSequences[selection * 4], 100, 16);
    }
    UI_SetMode(0);
    while (WINDOW_EFFECT_BUSY()) {
        func_801E0C40();
        SYS_ThreadWait(1);
    }
    Game_RequestAreaChange(*(u16*)&D_80143F04, *(u32*)&D_80143F08, *(u32*)&D_80143F0C, FACING_DOWN_RIGHT);
    selection = g_SndBGMId;
    if (selection != GAME_NONE && g_GamePrevSelection != selection) {
        SND_StopSequence(g_SelectionCues[selection * 4], g_SelectionSequences[selection * 4]);
    }
    g_GameEntryState    = GAME_STATE_AREA_LOAD;
    g_GameEntrySubstate = 0;
}
