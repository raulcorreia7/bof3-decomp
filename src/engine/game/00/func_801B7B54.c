#include "game_00.h"

MATCH void func_801B7B54(void) {
    u16 next;

    next = COORD_INT(g_Task->pos.z);
    next += 0x10;
    FIELD(u16, g_Task, 0x3Eu) = next;
    if ((s16)next >= Area_ReadHeight(D_80146264, D_80146268) - D_80181B70[g_GameState->chr.character_id]) {
        func_801C51B0();
        g_Task->unk_04++;
    } else {
        func_8014D978();
    }
}
