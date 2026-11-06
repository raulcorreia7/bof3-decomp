#include "start_08.h"

MATCH void SAVE_RunLoadRestore(void) {
    u8  countdown;
    s32 i;

    countdown        = g_MenuStartTimer;
    g_MenuStartTimer = countdown - 1;
    if (countdown == 0) {
        for (i = 0; (i & BYTE_MASK) < 9U; i++) {
            (&g_InputMasks)[i & BYTE_MASK] = D_80145594[i & BYTE_MASK];
        }
        if (D_801ED18C != 0) {
            D_80145AB6   = PADRright;
            g_InputMasks = PADRdown;
            D_80145AC0   = PADRup;
            D_80145AB8   = PADRleft;
            D_80145ABA   = PADR1;
            D_80145ABC   = PADL1;
            D_80145AC2   = PADRdown;
            D_80145AC4   = PADRup;
            D_80145ABE   = PADselect;
        }
        g_PartySize = Party_CountOrder(PARTY_ORDER_FIELD);
        EMI_StreamFamilyArchive(g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK, EMI_FAMILY_PLP);
        while (EMI_LoaderIsReady() == 0) {
            CallbackWait(1);
        }
        EMI_StreamFamilyArchive(g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK, EMI_FAMILY_PL);
        while (EMI_LoaderIsReady() == 0) {
            CallbackWait(1);
        }
        Party_BuildBattlers(PARTY_ORDER_FIELD);
        {
            u8* src;
            s8* dst;

            src = (u8*)&g_SaveData;
            dst = &g_SceneState;
            memcpy(dst, src, 0x10);
            g_SceneFlags = (*dst * 8) + ((u8*)&g_SaveData + 0x5B0);
        }
        g_ScriptVars[0] = g_SavedScriptVars[0];
        g_ScriptVars[1] = g_SavedScriptVars[1];
        g_ScriptVars[2] = g_SavedScriptVars[2];
        g_ScriptVars[3] = g_SavedScriptVars[3];
        Scene_RequestOverlay();
        while (EMI_LoaderIsReady() == 0) {
            CallbackWait(1);
        }
        g_GameEntrySubstate = 4;
        g_MenuStartStep     = 0;
    }
    if (WINDOW_EFFECT_BUSY()) {
        if (g_InputHeld & PADstart) {
            D_801ED18C = 1;
        }
        Menu_DrawClutStrip(D_80144953);
        Menu_DrawHeaderBar(MENU_HEADER_X, MENU_HEADER_Y, MENU_HEADER_WIDTH, MENU_HEADER_HEIGHT, g_WindowStyle);
        SAVE_DrawSlots(0x20, 0x30, 0U);
        UI_DrawText(28, 21, 0, 0xFFU, Resource_GetText(0xB1));
    }
}
