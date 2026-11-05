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
        if (g_BattlePartyBattlers[slot].action_flags.value & 2) {
            template_hp = tpl->max_hp;
            max_hp      = template_hp - ((template_hp * g_BattlePartyBattlers[slot].stats.fatigue + 5) / 10);
            work        = &g_BattlePartyBattlers[slot];

            work->stats.base_hp                      = max_hp;
            stat                                     = g_BattlePartyBattlers[slot].stats.base_power;
            g_BattlePartyBattlers[slot].stats.max_hp = max_hp;

            stat                                    = stat + tpl->power;
            work->stats.base_power                  = stat;
            g_BattlePartyBattlers[slot].stats.power = stat;

            stat                                      = g_BattlePartyBattlers[slot].stats.base_defense + tpl->defense;
            work->stats.base_defense                  = stat;
            g_BattlePartyBattlers[slot].stats.defense = stat;

            stat                                      = g_BattlePartyBattlers[slot].stats.base_agility + tpl->agility;
            work->stats.base_agility                  = stat;
            g_BattlePartyBattlers[slot].stats.agility = stat;

            stat                       = g_BattlePartyBattlers[slot].stats.base_intellect + tpl->intellect;
            work->stats.base_intellect = stat;
            g_BattlePartyBattlers[slot].stats.intellect = stat;

            res                                              = tpl->resistances[0];
            work->stats.base_resistances[0]                  = res;
            g_BattlePartyBattlers[slot].stats.resistances[0] = res;
            res                                              = tpl->resistances[1];
            work->stats.base_resistances[1]                  = res;
            g_BattlePartyBattlers[slot].stats.resistances[1] = res;
            res                                              = tpl->resistances[2];
            work->stats.base_resistances[2]                  = res;
            g_BattlePartyBattlers[slot].stats.resistances[2] = res;
            res                                              = tpl->resistances[3];
            work->stats.base_resistances[3]                  = res;
            g_BattlePartyBattlers[slot].stats.resistances[3] = res;
            res                                              = tpl->resistances[4];
            work->stats.base_resistances[4]                  = res;
            g_BattlePartyBattlers[slot].stats.resistances[4] = res;
            res                                              = tpl->resistances[5];
            work->stats.base_resistances[5]                  = res;
            g_BattlePartyBattlers[slot].stats.resistances[5] = res;
            res                                              = tpl->resistances[6];
            work->stats.base_resistances[6]                  = res;
            g_BattlePartyBattlers[slot].stats.resistances[6] = res;
            res                                              = tpl->resistances[7];
            work->stats.base_resistances[7]                  = res;
            g_BattlePartyBattlers[slot].stats.resistances[7] = res;
            res                                              = tpl->resistances[8];
            work->stats.base_resistances[8]                  = res;
            g_BattlePartyBattlers[slot].stats.resistances[8] = res;
        }
        slot++;
    } while (BATTLER_IS_PLAYER(slot));
}
