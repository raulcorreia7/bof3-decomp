#include "commu00_00.h"

#ifdef NON_MATCHING
/* Queues every copy job the village can afford; unk_03's high nibble is the state: 1 waiting, 2/3/4 result. */
NON_MATCHING s32 func_801EFA50(void) {
    s32 queue_off;
    s32 room;
    s32 job;
    s32 type_index;
    u32 price;
    u32 wait;
    u8  flags;
    u8  record;
    s32 value;
    s32 roll;

    for (room = 0; room < 8; room++) {
        if (g_FairyRooms[room * 8] != 0xD) {
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
            record = g_FairyJobs[job].record_state;
            switch (g_FairyJobs[job].unk_03 & 0xF) {
                case ITEM_CATEGORY_ITEM:
                    flags = g_Items[record].flags;
                    price = g_Items[record].price;
                    break;
                case ITEM_CATEGORY_WEAPON:
                    flags = g_Weapons[record].header.flags;
                    price = g_Weapons[record].price;
                    break;
                case ITEM_CATEGORY_ARMOR:
                    flags = g_Armors[record].header.flags;
                    price = g_Armors[record].price;
                    break;
                default:
                    flags = g_Accessories[record].header.flags;
                    price = g_Accessories[record].price;
                    break;
            }
            for (type_index = 0; type_index < FAIRY_VILLAGE_COPY_CLASS_COUNT; type_index++) {
                if (price <= D_801F24FC_Data.copy_class[type_index][0]) {
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
            value = D_801F24FC_Data.copy_class[type_index][2];
            value += (value * g_Fairies[job][8]) / 100;
            if ((s16)value < 0) {
                value = 0;
            } else if ((s16)value >= 0x65) {
                value = 0x64;
            }
            roll = RANDOM_MASK(0x7F);
            if (roll >= 0x65) {
                roll -= 0x1C;
            }
            if (roll < (s16)value) {
                g_FairyJobs[job].unk_03 |= 0x20;
                goto queue;
            }
            roll = RANDOM_MASK(0x7F);
            if (roll >= 0x65) {
                roll -= 0x1C;
            }
            if (roll < (s16)value - g_Fairies[job][8] * 2) {
                g_FairyJobs[job].unk_03       = 0x40;
                g_FairyJobs[job].record_state = 0x37;
            } else {
                g_FairyJobs[job].unk_03 |= 0x30;
            }
        queue:
            queue_off                 = g_FairyVillageUpdateCount * 2;
            D_80145E60[queue_off]     = 3;
            D_80145E60[queue_off + 1] = (u8)job;
            g_FairyVillageUpdateCount = (u8)(g_FairyVillageUpdateCount + 1);
        }
    }
    return 0;
}
#else
INCLUDE_ASM(func_801EFA50);
#endif
