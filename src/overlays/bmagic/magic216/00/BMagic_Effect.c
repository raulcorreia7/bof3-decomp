#include "magic216_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/BMagic_RunStep.h"

MATCH void func_801EEC70(void) {
    PartyBattler* work;
    PartyBattler* actor;
    s32           z;

    g_SpadWork->word_08.byte.facing_08 = D_801EB4E0->word_08.byte.facing_08;
    work                               = g_SpadWork;
    actor                              = D_801EB4E0;
    work->coord_x_34.raw               = actor->coord_x_34.raw;
    work->coord_y_38.raw               = actor->coord_y_38.raw;
    z                                  = actor->word_3C.word;
    work->word_08.byte.unk_0B          = 0;
    work->word_3C.word                 = z;
    g_SpadWork->step_01 += 1;
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
            SYS_CopyString(g_TextVariables, g_Items[index & BYTE_MASK].name, 0xC);
            break;
        case ITEM_CAT_WEAPON:
            SYS_CopyString(g_TextVariables, g_Weapons[index & BYTE_MASK].name, 0xC);
            break;
        case ITEM_CAT_ARMOR:
            SYS_CopyString(g_TextVariables, g_Armors[index & BYTE_MASK].name, 0xC);
            break;
        case ITEM_CAT_ACCESSORY:
            SYS_CopyString(g_TextVariables, g_Accessories[index & BYTE_MASK].name, 0xC);
            break;
    }
}
