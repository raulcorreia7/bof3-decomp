#include "battle_03.h"

/* resolves the selected ability action, draws its panel and either
 * starts the confirm step or queues the failure cues.
 */
/* func_801D3304 */
MATCH void Battle_SelectAbility(void) {
    u16 row;
    u16 flag;
    u16 action;

    {
        u16* battle_half;

        battle_half  = (u16*)&g_Battle.action_id;
        *battle_half = g_Battle.action->unk_02;
        if (func_800A9A84() & BYTE_MASK) {
            Battle_CancelTurn(g_Battle.active_battler);
            BATTLE_ACTIVE_PARTY.header.mode = 2;
            BATTLE_ACTIVE_PARTY.header.step = 0;
            g_Battle.phase.mode             = BATTLE_MODE_TURNS;
            g_Battle.phase.step             = 0;
            g_Battle.phase.sub_step         = 0;
            return;
        }
        if (*battle_half != 0x97) {
            /* a plain store: the volatile one blocks the func_801501E4 delay-slot fill */
            *(u8*)&g_BattleMessageState = 1;
            SYS_CopyString((u8*)&D_80149298, (u8*)&g_Abilities[*battle_half], 12);
            Battle_QueueEvent(1, 1, 0, 60, (u8*)&D_80149298);
        }
    }
    if (BATTLER_IS_PLAYER(g_Battle.active_battler)) {
        row  = BATTLE_ACTIVE_PARTY.chr.ap;
        flag = BATTLE_ACTIVE_PARTY.chr.status;
    } else {
        row  = ENEMY_COMBATANT(g_Battle.active_battler).ap;
        flag = ENEMY_COMBATANT(g_Battle.active_battler).status;
    }
    if ((flag & STATUS_SILENCED) != 0 && (D_801CA71C[*(u16*)&g_Battle.action_id].mask & 0x400)) {
        Battle_OpenPanel();
        Battle_QueueEvent(2, 0, 0, 45, Message_GetText(0x37));
        g_Battle.phase.step     = 0;
        g_Battle.phase.sub_step = 0;
        return;
    }
    action = *(u16*)&g_Battle.action_id;
    if (action != 0x97) {
        if (BATTLER_IS_PLAYER(g_Battle.active_battler)) {
            D_801463C8 = Char_GetAbilityCost(BATTLE_ACTIVE_PARTY.slot, action & BYTE_MASK, 1);
        } else {
            D_801463C8 = Char_GetAbilityCost(ENEMY_COMBATANT(g_Battle.active_battler).slot, action & BYTE_MASK, 1);
        }
    } else {
        D_801463C8 = D_801463B8[0];
    }
    if (row < D_801463C8) {
        Battle_OpenPanel();
        Battle_QueueEvent(2, 0, 0, 45, Message_GetText(0x36));
        g_Battle.phase.step     = 0;
        g_Battle.phase.sub_step = 0;
        return;
    }
    g_Battle.row_cursor = 0;
    if (!(func_800AA368() & BYTE_MASK)) {
        g_Battle.state |= 0x20;
    }
    g_Battle.ui_step += 1;
}
