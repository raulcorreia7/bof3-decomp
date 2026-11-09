#include "area030_04.h"

/* Initialises the AREA030 scratch record. */
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
