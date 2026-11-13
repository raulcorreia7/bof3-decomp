#include "area134_13.h"
#include <rand.h>

MATCH void func_801F3E8C(void) {
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
        *state              = D_801F5724[RANDOM_MASK(0xF)];
        g_Task->header.mode = 2;
    }
}
