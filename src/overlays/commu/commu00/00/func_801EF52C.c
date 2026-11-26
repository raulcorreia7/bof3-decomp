#include "commu00_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801EF52C(void) {
    s32 more_group_rows;
    s32 active_job_count;
    /* FAKE: the group byte offset stays in a3 so the table bases stay direct; the plain form is 139 rows off. */
    FAKE_REG(s32, group_byte_offset, "a3");
    s32  group_number;
    s32  job;
    s32  queue_record_index;
    s32  record_group_number;
    u32* battle_count_ptr;
    u32* timer_ptr;
    s16  weighted_progress;
    u32  battle_delta;
    u8   current_progress;
    u32  updated_progress;
    u32  queue_offset;
    u32  queue_entry_offset;
    s16  progress_cap;

    group_number      = 1;
    battle_count_ptr  = &g_BattleCount;
    timer_ptr         = (u32*)((u8*)battle_count_ptr + 0x780);
    group_byte_offset = 0;
    do {
        weighted_progress = active_job_count = 0;
        if (g_FairyRooms[group_byte_offset] == 5) {
            current_progress = D_801457AB[group_byte_offset];
            if (current_progress == 0) {
                D_801457AB[group_byte_offset] = 1;
                *timer_ptr                    = *battle_count_ptr;
            } else if (current_progress < 11) {
                record_group_number = group_number;
                for (job = 0; job < FAIRY_JOB_COUNT; job++) {
                    if (g_FairyJobs[job].active != 0 && g_FairyJobs[job].type == record_group_number) {
                        active_job_count += 1;
                        weighted_progress += D_801F24FC_Data.fairies[job].stats[2];
                    }
                }
                if ((u8)active_job_count != 0) {
                    battle_delta      = *battle_count_ptr - *timer_ptr;
                    weighted_progress = 6 * D_801457AA[group_byte_offset] - (s16)(weighted_progress - 12);
                    if (weighted_progress < 5) {
                        weighted_progress = 5;
                    }
                    battle_delta /= weighted_progress;
                    progress_cap = FIELD(u8, battle_count_ptr, 0x598u) + 4;
                    if (battle_delta != 0 && D_801457AB[group_byte_offset] < progress_cap) {
                        updated_progress              = D_801457AB[group_byte_offset] + battle_delta;
                        D_801457AB[group_byte_offset] = updated_progress;
                        if (progress_cap < (s32)(updated_progress & BYTE_MASK)) {
                            D_801457AB[group_byte_offset] = progress_cap;
                        }
                        *(u32*)((u8*)&D_801457AC + group_byte_offset) = *battle_count_ptr;
                        queue_record_index                            = 0;
                        queue_offset                                  = g_FairyVillageUpdateCount * 2;
                        D_80145E60[queue_offset]                      = 0;
                        while (queue_record_index < FAIRY_VILLAGE_COUNT) {
                            if (g_FairyJobs[queue_record_index].active != 0 && g_FairyJobs[queue_record_index].type == group_number) {
                                break;
                            }
                            queue_record_index += 1;
                        }
                        queue_entry_offset                 = g_FairyVillageUpdateCount * 2;
                        D_80145E60[queue_entry_offset + 1] = queue_record_index;
                        g_FairyVillageUpdateCount += 1;
                    }
                }
            }
        }
        group_number += 1;
        timer_ptr += 2;
        more_group_rows = (s32)timer_ptr < (s32)&D_801457EC;
        group_byte_offset += 8;
    } while (more_group_rows != 0);
}
#else
INCLUDE_ASM(func_801EF52C);
#endif
