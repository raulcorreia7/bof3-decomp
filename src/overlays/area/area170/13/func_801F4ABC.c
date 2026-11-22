#include "area170_13.h"

MATCH void func_801F4ABC(void) {
    s8* mode;

    mode = &g_SceneEventState.mode;
    if (*mode == 0x33) {
        *mode = 0x25;
    }
    func_801F3994();
    if (g_GameLastCellType == 2) {
        if (g_GameCellType == 1) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x0C));
        }
    }
    if (g_GameLastCellType == 3) {
        if (g_GameCellType == 2) {
            SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x0C));
        }
    }
}
