#include "area133_13.h"
#include "area/spad.h"

MATCH void func_801F2CEC(void) {
    u8  index;
    s16 y;
    s16 x;
    u8  selection;
    s32 result;

    TASK_SET((u8*)g_Game.members);
    index     = g_PartyFieldOrder[0];
    y         = g_Game.members[0].unk_30.signed_half;
    x         = g_Game.members[0].unk_2E.signed_half;
    selection = D_801F2DD4[index];
    result    = Actor_ClaimSlot(3, 0, selection, x, y);
    if ((u8)result != 0xFF) {
        g_Task->param.unk_0B = result;
    }
}
