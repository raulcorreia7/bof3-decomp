#include "battle_03.h"

/* func_801DE94C */
MATCH void Battle_SetTextActionName(u32 action_index, s8 queue_type) {
    SYS_CopyString(&D_801492B8, s_BattleActionNames[action_index & BYTE_MASK], 12u);
    g_BattleEventSlots[0].value = queue_type;
}
