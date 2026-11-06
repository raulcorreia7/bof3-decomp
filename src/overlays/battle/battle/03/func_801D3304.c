#include "battle_03.h"

/* resolves the selected ability action, draws its panel and either
 * starts the confirm step or queues the failure cues.
 */
MATCH void func_801D3304(void) {
    u16 row;
    u16 flag;
    u16 action;

    {
        u16* battle_half;

        battle_half  = (u16*)&g_BattleActionId;
        *battle_half = g_BattleAction->unk_02;
        if (func_800A9A84() & BYTE_MASK) {
            func_801DD14C(g_BattleActiveBattler);
            BATTLE_ACTIVE_PARTY.mode = 2;
            BATTLE_ACTIVE_PARTY.step = 0;
            g_BattleMode             = 3;
            g_BattleStep             = 0;
            g_BattleSubStep          = 0;
            return;
        }
        if (*battle_half != 0x97) {
            /* a plain store: the volatile one blocks the func_801501E4 delay-slot fill */
            *(u8*)&g_BattleMessageState = 1;
            SYS_CopyString((u8*)&D_80149298, (u8*)&g_Abilities[*battle_half], 0xC);
            func_801DE560(1, 1, 0, 0x3C, (u8*)&D_80149298);
        }
    }
    if (BATTLER_IS_PLAYER(g_BattleActiveBattler)) {
        row  = BATTLE_ACTIVE_PARTY.chr.ap;
        flag = BATTLE_ACTIVE_PARTY.chr.status;
    } else {
        row  = ENEMY_COMBATANT(g_BattleActiveBattler).ap;
        flag = ENEMY_COMBATANT(g_BattleActiveBattler).status;
    }
    if ((flag & STATUS_SILENCED) != 0 && (D_801CA71C[*(u16*)&g_BattleActionId].mask & 0x400)) {
        func_801D9484();
        func_801DE560(2, 0, 0, 0x2D, Resource_GetText(0x37));
        g_BattleStep    = 0;
        g_BattleSubStep = 0;
        return;
    }
    action = *(u16*)&g_BattleActionId;
    if (action != 0x97) {
        if (BATTLER_IS_PLAYER(g_BattleActiveBattler)) {
            D_801463C8 = Char_GetAbilityCost(BATTLE_ACTIVE_PARTY.slot, action & BYTE_MASK, 1);
        } else {
            D_801463C8 = Char_GetAbilityCost(ENEMY_COMBATANT(g_BattleActiveBattler).slot, action & BYTE_MASK, 1);
        }
    } else {
        D_801463C8 = D_801463B8[0];
    }
    if (row < D_801463C8) {
        func_801D9484();
        func_801DE560(2, 0, 0, 0x2D, Resource_GetText(0x36));
        g_BattleStep    = 0;
        g_BattleSubStep = 0;
        return;
    }
    g_BattleRowCursor = 0;
    if (!(func_800AA368() & BYTE_MASK)) {
        g_BattleState |= 0x20;
    }
    g_BattleUIStep += 1;
}
