#ifndef BMAGIC_RUN_EFFECT_STEP_H
#define BMAGIC_RUN_EFFECT_STEP_H

/* Runs the effect step the work step byte selects with the battle script table installed, then adds the
 * actor once the effect starts. The image passes its two step callbacks. A statement macro: the local
 * table must be the first statement of the function body. */
/* func_801EFAE0 (magic003), func_801EFAF4 (magic020) */
#define BMAGIC_RUN_EFFECT_STEP(FIRST, SECOND)                    \
    Callback table[2] = {FIRST, SECOND};                         \
    g_Scripts         = BATTLE_SCRIPT_TABLE;                     \
    table[g_Task->header.step]();                                \
    if (g_Task->header.flags != 0 && g_Task->header.step != 0) { \
        Area_AddActor();                                         \
    }                                                            \
    g_Scripts = AREA_SCRIPT_TABLE

#endif
