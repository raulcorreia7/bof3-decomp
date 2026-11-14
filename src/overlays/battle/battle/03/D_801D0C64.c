#include "battle_03.h"

/* Overlay head .data, 0x801D0C64..0x801D0CA0: the icon CLUT row, the
 * format strings and the five-entry panel table. */

/* In-overlay dispatch targets (split assembly units). */

BattleIconPalette D_801D0C64 = {
    0x08, 0x09, 0x08, 0x09, 0x08, 0x08, 0x08,
};

static u32 s_gap_801D0C6C = 0x2F;

char D_801D0C70[] = ":";

char D_801D0C74[] = "%4d";

s8 D_801D0C78[] = "%3d";

DamageSpread D_801D0C7C = {
    {50, 50, 50, 50, 60, 60, 60, 70},
};

/* 0x801D0C84 */
/* D_801D0C84 */
BattleEventSteps g_BattleEvents = {
    (Callback)func_801DE690, (Callback)func_801DE698, (Callback)func_801DE754,
    (Callback)func_801DE690, (Callback)func_801DE7FC,
};

/* D_801D0C98 */
u8 s_BattleCueIds[8] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x00, 0x00, 0x00,
};
