#include "battle_03.h"

/* The panel rows of the acting battler and of its target, inside g_Battle. */
#define ACTIVE_X      (*(s16*)(g_Battle.unk_96 + 0))
#define ACTIVE_Y      (*(s16*)(g_Battle.unk_96 + 2))
#define ACTIVE_DEPTH  (*(u16*)(g_Battle.unk_96 + 4))
#define ACTIVE_STATE  (*(void**)(g_Battle.unk_96 + 6))
#define ACTIVE_ACTION (*(void**)&g_Battle.action)
#define TARGET_X      (*(s16*)(g_Battle.unk_A5 + 1))
#define TARGET_Y      (*(s16*)(g_Battle.unk_A5 + 3))
#define TARGET_DEPTH  (*(u16*)(g_Battle.unk_A5 + 5))
#define TARGET_STATE  (*(void**)(g_Battle.unk_A5 + 7))
#define TARGET_ACTION (*(void**)&g_Battle.unk_B0[0])

/* Advances the battle actor: picks the next actor from the turn
 * table, writes its panel rows and copies the actor state into the battle
 * state block.
 */
#ifdef NON_MATCHING
NON_MATCHING void func_801D2B58(void) {
    PartyMember* actor;
    Stats*       stats;
    s32          enemy;
    s32          index;
    u8           id;
    u8           value;
    s8           dx;
    s8           dy;

    while (g_Battle.turn_cursor < g_Battle.turn_count) {
        id = g_Battle.turn_order[g_Battle.turn_cursor];

        if (id == GAME_NONE) {
            g_Battle.turn_cursor++;
            continue;
        }
        id = value;

        if (value < 3) {
            /* FAKE: the callee reads one argument. */
            ((void (*)(s32))func_800AB0B8)(value);
        } else {
            func_801E25E0(id - 3);
        }
        g_Battle.active_battler = id;
        if (id < 3) {
            ACTIVE_ACTION = &g_Game.members[id].u.turn.command.target;
            ACTIVE_STATE  = &g_Game.members[id];
            actor         = (PartyMember*)D_8014637C;
            index         = g_Game.members[id].chr.character_id * 8 + actor->facing * 2;
            dx            = g_BattlePanelOffsets[index];
            ACTIVE_X      = actor->unk_2E.value + dx;
            index         = actor->facing * 2 + g_Game.members[id].chr.character_id * 8;
            dy            = D_801EB0B1[index];
            ACTIVE_Y      = actor->unk_30.value + dy;
            ACTIVE_DEPTH  = actor->depth;
            stats         = (Stats*)((u8*)&g_Game.members[id] + 0x90);
        } else {
            ACTIVE_ACTION = &ENEMY_COMBATANT(id).turn.command.target;
            ACTIVE_STATE  = &ENEMY_COMBATANT(id);
            enemy         = id - 3;
            dx            = g_BattleEnemyBattlers[enemy].panel_offset_x;
            actor         = (PartyMember*)D_8014637C;
            ACTIVE_X      = actor->unk_2E.value + dx;
            dy            = g_BattleEnemyBattlers[enemy].panel_offset_y;
            ACTIVE_Y      = actor->unk_30.value + dy;
            ACTIVE_DEPTH  = actor->depth;
            stats         = (Stats*)&g_BattleEnemyBattlers[enemy].stats;
        }
        *(Stats*)D_801EC308 = *stats;

        id = LOBU(g_Battle.target_selector);
        if (id < 3) {
            TARGET_STATE  = &g_Game.members[id];
            TARGET_ACTION = &g_Game.members[id].u.turn.command.target;
            actor         = g_BattleSelectedActor;
            index         = g_Game.members[id].chr.character_id * 8 + actor->facing * 2;
            dx            = g_BattlePanelOffsets[index];
            TARGET_X      = actor->unk_2E.value + dx;
            index         = actor->facing * 2 + g_Game.members[id].chr.character_id * 8;
            dy            = D_801EB0B1[index];
            TARGET_Y      = actor->unk_30.value + dy;
            TARGET_DEPTH  = actor->depth;
        } else {
            TARGET_STATE  = g_BattleEnemies + id * 0x118;
            TARGET_ACTION = &ENEMY_COMBATANT(id).turn.command.target;
            enemy         = id - 3;
            dx            = g_BattleEnemyBattlers[enemy].panel_offset_x;
            actor         = g_BattleSelectedActor;
            TARGET_X      = actor->unk_2E.value + dx;
            dy            = g_BattleEnemyBattlers[enemy].panel_offset_y;
            TARGET_Y      = actor->unk_30.value + dy;
            TARGET_DEPTH  = actor->depth;
        }
        g_Battle.phase.sub_step++;
        g_Battle.turn_cursor += 1;
        return;
    }
    g_Battle.phase.mode = BATTLE_MODE_ROUND_END;
    g_Battle.phase.step = 0;
}
#else
INCLUDE_ASM(func_801D2B58);
#endif
