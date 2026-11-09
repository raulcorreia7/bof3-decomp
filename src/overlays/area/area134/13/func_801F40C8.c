#include "area134_13.h"

MATCH void func_801F40C8(void) {
    Actor* actor;
    u8*    state;

    state = &D_80146865;
    if (*state == 0xFE) {
        func_80196070();
    }
    actor          = g_Task;
    g_Game.current = (PartyMember*)&D_80146110;
    TASK_SET(&D_80146110);
    if (g_Game.members[2].pos.x.fixed > 0x33FFFF) {
        *state     = 0xFF;
        D_80146866 = 0;
        D_80146867 = 0;
        D_80146875 = 0x14;
        TASK_SET(actor);
        func_80196070();
    } else {
        TASK_SET(actor);
        if (g_Task->timer-- == 0) {
            D_80146876          = 0;
            g_Task->header.mode = 1;
        }
    }
}
