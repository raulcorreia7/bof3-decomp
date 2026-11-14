/* Sets the step kind from the cell under the lead party member's next position (1, 2 or 3 for cell codes 0xA1, 0xA0 or 0xAE, 4 for a walk transition, else 0), then runs the handler of the current mode. */
/* AREA_RUN_CELL_TYPE_STEP (area065 0x801F2F24, area087 0x801F2F20, area088 0x801F3A50, area115 0x801F2EF0, area121
 * 0x801F2F04) */
/* The step stores after the cell test re-read the work cell: the compiler must assume a call may have changed it.
 * A statement macro: the inline form moves bytes. */
#define AREA_RUN_CELL_TYPE_STEP(HANDLERS)                                                                    \
    s32    x;                                                                                                \
    s32    y;                                                                                                \
    s32    scaled;                                                                                           \
    Actor* work;                                                                                             \
    scaled   = g_Game.members[0].unk_0C * g_Game.members[0].unk_09;                                          \
    x        = FIX_INT(g_Game.members[0].pos.x.fixed + scaled);                                              \
    y        = FIX_INT(g_Game.members[0].pos.y.fixed + g_Game.members[0].unk_10 * g_Game.members[0].unk_09); \
    work     = g_Task;                                                                                       \
    work->vx = x;                                                                                            \
    work->vy = y;                                                                                            \
    if ((Area_GetCellCode(x, y) & BYTE_MASK) == 0xA1) {                                                      \
        g_Task->param.unk_0B = 1;                                                                            \
    } else if ((Area_GetCellCode(x, y) & BYTE_MASK) == 0xA0) {                                               \
        g_Task->param.unk_0B = 2;                                                                            \
    } else if ((Area_GetCellCode(x, y) & BYTE_MASK) == 0xAE) {                                               \
        g_Task->param.unk_0B = 3;                                                                            \
    } else if (g_Game.walk_flags & AREA_WALK_TRANSITION) {                                                   \
        g_Task->param.unk_0B = 4;                                                                            \
    } else {                                                                                                 \
        g_Task->param.unk_0B = 0;                                                                            \
    }                                                                                                        \
    HANDLERS[g_Task->header.mode]();
