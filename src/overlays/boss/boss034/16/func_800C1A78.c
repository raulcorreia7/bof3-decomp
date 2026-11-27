#include "boss034_16.h"

MATCH void func_800C1A78(void) {
    Script_AnimStepOnce();
    GFX_ClearRect(832, 256, 192, 256);
    SELF(PartyMember)->unk_18                = SELF(PartyMember)->screen_x.signed_value;
    SELF(PartyMember)->unk_1C                = SELF(PartyMember)->screen_y.signed_value;
    SELF(PartyMember)->unk_0C                = 190;
    SELF(PartyMember)->unk_10                = 104;
    SELF(PartyMember)->screen_x.signed_value = 100;
    SELF(PartyMember)->unk_20                = 0;
    SELF(PartyMember)->screen_y.signed_value = 80;
    SELF(PartyMember)->timer                 = 1;
    SELF(PartyMember)->unk_24 |= 0x88;
    SND_SEPlay(EMI_SE_ID(SND_BANK_ENEMY, 2));
    func_800C23D4(SELF(PartyMember)->unk_09);
    SELF(PartyMember)->unk_03++;
}
