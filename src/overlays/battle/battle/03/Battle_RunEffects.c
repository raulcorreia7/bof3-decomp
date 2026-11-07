#include "battle_03.h"

/* Dispatches each active queued slot through its selected handler.
 */
/* func_801E5824 */
MATCH void Battle_RunEffects(void) {
    BattleEffectStages handlers;
    Callback*          funcs;
    u8*                slot;
    s32                offset;
    u32                work;
    s32                i;

    handlers = g_BattleEffectStages;
    i        = 0;
    funcs    = handlers.handlers;
    slot     = (u8*)g_BattleEffects;
    offset   = 0;
    do {
        if (((u8*)g_BattleEffects)[offset] != 0u) {
            work       = *(u32*)(D_801EC3A4 + offset);
            D_801EC2E0 = (BattleEffect*)slot;
            TASK_SET((PartyBattler*)slot);
            g_BattleEffectBattler = (PartyBattler*)(work);
            funcs[slot[0x06]]();
        }
        slot += 0x78;
        i += 1;
        offset += 0x78;
    } while (i < BATTLE_EFFECT_COUNT);
}
