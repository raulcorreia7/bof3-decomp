#include "game_00.h"

MATCH void func_801B6418(void) {
    u16 world_id;
    s32 offset;

    world_id = g_GameAreaId;
    offset   = 0;
loop:
    if (world_id == *(u16*)(&D_801CD224.bytes[offset])) {
        g_GameContextSeed = *(u16*)(&D_801CD226[offset]);
        goto end; /* the routing table entry matched */
    }
    offset += 4;
    if (offset < 0x28) {
        goto loop; /* try the next table entry */
    }
end:;
}
