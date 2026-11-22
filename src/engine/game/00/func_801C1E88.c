#include "game_00.h"

MATCH void func_801C1E88(s32 key, s32* counter) {
    s32 room_index;
    s32 outer;
    s32 total;
    s32 inner;
    s32 next;
    s32 val;

    total = 0;
    outer = 0;
    val   = 4;
    key &= BYTE_MASK;
    room_index = 0;
    do {
        if ((g_FairyRooms[room_index] == val) && (g_FairyRooms[1 + room_index] == key)) {
            next  = outer + 1;
            inner = 0;
            do {
                if ((((u8*)g_FairyJobs)[inner] != 0) && (((u8*)g_FairyJobs)[inner + 1] == next)) {
                    total += 1;
                }
                inner += FAIRY_JOB_STRIDE;
            } while (inner < FAIRY_JOB_COUNT * FAIRY_JOB_STRIDE);
        }
        outer += 1;
        room_index += 8;
    } while (outer < 8);
    if (!(total & BYTE_MASK)) {
        *counter += 1;
    }
}
