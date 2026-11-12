#include "boss013_16.h"

MATCH u8 func_800C2138(u32 mode) {
    u8* flags;

    switch ((u8)mode) {
        case BOSS_EVENT_RESTART_BEGIN:
            if ((ENEMY_COMBATANT(3).status & STATUS_LOW_HP) || (ENEMY_COMBATANT(4).status & STATUS_LOW_HP)) {
                g_Battle.boss_flags |= 0x8;
            }
            break;
        case BOSS_EVENT_ACTION_START:
            if ((g_Battle.active_battler == 0) && (g_Battle.target_selector & BATTLE_TARGET_ENEMY_SIDE) && !(g_Battle.boss_flags & 0x1)) {
                g_Battle.action_type = BATTLE_ACTION_NONE;
                g_MenuPanelMode      = 2;
                Message_StartAreaMessage(0x27);
            }
            break;
        case BOSS_EVENT_TURN_END:
            flags = &g_Battle.boss_flags;
            if ((*flags & 0x40) || D_800C26E0) {
                break;
            }
            func_801D9484();
            SYS_CopyString(*g_TextVariables, g_Characters[D_80181B11].name, 8);
            func_801DE560(2, 0, 0, 0x2D, Message_GetText(0x25U));
            D_800C26E0 = 0;
            TASK_SET(&D_801EB860);
            g_BattleCurrentEnemy = (EnemyBattler*)&D_801EB860;
            Party_LoadMemberSprite(1, 1);
            g_BattleCurrentEnemy->script = &D_800C25FC;
            g_Task->unk_29               = 4;
            Actor_SelectScript((g_Task->facing + 4) & BYTE_MASK);
            *flags |= 0x40;
            break;
        case BOSS_EVENT_TICK:
        case BOSS_EVENT_EFFECTS_LOADED:
        case BOSS_EVENT_RESTART_END:
            break;
    }
    return 0;
}
