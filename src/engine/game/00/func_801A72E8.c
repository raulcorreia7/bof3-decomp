#include "game_00.h"

MATCH void func_801A72E8(void* selector) {
    if (FIELD(u8, selector, 0x1u) != 0) {
        g_CurrentActor->callback_index = FIELD(u8, selector, 0x3u);
        return;
    }
    g_CurrentActor->unk_7C = (FIELD(u8, selector, 0x3u) | (FIELD(u8, selector, 0x2u) << 8));
}
