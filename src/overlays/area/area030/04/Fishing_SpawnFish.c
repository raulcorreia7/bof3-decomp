#include "area030_04.h"

/* The kind tables read through a non-const view so the base is rebuilt at
 * every access, the way retail materializes it. */
#define KIND_TABLE            MEM_PTR(s8, 0x801E2AD6u)
#define LIMIT_TABLE           MEM_PTR(s8, 0x801E2AD7u)
#define COUNT_TABLE           MEM_PTR(u8, 0x801E2DF4u)

/* The spawn column count, the kind row stride and the state row stride. */
#define FISHING_SPAWN_COLUMNS 0x17
#define FISHING_TYPE_STRIDE   0x24
#define FISHING_ROW_STRIDE    0x98

/* Fields of the row published through g_CurrentActor. */
#define ROW_ROLL              FISHING_ROW->roll_90
#define ROW_VALUE             FISHING_ROW->ext.fishing.stamina_max
#define ROW_VALUE2            FISHING_ROW->ext.fishing.stamina

/* Spawns the area-030 state rows for the active spawn columns, rolling and clamping each row's hit value into
 * the kind table words. */
/* func_801DE1C0 */
#ifdef NON_MATCHING
NON_MATCHING void Fishing_SpawnFish(void) {
    s16 hit_value;
    s32 kind_offset;
    s32 steps;
    s32 walk;
    s32 walk_limit;
    s32 row_offset;
    s8  row_index;
    u16 roll;
    u16 clamped;
    u32 half;
    u32 roll_masked;
    u8* cur;
    u8* limits;
    u8* row;
    u8  kind;
    u8  limit;
    u8  count;
    u8  column;

    column    = 0;
    row_index = 0;
    do {
        count = *(COUNT_TABLE + g_GameContextKind * FISHING_SPAWN_COLUMNS + column);
        if ((s32)count > 0) {
            row_offset = row_index * FISHING_ROW_STRIDE;
            do {
                row            = &g_Actors[row_offset];
                g_Task         = row;
                g_CurrentActor = row;
                *row           = 0x21;
                g_Task->unk_05 = row_index;
                g_Task->unk_06 = column;
                roll           = RANDOM_MASK(0xFF);
            loop_4:
                ROW_ROLL    = roll;
                roll        = ROW_ROLL;
                limit       = *(LIMIT_TABLE + (g_Task->unk_06 * FISHING_TYPE_STRIDE));
                roll_masked = roll & HALF_MASK;
                if (limit < roll_masked) {
                    roll = roll - (limit >> 1);
                    goto loop_4; /* retry the roll store after subtracting the kind's half limit */
                }
                half    = limit >> 1;
                clamped = roll;
                if (roll_masked < half) {
                    clamped = (u16)half;
                }
                ROW_ROLL    = clamped;
                cur         = g_Task;
                kind_offset = FIELD(u8, cur, 0x6u) * FISHING_TYPE_STRIDE;
                hit_value   = (KIND_TABLE[kind_offset] * ((s32)(ROW_ROLL * 0xA) / (s32)LIMIT_TABLE[kind_offset])) / 10;
                ROW_VALUE   = hit_value;
                ROW_VALUE2  = hit_value;
                kind        = FIELD(u8, cur, 0x6u);
                if (kind != 0x15) {
                    limits = MEM_PTR(u8, D_801E2AD7) + (kind * FISHING_TYPE_STRIDE);
                    if (ROW_ROLL == *limits) {
                        steps = (*limits / 10) & BYTE_MASK;
                        walk  = 0;
                        if (steps >= 0) {
                            walk_limit = steps;
                        loop_12:
                            if RANDOM_MASK (1) {
                                walk += 1;
                                ROW_ROLL = (u16)(ROW_ROLL + 1);
                                if (walk_limit >= walk) {
                                    goto loop_12; /* keep walking while the roll stays under the limit */
                                }
                            }
                        }
                    }
                }
                g_Task->header.mode = 0;
                ACTOR_CLEAR_STEP();
                row_offset += FISHING_ROW_STRIDE;
                g_Task->unk_03 = 0;
                row_index += 1;
                g_Task->unk_04 = 0;
                count -= 1;
                g_Task->tint.bytes.flags = 0;
            } while ((s32)count > 0);
        }
        column += 1;
    } while ((s32)column < FISHING_SPAWN_COLUMNS);
}
#else
INCLUDE_ASM(Fishing_SpawnFish);
#endif
