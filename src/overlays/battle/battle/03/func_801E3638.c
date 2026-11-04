#include "battle_03.h"

/* runs the work area's step handler (D_801EB3FC[unk_02]); while bit 0x20 of the enemy's reach is set it
 * steps the active queued slot's signed level (flipping at 12 and -12) and sets the area's unk_34 or unk_38 from the
 * slot word plus level << 9; calls func_801E30F8 unless bit 0x1000 of unk_100 is set.
 */
MATCH void func_801E3638(void) {
    PartyBattler* work;

    D_801EB3FC[g_SpadWork->unk_02]();
    if (g_BattleCurrentEnemy->status_82 & STATUS_CONFUSED) {
        if (g_BattleCurrentEnemy->flags_100 & 0x800) {
            if ((s8)++g_BattleEffects[g_SpadWork->slot].unk_09 >= 12) {
                g_BattleCurrentEnemy->flags_100 ^= 0x800;
            }
        } else {
            if ((s8)--g_BattleEffects[g_SpadWork->slot].unk_09 < -11) {
                g_BattleCurrentEnemy->flags_100 ^= 0x800;
            }
        }
        work = g_SpadWork;
        if (work->word_08.byte.unk_08 == 1 || work->word_08.byte.unk_08 == 3) {
            work->coord_x_34.raw =
                g_BattleEffects[work->slot].unk_34.raw + ((s8)g_BattleEffects[work->slot].unk_09 << 9);
        } else {
            work->coord_y_38.raw =
                g_BattleEffects[work->slot].unk_38.raw + ((s8)g_BattleEffects[work->slot].unk_09 << 9);
        }
    }
    if (!(g_BattleCurrentEnemy->flags_100 & COMBATANT_FLAG_SKIP_ACTION_STEP)) {
        func_801E30F8();
    }
}
