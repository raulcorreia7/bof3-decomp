#include "battle_15.h"

MATCH void func_800A4C70(void) {
    u8*          flag;
    /* The state byte is accessed through a volatile view: retail orders the
     * counter load before this RMW and this store before the counter store. */
    volatile u8* state;
    u8           count;

    flag = &D_80148624;
    if ((*flag & 0x1) == 0) {
        *flag = 0;
        Menu_OpenPanelTask(0x12, 5);
        D_801485BA                               = 2;
        D_801485BC                               = -0xA5;
        g_BattlePanelMode                        = 0;
        D_801485BE                               = 0x3F;
        g_BattleTargetCursorCol                  = 0;
        D_801485CA                               = 0;
        D_801EB5B4[((D_801EC328 - 1) & 0xF) * 2] = Message_GetText(0x59);
        count                                    = g_BattleUIState + 1;
        state                                    = &g_Battle.row_cursor;
        *state |= 0x80;
        g_BattleUIState = count;
    }
}
