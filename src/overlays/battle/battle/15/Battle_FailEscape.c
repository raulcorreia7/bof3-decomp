#include "battle_15.h"

/* arms every idle battler slot and starts the battle phase when the
 * battle scene has not been entered yet.
 */
/* FAKE: retail reads g_Battle.flags as volatile. */
/* func_8009B828 */
MATCH void Battle_FailEscape(void) {
    u8 i;
    u8 flags;

    if (g_AreaCameraMoving == 0) {
        func_801DAAE4();
        i = 0;
        while (i < g_Battle.party_count) {
            if (!Battle_SlotIsBlocked(i)) {
                flags                         = g_Game.members[i].facing;
                g_Game.members[i].header.mode = 2;
                g_Game.members[i].facing      = flags ^ 0x2;
                func_801DDFEC(i);
                func_801DD14C(i);
            }
            i++;
        }
        func_801D9484();
        func_801DE560(2, 0, 0, 45, Message_GetText(0xF));
        g_BattleMode    = BATTLE_MODE_TURNS;
        g_BattleStep    = 0;
        g_BattleSubStep = 0;
        g_BattleUIStep  = 0;
        g_BattleUIState = 0;
        LOHU(*(volatile u16*)&g_Battle.flags) |= 8;
    }
}
