#include "start_08.h"
#include "sys/actor.h"

MATCH void func_801E3EC4(void) {
    u8* hint;
    u8* work;
    u8* tail;

    hint              = &g_EmiLoadedCharacterIndex;
    g_Game.flags      = 0;
    g_Game.walk_flags = 0;
    *hint             = 0;
    g_Game.current    = g_BattlePartyBattlers;
    SELF_SET(g_BattlePartyBattlers);
    Party_MemberLoadSprite(CHAR_ID_RYU_YOUNG, 0);
    SELF_BYTES[0]                    = 1;
    g_Game.current->chr.character_id = CHAR_ID_RYU_YOUNG;
    work                             = SELF_BYTES;
    work[0x29]                       = 0;
    tail                             = SELF_BYTES;
    FIELD(s16, work, 0x2Eu)          = 0x10A;
    FIELD(s16, work, 0x30u)          = 0x51;
    tail[0x48]                       = 0;
    SELF_BYTES[9]                    = 1;
    SELF_BYTES[0x24]                 = 0x81;
    SELF_BYTES[6]                    = 4;
    SELF_BYTES[9]                    = 0;
    Script_Select((SELF(Actor)->unk_06 + 8) & BYTE_MASK);
    D_801ED7EC     = 1;
    *hint          = 0xFF;
    D_801ED864     = 0x80;
    D_80148694     = 0;
    D_801ED868     = 0x40;
    g_MenuCampStep = 0;
    /* FAKE: retail takes the step counter's address before the increment. */
    (*(CampMenuStepCounter*)&g_GameEntrySubstate).rows[0] += 1;
}
