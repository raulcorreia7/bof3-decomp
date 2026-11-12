#include "area134_13.h"
#include <rand.h>

MATCH void func_801F3F78(void) {
    u8*    state;
    Actor* actor;
    u8*    p;
    u8     val;

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
        Actor_Clear();
        return;
    }
    TASK_SET(actor);
    if (*state == 0) {
        g_Task->timer       = D_801F5724[0x10 + (RANDOM_MASK(0xF))];
        g_Task->header.mode = 3;
        return;
    }
    if (g_InputHeld == (PADLup | PADLright) || g_InputHeld == (PADLright | PADLdown) || g_InputHeld == PADLright) {
        p   = &D_80146866;
        val = *p;
        *p  = val + 1;
        if (val < 0x10) {
            return;
        }
        *p = 0x80;
        Actor_Clear();
    }
}
