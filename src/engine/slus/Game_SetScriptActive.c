#include "engine/slus/slus.h"

/* sets bit 6 of D_80146871 and bit 8 of g_GameFlags.
 */
MATCH void Game_SetScriptActive(void) {
    u8* p = &D_80146871;
    (*p) |= 0x40;
    g_GameFlags |= GAME_FLAG_SCRIPT_ACTIVE;
}
