#include "battle_03.h"

/* func_801DE94C */
MATCH void Battle_SetTextActionName(u32 action_index, s8 queue_kind) {
    SYS_CopyString(&D_801492B8, s_BattleActionNames[action_index & BYTE_MASK], 12u);
    D_801EB4F2 = queue_kind;
}
