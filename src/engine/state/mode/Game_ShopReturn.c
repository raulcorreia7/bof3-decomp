#include "engine/game/00/game_00.h"

MATCH void Game_ShopReturn(void) {
    g_EmiStreamFlags = 0x20;
    EMI_LoadFamilyArchive(g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK, EMI_FAMILY_PL);
    while (EMI_IsReady() == 0) {
        Area_RunLoadingFrame();
        SYS_ThreadWait(1u);
    }
    if (g_GameRequestFlags & AREA_LOAD_FLAG_FAIRY_VILLAGE) {
        EMI_LoadArchive(EMI_SLOT_COMMU00);
        while (EMI_IsReady() == 0) {
            Area_RunLoadingFrame();
            SYS_ThreadWait(1u);
        }
        func_801F03D0();
    }
    g_GameEntryState    = GAME_MODE_FIELD;
    g_GameEntrySubstate = 0u;
    g_GameStateIndex    = GAME_REQUEST_IDLE;
    Area_RunFrame();
}
