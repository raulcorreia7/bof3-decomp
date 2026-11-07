#include "battle_15.h"

/* Battle-readiness helper lifted with target emi/battle/battle/03. */
/* EXE-side pointer to the shared battle state record. */

MATCH void func_800A8D3C(void) {
    func_801DEE4C();
    if (g_BattleEffectBattler->header.mode == 5) {
        func_801E5988();
    }
}
