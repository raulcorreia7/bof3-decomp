#include "area068_13.h"

MATCH void func_801F3304(void) {
    Actor* work;

    if (++D_801F4E10 >= 8) {
        work        = g_SpadWork;
        g_GameState = (GameStateRecord*)g_BattlePartyBattlers;
        g_SpadWork  = (Actor*)g_BattlePartyBattlers;
        D_80145EC8 &= 0xFFFFF000;
        D_80145EC4 &= 0xFFFFF000;
        g_SpadWork   = work;
        work->unk_01 = 0xF;
        D_801F4E04   = 0;
        D_801F4E10   = 0;
    } else {
        switch (D_801F4E14) {
            case 0x1000:
            case 0x3000:
                work        = g_SpadWork;
                g_GameState = (GameStateRecord*)g_BattlePartyBattlers;
                g_SpadWork  = (Actor*)g_BattlePartyBattlers;
                D_80145EC8 += 0x800;
                g_SpadWork = work;
                break;
            case 0x2000:
            case 0x6000:
                work        = g_SpadWork;
                g_GameState = (GameStateRecord*)g_BattlePartyBattlers;
                g_SpadWork  = (Actor*)g_BattlePartyBattlers;
                D_80145EC4 -= 0x800;
                g_SpadWork = work;
                break;
            case 0x4000:
            case 0xC000:
                work        = g_SpadWork;
                g_GameState = (GameStateRecord*)g_BattlePartyBattlers;
                g_SpadWork  = (Actor*)g_BattlePartyBattlers;
                D_80145EC8 -= 0x800;
                g_SpadWork = work;
                break;
            case 0x8000:
            case 0x9000:
                work        = g_SpadWork;
                g_GameState = (GameStateRecord*)g_BattlePartyBattlers;
                g_SpadWork  = (Actor*)g_BattlePartyBattlers;
                D_80145EC4 += 0x800;
                g_SpadWork = work;
                break;
        }
        g_SpadWork->unk_01 = 0xB;
    }
}
