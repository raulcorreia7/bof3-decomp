#include "battle_03.h"

u8 Battle_EndRound(void);
u8 Battle_StepBattlers(void);

MATCH void func_801D5024(void) {
    switch (g_Battle.phase.sub_step) {
        case 0: {
            u8* counter = &g_Battle.phase.sub_step;

            *counter += 1;
            if (Battle_EndRound() != 0) {
                return;
            }
            *counter += 1;
        }
        /* fall through */
        case 2: {
            u8* counter = &g_Battle.phase.sub_step;

            *counter += 1;
            if (func_801D54F8() != 0) {
                return;
            }
        }
        /* fall through */
        case 3: {
            u8* counter = &g_Battle.phase.sub_step;

            *counter += 1;
            if (func_801D5658() != 0) {
                return;
            }
        }
        /* fall through */
        case 4: {
            u8* counter = &g_Battle.phase.sub_step;

            *counter += 1;
            if (func_801D57AC() != 0) {
                return;
            }
        }
        /* fall through */
        case 5: {
            u8* counter = &g_Battle.phase.sub_step;

            *counter += 1;
            if (func_801D590C() != 0) {
                return;
            }
        }
        /* fall through */
        case 6: {
            u8* counter = &g_Battle.phase.sub_step;

            *counter += 1;
            if (func_801D5A60() != 0) {
                return;
            }
        }
        /* fall through */
        case 7: {
            u8* counter = &g_Battle.phase.sub_step;

            *counter += 1;
            if (func_801D5BC0() != 0) {
                return;
            }
            *counter += 1;
        }
        /* fall through */
        case 9: {
            u8* counter = &g_Battle.phase.sub_step;

            *counter += 1;
            if (Battle_ApplyTurnDamage() != 0) {
                return;
            }
            *counter += 1;
        }
        /* fall through */
        case 11: {
            u8* counter = &g_Battle.phase.sub_step;

            *counter += 1;
            if (Battle_StepBattlers() != 0) {
                return;
            }
            *counter += 1;
            goto advance; /* shared tail with case 13 */
        }
        case 1:
        case 8:
        case 10:
        case 12: {
            u8  counter;
            u16 battle_flags;

            if (D_801463C2 == 0) {
                counter      = g_BattleSubStep;
                battle_flags = g_BattleState;
                counter += 1;
                battle_flags &= 0xFFFB;
                g_Battle.state          = battle_flags;
                g_Battle.phase.sub_step = counter;
            }
            return;
        }
        case 13:
        advance:
            g_BattleSubStep = 0;
            {
                u8* step;

                step = &g_Battle.phase.step;
                *step += 1;
            }
            return;
    }
}
