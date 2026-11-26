#include "area030_04.h"

/* The spawn type and limit byte of each 0x24-byte species row, and the spawn counts. The type byte
 * is the byte after D_801E2AD5; the header gives it no symbol. */
#define FISH_TYPES            (D_801E2AD5 + 1)
#define LIMIT_TABLE           D_801E2AD7
#define COUNT_TABLE           ((u8*)g_FishingSpawnCounts)

/* The spawn column count, the type row stride and the state row stride. */
#define FISHING_SPAWN_COLUMNS 0x17
#define FISHING_TYPE_STRIDE   0x24
#define FISHING_ROW_STRIDE    0x98

/* Fields of the row published through g_CurrentActor. */
#define ROW_ROLL              FISHING_ROW->roll_90
#define ROW_VALUE             FISHING_ROW->ext.fishing.stamina_max
#define ROW_VALUE2            FISHING_ROW->ext.fishing.stamina

/* Spawns the area-030 state rows for the active spawn columns, rolling and clamping each row's hit value into
 * the type table words. */
/* func_801DE1C0 */
#ifdef NON_MATCHING
NON_MATCHING void Fishing_SpawnFish(void) {
    s32    column;
    s32    row_index;
    s32    count;
    s32    row_offset;
    s32    walk;
    u32    roll;
    u32    masked;
    Actor* fish;
    Actor* task;
    u8     limit;
    u8     type;

    column    = 0;
    row_index = 0;
next_column:
    count = COUNT_TABLE[g_GameEntryFacing * FISHING_SPAWN_COLUMNS + column];
    if (count > 0) {
        row_offset = row_index * FISHING_ROW_STRIDE;
    next_fish:
        TASK_SET((u8*)g_Actors + row_offset);
        g_CurrentActor       = (Actor*)((u8*)g_Actors + row_offset);
        *(u8*)g_CurrentActor = 0x21;
        TASK(Actor)->unk_05  = row_index;
        TASK(Actor)->unk_06  = column;
        FISHING_ROW->roll_90 = RANDOM_MASK(BYTE_MASK);
        fish                 = FISHING_ROW;
        task                 = TASK(Actor);
    retry:
        roll   = fish->roll_90;
        limit  = LIMIT_TABLE[task->unk_06 * FISHING_TYPE_STRIDE];
        masked = roll & 0xFFFF;
        if (limit < masked) {
            fish->roll_90 = roll - (limit >> 1);
            goto retry;
        }
        masked        = (masked < (limit >> 1)) ? (limit >> 1) : roll;
        fish->roll_90 = masked;
        ROW_VALUE     = FISH_TYPES[TASK(Actor)->unk_06 * FISHING_TYPE_STRIDE] * (ROW_ROLL * 10 / LIMIT_TABLE[TASK(Actor)->unk_06 * FISHING_TYPE_STRIDE]) / 10;
        ROW_VALUE2    = ROW_VALUE;
        type          = TASK(Actor)->unk_06;
        if (type != 0x15 && ROW_ROLL == LIMIT_TABLE[type * FISHING_TYPE_STRIDE]) {
            limit = LIMIT_TABLE[type * FISHING_TYPE_STRIDE];
            for (walk = 0; walk <= (u8)(limit / 10); walk++) {
                if (!RANDOM_MASK(1)) {
                    break;
                }
                ROW_ROLL++;
            }
        }
        TASK(Actor)->header.mode = 0;
        ACTOR_CLEAR_STEP();
        row_offset += FISHING_ROW_STRIDE;
        TASK(Actor)->unk_03 = 0;
        row_index++;
        TASK(Actor)->unk_04 = 0;
        count--;
        TASK(Actor)->tint.bytes.flags = 0;
        if (count > 0) {
            goto next_fish;
        }
    }
    column++;
    if (column < FISHING_SPAWN_COLUMNS) {
        goto next_column;
    }
}
#else
INCLUDE_ASM(Fishing_SpawnFish);
#endif
