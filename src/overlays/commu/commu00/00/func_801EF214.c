#include "commu00_00.h"

MATCH void func_801EF214(void) {
    s32 count;
    s32 total;
    s32 room;
    s32 room_off;
    s32 room_next;
    s32 rec_off;
    s32 weight_off;
    s16 wait;
    u8* level;
    s32 kind;

    total = 0;
    count = 0;
    if (D_801455C4 < 7) {
        room     = 0;
        kind     = 4;
        room_off = 0;
        for (; room < 8; room++, room_off += 8) {
            if (g_FairyRooms[room_off] == kind && D_801457A9[room_off] != 0) {
                room_next  = room + 1;
                weight_off = 0;
                for (rec_off = 0; rec_off < 480; rec_off += 8) {
                    if (((u8*)g_FairyJobs)[rec_off] != 0 && ((u8*)g_FairyJobs)[rec_off + 1] == room_next) {
                        count += 1;
                        total += D_801F2708[weight_off];
                    }
                    weight_off += 9;
                }
            }
        }
        if ((count & 0xFF) != 0) {
            level = &D_801455C4;
            wait  = (D_801F2514[*level] - total);
            if (wait <= 0) {
                wait = 1;
            }
            if ((g_BattleCount - D_801455B8) >= wait) {
                (*level) += 1;
                D_801455B8 += wait;
                D_80145E60[g_FairyVillageUpdateCount * 2] = 7;
                g_FairyVillageUpdateCount += 1;
            }
        }
    }
}
