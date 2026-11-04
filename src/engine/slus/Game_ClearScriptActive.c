#include "engine/slus/slus.h"

/* clears bit 6 of D_80146871 and bit 8 of g_GameFlags.
 */
MATCH void Game_ClearScriptActive(void) {
    u8* p = &D_80146871;
    *p &= 0xBF;
    g_GameFlags &= ~GAME_FLAG_SCRIPT_ACTIVE;
}
