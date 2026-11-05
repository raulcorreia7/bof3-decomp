#include "game_00.h"

MATCH void func_801B85C0(void) {
    u8  delay;
    u8* record;

    if (g_SpadWork->unk_09 == 0) {
        delay              = g_SpadWork->unk_0A - 1;
        g_SpadWork->unk_0A = delay;
        if ((delay & BYTE_MASK) == 0) {
            if (g_SpadWork->unk_05 == 0) {
                g_AreaWalkFlags &= ~AREA_WALK_ENTRY_ACTIVE;
            }
            g_GameState->counter_11C.s8_value = 3;
            record                            = (u8*)g_GameState;
            g_SpadWork->vx                    = 0;
            g_SpadWork->vy                    = 0;
            record[0x12B]                     = 0;
            g_SpadWork->unk_01                = 1;
            ACTOR_CLEAR_STATE();
            g_SpadWork->unk_03 = 0;
            g_SpadWork->unk_09 = 0;
            g_SpadWork->unk_0A = 0;
            Actor_RequestScript(g_SpadWork->direction_08);
            return;
        }
        func_801C24D0();
    }
    g_SpadWork->unk_09 = (u8)(g_SpadWork->unk_09 - 1);
    func_801B0DFC();
    func_8014D978();
}
