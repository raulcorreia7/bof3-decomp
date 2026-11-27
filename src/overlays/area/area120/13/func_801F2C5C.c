#include "area120_13.h"

MATCH void func_801F2C5C(void) {
    Actor* actor;

    func_801F35B8();
    actor         = SELF(Actor);
    actor->unk_06 = 0;
    actor->unk_32 = 0x78;
    SELF(Actor)->header.mode++;
    SND_SEPlay(EMI_SE_ID(SND_BANK_AREA, 0x01));
}
