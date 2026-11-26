#include "area191_13.h"
#include "menu/save_data.h"

MATCH void func_801F39AC(void) {
    u8* flags;
    u8  fatigue;
    u8  mode;
    u8  i;
    s16 slot;

    /* The flag rows lie in the save block above the record; retail reaches them from its base. */
    flags   = &g_Characters[0].fatigue;
    fatigue = flags[0];
    if (SYS_TestFlag(flags + 0x5A6, 0x77) != 0) {
        return;
    }
    if (!SYS_TestFlag(flags + 0x576, 0xA)) {
        if (fatigue < CHARACTER_FATIGUE_MAX) {
            if (fatigue < 5) {
                mode = g_SaveData.desert.days >= 5;
            } else {
                mode = 1;
            }
        } else {
            mode = 2;
        }
    } else if (fatigue < 5) {
        mode = g_SaveData.desert.days >= 5;
    } else {
        mode = 2;
    }
    for (i = 0; i < 6; i++) {
        slot                         = Actor_FindFreeField();
        g_ScratchPad.cells.halves[0] = slot;
        if (slot != GAME_NONE) {
            Actor_SpawnFromRecord(D_801F43D8[mode] + i * 17);
        }
    }
}
