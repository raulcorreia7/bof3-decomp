#include "area030_04.h"

/* Initialises the AREA030 scratch work record: copies the five world
 * state bytes at (u32)&D_80143FEC..(u32)&D_80143FF0 into scratch offsets 0x24..0x28, marks
 * 0x29 with 5, clears the byte at 0x48 and the words at 0x3C and 0x60..0x6C,
 * seeds the delta bytes 0x5D..0x5F with -100, then refreshes the record through
 * func_801D2AE0 and advances the scratch work index at 0x01. */
MATCH void func_801D29BC(void) {
    volatile u8* world;
    volatile u8* work;

    world = D_80140000;

    FISHING_STATE->active_flags   = world[0x3FECu];
    FISHING_STATE->saved_25       = world[0x3FEDu];
    FISHING_STATE->saved_26       = world[0x3FEEu];
    FISHING_STATE->saved_value_27 = world[0x3FEFu];
    FISHING_STATE->saved_value_28 = world[0x3FF0u];
    FISHING_STATE->state_29       = 5;

    work                     = (volatile u8*)g_Task;
    work[0x48u]              = 0;
    ((u32*)work)[0x3Cu / 4u] = 0;
    FISHING_STATE->unk_5C    = 0;

    FISHING_STATE->tint_5D = -100;
    FISHING_STATE->tint_5E = -100;
    FISHING_STATE->tint_5F = -100;
    FISHING_STATE->unk_60  = 0;
    FISHING_STATE->unk_64  = 0;
    FISHING_STATE->unk_68  = 0;
    FISHING_STATE->unk_6C  = 0;

    func_801D2AE0();

    FISHING_STATE->handler_index_01 += 1;
}
