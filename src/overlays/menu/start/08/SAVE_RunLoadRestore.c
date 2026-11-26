#include "start_08.h"

MATCH void SAVE_RunLoadRestore(void) {
    u8  countdown;
    s32 i;

    countdown        = g_MenuStartTimer;
    g_MenuStartTimer = countdown - 1;
    if (countdown == 0) {
        for (i = 0; (i & BYTE_MASK) < 9U; i++) {
            g_InputMasks[i & BYTE_MASK] = D_80145594[i & BYTE_MASK];
        }
        if (D_801ED18C != 0) {
            g_InputMasks[INPUT_SLOT_MOVE]    = PADRright;
            g_InputMasks[INPUT_SLOT_SPEAK]   = PADRdown;
            g_InputMasks[INPUT_SLOT_ACTION]  = PADRup;
            g_InputMasks[INPUT_SLOT_MENU]    = PADRleft;
            g_InputMasks[INPUT_SLOT_VIEW]    = PADR1;
            g_InputMasks[INPUT_SLOT_CHANGE]  = PADL1;
            g_InputMasks[INPUT_SLOT_CONFIRM] = PADRdown;
            g_InputMasks[INPUT_SLOT_CANCEL]  = PADRup;
            g_InputMasks[INPUT_SLOT_UNUSED]  = PADselect;
        }
        g_Game.party_size = Party_CountOrder(PARTY_ORDER_FIELD);
        EMI_ArchiveLoadFamily(g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK, EMI_FAMILY_PLP);
        while (EMI_IsReady() == 0) {
            SYS_ThreadWait(1);
        }
        EMI_ArchiveLoadFamily(g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK, EMI_FAMILY_PL);
        while (EMI_IsReady() == 0) {
            SYS_ThreadWait(1);
        }
        Party_BattlersBuild(PARTY_ORDER_FIELD);
        {
            u8* src;
            s8* dst;

            src = (u8*)&g_SaveData;
            dst = &g_ScenarioState;
            memcpy(dst, src, 0x10);
            g_SceneFlags = (u32*)g_SaveData.scene_flag_rows[*dst];
        }
        g_ScriptVars[0] = g_SavedScriptVars[0];
        g_ScriptVars[1] = g_SavedScriptVars[1];
        g_ScriptVars[2] = g_SavedScriptVars[2];
        g_ScriptVars[3] = g_SavedScriptVars[3];
        Scene_LoadOverlay();
        while (EMI_IsReady() == 0) {
            SYS_ThreadWait(1);
        }
        g_GameEntrySubstate = 4;
        g_MenuCampStep      = 0;
    }
    if (WINDOW_EFFECT_BUSY()) {
        if (g_PadStates[0].held & PADstart) {
            D_801ED18C = 1;
        }
        Menu_DrawClutStrip(g_WindowClut);
        MENU_DRAW_HEADER();
        SAVE_DrawSlots(SAVE_SLOTS_X, SAVE_SLOTS_Y, 0U);
        UI_TextDraw(28, 21, 0, TEXT_LENGTH_MAX, UI_MessageGetText(0xB1));
    }
}
