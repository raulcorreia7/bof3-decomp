#include "boss018_16.h"

MATCH void func_800C2A40(void) {
    switch (g_Game.members[0].chr.character_id) {
        case 0:
            g_Game.battle_order = 0x2C;
            break;
        case 1:
            g_Game.battle_order = 0x2D;
            break;
        case 5:
            g_Game.battle_order = 0x2E;
            break;
        case 6:
            g_Game.battle_order = 0x2F;
            break;
    }
}
