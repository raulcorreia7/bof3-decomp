#include "boss013_16.h"

MATCH void func_800C1F24(void) {
    u8* flags;

    func_801D9484();
    SYS_CopyString(*g_TextVariables, g_Characters[D_80181B11].name, 8);
    func_801DE560(2, 0, 0, 0x2D, Resource_GetText(0x25U));
    D_800C26E0 = 0;
    func_801C1254(1, 1);
    g_SpadWork->unk_29           = 4;
    g_BattleCurrentEnemy->script = &D_800C25FC;
    Actor_SelectScript((g_SpadWork->word_08.byte.facing_08 + 4) & 0xFF);
    flags = &g_BattleBossFlags;
    *flags |= 0x40;
}
