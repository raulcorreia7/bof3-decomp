#include "battle_15.h"

/* resets the stats of the first three battlers from the template at 0x801EBEF0: hit points
 * scaled down by fatigue, the other stats raised by the template, resistances copied.
 */
MATCH void func_800A4458(void) {
    BattleStatDisplayTemplate* tpl;
    PartyBattler*              work;
    u8                         slot;
    s16                        template_hp;
    s16                        max_hp;
    s16                        stat;
    u8                         res;

    slot = 0;
    tpl  = (BattleStatDisplayTemplate*)((u8*)&g_BattleMessageSlot - 0x18);

    do {
        if (g_BattlePartyBattlers[slot].turn.action_flags.value & 2) {
            template_hp = tpl->max_hp;
            max_hp      = template_hp - ((template_hp * g_BattlePartyBattlers[slot].chr.fatigue + 5) / 10);
            work        = &g_BattlePartyBattlers[slot];

            work->chr.base.max_hp                        = max_hp;
            stat                                         = g_BattlePartyBattlers[slot].chr.base.power;
            g_BattlePartyBattlers[slot].chr.stats.max_hp = max_hp;

            stat                                        = stat + tpl->power;
            work->chr.base.power                        = stat;
            g_BattlePartyBattlers[slot].chr.stats.power = stat;

            stat                                          = g_BattlePartyBattlers[slot].chr.base.defense + tpl->defense;
            work->chr.base.defense                        = stat;
            g_BattlePartyBattlers[slot].chr.stats.defense = stat;

            stat                                          = g_BattlePartyBattlers[slot].chr.base.agility + tpl->agility;
            work->chr.base.agility                        = stat;
            g_BattlePartyBattlers[slot].chr.stats.agility = stat;

            stat                     = g_BattlePartyBattlers[slot].chr.base.intellect + tpl->intellect;
            work->chr.base.intellect = stat;
            g_BattlePartyBattlers[slot].chr.stats.intellect = stat;

            res                                                  = tpl->resistances[0];
            work->chr.base.resistances[0]                        = res;
            g_BattlePartyBattlers[slot].chr.stats.resistances[0] = res;
            res                                                  = tpl->resistances[1];
            work->chr.base.resistances[1]                        = res;
            g_BattlePartyBattlers[slot].chr.stats.resistances[1] = res;
            res                                                  = tpl->resistances[2];
            work->chr.base.resistances[2]                        = res;
            g_BattlePartyBattlers[slot].chr.stats.resistances[2] = res;
            res                                                  = tpl->resistances[3];
            work->chr.base.resistances[3]                        = res;
            g_BattlePartyBattlers[slot].chr.stats.resistances[3] = res;
            res                                                  = tpl->resistances[4];
            work->chr.base.resistances[4]                        = res;
            g_BattlePartyBattlers[slot].chr.stats.resistances[4] = res;
            res                                                  = tpl->resistances[5];
            work->chr.base.resistances[5]                        = res;
            g_BattlePartyBattlers[slot].chr.stats.resistances[5] = res;
            res                                                  = tpl->resistances[6];
            work->chr.base.resistances[6]                        = res;
            g_BattlePartyBattlers[slot].chr.stats.resistances[6] = res;
            res                                                  = tpl->resistances[7];
            work->chr.base.resistances[7]                        = res;
            g_BattlePartyBattlers[slot].chr.stats.resistances[7] = res;
            res                                                  = tpl->resistances[8];
            work->chr.base.resistances[8]                        = res;
            g_BattlePartyBattlers[slot].chr.stats.resistances[8] = res;
        }
        slot++;
    } while (BATTLER_IS_PLAYER(slot));
}
