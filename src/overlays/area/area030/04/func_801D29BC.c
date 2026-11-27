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

    SELF(FishingState)->active_flags   = world[0x3FECu];
    SELF(FishingState)->saved_25       = world[0x3FEDu];
    SELF(FishingState)->saved_26       = world[0x3FEEu];
    SELF(FishingState)->saved_value_27 = world[0x3FEFu];
    SELF(FishingState)->saved_value_28 = world[0x3FF0u];
    SELF(FishingState)->state_29       = 5;

    work                       = SELF(volatile u8);
    work[0x48u]                = 0;
    ((u32*)work)[0x3Cu / 4u]   = 0;
    SELF(FishingState)->unk_5C = 0;

    SELF(FishingState)->tint_5D = -100;
    SELF(FishingState)->tint_5E = -100;
    SELF(FishingState)->tint_5F = -100;
    SELF(FishingState)->unk_60  = 0;
    SELF(FishingState)->unk_64  = 0;
    SELF(FishingState)->unk_68  = 0;
    SELF(FishingState)->unk_6C  = 0;

    func_801D2AE0();

    SELF(FishingState)->handler_index += 1;
}
