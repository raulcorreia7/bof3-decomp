#include "commu00_00.h"

MATCH void Fairy_VillageQueueRooms(void) {
    s32 flags;
    s32 index;
    s32 kind;

    flags = 0;
    if (g_GameAreaId > D_801455C0) {
        index = D_801455C0 + 1;
        if (g_GameAreaId >= index) {
            do {
                kind = D_801F2458[index];
                if (kind == 4) {
                    if (!(flags & 1)) {
                        D_80145E60[g_FairyVillageUpdateCount << 1] = kind;
                        flags |= 1;
                        g_FairyVillageUpdateCount += 1;
                    }
                } else if (kind == 5 && !(flags & 2)) {
                    D_80145E60[g_FairyVillageUpdateCount << 1] = 5;
                    flags |= 2;
                    g_FairyVillageUpdateCount += 1;
                }
                index += 1;
            } while (g_GameAreaId >= index);
        }
        D_801455C0 = g_GameAreaId;
    }
}
