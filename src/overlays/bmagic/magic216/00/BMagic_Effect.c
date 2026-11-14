#include "magic216_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_DispatchMode.h"

MATCH void func_801EEC70(void) {
    PartyMember* work;
    PartyMember* actor;
    s32          z;

    g_Task->facing     = g_BattleEffectBattler->facing;
    work               = g_Task;
    actor              = g_BattleEffectBattler;
    work->pos.x.fixed  = actor->pos.x.fixed;
    work->pos.y.fixed  = actor->pos.y.fixed;
    z                  = actor->pos.z.fixed;
    work->param.unk_0B = 0;
    work->pos.z.fixed  = z;
    g_Task->header.mode += 1;
}

/* Rolls the steal: the chance is the drop rate entry of the target enemy scaled by
 * the agility lead of the acting battler; a hit adds the item and clears the drop. */
MATCH void func_801EECDC(void) {
    s32 value;
    s32 active;
    s32 slot;
    s32 scale;
    s32 category;

    active = g_BattleActiveBattler;
    slot   = g_BattleTargetSelector;
    value  = g_Game.members[active].chr.stats.agility - g_BattleEnemyBattlers[slot - 3].stats.agility;
    scale  = 12;
    if (value < 49) {
        scale = 11;
    }
    if (value < 29) {
        scale = 10;
    }
    if (value < 19) {
        scale = 9;
    }
    if (value < 9) {
        scale = 8;
    }
    if (value < -10) {
        scale = 7;
    }
    if (value < -20) {
        scale = 6;
    }
    if (value < -30) {
        scale = 5;
    }
    if (value < -50) {
        scale = 4;
    }
    value = g_BattleEnemyBattlers[slot - 3].drops[0].rate;
    value = D_801EF078[value] * scale;
    if ((rand() & 0xFF) < value) {
        value = g_BattleEnemyBattlers[g_BattleTargetSelector - 3].drops[0].item;
        if (value != 0) {
            category = value >> 8;
            if (Item_Add(category, value & 0xFF, 1, 0)) {
                func_801EEF98(value & 0xFF, category & 0xFF);
                func_801DE8C0(1, 0xFF, Message_GetText(0x38));
                g_BattleEnemyBattlers[g_BattleTargetSelector - 3].drops[0].rate = 0;
                g_BattleEnemyBattlers[g_BattleTargetSelector - 3].drops[0].item = 0;
            } else {
                func_801DE8C0(1, 0xFF, Message_GetText(0x39));
            }
        } else {
            func_801DE8C0(1, 0xFF, Message_GetText(0x3A));
        }
    } else if (g_BattleEnemyBattlers[g_BattleTargetSelector - 3].drops[0].rate != 0) {
        func_801DE8C0(1, 0xFF, Message_GetText(0x39));
    } else {
        func_801DE8C0(1, 0xFF, Message_GetText(0x3A));
    }
    g_Task->header.mode += 1;
}

MATCH void func_801EEF58(void) {
    u16* flags;

    if (D_801EC2E4 == 0) {
        BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_PLAYING);
        func_801E5988();
    }
}

MATCH void func_801EEF98(s32 index, s32 category) {
    switch (category & BYTE_MASK) {
        case ITEM_CAT_ITEM:
        default:
            SYS_CopyString(g_TextVariables, g_Items[index & BYTE_MASK].name, 12);
            break;
        case ITEM_CAT_WEAPON:
            SYS_CopyString(g_TextVariables, g_Weapons[index & BYTE_MASK].header.name, 12);
            break;
        case ITEM_CAT_ARMOR:
            SYS_CopyString(g_TextVariables, g_Armors[index & BYTE_MASK].header.name, 12);
            break;
        case ITEM_CAT_ACCESSORY:
            SYS_CopyString(g_TextVariables, g_Accessories[index & BYTE_MASK].header.name, 12);
            break;
    }
}
