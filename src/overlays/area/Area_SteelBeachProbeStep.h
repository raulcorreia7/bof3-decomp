/* On the Steel Beach map, when PROBE accepts the actor's cell: runs the field reset calls, lowers the timer, flags field mode 1, sets step 1 and returns 1; otherwise returns 0. */
/* AREA_STEEL_BEACH_PROBE_STEP (area104 0x801F4D24, area121 0x801F5268) */
#define AREA_STEEL_BEACH_PROBE_STEP(PROBE)                                                                                                                                               \
    if ((g_GameAreaId != AREA_ID_STEEL_BEACH_MAP) || !(PROBE(g_Task->pos.x.fixed, g_Task->pos.y.fixed, Actor_FindInRange(g_Task->pos.x.fixed, g_Task->pos.y.fixed, 1) & 0xFF) & 0xFF)) { \
        return 0;                                                                                                                                                                        \
    }                                                                                                                                                                                    \
    func_801C24D0();                                                                                                                                                                     \
    g_Task->timer -= 1;                                                                                                                                                                  \
    Actor_UpdateMovement();                                                                                                                                                              \
    g_Game.current->u.field.mode_12B.s8_value = 1;                                                                                                                                       \
    g_Task->header.step                       = 1;                                                                                                                                       \
    return 1;
