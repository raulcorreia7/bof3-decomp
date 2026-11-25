#include "commu00_00.h"

/* The exploration success roll of each trip type, copied out of the overlay header. */
typedef struct FairyTripRolls {
    u8 roll[FAIRY_EXPLORE_TRIP_COUNT];
} FairyTripRolls;

#ifdef NON_MATCHING
NON_MATCHING s32 func_801EF784(void) {
    FairyTripRolls threshold;
    s32            entry;
    s32            room;
    s32            index;
    u8             trip;
    u8             roll;
    u8             chance;

    threshold = *(FairyTripRolls*)g_FairyVillageOverlayHeader.explore_threshold;
    for (room = 0; room < 8; room++) {
        if (((u8*)g_FairyRooms)[room * 8] != 9) {
            continue;
        }
        for (index = 0, entry = room * 8; index < FAIRY_JOB_COUNT; index++) {
            if (g_FairyJobs[index].active == 0 || g_FairyJobs[index].type != room + 1) {
                continue;
            }
            if (g_BattleCount - g_FairyJobs[index].progress_anchor >= (((u8*)g_FairyRooms)[entry + 1] + 1) * 6) {
                if (g_FairyJobs[index].record_state < 2) {
                    trip   = ((u8*)g_FairyRooms)[entry + 1] * 2 + 1;
                    chance = trip * 10 - g_Fairies[index][5] * trip;
                    roll   = rand() & 0x7F;
                    if (roll > 100) {
                        roll -= 100;
                    }
                    if (chance > roll) {
                        if ((u8)Fairy_CountFairies() >= 2) {
                            g_FairyJobs[index].active = 0;
                            D_80145E30[D_80145E44]    = index | 0x80;
                            D_80145E44++;
                            continue;
                        }
                        g_FairyJobs[index].record_state = 3;
                    } else {
                        roll = rand() & 0x7F;
                        if (roll > 100) {
                            roll -= 100;
                        }
                        if (roll < threshold.roll[((u8*)g_FairyRooms)[entry + 1]]) {
                            g_FairyJobs[index].record_state = 3;
                        } else {
                            g_FairyJobs[index].record_state = 2;
                        }
                    }
                    D_80145E60[g_FairyVillageUpdateCount * 2] = 2;
                    D_80145E61[g_FairyVillageUpdateCount * 2] = index;
                    g_FairyVillageUpdateCount++;
                }
            } else {
                g_FairyJobs[index].record_state = 1;
            }
        }
    }
}
#else
INCLUDE_ASM(func_801EF784);
#endif
