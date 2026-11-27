#include "battle_03.h"

MATCH void func_801E1BA8(void) {
    BattleEffect* slot;
    PartyMember*  work;
    PartyMember*  current;

    slot              = &g_BattleEffects[Battle_AllocEffect(0, 5) & BYTE_MASK];
    work              = SELF(PartyMember);
    current           = g_Game.current;
    slot->screen_x    = work->screen_x.value - (s8)s_LoaderRecordBytes[current->chr.character_id * 2];
    slot->screen_y    = work->screen_y.value - (s8) * (&D_80181D99 + current->chr.character_id * 2);
    work->header.step = work->header.step + 1;
}
