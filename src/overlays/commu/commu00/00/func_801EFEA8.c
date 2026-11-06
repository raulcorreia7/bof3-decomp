#include "commu00_00.h"

MATCH s32 func_801EFEA8(void) {
    s32 record_count_low_byte;
    s32 more_group_rows;
    s32 queue_scan_offset;
    s32 active_record_count;
    /* FAKE: retains the group byte offset in a2. */
    MATCH_REG(s32, group_byte_offset, "a2");
    s32  group_number;
    s32  active_record_offset;
    s32  queue_record_index;
    s32  record_group_number;
    s32  queue_group_number;
    u32* battle_count_ptr;
    u32* timer_ptr;
    s16  battle_delta;
    u8   updated_progress;
    u8   current_progress;
    u8   progress_or_queue_count;
    u32  queue_offset;
    u32  queue_entry_offset;

    group_number      = 1;
    battle_count_ptr  = &g_SaveData.battle_count;
    timer_ptr         = (u32*)((u8*)battle_count_ptr + 0x780);
    group_byte_offset = 0;
    do {
        active_record_count = 0;
        if (g_FairyRooms[group_byte_offset] == 0xB) {
            current_progress = D_801457AB[group_byte_offset];
            if (current_progress == 0) {
                D_801457AB[group_byte_offset] = 5;
                *timer_ptr                    = *battle_count_ptr;
            } else if (current_progress < (&D_801F2560)[D_801455C4]) {
                record_group_number = group_number;
                for (active_record_offset = 0; active_record_offset < 480; active_record_offset += 8) {
                    if (((u8*)g_SaveData.fairy_jobs)[active_record_offset] != 0 &&
                        ((u8*)g_SaveData.fairy_jobs)[active_record_offset + 1] == record_group_number) {
                        active_record_count += 1;
                    }
                }
                record_count_low_byte = active_record_count & BYTE_MASK;
                if (record_count_low_byte != 0) {
                    battle_delta = (*battle_count_ptr - *timer_ptr) / (6 - record_count_low_byte);
                    if (battle_delta != 0) {
                        updated_progress              = battle_delta + D_801457AB[group_byte_offset];
                        D_801457AB[group_byte_offset] = updated_progress;
                        /* kept: direct D_801455C4 access changes the retail register schedule. */
                        progress_or_queue_count       = (&D_801F2560)[FIELD(u8, battle_count_ptr, 0x598u)];
                        queue_record_index            = 0;
                        if (progress_or_queue_count < (updated_progress & BYTE_MASK)) {
                            D_801457AB[group_byte_offset] = progress_or_queue_count;
                        }
                        queue_group_number                            = group_number;
                        progress_or_queue_count                       = g_FairyVillageUpdateCount;
                        queue_scan_offset                             = 0;
                        *(u32*)((u8*)&D_801457AC + group_byte_offset) = *battle_count_ptr;
                        queue_offset                                  = progress_or_queue_count * 2;
                        D_80145E60[queue_offset]                      = 1;
                    scan_queue:
                        if (((u8*)g_SaveData.fairy_jobs)[queue_scan_offset] == 0 ||
                            ((u8*)g_SaveData.fairy_jobs)[queue_scan_offset + 1] != queue_group_number) {
                            queue_record_index += 1;
                            queue_scan_offset += 8;
                            if (queue_record_index < 60) {
                                /* Continue until this group's active record is found. */
                                goto scan_queue;
                            }
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
    return more_group_rows;
}
