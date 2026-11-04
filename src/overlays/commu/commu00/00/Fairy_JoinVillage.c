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
    count_ptr = &g_BattleCount;
    dst       = (u8*)count_ptr + 0x7BC;
    src       = g_Fairies[0];
    for (;;) {
        if (g_FairyJobs[index].active == 0) {
            dst_offset                         = index * 5;
            dst                                = (u8*)(dst_offset + (u32)dst);
            src_offset                         = index * 9;
            copy_src                           = (u8*)(src_offset + (u32)src);
            g_FairyJobs[index].active          = one;
            g_FairyJobs[index].type            = 0;
            count                              = *count_ptr;
            end                                = dst + 5;
            g_FairyJobs[index].record_state    = 0;
            g_FairyJobs[index].progress_anchor = count;

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
