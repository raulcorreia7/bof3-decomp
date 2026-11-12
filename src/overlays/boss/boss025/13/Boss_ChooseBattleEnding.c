#include "boss025_13.h"

MATCH void Boss_ChooseBattleEnding(void) {
    volatile u8* flags;

    BOSS_SEND_PARTY_TO_ENDING_POSE(0)
    BOSS_SEND_PARTY_TO_ENDING_POSE(1)
    BOSS_SEND_PARTY_TO_ENDING_POSE(2)
    flags = &g_Battle.boss_flags;
    if (*flags & 0x1) {
        D_80146875 = 0xF;
    }
    if (*flags & 0x2) {
        D_80146875 = 7;
    }
    if (*flags & 0x4) {
        D_80146875 = 0x14;
    }
    func_801DDF28();
}
