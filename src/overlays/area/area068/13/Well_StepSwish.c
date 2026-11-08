#include "area068_13.h"

/* func_801F3304 */
MATCH void Well_StepSwish(void) {
    Actor* work;

    if (++g_WellSwishStep >= WELL_SWISH_STEPS) {
        work        = g_Task;
        g_GameState = g_BattlePartyBattlers;
        TASK_SET(g_BattlePartyBattlers);
        D_80145EC8 &= 0xFFFFF000;
        D_80145EC4 &= 0xFFFFF000;
        g_Task            = work;
        work->header.mode = WELL_MODE_RAISE_BEGIN;
        g_WellPressCount  = 0;
        g_WellSwishStep   = 0;
    } else {
        switch (g_WellSwishButtons) {
            case 0x1000:
            case 0x3000:
                work        = g_Task;
                g_GameState = g_BattlePartyBattlers;
                TASK_SET(g_BattlePartyBattlers);
                D_80145EC8 += 0x800;
                g_Task = work;
                break;
            case 0x2000:
            case 0x6000:
                work        = g_Task;
                g_GameState = g_BattlePartyBattlers;
                TASK_SET(g_BattlePartyBattlers);
                D_80145EC4 -= 0x800;
                g_Task = work;
                break;
            case 0x4000:
            case 0xC000:
                work        = g_Task;
                g_GameState = g_BattlePartyBattlers;
                TASK_SET(g_BattlePartyBattlers);
                D_80145EC8 -= 0x800;
                g_Task = work;
                break;
            case 0x8000:
            case 0x9000:
                work        = g_Task;
                g_GameState = g_BattlePartyBattlers;
                TASK_SET(g_BattlePartyBattlers);
                D_80145EC4 += 0x800;
                g_Task = work;
                break;
        }
        g_Task->header.mode = WELL_MODE_SWISH_INPUT;
    }
}
