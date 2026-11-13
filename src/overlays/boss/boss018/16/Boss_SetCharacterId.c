#include "boss018_16.h"

/* func_800C2A40 */
MATCH void Boss_SetCharacterId(void) {
    switch (g_Game.members[0].chr.character_id) {
        case CHAR_ID_RYU_YOUNG:
            g_Game.battle_order = 0x2C;
            break;
        case CHAR_ID_NINA_YOUNG:
            g_Game.battle_order = 0x2D;
            break;
        case CHAR_ID_MOMO:
            g_Game.battle_order = 0x2E;
            break;
        case CHAR_ID_PECO:
            g_Game.battle_order = 0x2F;
            break;
    }
}
