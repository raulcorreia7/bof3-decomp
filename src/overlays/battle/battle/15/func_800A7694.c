#include "battle_15.h"

/* Gene-step bonus tables (five-byte rows). */

MATCH void func_800A7694(s8 affinity_0, s8 affinity_1, s8 affinity_2, s8 affinity_3, s8 affinity_4) {
    u8* rec;

    rec = D_80145F04 + g_Battle.active_battler * BATTLE_PARTY_STRIDE;

    {
        s8 index = affinity_0 + 2;
        u8 value;

        /* FAKE: plain `if`, not CLAMP_MIN: the macro's do/while(0) loop note bars
         * the scheduler hoist this slot's clamp needs. */
        if (index < 0) {
            index = 0;
        }
        if (index >= 5) {
            index = 4;
        }
        value      = s_BattleAffinityLevelBonus[index];
        rec[0x4B]  = value;
        rec[0x2B]  = value;
        D_801EBEFA = value;
    }

    {
        s8 index = affinity_1 + 2;
        u8 value;

        if (index < 0) {
            index = 0;
        }
        if (index >= 5) {
            index = 4;
        }
        value      = s_BattleAffinityLevelBonus[index];
        rec[0x4C]  = value;
        rec[0x2C]  = value;
        D_801EBEFB = value;
    }

    {
        s8 index = affinity_2 + 2;
        u8 value;

        if (index < 0) {
            index = 0;
        }
        if (index >= 5) {
            index = 4;
        }
        value      = s_BattleAffinityLevelBonus[index];
        rec[0x4D]  = value;
        rec[0x2D]  = value;
        D_801EBEFC = value;
    }

    {
        u8 value = 2;

        rec[0x4E]  = value;
        rec[0x2E]  = value;
        D_801EBEFD = value;
        rec[0x4F]  = value;
        rec[0x2F]  = value;
        D_801EBEFE = value;
    }

    {
        s8 index = affinity_4 + 2;
        u8 value;

        if (index < 0) {
            index = 0;
        }
        if (index >= 5) {
            index = 4;
        }
        value      = D_800B4E9E[index];
        rec[0x50]  = value;
        rec[0x30]  = value;
        D_801EBEFF = value;
    }

    {
        u8 value = 2;

        rec[0x51]  = value;
        rec[0x31]  = value;
        D_801EBF00 = value;
    }

    {
        s8 index = affinity_3 + 2;
        u8 value;
        u8 next;

        if (index < 0) {
            index = 0;
        }
        if (index >= 5) {
            index = 4;
        }
        value      = D_800B4E99[index];
        rec[0x52]  = value;
        rec[0x32]  = value;
        D_801EBF01 = value;

        next       = D_800B4E99[index];
        rec[0x53]  = next;
        rec[0x33]  = next;
        D_801EBF02 = next;
    }
}
