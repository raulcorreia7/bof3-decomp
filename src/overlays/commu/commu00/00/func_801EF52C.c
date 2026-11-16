#include "commu00_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801EF52C(void) {
    s32  more_group_rows;
    s32  queue_scan_offset;
    s32  active_job_count;
    s32  group_byte_offset;
    s32  group_number;
    s32  active_job_offset;
    s32  queue_record_index;
    s32  record_group_number;
    s32  weighted_job_offset;
    u32* battle_count_ptr;
    u32* timer_ptr;
    u32  weighted_progress;
    u32  battle_delta;
    s16  progress_divisor;
    u8   current_progress;
    u32  updated_progress;
    s32  progress_cap;

    /* FAKE: retail indexes these table bytes per access; GCC carries their bases. */
    group_number      = 1;
    battle_count_ptr  = &g_BattleCount;
    timer_ptr         = (u32*)((u8*)battle_count_ptr + 0x780);
    group_byte_offset = 0;
    do {
        weighted_progress = 0;
        if (*FAKE_VOLATILE_PTR(u8, &g_FairyRooms[group_byte_offset]) == 5) {
            active_job_count = 0;
            current_progress = *FAKE_VOLATILE_PTR(u8, &D_801457AB[group_byte_offset]);
            if (current_progress == 0) {
                *FAKE_VOLATILE_PTR(u8, &D_801457AB[group_byte_offset]) = 1;
                *timer_ptr                                             = *battle_count_ptr;
            } else if (current_progress < 11) {
                record_group_number = group_number;
                for (active_job_offset = 0, weighted_job_offset = 0; active_job_offset < 480; active_job_offset += 8, weighted_job_offset += 9) {
                    if (*FAKE_VOLATILE_PTR(u8, (u8*)g_FairyJobs + active_job_offset) != 0 && *FAKE_VOLATILE_PTR(u8, (u8*)g_FairyJobs + active_job_offset + 1) == record_group_number) {
                        active_job_count++;
                        weighted_progress += *FAKE_VOLATILE_PTR(u8, (u8*)&D_801F2560 + 0x1A7 + weighted_job_offset);
                    }
                }
                if ((u8)active_job_count != 0) {
                    progress_divisor = 6 * *FAKE_VOLATILE_PTR(u8, &D_801457AA[group_byte_offset]) - (weighted_progress - 12);
                    if (progress_divisor < 5) {
                        progress_divisor = 5;
                    }
                    battle_delta = (*battle_count_ptr - *timer_ptr) / progress_divisor;
                    progress_cap = ((u8*)battle_count_ptr)[0x598] + 4;
                    if (battle_delta != 0 && current_progress < progress_cap) {
                        updated_progress                                       = current_progress + battle_delta;
                        *FAKE_VOLATILE_PTR(u8, &D_801457AB[group_byte_offset]) = updated_progress;
                        if (progress_cap < (s32)(updated_progress & 0xFF)) {
                            *FAKE_VOLATILE_PTR(u8, &D_801457AB[group_byte_offset]) = progress_cap;
                        }
                        *(u32*)((u8*)D_801457AA + group_byte_offset + 2)                   = *battle_count_ptr;
                        *FAKE_VOLATILE_PTR(u8, &D_80145E60[g_FairyVillageUpdateCount * 2]) = 0;
                        queue_scan_offset                                                  = 0;
                        queue_record_index                                                 = 0;
                        while (queue_record_index < 60) {
                            if (*FAKE_VOLATILE_PTR(u8, (u8*)g_FairyJobs + queue_scan_offset) != 0 && *FAKE_VOLATILE_PTR(u8, (u8*)g_FairyJobs + queue_scan_offset + 1) == group_number) {
                                break;
                            }
                            queue_record_index++;
                            queue_scan_offset += 8;
                        }
                        *FAKE_VOLATILE_PTR(u8, &D_80145E60[g_FairyVillageUpdateCount * 2 + 1]) = queue_record_index;
                        g_FairyVillageUpdateCount++;
                    }
                }
            }
        }
        group_number++;
        timer_ptr += 2;
        more_group_rows = (s32)timer_ptr < (s32)&D_801457EC;
        group_byte_offset += 8;
    } while (more_group_rows != 0);
}
#else
INCLUDE_ASM(func_801EF52C);
#endif
