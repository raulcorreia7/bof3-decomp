#include "boss034_16.h"

MATCH void func_800C1A78(void) {
    Script_AnimStepOnce();
    GFX_ClearRect(832, 256, 192, 256);
    TASK(PartyMember)->unk_18                = TASK(PartyMember)->screen_x.signed_value;
    TASK(PartyMember)->unk_1C                = TASK(PartyMember)->screen_y.signed_value;
    TASK(PartyMember)->unk_0C                = 190;
    TASK(PartyMember)->unk_10                = 104;
    TASK(PartyMember)->screen_x.signed_value = 100;
    TASK(PartyMember)->unk_20                = 0;
    TASK(PartyMember)->screen_y.signed_value = 80;
    TASK(PartyMember)->timer                 = 1;
    TASK(PartyMember)->unk_24 |= 0x88;
    SND_SEPlay(EMI_SE_ID(SND_BANK_ENEMY, 2));
    func_800C23D4(TASK(PartyMember)->unk_09);
    TASK(PartyMember)->unk_03++;
}
