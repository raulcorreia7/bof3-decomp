#include "battle_15.h"

/* func_8009CCBC */
MATCH void Battle_ScaleEnemyStat(void* battler, s32 rate_type, s32 rate_percent) {
    EnemyBattler* enemy;
    u32           cap;
    u32           value;
    u8            percent;
    u8            kind;
    s32           scale;

    enemy   = (EnemyBattler*)battler;
    kind    = rate_type & BYTE_MASK;
    percent = rate_percent & BYTE_MASK;
    switch (kind) {
        case 0:
            scale = percent * 100;
            value = enemy->hp * scale / 1000;
            cap   = enemy->base.max_hp;
            if (cap >= value) {
                enemy->hp = value;
                return;
            }
            enemy->hp = cap;
            return;
        case 1:
            scale = percent * 100;
            value = enemy->ap * scale / 1000;
            cap   = enemy->base.max_ap;
            if (cap >= value) {
                enemy->ap = value;
                return;
            }
            enemy->ap = cap;
            return;
        case 2:
            value = enemy->base.power * (scale = percent * 100) / 1000;
            if (value < 0x3E8U) {
                enemy->base.power = value;
                return;
            }
            enemy->base.power = 0x3E7U;
            return;
        case 3:
            value = enemy->base.defense * (scale = percent * 100) / 1000;
            if (value < 0x3E8U) {
                enemy->base.defense = value;
                return;
            }
            enemy->base.defense = 0x3E7U;
            return;
        case 4:
            value = enemy->base.agility * (scale = percent * 100) / 1000;
            if (value < 0x3E8U) {
                enemy->base.agility = value;
                return;
            }
            enemy->base.agility = 0x3E7U;
            return;
        case 5:
            value = enemy->base.intelligence * (scale = percent * 100) / 1000;
            if (value < 0x3E8U) {
                enemy->base.intelligence = value;
                return;
            }
            enemy->base.intelligence = 0x3E7U;
            return;
        case 6:
            value = enemy->level * percent * (scale = percent * 100) / 1000;
            if (value < 0x3E8U) {
                enemy->level = value;
                return;
            }
            enemy->level = 0x3E7U;
            return;
        default:
            return;
    }
}
