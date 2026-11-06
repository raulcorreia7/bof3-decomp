#include "magic216_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

MATCH void func_801EEC70(void) {
    PartyBattler* work;
    PartyBattler* actor;
    s32           z;

    g_Task->facing    = D_801EB4E0->facing;
    work              = g_Task;
    actor             = D_801EB4E0;
    work->pos.x.fixed = actor->pos.x.fixed;
    work->pos.y.fixed = actor->pos.y.fixed;
    z                 = actor->pos.z.fixed;
    work->unk_0B      = 0;
    work->pos.z.fixed = z;
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
    switch (category & 0xFF) {
        case ITEM_CAT_ITEM:
        default:
            SYS_CopyString(g_TextVariables, g_Items[index & 0xFF].name, 0xC);
            break;
        case ITEM_CAT_WEAPON:
            SYS_CopyString(g_TextVariables, g_Weapons[index & 0xFF].header.name, 0xC);
            break;
        case ITEM_CAT_ARMOR:
            SYS_CopyString(g_TextVariables, g_Armors[index & 0xFF].header.name, 0xC);
            break;
        case ITEM_CAT_ACCESSORY:
            SYS_CopyString(g_TextVariables, g_Accessories[index & 0xFF].header.name, 0xC);
            break;
    }
}
