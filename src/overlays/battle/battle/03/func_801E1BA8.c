#include "battle_03.h"

MATCH void func_801E1BA8(void) {
    BattleEffect* slot;
    PartyMember*  work;
    PartyMember*  current;

    slot              = &g_BattleEffects[Battle_AllocEffect(0, 5) & BYTE_MASK];
    work              = g_Task;
    current           = g_Game.current;
    slot->unk_2E      = work->unk_2E.half - (s8)s_LoaderRecordBytes[current->chr.character_id * 2];
    slot->unk_30      = work->unk_30.half - (s8) * (&D_80181D99 + current->chr.character_id * 2);
    work->header.step = work->header.step + 1;
}
