#include "battle_03.h"

/* clears the work record's 0x40 flag and advances the step word by 0x2000 until it reaches 0x10000; on
 * completion it clears the 0x48 byte, drops the 0x2000 flag on the owner's damage row and the low suppress bits, then
 * runs the queued step.
 */
MATCH void func_801E8558(void) {
    PartyBattler* work;
    PartyBattler* stage;
    u32           step;

    D_801EB4E0->header.flags &= ~ACTOR_FLAG_HIDDEN;
    stage = D_801EB4E0;
    step  = stage->scale.x;
    if (step != 0x10000) {
        stage->scale.x = step + 0x2000;
        return;
    }
    stage->unk_48 = 0;
    work          = D_801EB4E0;
    g_BattlePartyBattlers[work->slot].damage_flags.value &= ~0x2000u;
    g_BattlePartyBattlers[work->slot].action_flags.value &= 0xFFFCFFF9u;
    func_801E5988();
}
