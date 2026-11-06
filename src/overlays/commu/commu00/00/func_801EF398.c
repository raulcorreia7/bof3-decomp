#include "commu00_00.h"

MATCH void func_801EF398(void) {
    s32 sum = 0;
    s32 count;
    s32 outer;
    s32 val;
    s32 step;
    s32 next;
    s32 inner;
    s32 off;
    s16 amount;

    count = 0;
    if (D_801455C3 < 10U) {
        outer = 0;
        val   = 4;
        step  = 0;
        do {
            if ((g_FairyRooms[step] == val) && (D_801457A9[step] == 0)) {
                next  = outer + 1;
                off   = 0;
                inner = 0;
                do {
                    if (((&g_SaveData.fairy_jobs[0].active)[inner] != 0) &&
                        ((&g_SaveData.fairy_jobs[0].active)[inner + 1] == next)) {
                        count += 1;
                        sum += D_801F2708[off];
                    }
                    inner += 8;
                    off += 9;
                } while (inner < 480);
            }
            outer += 1;
            step += 8;
        } while (outer < 8);
        if (count & BYTE_MASK) {
            amount = 0x14 - sum;
            if (amount <= 0) {
                amount = 1;
            }
            if ((g_SaveData.battle_count - D_801455BC) >= amount && D_801455C4 >= D_801F2523[D_801455C3 & BYTE_MASK]) {
                D_801455C3 += 1;
                D_801455BC += amount;
                D_80145E60[g_FairyVillageUpdateCount * 2] = 6;
                g_FairyVillageUpdateCount += 1;
            }
        }
    }
}
