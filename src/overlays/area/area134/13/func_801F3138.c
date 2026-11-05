/* The dispatch dance keeps every work-cell write. */
#define SPAD_WORK_VOLATILE
#include "area134_13.h"

MATCH void func_801F3138(void) {
    Actor* work;

    work        = g_SpadWork;
    g_SpadWork  = g_Actors;
    g_GameState = (GameStateRecord*)g_BattlePartyBattlers;
    g_SpadWork  = work;
    g_SpadWork  = (Actor*)g_BattlePartyBattlers;
    g_SpadWork  = work;
    if (FIELD(s32, D_801468BC, 0) >= D_80145EC4) {
        work->unk_01       = 0xD;
        g_SpadWork->unk_09 = 0;
        return;
    }
    work->unk_01 = 0xC;
}
