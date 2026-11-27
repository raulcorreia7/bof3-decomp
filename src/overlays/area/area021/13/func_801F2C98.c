#include "area021_13.h"

MATCH void func_801F2C98(void) {
    u16 value;
    s32 amount;
    u8  count;

    if (g_UIMessageChoice == 0) {
        if (Item_Count(ITEM_CATEGORY_ITEM, ITEM_HEALING_HERB, 0) != 0) {
            amount = (g_ScriptVars[3] != 0) ? (g_ScriptVars[3] * 10 + 10) : 10;
            sprintf(g_TextVariables[1], D_801F2C04, amount);
            g_UIMessageRequest = MSG_AREA021_SOLD_HERB_THANKS;
            Party_AddZenny(amount, 0);
            Item_Remove(ITEM_CATEGORY_ITEM, ITEM_HEALING_HERB, 1, 0);
            SYS_SetFlag(g_SceneFlags, 0x12);
            return;
        }
        value = MSG_AREA021_NO_HERB;
    } else {
        count           = g_ScriptVars[3] + 1;
        g_ScriptVars[3] = count;
        if (count == 8) {
            value           = MSG_AREA021_HELP_REFUSED;
            g_ScriptVars[3] = 0;
        } else {
            value = MSG_AREA021_ASK_HELP_HERB;
        }
    }
    g_UIMessageRequest = value;
}
