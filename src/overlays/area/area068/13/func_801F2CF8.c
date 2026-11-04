#include "area068_13.h"

/* Point the mode record and the work cell at the first party record, then once
 * the two scene flags line up run script 0x6E and hand the previous work row
 * back with its step set to 3. */
MATCH void func_801F2CF8(void) {
    Actor* actor;

    actor       = g_SpadWork;
    g_GameState = (GameStateRecord*)g_BattlePartyBattlers;
    g_SpadWork  = (Actor*)g_BattlePartyBattlers;
    if (D_80145EE8 == 0xC && D_80145EDA == 1) {
        Actor_SelectScript(0x6E);
        g_SpadWork = actor;
        D_80145E97 &= 0x11;
        actor->unk_01 = 3;
    }
}
