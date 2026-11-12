#include "boss013_16.h"

MATCH void func_800C1F24(void) {
    u8* flags;

    func_801D9484();
    SYS_CopyString(*g_TextVariables, g_Characters[D_80181B11].name, 8);
    func_801DE560(2, 0, 0, 45, Message_GetText(0x25U));
    D_800C26E0 = 0;
    Party_LoadMemberSprite(CHAR_ID_NINA_YOUNG, 1);
    g_Task->unk_29               = 4;
    g_BattleCurrentEnemy->script = &D_800C25FC;
    Actor_SelectScript((g_Task->facing + 4) & BYTE_MASK);
    flags = &g_Battle.boss_flags;
    *flags |= 0x40;
}
