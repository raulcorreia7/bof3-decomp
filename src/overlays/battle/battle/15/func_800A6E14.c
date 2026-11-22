#include "battle_15.h"

s8   func_800A7648(s8 index);
void func_800A7694(s8 affinity_0, s8 affinity_1, s8 affinity_2, s8 affinity_3, s8 affinity_4);
void func_800A78B8(void);

/* Rebuilds the dragon-form affinities from the queued genes and rescales the active member's stats. */
#ifdef NON_MATCHING
NON_MATCHING void func_800A6E14(u8 value) {
    PartyMember* battler;
    Character*   character;
    s8*          affinity;
    s16          percent;
    s16          stat;
    u8           i;
    u8           j;
    u8           count;

    for (i = 0; i < g_Battle.party_count; i++) {
        s_BattleBattlerTemplates[i] = g_Game.members[i];
    }

    battler   = &g_Game.members[g_Battle.active_battler];
    character = &g_Characters[battler->character_index];
    affinity  = &D_800B6F60;

    for (i = 0; i < 14; i++) {
        affinity[i] = 0;
    }
    for (i = 0; i < g_Battle.gene_count; i++) {
        if (g_Battle.genes[i] >= 10 && g_Battle.genes[i] <= 12) {
            continue;
        }
        for (j = 0; j < 14; j++) {
            affinity[j] += D_800B4D7C[g_Battle.genes[i]][j];
        }
    }
    for (i = 0; i < g_Battle.gene_count; i++) {
        if (g_Battle.genes[i] == 11) {
            for (j = 0; j < 10; j++) {
                affinity[j] = -affinity[j];
            }
        }
    }
    for (i = 0; i < g_Battle.gene_count; i++) {
        if (g_Battle.genes[i] == 10) {
            for (j = 0; j < 14; j++) {
                affinity[j] *= 2;
            }
        }
    }
    for (i = 0; i < g_Battle.gene_count; i++) {
        if (g_Battle.genes[i] == 12) {
            for (j = 0; j < 14; j++) {
                if (affinity[j] != 0) {
                    if (rand() & 1) {
                        if (rand() & 1) {
                            affinity[j]++;
                        } else {
                            affinity[j]--;
                        }
                    }
                } else if (rand() % 10 == 0) {
                    if (rand() & 1) {
                        affinity[j]++;
                    } else {
                        affinity[j]--;
                    }
                }
            }
        }
    }

    D_800B6F58 = 0;
    if (D_800B6F6D > 0) {
        D_800B6F58 = 3;
    } else if (D_800B6F6B > 0) {
        D_800B6F58 = 2;
    } else if (D_800B6F6A >= 2) {
        D_800B6F58 = 1;
    }

    percent = D_800B4E78[D_800B6F58][0] + func_800A7648(D_800B6F65);
    if (percent <= 0) {
        stat = 1;
    } else {
        stat = func_801DE0F8(character->base.max_hp, percent * 10);
    }
    D_801EBEF0.max_hp         = stat;
    stat                      = D_801EBEF0.max_hp - ((D_801EBEF0.max_hp * character->fatigue + 5) / 10);
    battler->chr.base.max_hp  = stat;
    battler->chr.stats.max_hp = stat;
    battler->chr.hp           = stat;

    D_801EBEF0.power = battler->chr.base.power;
    percent          = D_800B4E78[D_800B6F58][1] + func_800A7648(D_800B6F66);
    stat             = 0;
    if (percent > 0) {
        stat = func_801DE0AC(battler->chr.base.power, percent * 10);
    }
    battler->chr.base.power  = stat;
    battler->chr.stats.power = stat;
    D_801EBEF0.power         = stat - D_801EBEF0.power;

    D_801EBEF0.defense = battler->chr.base.defense;
    percent            = D_800B4E78[D_800B6F58][2] + func_800A7648(D_800B6F67);
    stat               = 0;
    if (percent > 0) {
        stat = func_801DE0AC(battler->chr.base.defense, percent * 10);
    }
    battler->chr.base.defense  = stat;
    battler->chr.stats.defense = stat;
    D_801EBEF0.defense         = stat - D_801EBEF0.defense;

    D_801EBEF0.agility = battler->chr.base.agility;
    percent            = D_800B4E78[D_800B6F58][3] + func_800A7648(D_800B6F68);
    stat               = 0;
    if (percent > 0) {
        stat = func_801DE0AC(battler->chr.base.agility, percent * 10);
    }
    battler->chr.base.agility  = stat;
    battler->chr.stats.agility = stat;
    D_801EBEF0.agility         = stat - D_801EBEF0.agility;

    D_801EBEF0.intelligence = battler->chr.base.intelligence;
    percent                 = D_800B4E78[D_800B6F58][4] + func_800A7648(D_800B6F69);
    stat                    = 0;
    if (percent > 0) {
        stat = func_801DE0AC(battler->chr.base.intelligence, percent * 10);
    }
    battler->chr.base.intelligence  = stat;
    battler->chr.stats.intelligence = stat;
    D_801EBEF0.intelligence         = stat - D_801EBEF0.intelligence;

    count      = 0;
    D_800B6F5C = 0;
    for (i = 0; i < 5; i++) {
        if (affinity[i] > 0) {
            D_800B6F5C = i + 1;
            count++;
        }
    }
    if (count < 2) {
        D_800B6F5C = 6;
    }
    func_800A7694(D_800B6F60, D_800B6F61, D_800B6F62, D_800B6F63, D_800B6F64);
    func_800A78B8();
}
#else
INCLUDE_ASM(func_800A6E14);
#endif
