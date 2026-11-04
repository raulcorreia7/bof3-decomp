#include "shared/etc.h"

/* Shop panel table: 0x24-byte records owned by this overlay. */
/* start_08.h cannot be included here: it declares g_BattleChoicePhase as u8 and
 * Party_CountOrder as u8(u8); this unit needs s8 and s32(s32). */
extern s8 D_8014854F;
extern s8 D_80148656;

u8 Party_CountOrder(u8 mode);

MATCH void func_801D2C7C(void) {
    u8 i;

    i = 0;
    while ((u8)i < (u8)(Party_CountOrder(0))) {
        if (i == D_80148656) {
            D_80148333[((i + 4) * 9) << 2]   = 6;
            D_80148333[((i + 0xC) * 9) << 2] = 4;
        } else {
            D_80148333[((i + 4) * 9) << 2]   = 8;
            D_80148333[((i + 0xC) * 9) << 2] = 6;
        }
        i++;
    }
    D_8014854F          = 1;
    g_BattleChoicePhase = 1;
    D_80148597          = 1;
}
