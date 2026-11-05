#include "area079_13.h"

MATCH void func_801F2E68(void) {
    FIELD(u8, g_Task, 0x0Au) = 0x40;
    FIELD(u8, g_Task, 0x04u) = 1;
    g_GameState->unk_122 -= 2;
}
