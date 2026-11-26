#include "commu00_00.h"

/* Queues every copy job the village can afford; unk_03's high nibble is the state: 1 waiting, 2/3/4 result. */
MATCH s32 func_801EFA50(void) {
    s32 room;
    s32 room_offset;
    s32 job;
    s32 type_index;
    u32 price;
    u32 wait;
    u8  flags;
    s16 value;
    s32 roll;
    s16 clamped;
    s16 chance;

    for (room = 0; room < 8; room++) {
        room_offset = room * 8;
        if (g_FairyRooms[room_offset] != 0xD) {
            continue;
        }
        for (job = 0; job < FAIRY_JOB_COUNT; job++) {
            if (g_FairyJobs[job].active == 0) {
                continue;
            }
            if (g_FairyJobs[job].type != room + 1) {
                continue;
            }
            if ((g_FairyJobs[job].unk_03 & 0xF0) != 0x10) {
                continue;
            }
            switch (g_FairyJobs[job].unk_03 & 0xF) {
                case ITEM_CATEGORY_ITEM:
                    price = g_Items[g_FairyJobs[job].record_state].price;
                    flags = g_Items[g_FairyJobs[job].record_state].flags;
                    break;
                case ITEM_CATEGORY_WEAPON:
                    price = g_Weapons[g_FairyJobs[job].record_state].price;
                    flags = g_Weapons[g_FairyJobs[job].record_state].header.flags;
                    break;
                case ITEM_CATEGORY_ARMOR:
                    price = g_Armors[g_FairyJobs[job].record_state].price;
                    flags = g_Armors[g_FairyJobs[job].record_state].header.flags;
                    break;
                default:
                    price = g_Accessories[g_FairyJobs[job].record_state].price;
                    flags = g_Accessories[g_FairyJobs[job].record_state].header.flags;
                    break;
            }
            for (type_index = 0; type_index < FAIRY_VILLAGE_COPY_CLASS_COUNT; type_index++) {
                if ((price & HALF_MASK) <= D_801F24FC_Data.copy_class[type_index][0]) {
                    break;
                }
            }
            wait = D_801F24FC_Data.copy_class[type_index][1];
            if ((u32)(g_BattleCount - g_FairyJobs[job].progress_anchor) < wait) {
                continue;
            }
            g_FairyJobs[job].unk_03 &= 0xF;
            if (flags & ITEM_UNSELLABLE) {
                g_FairyJobs[job].unk_03 |= 0x30;
                goto queue;
            }
            value = D_801F24FC_Data.copy_class[type_index][2] + (D_801F24FC_Data.copy_class[type_index][2] * g_Fairies[job][8]) / 20;
            if (value >= 0) {
                clamped = value;
                if (value >= 0x65) {
                    clamped = 0x64;
                }
            } else {
                clamped = 0;
            }
            value  = clamped;
            roll   = RANDOM_MASK(0x7F);
            chance = roll;
            if (roll >= 0x65) {
                chance = roll - 0x1C;
            }
            if (value > chance) {
                g_FairyJobs[job].unk_03 |= 0x20;
                goto queue;
            }
            value  = 30 - g_Fairies[job][8] * 2;
            roll   = RANDOM_MASK(0x7F);
            chance = roll;
            if (roll >= 0x65) {
                chance = roll - 0x1C;
            }
            if (chance >= value) {
                g_FairyJobs[job].unk_03 |= 0x30;
            } else {
                g_FairyJobs[job].unk_03       = 0x40;
                g_FairyJobs[job].record_state = 0x37;
            }
        queue:
            D_80145E60[g_FairyVillageUpdateCount * 2] = 3;
            D_80145E61[g_FairyVillageUpdateCount * 2] = job;
            g_FairyVillageUpdateCount += 1;
        }
    }
}
