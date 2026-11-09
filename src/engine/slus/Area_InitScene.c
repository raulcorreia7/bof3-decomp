#include "engine/slus/slus.h"

/* seeds the scratch work area for the incoming scene. */
MATCH void Area_InitScene(void) {
    Actor* work;

    g_Task->unk_05                          = 0;
    g_Task->param.unk_0B                    = g_Game.members[0].status.field.flags_12C.u8_value;
    *(u8*)&g_Game.current->u.turn.hp_change = 3; /* FAKE: retail stores the byte. */
    work                                    = g_Task;
    FIELD(u32, work, 0x34u)                 = g_Game.members[0].pos.x.fixed;
    FIELD(u32, work, 0x38u)                 = g_Game.members[0].pos.y.fixed;
    FIELD(u32, work, 0x3Cu)                 = D_80145ECC;
    work->header.mode                       = work->header.mode + 1;
}
