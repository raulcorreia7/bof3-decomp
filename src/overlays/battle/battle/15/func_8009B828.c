#include "battle_15.h"

/* arms every idle battler slot and starts the battle phase when the
 * battle scene has not been entered yet.
 */
/* FAKE: retail reads g_BattleState as volatile. */
MATCH void func_8009B828(void) {
    u8 i;
    u8 flags;

    if (LOBU(g_AreaCameraMoving) == 0) {
        func_801DAAE4();
        i = 0;
        /* FAKE: keeps i = 0 beside the call so it fills the jal delay slot;
         * pure-C best 91.25%, without this barrier 97.47%. */
        MATCH_BARRIER();
        while (i < g_BattlePartyCount) {
            if (!Battle_SlotIsBlocked(i)) {
                flags                                        = g_BattlePartyBattlers[i].word_08.byte.unk_08;
                g_BattlePartyBattlers[i].step_01             = 2;
                g_BattlePartyBattlers[i].word_08.byte.unk_08 = flags ^ 2;
                /* FAKE: keeps the slot argument move in the jal delay slot;
                 * pure-C best 91.25%, without this barrier 93.75%. */
                MATCH_BARRIER();
                func_801DDFEC(i);
                func_801DD14C(i);
            }
            i++;
        }
        func_801D9484();
        func_801DE560(2, 0, 0, 0x2D, Resource_GetText(0xF));
        g_BattleMode    = 3;
        g_BattleStep    = 0;
        g_BattleSubStep = 0;
        g_BattleUiStep  = 0;
        g_BattleUiState = 0;
        LOHU(*(volatile u16*)&g_BattleState) |= 8;
    }
}
