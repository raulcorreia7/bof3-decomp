#include "magic080_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC04(void) {
    ACTOR_RUN_MODE_HANDLER(func_801EEC5C, func_801EECE4);
}

INCLUDE_ASM(func_801EEC5C);

/* The two handlers read the variant byte already loaded in a0, so the calls pass no argument: a
 * call with an argument adds a zero-extension the retail code folds away. */
MATCH void func_801EECE4(void) {
    u8 ticks;
    u8 count;

    Battle_ProjectRange();
    ticks = g_Task->param.unk_0B;
    g_Task->unk_2E.half -= 0x24;
    if (ticks != 0) {
        func_801EEF5C();
    } else {
        func_801EED94();
    }
    count          = g_Task->unk_09 - 1;
    g_Task->unk_09 = count;
    if (!(count & BYTE_MASK)) {
        Battle_MarkDamaged(g_Battle.target_selector);
        g_Battle.state |= BATTLE_STATE_EFFECT_PLAYING;
        func_801E5988();
    }
}

MATCH void func_801EED94(void) {
    POLY_FT4* prim;
    s32       i;

    MAGIC080_DRAW_CELLS(6, D_801EF124, 0x100);
}

MATCH void func_801EEF5C(void) {
    POLY_FT4* prim;
    s32       i;

    MAGIC080_DRAW_CELLS(7, D_801EF13C, 0);
}
