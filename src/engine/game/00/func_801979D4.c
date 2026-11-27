#include "game_00.h"

MATCH void func_801979D4(void) {
    if ((g_UIWindowChannel & FRONTEND_FLAG_CONFIRM) != 0u) {
        D_80146256                              = 0x10u;
        g_SysThreads[0].tail.game_entry.request = GAME_REQUEST_IDLE;
        g_SysThreads[0].tail.game_entry.state   = GAME_MODE_FIELD;
    }

    func_80199230();
}
