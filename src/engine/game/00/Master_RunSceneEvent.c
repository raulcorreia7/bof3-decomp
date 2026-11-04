#include "game_00.h"

MATCH void Master_RunSceneEvent(void) {
    switch (D_801448EC) {
        case 0:
            g_AreaWalkFlags |= AREA_WALK_BUSY_ALL;
            EMI_LoaderStreamInitSlot(EMI_SLOT_SISYOU);
            {
                s8* state = &D_801448EC;
                *state    = (u8)*state + 1;
            }
            return;
        case 1:
            if (EMI_LoaderIsReady() != 0) {
                GFX_CopyPalette(2U);
                func_801D0C18();
                {
                    s8* state = &D_801448EC;
                    *state    = (u8)*state + 1;
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
            EMI_StreamFamilyArchive(g_EmiLoadedCharacterIndex & EMI_LOADED_INDEX_MASK, EMI_FAMILY_PL);
            D_801448EC = (u8)D_801448EC + 1;
            return;
        case 4:
            if (EMI_LoaderIsReady() != 0) {
                g_AreaWalkFlags &= ~AREA_WALK_BUSY_ALL;
                Game_ClearScriptActive();
                D_801448EB = 0;
                D_801448EC = 0;
                D_801448ED = 0;
                return;
            }
            break;
        case 5:
            if (g_AreaSceneMode == 2) {
                D_801448EC = 0;
            }
            break;
    }
}
