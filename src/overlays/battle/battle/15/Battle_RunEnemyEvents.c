#include "battle_15.h"

#define BATTLE_UPDATE_ENEMY_EVENT(condition)                    \
    do {                                                        \
        if (condition) {                                        \
            if (Battle_EnemyEventTriggered(enemy, i) == 0) {    \
                Battle_ApplyEnemyEvent(enemy, packet);          \
                Battle_SetEnemyEventTriggered(enemy, i, 1);     \
            }                                                   \
        } else if (Battle_EnemyEventTriggered(enemy, i) != 0) { \
            Battle_SetEnemyEventTriggered(enemy, i, 0);         \
        }                                                       \
    } while (0)

/* func_8009BFC4 */
#ifdef NON_MATCHING
NON_MATCHING void Battle_RunEnemyEvents(void) {
    BattleEventPacket* packet;
    EnemyBattler*      enemy;
    u8                 row;
    u8                 i;
    u8                 other;
    u8                 count;

    for (row = 0; row < 8; row++) {
        if (Battle_SlotIsBlocked(row + 3) != 0) {
            continue;
        }

        enemy = &g_BattleEnemyBattlers[row];
        for (i = 0; i < ENEMY_AI_COUNT; i++) {
            packet = &BATTLE_ENEMY_EVENTS[enemy->type].packets[i];
            switch (packet->type) {
                case 11:
                    BATTLE_UPDATE_ENEMY_EVENT(enemy->hp <= enemy->stats.max_hp / 4);
                    break;
                case 12:
                    BATTLE_UPDATE_ENEMY_EVENT(enemy->hp <= enemy->stats.max_hp / 2);
                    break;
                case 13:
                    BATTLE_UPDATE_ENEMY_EVENT(enemy->ap <= enemy->stats.max_ap / 10);
                    break;
                case 14:
                    count = 0;
                    for (other = 0; other < 8; other++) {
                        if (Battle_SlotIsBlocked(other + 3) == 0 && (g_BattleEnemyBattlers[other].status & STATUS_LOW_HP) != 0) {
                            count++;
                        }
                    }
                    BATTLE_UPDATE_ENEMY_EVENT(count != 0);
                    break;
                case 15:
                    BATTLE_UPDATE_ENEMY_EVENT(g_Battle.living_enemy_count < g_Battle.enemy_count);
                    break;
                case 16:
                    BATTLE_UPDATE_ENEMY_EVENT(g_Battle.living_enemy_count == 1);
                    break;
                case 17:
                    BATTLE_UPDATE_ENEMY_EVENT(enemy->hp > enemy->stats.max_hp / 2);
                    break;
                case 18:
                    BATTLE_UPDATE_ENEMY_EVENT(enemy->ap <= enemy->stats.max_ap / 2);
                    break;
                case 19:
                    BATTLE_UPDATE_ENEMY_EVENT(*(u32*)&g_Battle.unk_EF[1] == 2);
                    break;
                case 20:
                    BATTLE_UPDATE_ENEMY_EVENT(*(u32*)&g_Battle.unk_EF[1] == 10);
                    break;
                case 21:
                    BATTLE_UPDATE_ENEMY_EVENT((s32)g_Game.members[0].chr.level - enemy->level >= 6);
                    break;
                case 25:
                    BATTLE_UPDATE_ENEMY_EVENT((*(u32*)&g_Battle.unk_EF[1] & 1) == 0);
                    break;
                case 26:
                    BATTLE_UPDATE_ENEMY_EVENT((*(u32*)&g_Battle.unk_EF[1] & 1) != 0);
                    break;
                case 27:
                    BATTLE_UPDATE_ENEMY_EVENT(*(u32*)&g_Battle.unk_EF[1] % 3 == 0);
                    break;
                case 28:
                    BATTLE_UPDATE_ENEMY_EVENT(*(u32*)&g_Battle.unk_EF[1] % 3 != 0);
                    break;
                case 29:
                    BATTLE_UPDATE_ENEMY_EVENT(g_Battle.living_party_count == 1);
                    break;
                case 30:
                    BATTLE_UPDATE_ENEMY_EVENT(g_Battle.living_party_count != 1);
                    break;
                case 31:
                    BATTLE_UPDATE_ENEMY_EVENT(g_Battle.living_enemy_count == g_Battle.enemy_count);
                    break;
                case 32:
                    BATTLE_UPDATE_ENEMY_EVENT(g_Battle.living_enemy_count != 1);
                    break;
                case 38:
                    BATTLE_UPDATE_ENEMY_EVENT(func_8009C794(i, row));
                    break;
                case 39:
                    BATTLE_UPDATE_ENEMY_EVENT(g_Battle.unk_EF[8] == 1);
                    break;
            }
        }
    }
    Battle_MergeEnemyPanels();
}
#else
INCLUDE_ASM(Battle_RunEnemyEvents);
#endif

#undef BATTLE_UPDATE_ENEMY_EVENT
