#include "battle_03.h"

/* runs the work area's step handler (D_801EB3FC[unk_02]); while bit 0x20 of the enemy's reach is set it
 * steps the active queued slot's signed level (flipping at 12 and -12) and sets the area's unk_34 or unk_38 from the
 * slot word plus level << 9; calls func_801E30F8 unless bit 0x1000 of unk_100 is set.
 */
MATCH void func_801E3638(void) {
    PartyBattler* work;

    D_801EB3FC[g_Task->step]();
    if (g_BattleCurrentEnemy->status_82 & STATUS_CONFUSED) {
        if (g_BattleCurrentEnemy->flags_100 & 0x800) {
            if ((s8)++g_BattleEffects[g_Task->slot].unk_09 >= 12) {
                g_BattleCurrentEnemy->flags_100 ^= 0x800;
            }
        } else {
            if ((s8)--g_BattleEffects[g_Task->slot].unk_09 < -11) {
                g_BattleCurrentEnemy->flags_100 ^= 0x800;
            }
        }
        work = g_Task;
        if (work->facing == 1 || work->facing == 3) {
            work->x.raw = g_BattleEffects[work->slot].unk_34.raw + ((s8)g_BattleEffects[work->slot].unk_09 << 9);
        } else {
            work->y.raw = g_BattleEffects[work->slot].unk_38.raw + ((s8)g_BattleEffects[work->slot].unk_09 << 9);
        }
    }
    if (!(g_BattleCurrentEnemy->flags_100 & COMBATANT_FLAG_SKIP_ACTION_STEP)) {
        func_801E30F8();
    }
}
