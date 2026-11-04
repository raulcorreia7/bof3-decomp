#include "batl_end_00.h"

MATCH void func_801EECD0(void) {
    u32* pool = &D_8014632C;
    u8   count;

    if (*pool != 0 && (count = func_801EEDA8()) != 0) {
        *pool = (*pool + count - 1) / count;
    } else {
        *pool = 0;
    }
    sprintf(g_TextVariables, D_801EEC04, D_8014632C);
    D_801EB4F4 = Resource_GetText(5);
    EMI_StreamFamilyArchive(g_EmiLoadedCharacterIndex & 0x7F, 0);
    g_BattleUiState += 1;
}
