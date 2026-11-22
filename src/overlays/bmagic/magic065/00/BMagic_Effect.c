#include "magic065_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/shared/func_801EEC24.h"

#ifdef NON_MATCHING
/* Sets the steal task up from the effect battler, queues the stolen-item effect, then rolls the
 * steal: the drop rate entry scaled by the agility lead. The result message id lands in unk_0A. */
NON_MATCHING void func_801EEC90(void) {
    PartyMember*     work;
    PartyMember*     actor;
    BattleWorkImage* row;
    s32              value;
    s32              scale;
    s32              category;
    u32              slot;
    u16              item;

    TASK(PartyMember)->facing = g_BattleEffectBattler->facing;
    work                      = TASK(PartyMember);
    actor                     = g_BattleEffectBattler;
    work->pos.x.fixed         = actor->pos.x.fixed;
    work->pos.y.fixed         = actor->pos.y.fixed;
    work->param.unk_0B        = 0;
    work->pos.z.fixed         = actor->pos.z.fixed;
    work->unk_09              = 0x1E;
    work->header.mode += 1;
    Battle_SelectActiveBattlerScript(12, 2);
    slot                                             = func_801E590C(1, 0x45);
    D_801EC330[slot & BYTE_MASK].target.party        = TASK(PartyMember);
    row                                              = (BattleWorkImage*)&g_Game.members[g_Battle.active_battler];
    *(BattleWorkImage*)&D_801EC330[slot & BYTE_MASK] = *row;
    D_801EC330[slot & BYTE_MASK].unk_06              = 1;
    D_801EC330[slot & BYTE_MASK].header.mode         = 0;
    D_801EC330[slot & BYTE_MASK].header.step         = 0;
    D_801EC330[slot & BYTE_MASK].step_index          = 0x45;
    TASK(PartyMember)->param.unk_0B++;
    g_BattleEffectBattler->header.flags |= ACTOR_FLAG_HIDDEN;

    value = g_Game.members[g_Battle.active_battler].chr.stats.agility - D_801EB6C8[g_Battle.target_selector - 3].agility;
    scale = 12;
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
    value = D_801EF508[D_801EB6C8[g_Battle.target_selector - 3].rate] * scale;
    if ((rand() & 0xFF) < value) {
        item = D_801EB6C8[g_Battle.target_selector - 3].item;
        if (item != 0) {
            category = item >> 8;
            if (Item_Add(category, item & 0xFF, 1, 0)) {
                TASK(PartyMember)->timer                      = 0x38;
                TASK(PartyMember)->unk_2C.value               = item;
                D_801EB6C8[g_Battle.target_selector - 3].rate = 0;
                D_801EB6C8[g_Battle.target_selector - 3].item = 0;
            } else {
                TASK(PartyMember)->timer = 0x39;
            }
        } else {
            TASK(PartyMember)->timer = 0x3A;
        }
    } else if (D_801EB6C8[g_Battle.target_selector - 3].rate != 0) {
        TASK(PartyMember)->timer = 0x39;
    } else {
        TASK(PartyMember)->timer = 0x3A;
    }
}
#else
INCLUDE_ASM(func_801EEC90);
#endif

MATCH void func_801EF08C(void) {
    u8 counter;

    if (TASK(PartyMember)->param.unk_0B == 0) {
        if (TASK(PartyMember)->unk_09 == 0x1E) {
            Battle_SelectActiveBattlerScript(4, 0);
            BATTLE_ACTIVE_WORK->header.flags &= ~PARTY_MEMBER_FLAG_HANDLER_BUSY;
        }
        counter                   = TASK(PartyMember)->unk_09 - 1;
        TASK(PartyMember)->unk_09 = counter;
        if (!(counter & BYTE_MASK)) {
            TASK(PartyMember)->header.mode += 1;
        }
    }
}

MATCH void func_801EF134(void) {
    u16 item;

    if (D_801EC2E4 == 0) {
        if (TASK(PartyMember)->timer == 56) {
            item = TASK(PartyMember)->unk_2C.value;
            BMagic_SetTextItemName(item & BYTE_MASK, item >> 8);
        }
        func_801DE8C0(1, 0x1E, UI_MessageGetText(TASK(PartyMember)->timer));
        TASK(PartyMember)->header.mode += 1;
    }
}

MATCH void func_801EF1CC(void) {
    u16* battle_flags;

    if (D_801EC2E4 == 0) {
        battle_flags = &g_Battle.flags;
        *battle_flags |= 4;
        Effect_Reset();
    }
}

/* func_801EF20C */
#include "overlays/bmagic/shared/BMagic_DispatchEffectMode.h"

MATCH void func_801EF250(void) {
    Magic065TaskSteps handlers;

    handlers = D_801EEC14;
    SYS_DISPATCH_BYTE(handlers.steps, TASK(PartyMember)->header.step);
    if (TASK(PartyMember)->header.flags != 0) {
        Area_AddGridActor();
    }
}

#include "overlays/bmagic/shared/Effect_SetDuration.h"

MATCH void func_801EF328(void) {
    u8 timer;

    Script_AnimStepOnce();
    timer                     = TASK(PartyMember)->unk_09 - 1;
    TASK(PartyMember)->unk_09 = timer;
    if (timer == 0) {
        Battle_PlayActiveBattlerSE(0, 4);
        TASK(PartyMember)->header.step = TASK(PartyMember)->header.step + 1;
    }
}

MATCH void func_801EF394(void) {
    if (Script_AnimStepOnce() & BYTE_MASK) {
        Battle_MarkDamaged(g_Battle.target_selector);
        BATTLE_ACTIVE_WORK->param.unk_0B -= 1;
        TASK(PartyMember)->header.step += 1;
    }
}

MATCH void func_801EF408(void) {
    Effect_Reset();
}

/* func_801EF428 */
MATCH void BMagic_SetTextItemName(u8 item_id, u8 category) {
    switch (category) {
        case ITEM_CATEGORY_ITEM:
        default:
            SYS_CopyString(g_TextVariables[0], g_Items[item_id].name, ITEM_NAME_LENGTH);
            break;
        case ITEM_CATEGORY_WEAPON:
            SYS_CopyString(g_TextVariables[0], g_Weapons[item_id].header.name, ITEM_NAME_LENGTH);
            break;
        case ITEM_CATEGORY_ARMOR:
            SYS_CopyString(g_TextVariables[0], g_Armors[item_id].header.name, ITEM_NAME_LENGTH);
            break;
        case ITEM_CATEGORY_ACCESSORY:
            SYS_CopyString(g_TextVariables[0], g_Accessories[item_id].header.name, ITEM_NAME_LENGTH);
            break;
    }
}
