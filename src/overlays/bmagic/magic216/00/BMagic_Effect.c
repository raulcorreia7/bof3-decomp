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

INCLUDE_ASM(func_801EECDC);

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
