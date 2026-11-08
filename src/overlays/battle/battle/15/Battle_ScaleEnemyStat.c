#include "battle_15.h"

/* Rate field of the battler row; the row type does not name 0x88..0xCA yet. */
#define RATE_FIELD(offset) FIELD(u16, battler, offset)

/* func_8009CCBC */
MATCH void Battle_ScaleEnemyStat(void* battler, s32 rate_type, s32 rate_percent) {
    u32 cap;
    u32 value;
    u8  percent;
    u8  kind;
    s32 scale;

    kind    = rate_type & BYTE_MASK;
    percent = rate_percent & BYTE_MASK;
    switch (kind) {
        case 0:
            scale = percent * 100;
            value = RATE_FIELD(0x94u) * scale / 1000;
            cap   = RATE_FIELD(0xC0u);
            if (cap >= value) {
                RATE_FIELD(0x94u) = value;
                return;
            }
            RATE_FIELD(0x94u) = cap;
            return;
        case 1:
            scale = percent * 100;
            value = RATE_FIELD(0x96u) * scale / 1000;
            cap   = RATE_FIELD(0xC2u);
            if (cap >= value) {
                RATE_FIELD(0x96u) = value;
                return;
            }
            RATE_FIELD(0x96u) = cap;
            return;
        case 2:
            value = RATE_FIELD(0xC4u) * (scale = percent * 100) / 1000;
            if (value < 0x3E8U) {
                RATE_FIELD(0xC4u) = value;
                return;
            }
            RATE_FIELD(0xC4u) = 0x3E7U;
            return;
        case 3:
            value = RATE_FIELD(0xC6u) * (scale = percent * 100) / 1000;
            if (value < 0x3E8U) {
                RATE_FIELD(0xC6u) = value;
                return;
            }
            RATE_FIELD(0xC6u) = 0x3E7U;
            return;
        case 4:
            value = RATE_FIELD(0xC8u) * (scale = percent * 100) / 1000;
            if (value < 0x3E8U) {
                RATE_FIELD(0xC8u) = value;
                return;
            }
            RATE_FIELD(0xC8u) = 0x3E7U;
            return;
        case 5:
            value = RATE_FIELD(0xCAu) * (scale = percent * 100) / 1000;
            if (value < 0x3E8U) {
                RATE_FIELD(0xCAu) = value;
                return;
            }
            RATE_FIELD(0xCAu) = 0x3E7U;
            return;
        case 6:
            value = RATE_FIELD(0x88u) * percent * (scale = percent * 100) / 1000;
            if (value < 0x3E8U) {
                RATE_FIELD(0x88u) = value;
                return;
            }
            RATE_FIELD(0x88u) = 0x3E7U;
            return;
        default:
            return;
    }
}
