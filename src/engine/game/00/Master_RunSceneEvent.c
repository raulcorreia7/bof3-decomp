#include "game_00.h"

MATCH void Master_RunSceneEvent(void) {
    switch (g_SaveData.scene_event.step) {
        case 0:
            g_AreaWalkFlags |= AREA_WALK_BUSY_ALL;
            EMI_LoaderStreamInitSlot(EMI_SLOT_SISYOU);
            {
                s8* state = &g_SaveData.scene_event.step;
                *state    = *state + 1;
            }
            return;
        case 1:
            if (EMI_LoaderIsReady() != 0) {
                GFX_CopyPalette(2U);
                func_801D0C18();
                {
                    s8* state = &g_SaveData.scene_event.step;
                    *state    = *state + 1;
                }
            }
            return;
        default:
            return;
        case 2:
            func_801D25D8();
            return;
        case 3:
            g_EmiStreamFlags = 0x20;
            EMI_StreamFamilyArchive(g_SaveData.emi_loaded_character_index & EMI_LOADED_INDEX_MASK, EMI_FAMILY_PL);
            g_SaveData.scene_event.step = g_SaveData.scene_event.step + 1;
            return;
        case 4:
            if (EMI_LoaderIsReady() != 0) {
                g_AreaWalkFlags &= ~AREA_WALK_BUSY_ALL;
                Game_ClearScriptActive();
                g_SaveData.scene_event.mode      = 0;
                g_SaveData.scene_event.step      = 0;
                g_SaveData.scene_event.selection = 0;
                return;
            }
            break;
        case 5:
            if (g_AreaSceneMode == 2) {
                g_SaveData.scene_event.step = 0;
            }
            break;
    }
}
