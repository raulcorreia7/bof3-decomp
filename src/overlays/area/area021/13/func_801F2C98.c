#include "area021_13.h"

MATCH void func_801F2C98(void) {
    u16 value;
    s32 amount;
    u8  count;

    if (g_MessageChoice == 0) {
        if (Item_Count(0, 3, 0) != 0) {
            amount = (g_ScriptVars[3] != 0) ? (g_ScriptVars[3] * 10 + 10) : 10;
            sprintf(g_TextVariables[1], D_801F2C04, amount);
            g_MessageRequest = MSG_048;
            Party_AddZenny(amount, 0);
            Item_Remove(0, 3, 1, 0);
            SYS_SetFlag(g_SceneFlags, 0x12);
            return;
        }
        value = MSG_050;
    } else {
        count           = g_ScriptVars[3] + 1;
        g_ScriptVars[3] = count;
        if (count == 8) {
            value           = MSG_052;
            g_ScriptVars[3] = 0;
        } else {
            value = MSG_049;
        }
    }
    g_MessageRequest = value;
}
