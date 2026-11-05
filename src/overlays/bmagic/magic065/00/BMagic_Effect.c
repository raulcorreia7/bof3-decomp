#include "magic065_00.h"

#if BOF3_USE_ASM
__asm__(".include \"include/match/macro.inc\"\n");
#endif

#include "overlays/bmagic/func_801EEC24.h"

INCLUDE_ASM(func_801EEC90);

MATCH void func_801EF08C(void) {
    u8 counter;

    if (g_SpadWork->word_08.byte.unk_0B == 0) {
        if (g_SpadWork->word_08.byte.unk_09 == 0x1E) {
            func_800AEF98(4, 0);
            BATTLE_ACTIVE_WORK->flags_00 &= 0xBF;
        }
        counter                         = g_SpadWork->word_08.byte.unk_09 - 1;
        g_SpadWork->word_08.byte.unk_09 = counter;
        if (!(counter & 0xFF)) {
            g_SpadWork->step_01 += 1;
        }
    }
}

MATCH void func_801EF134(void) {
    u16 item;

    if (D_801EC2E4 == 0) {
        if (g_SpadWork->word_08.byte.timer_0A == 0x38) {
            item = g_SpadWork->unk_2C.half;
            BMagic_SetTextItemName(item & 0xFF, item >> 8);
        }
        func_801DE8C0(1, 0x1E, Resource_GetText((u32)g_SpadWork->word_08.byte.timer_0A));
        g_SpadWork->step_01 += 1;
    }
}

INCLUDE_ASM(func_801EF1CC);

MATCH void func_801EF20C(void) {
    SYS_DISPATCH_BYTE(g_BMagicEffectFuncs, ((u8*)g_SpadWork)[1]);
}

INCLUDE_ASM(func_801EF250);

#include "overlays/bmagic/Effect_ReloadTimerAndStep.h"

MATCH void func_801EF328(void) {
    u8 timer;

    func_8014DAEC();
    timer                           = g_SpadWork->word_08.byte.unk_09 - 1;
    g_SpadWork->word_08.byte.unk_09 = timer;
    if (timer == 0) {
        func_800AFC98(0, 4);
        g_SpadWork->unk_02 = g_SpadWork->unk_02 + 1;
    }
}

MATCH void func_801EF394(void) {
    if (func_8014DAEC() & 0xFF) {
        func_800A9820(g_BattleTargetSelector);
        BATTLE_ACTIVE_WORK->word_08.byte.unk_0B -= 1;
        g_SpadWork->unk_02 += 1;
    }
}

MATCH void func_801EF408(void) {
    func_801E5988();
}

/* func_801EF428 */
MATCH void BMagic_SetTextItemName(u8 item_id, u8 category) {
    switch (category) {
        case ITEM_CAT_ITEM:
        default:
            SYS_CopyString(g_TextVariables[0], g_Items[item_id].name, ITEM_NAME_LENGTH);
            break;
        case ITEM_CAT_WEAPON:
            SYS_CopyString(g_TextVariables[0], g_Weapons[item_id].name, ITEM_NAME_LENGTH);
            break;
        case ITEM_CAT_ARMOR:
            SYS_CopyString(g_TextVariables[0], g_Armors[item_id].name, ITEM_NAME_LENGTH);
            break;
        case ITEM_CAT_ACCESSORY:
            SYS_CopyString(g_TextVariables[0], g_Accessories[item_id].name, ITEM_NAME_LENGTH);
            break;
    }
}
