#include "battle_15.h"

s8   func_800A7648(s8 index);
void func_800A7694(s8 affinity_0, s8 affinity_1, s8 affinity_2, s8 affinity_3, s8 affinity_4);
void func_800A78B8(void);

/* Rebuilds the dragon-form affinities from the queued genes and rescales the active member's stats. */
MATCH void func_800A6E14(u8 value) {
    Character* chr;
    Character* character;
    s16        percent;
    s16        stat;
    u8         i;
    u8         j;

    for (i = 0; i < g_Battle.party_count; i++) {
        s_BattleBattlerTemplates[i] = g_Game.members[i];
    }

    chr       = &g_Game.members[g_Battle.active_battler].chr;
    character = &g_Characters[g_Game.members[g_Battle.active_battler].character_index];

    for (i = 0; i < 14; i++) {
        D_800B6F60[i] = 0;
    }
    for (i = 0; i < g_Battle.gene_count; i++) {
        if (g_Battle.genes[i] == 10 || g_Battle.genes[i] == 11 || g_Battle.genes[i] == 12) {
            continue;
        }
        for (j = 0; j < 14; j++) {
            D_800B6F60[j] += D_800B4D7C[g_Battle.genes[i]][j];
        }
    }
    for (i = 0; i < g_Battle.gene_count; i++) {
        if (g_Battle.genes[i] == 11) {
            for (j = 0; j < 10; j++) {
                D_800B6F60[j] *= -1;
            }
        }
    }
    for (i = 0; i < g_Battle.gene_count; i++) {
        if (g_Battle.genes[i] == 10) {
            for (j = 0; j < 14; j++) {
                D_800B6F60[j] *= 2;
            }
        }
    }
    for (i = 0; i < g_Battle.gene_count; i++) {
        if (g_Battle.genes[i] == 12) {
            for (j = 0; j < 14; j++) {
                if (D_800B6F60[j] == 0) {
                    if (rand() % 10 == 0) {
                        if (rand() & 1) {
                            D_800B6F60[j]++;
                        } else {
                            D_800B6F60[j]--;
                        }
                    }
                } else if (rand() & 1) {
                    if (rand() & 1) {
                        D_800B6F60[j]++;
                    } else {
                        D_800B6F60[j]--;
                    }
                }
            }
        }
    }

    D_800B6F58 = 0;
    if (D_800B6F60[13] > 0) {
        D_800B6F58 = 3;
    } else if (D_800B6F60[11] > 0) {
        D_800B6F58 = 2;
    } else if (D_800B6F60[10] >= 2) {
        D_800B6F58 = 1;
    }

    percent = D_800B4E78[D_800B6F58][0] + func_800A7648(D_800B6F60[5]);
    if (percent > 0) {
        D_801EBEF0.max_hp = func_801DE0F8(character->base.max_hp, percent * 10);
    } else {
        D_801EBEF0.max_hp = 1;
    }
    stat              = D_801EBEF0.max_hp - ((D_801EBEF0.max_hp * character->fatigue + 5) / 10);
    chr->base.max_hp  = stat;
    chr->stats.max_hp = stat;
    chr->hp           = stat;

    D_801EBEF0.power = chr->base.power;
    percent          = D_800B4E78[D_800B6F58][1] + func_800A7648(D_800B6F60[6]);
    if (percent > 0) {
        stat = func_801DE0AC(chr->base.power, percent * 10);
    } else {
        stat = 0;
    }
    D_801EBEF0.power = stat - D_801EBEF0.power;
    chr->base.power  = stat;
    chr->stats.power = stat;

    D_801EBEF0.defense = chr->base.defense;
    percent            = D_800B4E78[D_800B6F58][2] + func_800A7648(D_800B6F60[7]);
    if (percent > 0) {
        stat = func_801DE0AC(chr->base.defense, percent * 10);
    } else {
        stat = 0;
    }
    D_801EBEF0.defense = stat - D_801EBEF0.defense;
    chr->base.defense  = stat;
    chr->stats.defense = stat;

    D_801EBEF0.agility = chr->base.agility;
    percent            = D_800B4E78[D_800B6F58][3] + func_800A7648(D_800B6F60[8]);
    if (percent > 0) {
        stat = func_801DE0AC(chr->base.agility, percent * 10);
    } else {
        stat = 0;
    }
    D_801EBEF0.agility = stat - D_801EBEF0.agility;
    chr->base.agility  = stat;
    chr->stats.agility = stat;

    D_801EBEF0.intelligence = chr->base.intelligence;
    percent                 = D_800B4E78[D_800B6F58][4] + func_800A7648(D_800B6F60[9]);
    if (percent > 0) {
        stat = func_801DE0AC(chr->base.intelligence, percent * 10);
    } else {
        stat = 0;
    }
    D_801EBEF0.intelligence = stat - D_801EBEF0.intelligence;
    chr->base.intelligence  = stat;
    chr->stats.intelligence = stat;

    j          = 0;
    D_800B6F5C = 0;
    for (i = 0; i < 5; i++) {
        if (D_800B6F60[i] > 0) {
            D_800B6F5C = i + 1;
            j++;
        }
    }
    if (j >= 2) {
        D_800B6F5C = 6;
    }
    func_800A7694(D_800B6F60[0], D_800B6F60[1], D_800B6F60[2], D_800B6F60[3], D_800B6F60[4]);
    func_800A78B8();
}
