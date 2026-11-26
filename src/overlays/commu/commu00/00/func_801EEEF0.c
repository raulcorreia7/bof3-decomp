#include "commu00_00.h"

/* Runs the village upkeep for one row count: Fairy_JoinVillage per 10 battles or func_801F01F4 per 20 since the D_801455AC and D_801455B0 stamps. */
void func_801EEEF0(u32 row) {
    s8*  fairy_count;
    s32  slots;
    s32  fairies;
    s32  count;
    s32  i;
    u32  first;
    u32  battles;
    u32* battle_count;

    fairy_count = &g_SaveData.fairy_count;
    row &= BYTE_MASK;
    fairies = *fairy_count;
    if ((s32)(row * 4) < fairies) {
        battle_count = &g_SaveData.battle_count;
        battles      = *battle_count;
        if (battles - D_801455B0 > 20) {
            D_801455B0 = battles - 20;
        }
        if (row < 20) {
            slots = ((fairies - (s32)(row * 4)) >> 2) + 1;
            count = (battles - D_801455AC) / 10;
            if (slots < count) {
                count = slots;
            }
            if (count != 0) {
                for (i = 0; i < count; i++) {
                    first = row;
                    if (first + i == 20) {
                        break;
                    }
                    Fairy_JoinVillage();
                }
                battle_count = &g_SaveData.battle_count;
                D_801455AC   = *battle_count;
            }
        }
    } else if (fairies == 0) {
        battles = g_BattleCount;
        if (battles - D_801455AC > 10) {
            D_801455AC = battles - 10;
        }
        if (row >= 2) {
            count = (battles - D_801455B0) / 20;
            if (count != 0) {
                for (i = 0; i < count; i++) {
                    first = row;
                    if (first - i == 1) {
                        break;
                    }
                    func_801F01F4();
                }
                D_801455B0 = g_BattleCount;
            }
        }
    } else {
        battles = g_BattleCount;
        if (battles - D_801455AC > 10) {
            D_801455AC = battles - 10;
        }
        if (battles - D_801455B0 > 20) {
            D_801455B0 = battles - 20;
        }
    }
}
