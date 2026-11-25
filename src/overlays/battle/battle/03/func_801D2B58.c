#include "battle_03.h"

/* The panel row of the acting battler (at g_Battle.active_battler) and of its target (at
 * g_Battle.target_selector): the two coordinates, the height and the record the row stands for. */
#define ACTIVE_X      (*(s16*)(&g_Battle.active_battler + 2))
#define ACTIVE_Y      (*(s16*)(&g_Battle.active_battler + 4))
#define ACTIVE_DEPTH  (*(u16*)(&g_Battle.active_battler + 6))
#define ACTIVE_ACTOR  (*(PartyMember**)(&g_Battle.active_battler + 8))
#define ACTIVE_ACTION (*(void**)(&g_Battle.active_battler + 12))
#define TARGET_X      (*(u16*)(&g_Battle.target_selector + 2))
#define TARGET_Y      (*(u16*)(&g_Battle.target_selector + 4))
#define TARGET_DEPTH  (*(u16*)(&g_Battle.target_selector + 6))
#define TARGET_ACTOR  (*(PartyMember**)(&g_Battle.target_selector + 8))
#define TARGET_ACTION (*(void**)(&g_Battle.target_selector + 12))

/* Advances the battle actor: takes the next actor from the turn table, writes the panel rows of
 * the actor and of its target, and copies the actor's stats into the damage-calculation pair.
 */
#ifdef NON_MATCHING
NON_MATCHING void func_801D2B58(void) {
    PartyMember* actor;
    u8           id;
    u8           target;
    s32          index;
    s32          enemy;
    s8           dx;
    s8           dy;

    while (g_Battle.turn_cursor < g_Battle.turn_count) {
        if (g_Battle.turn_order[g_Battle.turn_cursor] == 0xFF) {
            g_Battle.turn_cursor++;
            continue;
        }
        id = g_Battle.turn_order[g_Battle.turn_cursor];

        if (id < 3) {
            func_800AB0B8(id);
        } else {
            func_801E25E0(id - 3);
        }
        g_Battle.active_battler = id;

        if (id < 3) {
            ACTIVE_ACTION        = &g_Game.members[id].u.turn.command.target;
            ACTIVE_ACTOR         = &g_Game.members[id];
            actor                = D_8014637C;
            index                = g_Game.members[id].chr.character_id * 8 + actor->facing * 2;
            dx                   = g_BattlePanelOffsets[index];
            ACTIVE_X             = actor->screen_x.value + dx;
            index                = actor->facing * 2 + g_Game.members[id].chr.character_id * 8;
            dy                   = D_801EB0B1[index];
            ACTIVE_Y             = actor->screen_y.value + dy;
            ACTIVE_DEPTH         = actor->depth;
            g_BattleCalcStats[1] = g_Game.members[id].chr.stats;
        } else {
            ACTIVE_ACTION        = &ENEMY_COMBATANT(id).turn.command.target;
            ACTIVE_ACTOR         = (PartyMember*)&ENEMY_COMBATANT(id);
            enemy                = id - 3;
            dx                   = g_BattleEnemyBattlers[enemy].panel_offset_x;
            actor                = D_8014637C;
            ACTIVE_X             = actor->screen_x.value + dx;
            dy                   = g_BattleEnemyBattlers[enemy].panel_offset_y;
            ACTIVE_Y             = actor->screen_y.value + dy;
            ACTIVE_DEPTH         = actor->depth;
            g_BattleCalcStats[1] = g_BattleEnemyBattlers[enemy].stats;
        }

        target = g_Battle.target_selector;
        if (target < 3) {
            TARGET_ACTOR  = &g_Game.members[target];
            TARGET_ACTION = &g_Game.members[target].u.turn.command.target;
            actor         = g_BattleSelectedActor;
            index         = g_Game.members[target].chr.character_id * 8 + actor->facing * 2;
            dx            = g_BattlePanelOffsets[index];
            TARGET_X      = actor->screen_x.value + dx;
            index         = g_Game.members[target].chr.character_id * 8 + actor->facing * 2;
            dy            = D_801EB0B1[index];
            TARGET_Y      = actor->screen_y.value + dy;
            TARGET_DEPTH  = actor->depth;
        } else {
            TARGET_ACTOR  = (PartyMember*)(g_BattleEnemies + target * BATTLE_ENEMY_STRIDE);
            TARGET_ACTION = &ENEMY_COMBATANT(target).turn.command.target;
            enemy         = target - 3;
            dx            = g_BattleEnemyBattlers[enemy].panel_offset_x;
            actor         = g_BattleSelectedActor;
            TARGET_X      = actor->screen_x.value + dx;
            dy            = g_BattleEnemyBattlers[enemy].panel_offset_y;
            TARGET_Y      = actor->screen_y.value + dy;
            TARGET_DEPTH  = actor->depth;
        }
        g_Battle.phase.sub_step++;
        g_Battle.turn_cursor++;
        return;
    }
    g_Battle.phase.mode = BATTLE_MODE_ROUND_END;
    g_Battle.phase.step = 0;
}
#else
INCLUDE_ASM(func_801D2B58);
#endif
