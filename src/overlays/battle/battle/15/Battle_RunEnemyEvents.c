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
    u8                 enemy_slot;
    u8                 i;
    u8                 other_enemy;
    u8                 count;

    for (enemy_slot = 0; enemy_slot < 8; enemy_slot++) {
        if (Battle_SlotIsBlocked((u8)(enemy_slot + 3)) != 0) {
            continue;
        }

        enemy = &g_BattleEnemyBattlers[enemy_slot];
        for (i = 0; i < ENEMY_AI_COUNT; i++) {
            packet = &BATTLE_ENEMY_EVENTS[g_BattleEnemyBattlers[enemy_slot].type].packets[i];
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
                    for (other_enemy = 0; other_enemy < 8; other_enemy++) {
                        if (Battle_SlotIsBlocked((u8)(other_enemy + 3)) == 0 && (g_BattleEnemyBattlers[other_enemy].status & STATUS_LOW_HP) != 0) {
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
                    BATTLE_UPDATE_ENEMY_EVENT(enemy->ap > enemy->stats.max_ap / 2);
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
                    BATTLE_UPDATE_ENEMY_EVENT(func_8009C794(i, enemy_slot));
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
