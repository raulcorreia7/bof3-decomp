#include "commu00_00.h"

MATCH void Fairy_JoinVillage(void) {
    u32* count_ptr;
    /* FAKE: keeps the advanced destination pointer in v1. */
    MATCH_REG(u8*, dst, "v1");
    u8* src;
    u8* copy_src;
    u8* end;
    u32 dst_offset;
    u32 src_offset;
    u8  index;
    u8  one;
    u32 count;

    index = RANDOM_MASK(0x3F);
    if (index >= 60) {
        index -= 60;
    }
    one       = 1;
    count_ptr = &g_SaveData.battle_count;
    dst       = (u8*)count_ptr + 0x7BC;
    src       = g_Fairies[0];
    for (;;) {
        if (g_SaveData.fairy_jobs[index].active == 0) {
            dst_offset                                   = index * 5;
            dst                                          = (u8*)(dst_offset + (u32)dst);
            src_offset                                   = index * 9;
            copy_src                                     = (u8*)(src_offset + (u32)src);
            g_SaveData.fairy_jobs[index].active          = one;
            g_SaveData.fairy_jobs[index].type            = FAIRY_JOB_IDLE;
            count                                        = *count_ptr;
            end                                          = dst + 5;
            g_SaveData.fairy_jobs[index].record_state    = 0;
            g_SaveData.fairy_jobs[index].progress_anchor = count;

            do {
                *dst++ = *copy_src++;
            } while ((s32)dst < (s32)end);

            D_80145E48[g_FairyVillagePendingQueueCount] = index;
            g_FairyVillagePendingQueueCount++;
            return;
        }
        index++;
        if (index >= 60) {
            index = 0;
        }
    }
}
