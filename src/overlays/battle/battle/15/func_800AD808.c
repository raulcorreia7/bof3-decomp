#include "battle_15.h"

MATCH void func_800AD808(void) {
    u8*      work;
    Callback funcs[2] = {func_800AD8D8, func_800AD930};

    work = SELF_BYTES;
    funcs[((PartyMember*)work)->header.step]();
    work = SELF_BYTES;
    if (!(((PartyMember*)work)->header.flags & 0x1)) {
        return;
    }
    if (!(g_UiPanelTasks[21].active & 0x1)) {
        ((PartyMember*)work)->header.mode = 2;
        SELF(PartyMember)->header.step    = 0;
        return;
    }
    *(u16*)(work + 0x2E) = D_80148628 + 0x14;
    *(u16*)(work + 0x30) = D_8014862A + 0x12;
    Area_AddActor();
}
