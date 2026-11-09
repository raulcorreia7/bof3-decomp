#include "battle_03.h"

/* Dispatches each active queued slot through its selected handler.
 */
/* func_801E5824 */
MATCH void Battle_UpdateEffects(void) {
    BattleEffectStages handlers;
    Callback*          funcs;
    BattleEffect*      effect;
    PartyMember*       target;
    s32                i;

    handlers = g_BattleEffectStages;
    i        = 0;
    funcs    = handlers.handlers;
    effect   = g_BattleEffects;
    do {
        if (g_BattleEffects[i].header.flags != 0u) {
            target     = g_BattleEffects[i].target.party;
            D_801EC2E0 = effect;
            TASK_SET(effect);
            g_BattleEffectBattler = target;
            funcs[effect->unk_06]();
        }
        effect++;
        i += 1;
    } while (i < BATTLE_EFFECT_COUNT);
}
