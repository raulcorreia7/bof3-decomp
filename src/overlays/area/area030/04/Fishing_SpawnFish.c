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
    s16 hit_value;
    s32 type_offset;
    s32 steps;
    s32 walk;
    s32 walk_limit;
    s32 row_offset;
    s8  row_index;
    u8  count;
    u16 roll;
    u16 clamped;
    u16 half;
    u32 roll_masked;
    u8* cur;
    u8* limits;
    u8* row;
    u8  type;
    u8  limit;
    u8  column;

    column    = 0;
    row_index = 0;
    do {
        count = COUNT_TABLE[g_GameEntryFacing * FISHING_SPAWN_COLUMNS + column];
        if (count > 0) {
            row_offset = row_index * FISHING_ROW_STRIDE;
            do {
                row = (u8*)g_Actors + row_offset;
                TASK_SET(row);
                g_CurrentActor      = (Actor*)row;
                *row                = 0x21;
                TASK(Actor)->unk_05 = (u8)row_index;
                TASK(Actor)->unk_06 = (u8)column;
                roll                = RANDOM_MASK(BYTE_MASK);
            loop_4:
                ROW_ROLL    = roll;
                roll        = ROW_ROLL;
                limit       = LIMIT_TABLE[TASK(Actor)->unk_06 * FISHING_TYPE_STRIDE];
                roll_masked = roll & HALF_MASK;
                if (limit < roll_masked) {
                    roll = (u16)(roll - (limit >> 1));
                    goto loop_4; /* retry the roll store after subtracting the type's half limit */
                }
                half    = (u16)(limit >> 1);
                clamped = roll;
                if (roll_masked < half) {
                    clamped = half;
                }
                ROW_ROLL    = clamped;
                cur         = (u8*)g_Task;
                type_offset = cur[6] * FISHING_TYPE_STRIDE;
                hit_value   = (s16)((FISH_TYPES[type_offset] * ((s32)(ROW_ROLL * 0xA) / (s32)LIMIT_TABLE[type_offset])) / 10);
                ROW_VALUE   = hit_value;
                ROW_VALUE2  = hit_value;
                type        = cur[6];
                if (type != 0x15) {
                    limits = LIMIT_TABLE + (type * FISHING_TYPE_STRIDE);
                    if (ROW_ROLL == *limits) {
                        steps = (*limits / 10) & BYTE_MASK;
                        walk  = 0;
                        if (steps >= 0) {
                            walk_limit = steps;
                        loop_12:
                            if (RANDOM_MASK(1)) {
                                walk += 1;
                                ROW_ROLL = (u16)(ROW_ROLL + 1);
                                if (walk_limit >= walk) {
                                    goto loop_12; /* keep walking while the roll stays under the limit */
                                }
                            }
                        }
                    }
                }
                TASK(Actor)->header.mode = 0;
                ACTOR_CLEAR_STEP();
                row_offset += FISHING_ROW_STRIDE;
                TASK(Actor)->unk_03 = 0;
                row_index += 1;
                TASK(Actor)->unk_04 = 0;
                count -= 1;
                TASK(Actor)->tint.bytes.flags = 0;
            } while (count > 0);
        }
        column += 1;
    } while (column < FISHING_SPAWN_COLUMNS);
}
#else
INCLUDE_ASM(Fishing_SpawnFish);
#endif
