#include "game_00.h"

MATCH void func_801983D8(void) {
    g_EmiStreamFlags = 0x20;
    EMI_StreamFamilyArchive(g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK, EMI_FAMILY_PL);
    while (EMI_LoaderIsReady() == 0) {
        func_801992B8();
        CallbackWait(1u);
    }
    if (g_GameRequestFlags & AREA_LOAD_FLAG_FAIRY_VILLAGE) {
        EMI_LoaderStreamInitSlot(EMI_SLOT_COMMU00);
        while (EMI_LoaderIsReady() == 0) {
            func_801992B8();
            CallbackWait(1u);
        }
        func_801F03D0();
    }
    g_GameEntryState    = 2u;
    g_GameEntrySubstate = 0u;
    g_GameStateIndex    = GAME_REQUEST_IDLE;
    Area_RunFrame();
}
