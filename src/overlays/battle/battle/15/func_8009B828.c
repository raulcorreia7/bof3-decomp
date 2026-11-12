#include "battle_15.h"

/* arms every idle battler slot and starts the battle phase when the
 * battle scene has not been entered yet.
 */
/* FAKE: retail reads g_Battle.state as volatile. */
MATCH void func_8009B828(void) {
    u8 i;
    u8 flags;

    if (g_AreaCameraMoving == 0) {
        func_801DAAE4();
        i = 0;
        /* FAKE: keeps i = 0 beside the call so it fills the jal delay slot;
         * pure-C best 91.25%, without this barrier 97.47%. */
        FAKE_BARRIER();
        while (i < g_Battle.party_count) {
            if (!Battle_SlotIsBlocked(i)) {
                flags                         = g_Game.members[i].facing;
                g_Game.members[i].header.mode = 2;
                g_Game.members[i].facing      = flags ^ 0x2;
                /* FAKE: keeps the slot argument move in the jal delay slot;
                 * pure-C best 91.25%, without this barrier 93.75%. */
                FAKE_BARRIER();
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
        LOHU(*(volatile u16*)&g_Battle.state) |= 8;
    }
}
