#include "area030_04.h"

/* The saved work word at 0x3C and the scale halfword at 0x3E overlap. */
typedef struct AreaWorkSaved {
    u8  pad_00[0x3C];
    u32 saved_3C;
} AreaWorkSaved;

typedef struct AreaWorkScale {
    u8  pad_00[0x3E];
    s16 scale_3E;
    s32 result_40;
    s32 result_44;
    u8  pad_48[0x18];
    s32 distance_60;
} AreaWorkScale;

/* Suspends the scratchpad work word across a scene call. */
MATCH void func_801E084C(void) {
    AreaWorkSaved* saved;
    AreaWorkScale* work;
    s32            save;

    saved           = (AreaWorkSaved*)g_Task;
    save            = saved->saved_3C;
    saved->saved_3C = 0;
    func_8014D290();
    work                             = (AreaWorkScale*)g_Task;
    ((AreaWorkSaved*)work)->saved_3C = save;
    if (work->distance_60 < 0) {
        work->result_40 = (0x4650000 / (work->distance_60 - work->scale_3E * 2)) & ~0xFF;
        work->result_44 = (0x4650000 / (work->distance_60 - work->scale_3E * 2)) & ~0xFF;
        return;
    }
    if (work->distance_60 > 0) {
        work->result_40 = (0x4650000 / work->distance_60) & ~0xFF;
        work->result_44 = (0x4650000 / work->distance_60) & ~0xFF;
        return;
    }
    work->result_40 = 0;
    work->result_44 = 0;
}
