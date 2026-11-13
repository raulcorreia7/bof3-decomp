#include "magic060_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

MATCH void func_801EEC34(void) {
    Magic060Steps handlers;

    handlers = D_801EEC04;
    SYS_DISPATCH_TASK(handlers.steps, 1, g_Task);
}

INCLUDE_ASM(func_801EECA4);

MATCH void func_801EED68(void) {
    u32          slot;
    PartyMember* work;

    if (g_Task->param.unk_0B == 2) {
        slot                               = Battle_AllocEffect(1, 18) & BYTE_MASK;
        work                               = g_Task;
        g_BattleEffects[slot].header.mode  = 2;
        g_BattleEffects[slot].target.party = work;
        g_Task->unk_09                     = 0x10;
        g_Task->header.mode                = g_Task->header.mode + 1;
    }
}

MATCH void func_801EEE00(void) {
    u8 timer;

    if (g_Battle.target_selector < 3U) {
        func_801EF174();
    } else {
        func_801EF2DC();
    }
    timer          = g_Task->unk_09 - 1;
    g_Task->unk_09 = timer;
    if (!(timer & BYTE_MASK)) {
        g_Task->header.mode += 1;
    }
}

MATCH void func_801EEE84(void) {
    if (g_Battle.target_selector < 3) {
        func_801EF174();
    } else {
        func_801EF2DC();
    }
    if (g_InputPressed != 0) {
        g_Task->param.unk_0B = 0x83;
        g_Task->header.mode++;
    }
}

MATCH void func_801EEF04(void) {
    u16* flags;

    if (g_Task->param.unk_0B == 0x80) {
        BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING);
        func_801E5988();
    }
}

INCLUDE_ASM(func_801EEF50);

/* Sets the bit of the targeted enemy's id in g_IdentifiedEnemies. */
MATCH void Effect_MarkTargetIdentified(void) {
    u8 id;

    id = ENEMY_COMBATANT(g_Battle.target_selector).enemy_id.byte.kind;
    BIT_ARRAY_SET(g_IdentifiedEnemies, id);
}

/* Whether the bit of the targeted enemy's id is set in g_IdentifiedEnemies. */
MATCH bool Effect_TargetIsIdentified(void) {
    u8 id;

    id = ENEMY_COMBATANT(g_Battle.target_selector).enemy_id.byte.kind;
    return BIT_ARRAY_TEST(g_IdentifiedEnemies, id) != 0;
}

MATCH void func_801EF174(void) {
    u8 id;

    /* kept: retail reloads the target row at each access; a PartyMember* local changes the bytes. */
    id                                                        = g_Game.members[g_Battle.target_selector].chr.character_id;
    g_Game.members[g_Battle.target_selector].chr.character_id = CHAR_ID_RYU_YOUNG;
    func_801EF590(g_Game.members[g_Battle.target_selector].chr.name, 112, 48);
    g_Game.members[g_Battle.target_selector].chr.character_id = id;
    func_801EF76C(D_801F0B64, 90, 68);
    func_801EF76C(D_801F0B7C, 128, 68);
    func_801EF590(D_801F0B8C, 112, 80);
    func_801EF590(D_801F0B88, 156, 100);
    func_801EF590(D_801F0B6C, 176, 100);
    func_801EF590(D_801F0B88, 156, 120);
    func_801EF590(D_801F0B70, 176, 120);
    func_801EF76C(D_801F0B74, 90, 138);
    func_801EF590(D_801F0B8C, 112, 152);
    func_801EF590(D_801F0B8C, 112, 172);
}

INCLUDE_ASM(func_801EF2DC);

MATCH void func_801EF470(u8 item_id, u8 category, s32 y) {
    /* FAKE: the record pointer must stay in s0 through the switch; an unpinned local scales the table index in v1, and the best pure-C body differs in 11 instructions at the same 0x120-byte size. */
    FAKE_REG(u8*, record, "s0");

    if (g_Task->unk_04 != 0) {
        switch (category) {
            case ITEM_CAT_ITEM:
            default:
                record = (u8*)&g_Items[item_id];
                break;
            case ITEM_CAT_WEAPON:
                record = (u8*)&g_Weapons[item_id];
                break;
            case ITEM_CAT_ARMOR:
                record = (u8*)&g_Armors[item_id];
                break;
            case ITEM_CAT_ACCESSORY:
                record = (u8*)&g_Accessories[item_id];
                break;
        }
        UI_DrawText(112, (s16)y, 0, Game_ReadCommand(record) & BYTE_MASK, record);
    } else {
        func_801EF590(D_801F0B8C, 112, (s16)y);
    }
}

INCLUDE_ASM(func_801EF590);

INCLUDE_ASM(func_801EF76C);

INCLUDE_ASM(func_801EF924);

INCLUDE_ASM(func_801EFB00);
