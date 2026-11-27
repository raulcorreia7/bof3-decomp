#include "battle_03.h"

/* loads the active work area's two sprite bytes from either the queued
 * battler table or the current battler table, queues the palette step and
 * advances the area's phase.
 */
MATCH void func_801DF914(void) {
    PartyMember* current;
    PartyMember* work;
    u8*          selector;

    current = g_Game.current;
    if ((current->u.turn.action_flags.value & BATTLER_ACTION_DRAGON_FORM) != 0) {
        selector                  = &g_Battle.dragon_form;
        SELF(PartyMember)->unk_09 = *(u8*)((u8*)&D_801EB198 + *selector);
        SELF(PartyMember)->timer  = *(u8*)((u8*)&D_801EB198 + *selector);
    } else {
        SELF(PartyMember)->unk_09 = *(u8*)((u8*)&s_BattleCharacterSprites + current->chr.character_id);
        SELF(PartyMember)->timer  = *(u8*)((u8*)&s_BattleCharacterSprites + g_Game.current->chr.character_id);
    }
    Script_Request((SELF(PartyMember)->facing + 0xC) & BYTE_MASK);
    func_801DEDE4();
    work              = SELF(PartyMember);
    work->header.mode = work->header.mode + 1;
}
