#include "start_08.h"

MATCH void SAVE_RunLoadRestore(void) {
    u8  countdown;
    s32 i;

    countdown  = (u8)D_801ED7F0;
    D_801ED7F0 = countdown - 1;
    if (countdown == 0) {
        for (i = 0; (u32)(i & BYTE_MASK) < 9U; i++) {
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
        g_PartySize = Party_CountOrder(0U);
        EMI_StreamFamilyArchive(g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK, EMI_FAMILY_PLP);
        while (EMI_LoaderIsReady() == 0) {
            CallbackWait(1);
        }
        EMI_StreamFamilyArchive(g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK, EMI_FAMILY_PL);
        while (EMI_LoaderIsReady() == 0) {
            CallbackWait(1);
        }
        Party_BuildBattlers(0);
        {
            u8* src;
            s8* dst;

            src = &D_801448D8;
            dst = &g_SceneState;
            memcpy(dst, src, 0x10);
            g_SceneFlags = (*dst * 8) + (&D_801448D8 + 0x5B0);
        }
        g_ScriptVars[0] = D_801448F8;
        g_ScriptVars[1] = D_801448F9;
        g_ScriptVars[2] = D_801448FA;
        g_ScriptVars[3] = D_801448FB;
        Scene_RequestOverlay();
        while (EMI_LoaderIsReady() == 0) {
            CallbackWait(1);
        }
        g_GameEntrySubstate = 4;
        D_801ED860          = 0;
    }
    if (WINDOW_EFFECT_BUSY()) {
        if (g_InputHeld & PADstart) {
            D_801ED18C = 1;
        }
        Menu_DrawClutStrip(D_80144953);
        Menu_DrawHeaderBar(0x14, 0x12, 0x118, 0x13, (s32)D_80144952);
        SAVE_DrawSlots(0x20, 0x30, 0U);
        UI_DrawText(28, 21, 0, 0xFFU, Resource_GetText(0xB1));
    }
}
