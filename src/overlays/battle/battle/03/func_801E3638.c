#include "battle_03.h"

/* runs the work area's step handler (D_801EB3FC[unk_02]); while bit 0x20 of the enemy's reach is set it
 * steps the active queued slot's signed level (flipping at 12 and -12) and sets the area's unk_34 or unk_38 from the
 * slot word plus level << 9; calls func_801E30F8 unless bit 0x1000 of unk_100 is set.
 */
MATCH void func_801E3638(void) {
    PartyBattler* work;

    D_801EB3FC[g_Task->header.step]();
    if (g_BattleCurrentEnemy->status & STATUS_CONFUSED) {
        if (g_BattleCurrentEnemy->turn.damage_flags.value & COMBATANT_FLAG_UNK_11) {
            if ((s8)++g_BattleEffects[g_Task->slot].unk_09 >= 12) {
                g_BattleCurrentEnemy->turn.damage_flags.value ^= 0x800;
            }
        } else {
            if ((s8)--g_BattleEffects[g_Task->slot].unk_09 < -11) {
                g_BattleCurrentEnemy->turn.damage_flags.value ^= 0x800;
            }
        }
        work = g_Task;
        if (work->facing == FACING_UP || work->facing == FACING_RIGHT) {
            work->pos.x.fixed = g_BattleEffects[work->slot].pos.x.fixed + ((s8)g_BattleEffects[work->slot].unk_09 << 9);
        } else {
            work->pos.y.fixed = g_BattleEffects[work->slot].pos.y.fixed + ((s8)g_BattleEffects[work->slot].unk_09 << 9);
        }
    }
    if (!(g_BattleCurrentEnemy->turn.damage_flags.value & COMBATANT_FLAG_SKIP_ACTION_STEP)) {
        func_801E30F8();
    }
}
